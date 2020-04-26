#   @author   Adam Golya
#   @brief    Python file for STM32 functional tester
#   #######################################


import time, os, sys, serial
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from decimal import Decimal
from functools import partial

import functional_test_pb2
import sequence
import config
import array
from importlib import import_module
from link_layer import link_layer

ui_path = os.path.dirname(os.path.abspath(__file__))
Ui_MainWindow  = uic.loadUiType(os.path.join(ui_path, "stm_gui.ui"))[0]


class MyWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    # Initialization
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)
        # Signals connected to slots
        self.connect_button.clicked.connect(self.connect)
        self.cmd_button.clicked.connect(self.send_command)
        self.close_button.clicked.connect(self.close_port)
        self.cmd_box.activated[str].connect(self.on_changed_cmd_box)
        self.move_up_button.clicked.connect(self.move_up)
        self.move_down_button.clicked.connect(self.move_down)
        self.delete_row_button.clicked.connect(self.delete_row)
        self.sequence_add_button.clicked.connect(self.add_seq)
        self.delete_seq_button.clicked.connect(self.delete_seq)
        self.save_seq_button.clicked.connect(self.save_seq)
        self.load_seq_button.clicked.connect(self.load_seq)
        self.send_seq_button.clicked.connect(self.send_seq)
        self.clear_button.clicked.connect(self.clear_response)
        self.cfg_browse_button.clicked.connect(self.browse_cfg)
        self.cfg_load_button.clicked.connect(self.load_cfg)
        self.cfg_checkbox.stateChanged.connect(self.cfg_checkbox_state_changed)
        self.scrollArea.verticalScrollBar().rangeChanged.connect(self.resizeScroll)
        # Fill command combo box
        self.fill_cmd_box()
        # Flags: avoid command reselection
        self.I2C_active = False
        self.MENU_active = False
        self.SPI_active = False
        self.USART_active = False
        self.GPIO_active = False
        self.AnalogRead_active = False
        self.AnalogWrite_active = False
        # Validators: in forms of regular expressions
        self.byteValidator = QRegExpValidator(QRegExp("0x[0-9A-Fa-f]{2}"))                      # Byte validator for input fields (0xhh format): i2c address, register; spi command
        self.wordValidator = QRegExpValidator(QRegExp("0x[0-9A-Fa-f]{2,8}"))                    # Word validator for usart command field
        self.byteSizeValidatorI2CWrite  = QRegExpValidator(QRegExp("[1-2]"))                    # 1-digit decimal validator for I2C write size
        self.byteSizeValidatorI2CRead  = QRegExpValidator(QRegExp("[1-4]"))                     # 1-digit decimal validator for I2C read size
        self.byteSizeValidatorSPI  = QRegExpValidator(QRegExp("[0-2]"))                         # 1-digit decimal validator for SPI write size
        self.slaveSizeValidatorSPI  = QRegExpValidator(QRegExp("[0-4]"))                        # 1-digit decimal validator for SPI slave response size
        self.dummyValidator  = QRegExpValidator(QRegExp("[0-9]|(1[0-5])"))                          # 2-digit decimal validator for SPI dummy clocks
        self.pwmTimeValidator = QRegExpValidator(QRegExp("[0-9]{1,5}"))                         # Max 5-digit decimal validator for PWM time dependency field
        self.baudValidator  = QRegExpValidator(QRegExp("[0-9]{4,7}"))                           # Max 7-digit decimal validator for USART baudrate
        self.dutyValidator = QRegExpValidator(QRegExp("0|100|[1-9][0-9]?"))                     # Max. 3-digit validator for PWM duty cycle [0-100]
        self.freqValidator = QRegExpValidator(QRegExp("0|0\.[0-9]|[1-9][0-9]{0,2}\.?[0-9]"))    # Max. 4-digit validator for freqency [0-1000], limits checked
        self.valueValidator = QRegExpValidator(QRegExp("0x[0-9A-Fa-f]{2,4}"))                   # Max. 2 bytes validator for I2C/SPI write value
        # Miscellaneous
        self.test_list = []                                     # List filled with test objects
        self.helpLabel_list = []
        self.scroll_layout.addStretch()                         # Add stretch for scroll area
        self.container_widget.setLayout(self.scroll_layout)     # Set layout for scrollArea container widget
        self.cfg_browse_button.setEnabled(False)
        self.cfg_load_button.setEnabled(False)
        self.cfg_file_path.setEnabled(False)
        self.use_config_file = False
        self.LL = link_layer()
        self.ser = serial.Serial()
        self.close_button.setEnabled(False)
        # Create own font style
        self.italicFont = QFont()
        self.italicFont.setItalic(True)

    # Move up row (Move up QListWidgetItem)
    def move_up(self):
        currentRow = self.sequence_list.currentRow()
        if currentRow > 0:
            # Move test object forward in test list
            sequence.move_up_test_in_sequence(self.test_list, currentRow)
            # Move up item in list
            currentItem = self.sequence_list.takeItem(currentRow)
            self.sequence_list.insertItem(currentRow - 1, currentItem)
            self.sequence_list.setCurrentRow(currentRow - 1)
            testMovedUpLabel = QLabel("Test moved upward.")
            testMovedUpLabel.setFont(self.italicFont)
            self.scroll_layout.addWidget(testMovedUpLabel)
#            print(self.test_list[0].cmdType)


    # Move down row (Move down QListWidgetItem)
    def move_down(self):
        currentRow = self.sequence_list.currentRow()
        if currentRow < (self.sequence_list.count()-1):
            # Move test object backward in test list
            sequence.move_down_test_in_sequence(self.test_list, currentRow)
            # Move down item in list
            currentItem = self.sequence_list.takeItem(currentRow)
            self.sequence_list.insertItem(currentRow + 1, currentItem)
            self.sequence_list.setCurrentRow(currentRow + 1)
            testMovedDownLabel = QLabel("Test moved downward.")
            testMovedDownLabel.setFont(self.italicFont)
            self.scroll_layout.addWidget(testMovedDownLabel)
#            print(self.test_list[0].cmdType)


    # Delete row
    def delete_row(self):
        try:
            currentRow = self.sequence_list.currentRow()        # Get index of current row
            self.sequence_list.takeItem(currentRow)             # Delete current row (listWidgetitem)
            sequence.delete_test_object_from_test_list(self.test_list, currentRow)    # Delete test from test list
            testObjectDeletedLabel = QLabel("Test removed from sequence.")
            testObjectDeletedLabel.setFont(self.italicFont)
            self.scroll_layout.addWidget(testObjectDeletedLabel)
        except:
            return

#        print("len seq:", len(self.sequence_list))
#        print("len test:", len(self.test_list))
#        print("")


    # Add command to test list and sequence list
    def add_seq(self, rowObject):
        if self.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.Show_empty:
            return
        test_object = sequence.make_test_object_from_options(self)                                      # Make test object from selected options
        sequence.add_test_object_to_test_list(test_object, self.test_list)                              # Add test object to test list
        command_to_add = sequence.make_string_from_test_object(self.test_list[len(self.test_list)-1])   # Make string from test object
        self.sequence_list.insertItem(self.sequence_list.count(),command_to_add)                        # Add string to sequence list
        testObjectAddedLabel = QLabel("Test added to sequence.")
        testObjectAddedLabel.setFont(self.italicFont)
        self.scroll_layout.addWidget(testObjectAddedLabel)
#        print("len seq:", len(self.sequence_list))
#        print("len test:", len(self.test_list))


   # Delete the whole sequence
    def delete_seq(self):
        self.sequence_list.clear()                  # Delete sequence list
        sequence.delete_test_list(self.test_list)        # Delete test list
        sequenceDeletedLabel = QLabel("Sequence deleted.")
        sequenceDeletedLabel.setFont(self.italicFont)
        self.scroll_layout.addWidget(sequenceDeletedLabel)
#        print("len seq:", len(self.sequence_list))
#        print("len test:", len(self.test_list))


    # Save sequence: Make a data_line list (string list from the lines) from sequence_list, and save it to a .txt file
    def save_seq(self):
        data_line = []
        for i in range (self.sequence_list.count()):
          self.sequence_list.setCurrentRow(i)
          line = self.sequence_list.currentItem().text()
          data_line.append(line)

        dialog = QFileDialog.getSaveFileName(self, "Save config to file", ".", "Text file (*.txt)")
        if not dialog[0]: return    # If no file name was given, then return
        file = open(dialog[0], 'w')
        for i in range(len(data_line)):
           file.write(data_line[i])
           file.write("\n")
        file.close()
        sequenceSavedLabel = QLabel("Sequence saved.")
        sequenceSavedLabel.setFont(self.italicFont)
        self.scroll_layout.addWidget(sequenceSavedLabel)

    # Load sequence: open text file, and read line-by-line
    def load_seq(self):
        dialog = QFileDialog(self)
        dialog.setFileMode(QFileDialog.ExistingFile)
        dialog.setNameFilters(["Text files (*.txt)"])
        filenames = []
        if dialog.exec_():
            filenames = dialog.selectedFiles()
            file = open(filenames[0], 'r')
            with file:
                data_line = file.readlines()
                for i in range(len(data_line)):
                    data_line[i] = data_line[i].rstrip()    # Remove trailing characters: \n
                    print(data_line[i])
                    self.sequence_list.insertItem(self.sequence_list.count(),data_line[i])      # Add string line to sequence
                    test_object = sequence.make_test_object_from_string(data_line[i])           # Make object from string line
                    sequence.add_test_object_to_test_list(test_object, self.test_list)          # Add object to test list
                file.close()
                sequenceLoadedLabel = QLabel("Sequence loaded.")
                sequenceLoadedLabel.setFont(self.italicFont)
                self.scroll_layout.addWidget(sequenceLoadedLabel)


    # Send sequence via serial port
    def send_seq(self):
        if not self.test_list:
            return
        separationLabelStart = QLabel("------------------------------------------------------")
        sequenceStartedLabel = QLabel("Sequence started.")
        sequenceStartedLabel.setFont(self.italicFont)
        self.scroll_layout.addWidget(separationLabelStart)
        self.scroll_layout.addWidget(sequenceStartedLabel)
        for i in range(len(self.test_list)):
            pb = sequence.make_protobuf_command_from_test_object(self.test_list[i])    # Make protobuf command
            self.LL.link_frame_data(pb)            # Frame protobuf data
            print("TxBuffer: ",self.LL.tx_buffer)
            try:
                self.ser.write(self.LL.tx_buffer)
                command_send_success = 'Command sent'
                read_response = self.read_data_depending_on_cmd_type(self.test_list[i])
            except serial.serialutil.SerialException:
                if self.ser.is_open:
                    command_send_success = 'Error while sending command'
                else:
                    command_send_success = 'Port is not open'
                # If serial write is unsuccessful, then display it on scrollArea and return immediately.
                successLabel = QLabel(command_send_success)
                self.scroll_layout.addWidget(successLabel)
                break

            # Print current command
            self.sequence_list.setCurrentRow(i)
            currentCommand = self.sequence_list.currentItem().text()
            currentCommandLabel = QLabel(currentCommand)
            currentCommandLabel.setFont(self.italicFont)             # Set own font style for command print

            # Print serial read response
            response = ">>  " + read_response
            responseLabel = QLabel(response)

            # Add widgets (labels) to scrollArea
            self.scroll_layout.addWidget(currentCommandLabel)
            self.scroll_layout.addWidget(responseLabel)
            last_widget = self.scroll_layout.itemAt(self.scroll_layout.count()-1).widget()
            QtCore.QTimer.singleShot(0, partial(self.scrollArea.ensureWidgetVisible, last_widget))

        separationLabelFinish = QLabel("------------------------------------------------------")
        sequenceFinishedLabel = QLabel("Sequence finished.")
        sequenceFinishedLabel.setFont(self.italicFont)
        self.scroll_layout.addWidget(sequenceFinishedLabel)
        self.scroll_layout.addWidget(separationLabelFinish)

    # Clear response (scrollArea)
    def clear_response(self):
        self.delete_all_child_widget(self.scroll_layout)    # delete children widgets
        self.scroll_layout.addStretch()                     # Add stretch for scroll area

    # Browse and get path of CubeMX config file (.ioc)
    def browse_cfg(self):
        dialog = QFileDialog(self)
        dialog.setFileMode(QFileDialog.ExistingFile)
        dialog.setNameFilters(["CubeMX files (*.ioc)"])
        filenames = []
        if dialog.exec_():
            filenames = dialog.selectedFiles()
            self.cfg_file_path.setText(filenames[0])

    # Load CubeMX config file: open and analyze file, then reload current command options view
    def load_cfg(self):
        path = self.cfg_file_path.text()
        success = config.process_config_file(path)
        if(success == True):
            self.use_config_file = True
            self.on_changed_cmd_box()           # Reload current view, call function explicitly
            deviceInfo = "Config loaded. MCU Family: " + str(config.dict_mcu_info["Family"])
            deviceInfoLabel = QLabel(deviceInfo)
            self.scroll_layout.addWidget(deviceInfoLabel)
        else:
            self.use_config_file = False
            errorLabel = QLabel("No such file or directory")
            self.scroll_layout.addWidget(errorLabel)

    # Check config checkbox state
    def cfg_checkbox_state_changed(self):
        if self.cfg_checkbox.isChecked():
            self.cfg_browse_button.setEnabled(True)
            self.cfg_load_button.setEnabled(True)
            self.cfg_file_path.setEnabled(True)
        else:
            self.cfg_browse_button.setEnabled(False)
            self.cfg_load_button.setEnabled(False)
            self.cfg_file_path.setEnabled(False)
            self.use_config_file = False
            self.on_changed_cmd_box()
            deviceInfoLabel = QLabel("Config removed.")
            self.scroll_layout.addWidget(deviceInfoLabel)

    # Check pwm time checkbox state
    def pwm_time_checkbox_state_changed(self):
        if self.pwm_time_checkbox.isChecked():
            self.pwm_time_select.setEnabled(True)
        else:
            self.pwm_time_select.setEnabled(False)


    # Fill combobox with commands
    def fill_cmd_box(self):
        self.cmd_box.addItem("Click to select...",functional_test_pb2.CommandTypeEnum.Show_empty)
        self.cmd_box.addItem("I2C test",functional_test_pb2.CommandTypeEnum.I2C_test)
        self.cmd_box.addItem("SPI test",functional_test_pb2.CommandTypeEnum.SPI_test)
        self.cmd_box.addItem("USART test", functional_test_pb2.USART_test)
        self.cmd_box.addItem("GPIO digital",functional_test_pb2.CommandTypeEnum.GPIO_digital)
        self.cmd_box.addItem("Analog read",functional_test_pb2.CommandTypeEnum.Analog_read)
        self.cmd_box.addItem("PWM",functional_test_pb2.CommandTypeEnum.Analog_write)

    # Called whenever GPIO direction is changed in GPIO digital command
    def on_changed_gpio_dir(self):
        if self.gpio_direction_select.currentData() == functional_test_pb2.gpioDirection.GPIO_INPUT:
            self.gpio_state_select.setEnabled(False)
            self.gpio_state_select.addItem(list(sequence.dict_gpio_state.keys())[2],list(sequence.dict_gpio_state.values())[2]) # Add and set N/A option
            self.gpio_state_select.setCurrentIndex(2)
        else:
            self.gpio_state_select.removeItem(2)        # Remove N/A option
            self.gpio_state_select.setEnabled(True)


    # Called whenever a command is selected
    def on_changed_cmd_box(self):
#        print("CmdType:",self.cmd_box.currentData())
        self.delete_all_child_widget(self.options_layout)
        self.show_data_depending_on_cmd_type(self.cmd_box.currentData())
        self.show()


    # Called when I2C clock speed option is changed: add/remove widgets and set parent
    def on_changed_i2c_speed_mode(self):
        if self.i2c_speed_mode_select.currentData() == list(sequence.dict_i2c_speedmode.values())[0]:
            self.i2c_clock_speed_select.setText("100000")           # Set default value to 100000 in case standard mode selected
            self.options_layout.removeWidget(self.i2c_duty_cycle_label)
            self.options_layout.removeWidget(self.i2c_duty_cycle_select)
            self.i2c_duty_cycle_label.setParent(None)
            self.i2c_duty_cycle_select.setParent(None)
        else:
            self.i2c_clock_speed_select.setText("400000")           # Set default value to 400000 in case standard mode selected
            self.options_layout.addWidget(self.i2c_duty_cycle_label,9,0)
            self.options_layout.addWidget(self.i2c_duty_cycle_select,9,2)

    def on_changed_i2c_rw(self):
        if self.i2c_rw_select.currentData() == list(sequence.dict_i2c_rw.values())[0]:
            self.i2c_write_value_select.setEnabled(True)
            self.i2c_write_value_select.setText("")
            self.i2c_size_select.setPlaceholderText("1..2")
            self.i2c_size_select.setValidator(self.byteSizeValidatorI2CWrite)
        else:
            self.i2c_write_value_select.setEnabled(False)
            self.i2c_write_value_select.setText("0x00")
            self.i2c_size_select.setPlaceholderText("1..4")
            self.i2c_size_select.setValidator(self.byteSizeValidatorI2CRead)


    # Called when SPI frame format option is changed: add/remove widgets and set parent
    def on_changed_spi_frame_format(self):
        if self.spi_frame_format_select.currentData() == list(sequence.dict_spi_frame_format.values())[0]:
            self.options_layout.addWidget(self.spi_first_bit_label,10,0)
            self.options_layout.addWidget(self.spi_first_bit_select,10,2)
            self.options_layout.addWidget(self.spi_clockmode_label,11,0)
            self.options_layout.addWidget(self.spi_clockmode_select,11,2)
        else:
            self.options_layout.removeWidget(self.spi_first_bit_label)
            self.options_layout.removeWidget(self.spi_first_bit_select)
            self.options_layout.removeWidget(self.spi_clockmode_label)
            self.options_layout.removeWidget(self.spi_clockmode_select)
            self.spi_first_bit_label.setParent(None)
            self.spi_first_bit_select.setParent(None)
            self.spi_clockmode_label.setParent(None)
            self.spi_clockmode_select.setParent(None)


    # Called when SPI hardware NSS option is changed: enables/disable 'TI' frame format option
    def on_changed_spi_hardware_nss(self):
        if self.spi_hardware_nss_select.currentData() == list(sequence.dict_spi_hardware_nss.values())[0]:  # Disable 'TI' if hardware NSS is disabled
            self.spi_frame_format_select.model().item(1).setEnabled(False)
            self.spi_frame_format_select.setCurrentIndex(0)     # Set frame format to 'Motorola'
            self.on_changed_spi_frame_format()                  # Call function explicitly to show special options
        else:
            self.spi_frame_format_select.model().item(1).setEnabled(True)

    # Called when SPI operating mode option is changed: enables/disable slave response (bytes) field
    def on_changed_spi_opmode(self):
        if self.spi_operating_mode_select.currentData() == list(sequence.dict_spi_operating_mode.values())[0]:  # Full-duplex
            self.spi_slave_response_select.setEnabled(True)
            self.spi_slave_response_select.setText("")
            self.spi_write_value_select.setEnabled(True)
            self.spi_write_value_select.setText("")
            self.spi_write_size_select.setEnabled(True)
            self.spi_write_size_select.setText("")
            self.spi_command_select.setEnabled(True)
            self.spi_command_select.setText("")
            self.spi_dummyclocks_select.setEnabled(True)
            self.spi_dummyclocks_select.setText("")

        elif self.spi_operating_mode_select.currentData() == list(sequence.dict_spi_operating_mode.values())[1]:  # Transmit (4Wire)
            self.spi_slave_response_select.setEnabled(False)
            self.spi_slave_response_select.setText("0")
            self.spi_write_value_select.setEnabled(True)
            self.spi_write_value_select.setText("")
            self.spi_write_size_select.setEnabled(True)
            self.spi_write_size_select.setText("")
            self.spi_command_select.setEnabled(True)
            self.spi_command_select.setText("")
            self.spi_dummyclocks_select.setEnabled(False)
            self.spi_dummyclocks_select.setText("0")

        elif self.spi_operating_mode_select.currentData() == list(sequence.dict_spi_operating_mode.values())[2]: # Receive (4Wire)
            self.spi_slave_response_select.setEnabled(True)
            self.spi_slave_response_select.setText("")
            self.spi_write_value_select.setEnabled(False)
            self.spi_write_value_select.setText("0x00")
            self.spi_write_size_select.setEnabled(False)
            self.spi_write_size_select.setText("0")
            self.spi_command_select.setEnabled(False)
            self.spi_command_select.setText("0x00")
            self.spi_dummyclocks_select.setEnabled(False)
            self.spi_dummyclocks_select.setText("0")

        elif self.spi_operating_mode_select.currentData() == list(sequence.dict_spi_operating_mode.values())[3]: # Half Duplex Transmit
            self.spi_slave_response_select.setEnabled(False)
            self.spi_slave_response_select.setText("0")
            self.spi_write_value_select.setEnabled(True)
            self.spi_write_value_select.setText("")
            self.spi_write_size_select.setEnabled(True)
            self.spi_write_size_select.setText("")
            self.spi_command_select.setEnabled(True)
            self.spi_command_select.setText("")
            self.spi_dummyclocks_select.setEnabled(False)
            self.spi_dummyclocks_select.setText("0")

        elif self.spi_operating_mode_select.currentData() == list(sequence.dict_spi_operating_mode.values())[4]: # Receive (4Wire)
            self.spi_slave_response_select.setEnabled(True)
            self.spi_slave_response_select.setText("")
            self.spi_write_value_select.setEnabled(False)
            self.spi_write_value_select.setText("0x00")
            self.spi_write_size_select.setEnabled(False)
            self.spi_write_size_select.setText("0")
            self.spi_command_select.setEnabled(False)
            self.spi_command_select.setText("0x00")
            self.spi_dummyclocks_select.setEnabled(False)
            self.spi_dummyclocks_select.setText("0")


    # Called when USART mode setting is changed
    def on_changed_usart_mode(self):
        # If 'Asynchronous' mode is selected: remove clock settings if necessary, add HW Flow Control settings
        if self.usart_mode_select.currentData() == list(sequence.dict_usart_mode.values())[0]:
            if self.options_layout.count() > 7:         # No remove is necessary at first call
                self.options_layout.removeWidget(self.usart_clock_polarity_label)
                self.options_layout.removeWidget(self.usart_clock_phase_label)
                self.options_layout.removeWidget(self.usart_clock_last_bit_label)
                self.options_layout.removeWidget(self.usart_clock_polarity_select)
                self.options_layout.removeWidget(self.usart_clock_phase_select)
                self.options_layout.removeWidget(self.usart_clock_last_bit_select)
                self.usart_clock_polarity_label.setParent(None)
                self.usart_clock_phase_label.setParent(None)
                self.usart_clock_last_bit_label.setParent(None)
                self.usart_clock_polarity_select.setParent(None)
                self.usart_clock_phase_select.setParent(None)
                self.usart_clock_last_bit_select.setParent(None)

            self.options_layout.addWidget(self.usart_hw_flow_control_label,8,0)
            self.options_layout.addWidget(self.usart_hw_flow_control_select,8,2)
        # If 'Synchronous' mode is selected: remove HW flow control settings if necessary, add clock settings
        else:
            self.options_layout.removeWidget(self.usart_hw_flow_control_label)
            self.options_layout.removeWidget(self.usart_hw_flow_control_select)
            self.usart_hw_flow_control_label.setParent(None)
            self.usart_hw_flow_control_select.setParent(None)
            self.options_layout.addWidget(self.usart_clock_polarity_label,8,0)
            self.options_layout.addWidget(self.usart_clock_phase_label,9,0)
            self.options_layout.addWidget(self.usart_clock_last_bit_label,10,0)
            self.options_layout.addWidget(self.usart_clock_polarity_select,8,2)
            self.options_layout.addWidget(self.usart_clock_phase_select,9,2)
            self.options_layout.addWidget(self.usart_clock_last_bit_select,10,2)

    def on_changed_usart_direction(self):
        if self.usart_direction_select.currentData() == list(sequence.dict_usart_direction.values())[0]: # If 'TX only' is selected
            self.usart_command_select.setEnabled(True)
            self.usart_command_select.setText("")
        elif self.usart_direction_select.currentData() == list(sequence.dict_usart_direction.values())[1]: # If 'RX only' is selected
            self.usart_command_select.setEnabled(False)
            self.usart_command_select.setText("0x00000000")
        else:
            self.usart_command_select.setEnabled(True)
            self.usart_command_select.setText("")


    def on_changed_adc_channel(self):
        pin = sequence.select_pin_for_adc_channel(self.adc_channel_select.currentData())
        self.adc_pin_select.setText(pin)



    # Show data depending on the command type selected
    def show_data_depending_on_cmd_type(self,cmdType):
        self.spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding) # Row Spacer if needed
        self.options_layout.setColumnMinimumWidth(0,80)

        if cmdType == functional_test_pb2.CommandTypeEnum.Show_empty:
            if self.MENU_active == False:
                self.MENU_active = True


        elif cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
            if self.I2C_active == False:
                self.I2C_active = True
                self.i2c_bus_label = QLabel("Bus", self)
                self.i2c_rw_label = QLabel("R/W", self)
                self.i2c_addr_label = QLabel("Address", self)
                self.i2c_reg_label = QLabel("Register", self)
                self.i2c_reg_size_label = QLabel("Reg. size (bytes)", self)
                self.i2c_write_value_label = QLabel("Write value", self)
                self.i2c_size_label = QLabel("Size (bytes)", self)
                self.i2c_speed_mode_label = QLabel("Speed mode",self)
                self.i2c_clock_speed_label = QLabel("Clock speed",self)
                self.i2c_duty_cycle_label = QLabel("Duty cycle", self)

                self.i2c_bus_select = QComboBox(self)
                self.i2c_rw_select = QComboBox(self)
                self.i2c_addr_select = QLineEdit(self)
                self.i2c_reg_select = QLineEdit(self)
                self.i2c_reg_size_select = QLineEdit(self)
                self.i2c_write_value_select = QLineEdit(self)
                self.i2c_size_select = QLineEdit(self)
                self.i2c_speed_mode_select = QComboBox(self)
                self.i2c_clock_speed_select = QLineEdit(self)
                self.i2c_duty_cycle_select = QComboBox(self)


                # Fill I2C bus combobox
                if self.use_config_file == True:
                    for i in range(len(config.dict_available_i2c_buses)):
                        self.i2c_bus_select.addItem(list(config.dict_available_i2c_buses.keys())[i],list(config.dict_available_i2c_buses.values())[i] )
                else:
                    for i in range(len(sequence.dict_i2c_bus)):
                        self.i2c_bus_select.addItem(list(sequence.dict_i2c_bus.keys())[i],list(sequence.dict_i2c_bus.values())[i] )

                # Fill I2C direction combobox
                self.i2c_rw_select.addItem(list(sequence.dict_i2c_rw.keys())[0],list(sequence.dict_i2c_rw.values())[0])
                self.i2c_rw_select.addItem(list(sequence.dict_i2c_rw.keys())[1],list(sequence.dict_i2c_rw.values())[1])

                # Fill I2C speed mode combobox
                self.i2c_speed_mode_select.addItem(list(sequence.dict_i2c_speedmode.keys())[0],list(sequence.dict_i2c_speedmode.values())[0])
                self.i2c_speed_mode_select.addItem(list(sequence.dict_i2c_speedmode.keys())[1],list(sequence.dict_i2c_speedmode.values())[1])

                # Fill I2C fast mode duty cycle combobox
                self.i2c_duty_cycle_select.addItem(list(sequence.dict_i2c_duty_cycle.keys())[0],list(sequence.dict_i2c_duty_cycle.values())[0])
                self.i2c_duty_cycle_select.addItem(list(sequence.dict_i2c_duty_cycle.keys())[1],list(sequence.dict_i2c_duty_cycle.values())[1])

                # Set validators and placeholders for input fields
                self.i2c_addr_select.setValidator(self.byteValidator)
                self.i2c_addr_select.setPlaceholderText("0x00")

                self.i2c_reg_select.setValidator(self.valueValidator)
                self.i2c_reg_select.setPlaceholderText("0x00..0xFFFF")

                self.i2c_write_value_select.setValidator(self.valueValidator)
                self.i2c_write_value_select.setPlaceholderText("0x00..0xFFFF")

                self.i2c_reg_size_select.setPlaceholderText("1..2")
                self.i2c_reg_size_select.setValidator(self.byteSizeValidatorI2CWrite)


                # Connect signals and call functions explicitly
                self.i2c_speed_mode_select.activated[str].connect(self.on_changed_i2c_speed_mode)
                self.i2c_rw_select.activated[str].connect(self.on_changed_i2c_rw)
                self.on_changed_i2c_speed_mode()
                self.on_changed_i2c_rw()

                # Add widgets to layout
                self.options_layout.addWidget(self.i2c_bus_label,0,0)
                self.options_layout.addWidget(self.i2c_rw_label,1,0)
                self.options_layout.addWidget(self.i2c_addr_label,2,0)
                self.options_layout.addWidget(self.i2c_reg_label,3,0)
                self.options_layout.addWidget(self.i2c_reg_size_label,4,0)
                self.options_layout.addWidget(self.i2c_write_value_label,5,0)
                self.options_layout.addWidget(self.i2c_size_label,6,0)
                self.options_layout.addWidget(self.i2c_speed_mode_label,7,0)
                self.options_layout.addWidget(self.i2c_clock_speed_label,8,0)

                self.options_layout.addWidget(self.i2c_bus_select,0,2)
                self.options_layout.addWidget(self.i2c_rw_select,1,2)
                self.options_layout.addWidget(self.i2c_addr_select,2,2)
                self.options_layout.addWidget(self.i2c_reg_select,3,2)
                self.options_layout.addWidget(self.i2c_reg_size_select,4,2)
                self.options_layout.addWidget(self.i2c_write_value_select,5,2)
                self.options_layout.addWidget(self.i2c_size_select,6,2)
                self.options_layout.addWidget(self.i2c_speed_mode_select,7,2)
                self.options_layout.addWidget(self.i2c_clock_speed_select,8,2)

                # Layout settings
                self.options_layout.addItem(self.spacerItem,10,0)
                self.options_layout.setColumnMinimumWidth(1,30)

        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            if self.SPI_active == False:
                self.SPI_active = True
                self.spi_operating_mode_label = QLabel("SPI operating mode", self)
                self.spi_bus_label = QLabel("Bus", self)
                self.spi_command_label = QLabel("Command", self)
                self.spi_dummyclocks_label = QLabel("Dummy clocks (bytes)", self)
                self.spi_write_value_label = QLabel("Write value", self)
                self.spi_write_size_label = QLabel("Write size (bytes)", self)
                self.spi_slave_response_label = QLabel("Slave response (bytes)", self)
                self.spi_hardware_nss_label = QLabel("Hardware NSS",self)
                self.spi_frame_format_label = QLabel("Frame format", self)
                self.spi_data_size_label = QLabel("Data size", self)
                self.spi_first_bit_label = QLabel("First bit", self)
                self.spi_clockmode_label = QLabel("Clock mode", self)

                self.spi_operating_mode_select = QComboBox(self)
                self.spi_bus_select = QComboBox(self)
                self.spi_command_select = QLineEdit(self)
                self.spi_dummyclocks_select = QLineEdit(self)
                self.spi_write_value_select = QLineEdit(self)
                self.spi_write_size_select = QLineEdit(self)
                self.spi_slave_response_select = QLineEdit(self)
                self.spi_hardware_nss_select = QComboBox(self)
                self.spi_frame_format_select = QComboBox(self)
                self.spi_data_size_select = QComboBox(self)
                self.spi_first_bit_select = QComboBox(self)
                self.spi_clockmode_select = QComboBox(self)

                # Set tooltip for clock mode
                self.spi_clockmode_select.setToolTip('Mode 0: CPOL=0 CPHA=0\nMode 1: CPOL=0 CPHA=1\nMode 2: CPOL=1 CPHA=0\nMode 3: CPOL=1 CPHA=1')

                # Fill SPI bus combobox
                if self.use_config_file == True:
                    for i in range(len(config.dict_available_spi_buses)):
                        self.spi_bus_select.addItem(list(config.dict_available_spi_buses.keys())[i],list(config.dict_available_spi_buses.values())[i] )
                else:
                    for i in range(len(sequence.dict_spi_bus)):
                        self.spi_bus_select.addItem(list(sequence.dict_spi_bus.keys())[i],list(sequence.dict_spi_bus.values())[i] )


                # Set placeholders and validators for input field
                self.spi_command_select.setValidator(self.byteValidator)
                self.spi_command_select.setPlaceholderText("0xFF")

                self.spi_dummyclocks_select.setValidator(self.dummyValidator)
                self.spi_dummyclocks_select.setPlaceholderText("0..15")

                self.spi_write_value_select.setValidator(self.valueValidator)
                self.spi_write_value_select.setPlaceholderText("0x00..0xFFFF")

                self.spi_write_size_select.setValidator(self.byteSizeValidatorSPI)
                self.spi_write_size_select.setPlaceholderText("0..2")

                self.spi_slave_response_select.setValidator(self.slaveSizeValidatorSPI)
                self.spi_slave_response_select.setPlaceholderText("0..4")


                # Fill SPI operating mode combobox
                for i in range(len(sequence.dict_spi_operating_mode)):
                    self.spi_operating_mode_select.addItem(list(sequence.dict_spi_operating_mode.keys())[i],list(sequence.dict_spi_operating_mode.values())[i] )

                # Fill SPI hardware NSS combobox
                for i in range(len(sequence.dict_spi_hardware_nss)):
                    self.spi_hardware_nss_select.addItem(list(sequence.dict_spi_hardware_nss.keys())[i],list(sequence.dict_spi_hardware_nss.values())[i] )

                # Fill SPI frame format combobox
                for i in range(len(sequence.dict_spi_frame_format)):
                    self.spi_frame_format_select.addItem(list(sequence.dict_spi_frame_format.keys())[i],list(sequence.dict_spi_frame_format.values())[i] )

                # Fill SPI data size combobox
                for i in range(len(sequence.dict_spi_data_size)):
                    self.spi_data_size_select.addItem(list(sequence.dict_spi_data_size.keys())[i],list(sequence.dict_spi_data_size.values())[i] )

                # Fill SPI first bit combobox
                for i in range(len(sequence.dict_spi_first_bit)):
                    self.spi_first_bit_select.addItem(list(sequence.dict_spi_first_bit.keys())[i],list(sequence.dict_spi_first_bit.values())[i] )

                # Fill SPI clock mode combobox
                for i in range(len(sequence.dict_spi_clockmode)):
                    self.spi_clockmode_select.addItem(list(sequence.dict_spi_clockmode.keys())[i],list(sequence.dict_spi_clockmode.values())[i] )

                # Connect signals and call functions explicitly
                self.spi_frame_format_select.activated[str].connect(self.on_changed_spi_frame_format)
                self.spi_hardware_nss_select.activated[str].connect(self.on_changed_spi_hardware_nss)
                self.spi_operating_mode_select.activated[str].connect(self.on_changed_spi_opmode)
                self.on_changed_spi_frame_format()
                self.on_changed_spi_hardware_nss()

                # Add widgets to layout
                self.options_layout.addWidget(self.spi_bus_label,0,0)
                self.options_layout.addWidget(self.spi_operating_mode_label,1,0)
                self.options_layout.addWidget(self.spi_command_label,2,0)
                self.options_layout.addWidget(self.spi_dummyclocks_label,3,0)
                self.options_layout.addWidget(self.spi_write_value_label,4,0)
                self.options_layout.addWidget(self.spi_write_size_label,5,0)
                self.options_layout.addWidget(self.spi_slave_response_label,6,0)
                self.options_layout.addWidget(self.spi_hardware_nss_label,7,0)
                self.options_layout.addWidget(self.spi_frame_format_label,8,0)
                self.options_layout.addWidget(self.spi_data_size_label,9,0)

                self.options_layout.addWidget(self.spi_bus_select,0,2)
                self.options_layout.addWidget(self.spi_operating_mode_select,1,2)
                self.options_layout.addWidget(self.spi_command_select,2,2)
                self.options_layout.addWidget(self.spi_dummyclocks_select,3,2)
                self.options_layout.addWidget(self.spi_write_value_select,4,2)
                self.options_layout.addWidget(self.spi_write_size_select,5,2)
                self.options_layout.addWidget(self.spi_slave_response_select,6,2)
                self.options_layout.addWidget(self.spi_hardware_nss_select,7,2)
                self.options_layout.addWidget(self.spi_frame_format_select,8,2)
                self.options_layout.addWidget(self.spi_data_size_select,9,2)

                # Layout settings
                self.options_layout.addItem(self.spacerItem,12,0)
                self.options_layout.setColumnMinimumWidth(1,0)

        elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
            if self.GPIO_active == False:
                self.GPIO_active = True
                self.gpio_pin_label = QLabel("GPIO pin", self)
                self.gpio_direction_label = QLabel("Direction", self)
                self.gpio_state_label = QLabel("State", self)
                self.gpio_pull_label = QLabel("Pull-up/pull-down", self)

                self.gpio_pin_select = QComboBox(self)
                self.gpio_direction_select = QComboBox(self)
                self.gpio_state_select = QComboBox(self)
                self.gpio_pull_select = QComboBox(self)


                # Fill GPIO digital pins combobox
                if self.use_config_file == True:
                    for i in range(len(config.dict_available_digital_pins)):
                        self.gpio_pin_select.addItem(list(config.dict_available_digital_pins.keys())[i],list(config.dict_available_digital_pins.values())[i] )
                else:
                    for i in range(len(sequence.dict_gpio_digital_pins) - 1):   # Last pin in list is the 'invalid' pin
                        self.gpio_pin_select.addItem(list(sequence.dict_gpio_digital_pins.keys())[i],list(sequence.dict_gpio_digital_pins.values())[i] )

                # Fill GPIO direction combobox
                self.gpio_direction_select.addItem(list(sequence.dict_gpio_rw.keys())[0],list(sequence.dict_gpio_rw.values())[0])
                self.gpio_direction_select.addItem(list(sequence.dict_gpio_rw.keys())[1],list(sequence.dict_gpio_rw.values())[1])

                # Fill GPIO state combobox
                self.gpio_state_select.addItem(list(sequence.dict_gpio_state.keys())[0],list(sequence.dict_gpio_state.values())[0])
                self.gpio_state_select.addItem(list(sequence.dict_gpio_state.keys())[1],list(sequence.dict_gpio_state.values())[1])

                # Fill GPIO pull-up/pull-down combobox
                self.gpio_pull_select.addItem(list(sequence.dict_gpio_pull.keys())[0],list(sequence.dict_gpio_pull.values())[0])
                self.gpio_pull_select.addItem(list(sequence.dict_gpio_pull.keys())[1],list(sequence.dict_gpio_pull.values())[1])
                self.gpio_pull_select.addItem(list(sequence.dict_gpio_pull.keys())[2],list(sequence.dict_gpio_pull.values())[2])

                # Connect signal and call function explicitly
                self.gpio_state_select.setEnabled(True)
                self.gpio_direction_select.activated[str].connect(self.on_changed_gpio_dir)

                # Add widgets to layout
                self.options_layout.addWidget(self.gpio_pin_label,0,0)
                self.options_layout.addWidget(self.gpio_direction_label,1,0)
                self.options_layout.addWidget(self.gpio_state_label,2,0)
                self.options_layout.addWidget(self.gpio_pull_label,3,0)

                self.options_layout.addWidget(self.gpio_pin_select,0,2)
                self.options_layout.addWidget(self.gpio_direction_select,1,2)
                self.options_layout.addWidget(self.gpio_state_select,2,2)
                self.options_layout.addWidget(self.gpio_pull_select,3,2)

                # Layout settings
                self.options_layout.addItem(self.spacerItem,4,0)
                self.options_layout.setColumnMinimumWidth(1,0)

        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
            if self.AnalogRead_active == False:
                self.AnalogRead_active = True
                self.adc_instance_label = QLabel("Instance", self)
                self.adc_channel_label = QLabel("Channel", self)
                self.adc_pin_label = QLabel("GPIO pin", self)
                self.adc_resolution_label = QLabel("Resolution", self)
                self.adc_clock_prescaler_label = QLabel("Clock prescaler", self)

                self.adc_instance_select = QComboBox(self)
                self.adc_channel_select = QComboBox(self)
                self.adc_pin_select = QLineEdit("", self)
                self.adc_resolution_select = QComboBox(self)
                self.adc_clock_prescaler_select = QComboBox(self)

                # Fill ADC instance combobox
                if self.use_config_file == True:
                    for i in range(len(config.dict_available_adc_instances)):
                        self.adc_instance_select.addItem(list(config.dict_available_adc_instances.keys())[i],list(config.dict_available_adc_instances.values())[i] )
                else:
                    for i in range(len(sequence.dict_adc_instances)):
                        self.adc_instance_select.addItem(list(sequence.dict_adc_instances.keys())[i],list(sequence.dict_adc_instances.values())[i] )

                # Fill ADC channels combobox
                if self.use_config_file == True:
                    for i in range(len(config.dict_available_adc_channels)):
                        self.adc_channel_select.addItem(list(config.dict_available_adc_channels.keys())[i],list(config.dict_available_adc_channels.values())[i] )
                else:
                    for i in range(len(sequence.dict_adc_channels)):
                        self.adc_channel_select.addItem(list(sequence.dict_adc_channels.keys())[i],list(sequence.dict_adc_channels.values())[i] )

                # Fill ADC resolution combobox
                for i in range(len(sequence.dict_adc_res)):
                    self.adc_resolution_select.addItem(list(sequence.dict_adc_res.keys())[i],list(sequence.dict_adc_res.values())[i] )

                # Fill ADC clock prescaler combobox
                for i in range(len(sequence.dict_adc_clock_prescaler)):
                    self.adc_clock_prescaler_select.addItem(list(sequence.dict_adc_clock_prescaler.keys())[i],list(sequence.dict_adc_clock_prescaler.values())[i] )

                # Connect signal and call function explicitly, disable ADC pin input field
                self.adc_channel_select.activated[str].connect(self.on_changed_adc_channel)
                self.on_changed_adc_channel()
                self.adc_pin_select.setEnabled(False)

                # Add widgets to layout
                self.options_layout.addWidget(self.adc_instance_label,0,0)
                self.options_layout.addWidget(self.adc_channel_label,1,0)
                self.options_layout.addWidget(self.adc_pin_label,2,0)
                self.options_layout.addWidget(self.adc_resolution_label,3,0)
                self.options_layout.addWidget(self.adc_clock_prescaler_label,4,0)

                self.options_layout.addWidget(self.adc_instance_select,0,2)
                self.options_layout.addWidget(self.adc_channel_select,1,2)
                self.options_layout.addWidget(self.adc_pin_select,2,2)
                self.options_layout.addWidget(self.adc_resolution_select,3,2)
                self.options_layout.addWidget(self.adc_clock_prescaler_select,4,2)

                # Layout settings
                self.options_layout.addItem(self.spacerItem,5,0)
                self.options_layout.setColumnMinimumWidth(1,30)

        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
            if self.AnalogWrite_active == False:
                self.AnalogWrite_active = True
                self.gpio_pin_label = QLabel("GPIO pin", self)
                self.pwm_freq_label= QLabel("Frequency (Hz)", self)
                self.pwm_duty_label = QLabel("Duty cycle (%)", self)
                self.pwm_time_checkbox = QCheckBox("Active for given time only")
                self.pwm_time_label = QLabel("Time (ms)",self)

                self.gpio_pin_select = QComboBox(self)
                self.pwm_freq_select = QLineEdit(self)
                self.pwm_duty_select = QLineEdit(self)
                self.pwm_time_select = QLineEdit(self)

                # Fill GPIO pins combobox
                if self.use_config_file == True:
                    for i in range(len(config.dict_available_digital_pins)):
                        self.gpio_pin_select.addItem(list(config.dict_available_digital_pins.keys())[i],list(config.dict_available_digital_pins.values())[i] )
                else:
                    for i in range(len(sequence.dict_gpio_digital_pins) - 1):       # Last pin in list is the 'invalid' pin
                        self.gpio_pin_select.addItem(list(sequence.dict_gpio_digital_pins.keys())[i],list(sequence.dict_gpio_digital_pins.values())[i] )

                # Set validators and placeholders for input fields
                self.pwm_freq_select.setValidator(self.freqValidator)
                self.pwm_freq_select.setPlaceholderText("0..1000")

                self.pwm_duty_select.setValidator(self.dutyValidator)
                self.pwm_duty_select.setPlaceholderText("0..100")

                self.pwm_time_select.setValidator(self.pwmTimeValidator)
                self.pwm_time_select.setPlaceholderText("1000")

                # Connect signal and call function explicitly
                self.pwm_time_checkbox.stateChanged.connect(self.pwm_time_checkbox_state_changed)
                self.pwm_time_checkbox_state_changed()

                # Add widgets to layout
                self.options_layout.addWidget(self.gpio_pin_label,0,0)
                self.options_layout.addWidget(self.pwm_freq_label,1,0)
                self.options_layout.addWidget(self.pwm_duty_label,2,0)

                self.options_layout.addWidget(self.gpio_pin_select,0,2)
                self.options_layout.addWidget(self.pwm_freq_select,1,2)
                self.options_layout.addWidget(self.pwm_duty_select,2,2)

                self.options_layout.addWidget(self.pwm_time_checkbox,3,0,1,3)
                self.options_layout.addWidget(self.pwm_time_label,4,0)
                self.options_layout.addWidget(self.pwm_time_select,4,2)

                # Layout settings
                self.options_layout.addItem(self.spacerItem,5,0)
                self.options_layout.setColumnMinimumWidth(1,30)

        elif cmdType == functional_test_pb2.CommandTypeEnum.USART_test:
            if self.USART_active == False:
                self.USART_active = True
                self.usart_bus_label = QLabel("Bus", self)
                self.usart_mode_label = QLabel("Mode", self)
                self.usart_baudrate_label = QLabel("Baud Rate", self)
                self.usart_word_length_label = QLabel("Word Length", self)
                self.usart_parity_label = QLabel("Parity", self)
                self.usart_stop_bits_label = QLabel("Stop Bits", self)
                self.usart_direction_label = QLabel("Direction", self)
                self.usart_command_label = QLabel("Command", self)
                self.usart_clock_polarity_label = QLabel("Clock Polarity", self)
                self.usart_clock_phase_label = QLabel("Clock Phase", self)
                self.usart_clock_last_bit_label = QLabel("Clock Last Bit", self)
                self.usart_hw_flow_control_label = QLabel("HW Flow control", self)

                self.usart_bus_select = QComboBox(self)
                self.usart_mode_select = QComboBox(self)
                self.usart_baudrate_select = QLineEdit(self)
                self.usart_word_length_select = QComboBox(self)
                self.usart_parity_select = QComboBox(self)
                self.usart_stop_bits_select = QComboBox(self)
                self.usart_direction_select = QComboBox(self)
                self.usart_command_select = QLineEdit(self)
                self.usart_clock_polarity_select = QComboBox(self)
                self.usart_clock_phase_select = QComboBox(self)
                self.usart_clock_last_bit_select = QComboBox(self)
                self.usart_hw_flow_control_select = QComboBox(self)

                # Fill USART bus combobox
                if self.use_config_file == True:
                    for i in range(len(config.dict_available_usart_buses)):
                        self.usart_bus_select.addItem(list(config.dict_available_usart_buses.keys())[i],list(config.dict_available_usart_buses.values())[i] )
                else:
                    for i in range(len(sequence.dict_usart_bus)):
                        self.usart_bus_select.addItem(list(sequence.dict_usart_bus.keys())[i],list(sequence.dict_usart_bus.values())[i] )

                # Fill USART mode select combobox
                for i in range(len(sequence.dict_usart_mode)):
                    self.usart_mode_select.addItem(list(sequence.dict_usart_mode.keys())[i],list(sequence.dict_usart_mode.values())[i] )

                # Fill USART word length combobox
                for i in range(len(sequence.dict_usart_word_length)):
                    self.usart_word_length_select.addItem(list(sequence.dict_usart_word_length.keys())[i],list(sequence.dict_usart_word_length.values())[i] )

                # Fill USART parity combobox
                for i in range(len(sequence.dict_usart_parity)):
                    self.usart_parity_select.addItem(list(sequence.dict_usart_parity.keys())[i],list(sequence.dict_usart_parity.values())[i] )

                # Fill USART stop bits combobox
                for i in range(len(sequence.dict_usart_stop_bits)):
                    self.usart_stop_bits_select.addItem(list(sequence.dict_usart_stop_bits.keys())[i],list(sequence.dict_usart_stop_bits.values())[i] )

                # Fill USART direction combobox
                for i in range(len(sequence.dict_usart_direction)):
                    self.usart_direction_select.addItem(list(sequence.dict_usart_direction.keys())[i],list(sequence.dict_usart_direction.values())[i] )

                # Fill USART clock polarity combobox
                for i in range(len(sequence.dict_usart_clock_polarity)):
                    self.usart_clock_polarity_select.addItem(list(sequence.dict_usart_clock_polarity.keys())[i],list(sequence.dict_usart_clock_polarity.values())[i] )

                # Fill USART clock polarity combobox
                for i in range(len(sequence.dict_usart_clock_phase)):
                    self.usart_clock_phase_select.addItem(list(sequence.dict_usart_clock_phase.keys())[i],list(sequence.dict_usart_clock_phase.values())[i] )

                # Fill USART clock last bit combobox
                for i in range(len(sequence.dict_usart_clock_last_bit)):
                    self.usart_clock_last_bit_select.addItem(list(sequence.dict_usart_clock_last_bit.keys())[i],list(sequence.dict_usart_clock_last_bit.values())[i] )

                # Fill USART HW Flow Control combobox
                for i in range(len(sequence.dict_usart_hw_flow)):
                    self.usart_hw_flow_control_select.addItem(list(sequence.dict_usart_hw_flow.keys())[i],list(sequence.dict_usart_hw_flow.values())[i] )

                # Set placeholders and validator for input fields
                self.usart_baudrate_select.setValidator(self.baudValidator)
                self.usart_baudrate_select.setPlaceholderText("115200")

                self.usart_command_select.setValidator(self.wordValidator)
                self.usart_command_select.setPlaceholderText("0x00000000")

                # Connect signal and call function explicitly
                self.usart_mode_select.activated[str].connect(self.on_changed_usart_mode)
                self.on_changed_usart_mode()

                self.usart_direction_select.activated[str].connect(self.on_changed_usart_direction)
                self.on_changed_usart_direction()

                # Add widgets to layout
                self.options_layout.addWidget(self.usart_bus_label,0,0)
                self.options_layout.addWidget(self.usart_mode_label,1,0)
                self.options_layout.addWidget(self.usart_baudrate_label,2,0)
                self.options_layout.addWidget(self.usart_word_length_label,3,0)
                self.options_layout.addWidget(self.usart_parity_label,4,0)
                self.options_layout.addWidget(self.usart_stop_bits_label,5,0)
                self.options_layout.addWidget(self.usart_direction_label,6,0)
                self.options_layout.addWidget(self.usart_command_label,7,0)

                self.options_layout.addWidget(self.usart_bus_select,0,2)
                self.options_layout.addWidget(self.usart_mode_select,1,2)
                self.options_layout.addWidget(self.usart_baudrate_select,2,2)
                self.options_layout.addWidget(self.usart_word_length_select,3,2)
                self.options_layout.addWidget(self.usart_parity_select,4,2)
                self.options_layout.addWidget(self.usart_stop_bits_select,5,2)
                self.options_layout.addWidget(self.usart_direction_select,6,2)
                self.options_layout.addWidget(self.usart_command_select,7,2)

                # Layout settings
                self.options_layout.addItem(self.spacerItem,11,0)
                self.options_layout.setColumnMinimumWidth(1,30)


    # Delete all child widget from a layout
    def delete_all_child_widget(self, layout):
#        for i in reversed(range(layout.count())):
#            layout.itemAt(i).widget().setParent(None)
        if layout is not None:
            while layout.count():
                item = layout.takeAt(0)
                widget = item.widget()
                if widget is not None:
                    widget.deleteLater()
#                else:
#                    self.clearLayout(item.layout())

        self.MENU_active = False
        self.I2C_active = False
        self.SPI_active = False
        self.GPIO_active = False
        self.USART_active = False
        self.AnalogRead_active = False
        self.AnalogWrite_active = False

    # Get a maximum number of response bytes depending on command type
    def read_data_depending_on_cmd_type(self, test_object):
        cmdType = test_object.commandType
        response_num = 20 # Should depend on buad rate..

        # Get response
        response_data = self.ser.read(response_num)             # Read response data
        self.LL.link_unframe_data(response_data)                # Unframe response data
        pb = array.array('B',self.LL.rx_buffer).tobytes()      # Make string from response data
        message_data = functional_test_pb2.Command()
        message_data.ParseFromString(pb)                        # Deserialize response data into data structure

        if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
            if test_object.i2c.direction == functional_test_pb2.i2cDirection.I2C_write: # I2C write response: OK/failed
                response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
            else:   # I2C read response: data/failed
                if message_data.response.responseEnum == list(sequence.dict_response_write.values())[list(sequence.dict_response_write.keys()).index("I2C read failed")]:
                    response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
                else:
                    if test_object.i2c.size == 1:
                        response = "I2C read: " + "0x{:02X}".format(message_data.response.responseRead)
                    else:
                        response = "I2C read: " + "0x{:04X}".format(message_data.response.responseRead)


        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            if test_object.spi.operatingMode == list(sequence.dict_spi_operating_mode.values())[1]: # SPI Transmit-only response: OK/failed
                response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
            elif test_object.spi.operatingMode == list(sequence.dict_spi_operating_mode.values())[3]: # SPI Half duplex Transmit-only response: OK/failed
                response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
            else:   # SPI transmit/receive response: data/failed
                if message_data.response.responseEnum == list(sequence.dict_response_write.values())[list(sequence.dict_response_write.keys()).index("SPI transmission failed")]:
                    response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
                else:
                    response = "SPI transmit/receive: " + "0x{:04X}".format(message_data.response.responseRead)

        elif cmdType == functional_test_pb2.CommandTypeEnum.USART_test:
            if test_object.usart.direction == list(sequence.dict_usart_direction.values())[0]:      # USART TX-only response: OK/failed
                response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
            elif test_object.usart.direction == list(sequence.dict_usart_direction.values())[1]:    # USART RX-only response: data/failed
                if message_data.response.responseEnum == list(sequence.dict_response_write.values())[list(sequence.dict_response_write.keys()).index("USART RX failed")]:
                    response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
                else:
                    response = "USART/UART receive: " + "0x{:08X}".format(message_data.response.responseRead)


            else:                                                                                   # USART TX+RX response: data/failed
                if message_data.response.responseEnum == list(sequence.dict_response_write.values())[list(sequence.dict_response_write.keys()).index("USART TX+RX failed")]:
                    response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
                else:
                    response = "USART/UART receive: " + "0x{:08X}".format(message_data.response.responseRead)

        elif cmdType == functional_test_pb2.GPIO_digital:
            if test_object.gpio.direction == functional_test_pb2.gpioDirection.GPIO_INPUT:          # GPIO read: state/failed
                if message_data.response.responseEnum == list(sequence.dict_response_write.values())[list(sequence.dict_response_write.keys()).index("GPIO read failed")]:
                    response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
                else:
                    response = "GPIO state: " + list(sequence.dict_gpio_state.keys())[list(sequence.dict_gpio_state.values()).index(message_data.response.responseRead)] # Search key by value (GPIO state)
            else:                                                                                   # GPIO set: OK/failed
                response =  list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)] # Search key by value (responseWrite enum)
                response += ": " + list(sequence.dict_gpio_digital_pins.keys())[list(sequence.dict_gpio_digital_pins.values()).index(test_object.gpio.pin)]

        elif cmdType == functional_test_pb2.Analog_read:    # ADC read: data/failed
            if message_data.response.responseEnum == list(sequence.dict_response_write.values())[list(sequence.dict_response_write.keys()).index("Analog read failed")]:
                response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)]
            else:
                response = "Voltage: " + str(message_data.response.responseRead) + " mV"

        elif cmdType == functional_test_pb2.Analog_write:   # PWM set: OK/failed
            response = list(sequence.dict_response_write.keys())[list(sequence.dict_response_write.values()).index(message_data.response.responseEnum)] # Search key by value (responseWrite enum)
            response += ": " + list(sequence.dict_gpio_digital_pins.keys())[list(sequence.dict_gpio_digital_pins.values()).index(test_object.analog_out.pin)]

        del message_data
        self.ser.flush()
        return response


    # Connect to a serial port
    def connect(self):
        try:
#            if self.serial_line_field.text() == "":
            if sequence.is_empty(self.serial_line_field.text()):
                port_field = 'COM9'
            else:
               port_field = self.serial_line_field.text()
            if sequence.is_empty(self.speed_field.text()):
                speed = 115200
            else:
                speed = self.speed_field.text()
            self.ser = serial.Serial(port=port_field, baudrate=speed, bytesize=8, parity='N', stopbits=1, timeout=0.4)
            self.ser.setDTR(1)
            is_port_open = 'Port open'
            self.connect_button.setEnabled(False)
            self.close_button.setEnabled(True)
        except serial.serialutil.SerialException:
            is_port_open = 'Error opening port'
        openPortLabel = QLabel(is_port_open)
        self.scroll_layout.addWidget(openPortLabel)

    # Close serial port
    def close_port(self):
        if self.ser.is_open:
            try:
                self.ser.close()
                is_port_open = 'Port closed'
                self.connect_button.setEnabled(True)
                self.close_button.setEnabled(False)
            except serial.serialutil.SerialException:
                is_port_open = 'Error closing port'
        closePortLabel = QLabel(is_port_open)
        self.scroll_layout.addWidget(closePortLabel)

    # Serialize command and options, then send out data via UART
    def send_command(self):
        test_object = sequence.make_test_object_from_options(self)              # Make test object from selected options
        if test_object == None:
            return
        pb = sequence.make_protobuf_command_from_test_object(test_object)       # Make protobuf encoded command from test object
        str_test_object = sequence.make_string_from_test_object(test_object)    # Make string from test object
        self.LL.link_frame_data(pb)                                             # Frame protobuf encoded data
        print("TxBuffer: ",self.LL.tx_buffer)
        commandStringLabel = QLabel(str_test_object)
        commandStringLabel.setFont(self.italicFont)
        self.scroll_layout.addWidget(commandStringLabel)
        try:
            self.ser.write(self.LL.tx_buffer)
            response = ">> " + self.read_data_depending_on_cmd_type(test_object)
            responseLabel = QLabel(response)
            self.scroll_layout.addWidget(responseLabel)
        except serial.serialutil.SerialException:
            if self.ser.is_open:
                command_send_success = 'Error while sending command'
            else:
                command_send_success = 'Port is not open'
            commandSendingLabel = QLabel(command_send_success)
            self.scroll_layout.addWidget(commandSendingLabel)

    # Scroll down in scrollArea
    def resizeScroll(self, min, maxi):
        self.scrollArea.verticalScrollBar().setValue(maxi)








if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
