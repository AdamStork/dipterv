import time, os, sys, serial
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from decimal import Decimal
from functools import partial

import functional_test_pb2
import sequence
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
        self.cmd_box.activated[str].connect(self.on_changed)
        self.move_up_button.clicked.connect(self.move_up)
        self.move_down_button.clicked.connect(self.move_down)
        self.delete_row_button.clicked.connect(self.delete_row)
        self.sequence_add_button.clicked.connect(self.add_seq)
        self.delete_seq_button.clicked.connect(self.delete_seq)
        self.save_seq_button.clicked.connect(self.save_seq)
        self.load_seq_button.clicked.connect(self.load_seq)
        self.send_seq_button.clicked.connect(self.send_seq)
        self.fill_cmd_box()
        # flags: avoid command reselection
        self.I2C_active = False
        self.LED_active = False
        self.SPI_active = False
        self.GPIO_active = False
        self.AnalogRead_active = False
        self.AnalogWrite_active = False
        self.LL = link_layer()
        self.ser = serial.Serial()
        self.close_button.setEnabled(False)
        self.byteValidator = QRegExpValidator(QRegExp("0x[0-9A-Fa-f][0-9A-Fa-f]")) # Byte validator for input fields (0xhh format)
        self.decValidator  = QRegExpValidator(QRegExp("[0-9][0-9]")) # 2-digit decimal validator for input fields
        self.gpioValidator = QRegExpValidator(QRegExp("[0-7][0-7]")) # 2-digit decimal validator for GPIO fields
        self.dutyValidator = QRegExpValidator(QRegExp("[0-9][0-9][0-9]")) # Max. 3 digit validator for duty cycle [0-100], limits checked
        self.freqValidator = QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9]")) # Max. 4 digit validator for freqency [0-1000], limits checked
        self.test_list = []     # List filled with test objects
        self.helpLabel_list = []
        self.scroll_layout.addStretch()                            # Add stretch for scroll area
        self.container_widget.setLayout(self.scroll_layout)        # Set layout for scrollArea container widget

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
#            print(self.test_list[0].cmdType)


    # Delete row
    def delete_row(self):
        currentRow = self.sequence_list.currentRow()        # Get index of current row
        self.sequence_list.takeItem(currentRow)             # Delete current row (listWidgetitem)
        sequence.delete_test_object_from_test_list(self.test_list, currentRow)    # Delete test from test list
#        print("len seq:", len(self.sequence_list))
#        print("len test:", len(self.test_list))
#        print("")


    # Add command to test list and sequence list
    def add_seq(self, rowObject):
        if self.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.LED_test:
            return
        test_object = sequence.make_test_object_from_options(self)                                      # Make test object from selected options
        sequence.add_test_object_to_test_list(test_object, self.test_list)                              # Add test object to test list
        command_to_add = sequence.make_string_from_test_object(self.test_list[len(self.test_list)-1])   # Make string from test object
        self.sequence_list.insertItem(self.sequence_list.count(),command_to_add)                        # Add string to sequence list
#        print("len seq:", len(self.sequence_list))
#        print("len test:", len(self.test_list))


   # Delete the whole sequence
    def delete_seq(self):
        self.sequence_list.clear()                  # Delete sequence list
        sequence.delete_test_list(self.test_list)        # Delete test list
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
                    data_line[i] = data_line[i].rstrip()
#                    print(data_line[i])
                    self.sequence_list.insertItem(self.sequence_list.count(),data_line[i])      # Add string line to sequence
                    test_object = sequence.make_test_object_from_string(data_line[i])           # Make object from string line
                    sequence.add_test_object_to_test_list(test_object, self.test_list)          # Add object to test list
                file.close()

    def send_seq(self):
        for i in range(len(self.test_list)):
            pb = sequence.make_protobuf_command_from_test_object(self.test_list[i])    # Make protobuf command
            self.LL.link_frame_data(pb)            # Frame protobuf data
            print("TxBuffer: ",self.LL.tx_buffer)
            try:
                self.ser.write(self.LL.tx_buffer)
                command_send_success = 'Command sent'
                self.read_data_depending_on_cmd_type(self.test_list[i].cmdType)
            except serial.serialutil.SerialException:
                if self.ser.is_open:
                    command_send_success = 'Error while sending command'
                else:
                    command_send_success = 'Port is not open'
                # If serial write is unsuccessful, then display it on scrollArea and return immediately.
                successLabel = QLabel(command_send_success)
                self.scroll_layout.addWidget(successLabel)
                return

            # Print current command
            self.sequence_list.setCurrentRow(i)
            currentCommand = "Cmd: " + self.sequence_list.currentItem().text()
            currentCommandLabel = QLabel(currentCommand)



            # Print serial read response
            response = "Response:"
            responseLabel = QLabel(response)

            # Add widgets (labels) to scrollArea
            self.scroll_layout.addWidget(currentCommandLabel)
            self.scroll_layout.addWidget(responseLabel)
            last_widget = self.scroll_layout.itemAt(self.scroll_layout.count()-1).widget()
            QtCore.QTimer.singleShot(0, partial(self.scrollArea.ensureWidgetVisible, last_widget))


    # Fill combobox with commands
    def fill_cmd_box(self):
        self.cmd_box.addItem("Click to select...",functional_test_pb2.CommandTypeEnum.LED_test)
        self.cmd_box.addItem("I2C test",functional_test_pb2.CommandTypeEnum.I2C_test)
        self.cmd_box.addItem("SPI test",functional_test_pb2.CommandTypeEnum.SPI_test)
        self.cmd_box.addItem("GPIO digital",functional_test_pb2.CommandTypeEnum.GPIO_digital)
        self.cmd_box.addItem("Analog read",functional_test_pb2.CommandTypeEnum.Analog_read)
        self.cmd_box.addItem("PWM",functional_test_pb2.CommandTypeEnum.Analog_write)

    # Called whenever GPIO direction is changed in GPIO digital command
    def on_changed_gpio_dir(self):
        if self.gpio_direction_select.currentData() == functional_test_pb2.gpioDirection.GPIO_INPUT:
            self.gpio_state_select.setEnabled(False)
        else:
            self.gpio_state_select.setEnabled(True)

    # Called whenever GPIO port selection is changed in Analog read command
    def on_changed_gpio_port(self):
        if self.gpio_port_select.currentData() == functional_test_pb2.gpioPort.GPIO_TEMP_SENSOR:
            self.gpio_pin_select.setEnabled(False)
        elif self.gpio_port_select.currentData() == functional_test_pb2.gpioPort.GPIO_VREFINT:
            self.gpio_pin_select.setEnabled(False)
        elif self.gpio_port_select.currentData() == functional_test_pb2.gpioPort.GPIO_VBAT:
            self.gpio_pin_select.setEnabled(False)
        else:
            self.gpio_pin_select.setEnabled(True)

    # Called whenever a command is selected
    def on_changed(self,text):
        print("CmdType:",self.cmd_box.currentData())
        self.delete_all_child_widget(self.options_layout)
        self.show_data_depending_on_cmd_type(self.cmd_box.currentData())
        self.show()

    # Show data depending on the command type selected
    def show_data_depending_on_cmd_type(self,cmdType):
        self.spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding) # Row Spacer if needed

        if cmdType == functional_test_pb2.CommandTypeEnum.LED_test:
            print("LED options")
            if self.LED_active == False:
                self.LED_active = True
                self.led_label = QLabel("Let there be (LED) light!", self)
                self.options_layout.addWidget(self.led_label)

        elif cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
            print("I2C options")
            if self.I2C_active == False:
                self.I2C_active = True
                self.i2c_bus_label = QLabel("I2C bus", self)
                self.i2c_addr_label = QLabel("I2C address", self)
                self.i2c_reg_label = QLabel("I2C register", self)
                self.i2c_rw_label = QLabel("I2C R/W", self)
                self.i2c_bus_select = QComboBox(self)
                self.i2c_addr_select = QLineEdit(self)
                self.i2c_reg_select = QLineEdit(self)
                self.i2c_rw_select = QComboBox(self)

                self.i2c_bus_select.addItem("I2C1",functional_test_pb2.i2cBus.I2C1)  # TODO: melyik buszok elerhetok: addItem()
                self.i2c_bus_select.addItem("I2C2",functional_test_pb2.i2cBus.I2C2)
                self.i2c_bus_select.addItem("I2C3",functional_test_pb2.i2cBus.I2C3)

                self.i2c_rw_select.addItem("Read",functional_test_pb2.i2cDirection.I2C_read)
                self.i2c_rw_select.addItem("Write",functional_test_pb2.i2cDirection.I2C_write)          

                self.i2c_addr_select.setValidator(self.byteValidator)
                self.i2c_addr_select.setPlaceholderText("0xFF")
                self.i2c_reg_select.setValidator(self.byteValidator)
                self.i2c_reg_select.setPlaceholderText("0xFF")

                self.options_layout.addWidget(self.i2c_bus_label,0,0)
                self.options_layout.addWidget(self.i2c_addr_label,1,0)
                self.options_layout.addWidget(self.i2c_reg_label,2,0)
                self.options_layout.addWidget(self.i2c_rw_label,3,0)
                self.options_layout.addWidget(self.i2c_bus_select,0,2)
                self.options_layout.addWidget(self.i2c_addr_select,1,2)
                self.options_layout.addWidget(self.i2c_reg_select,2,2)
                self.options_layout.addWidget(self.i2c_rw_select,3,2)

                self.options_layout.addItem(self.spacerItem,4,0)
                self.options_layout.setColumnMinimumWidth(1,40)

        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            print("SPI options")
            if self.SPI_active == False:
                self.SPI_active = True
                self.spi_bus_label = QLabel("SPI bus", self)
                self.spi_clockmode_label = QLabel("SPI mode", self)
                self.spi_command_label = QLabel("SPI command", self)
                self.spi_dummyclocks_label = QLabel("SPI dummy clocks", self)
                self.spi_direction_label = QLabel("SPI direction", self)     # Needed for response (register value or write success)

                self.spi_bus_select = QComboBox(self)
                self.spi_clockmode_select = QComboBox(self)
                self.spi_command_select = QLineEdit(self)
                self.spi_dummyclocks_select = QLineEdit(self)
                self.spi_direction_select = QComboBox(self)

                self.spi_bus_select.addItem("SPI1",functional_test_pb2.spiBus.SPI1)
                self.spi_bus_select.addItem("SPI2",functional_test_pb2.spiBus.SPI2)
                self.spi_bus_select.addItem("SPI3",functional_test_pb2.spiBus.SPI3)

                self.spi_clockmode_select.addItem("Mode 0",functional_test_pb2.clockMode.MODE_0)
                self.spi_clockmode_select.addItem("Mode 1",functional_test_pb2.clockMode.MODE_1)
                self.spi_clockmode_select.addItem("Mode 2",functional_test_pb2.clockMode.MODE_2)
                self.spi_clockmode_select.addItem("Mode 3",functional_test_pb2.clockMode.MODE_3)

                self.spi_command_select.setValidator(self.byteValidator)
                self.spi_command_select.setPlaceholderText("0xFF")
                self.spi_dummyclocks_select.setValidator(self.decValidator)
                self.spi_dummyclocks_select.setPlaceholderText("0..99")

                self.spi_direction_select.addItem("Transmit",functional_test_pb2.spiDirection.SPI_TRANSMIT)
                self.spi_direction_select.addItem("Receive",functional_test_pb2.spiDirection.SPI_RECEIVE)

                self.options_layout.addWidget(self.spi_bus_label,0,0)
                self.options_layout.addWidget(self.spi_clockmode_label,1,0)
                self.options_layout.addWidget(self.spi_command_label,2,0)
                self.options_layout.addWidget(self.spi_dummyclocks_label,3,0)
                self.options_layout.addWidget(self.spi_direction_label,4,0)
                self.options_layout.addWidget(self.spi_bus_select,0,2)
                self.options_layout.addWidget(self.spi_clockmode_select,1,2)
                self.options_layout.addWidget(self.spi_command_select,2,2)
                self.options_layout.addWidget(self.spi_dummyclocks_select,3,2)
                self.options_layout.addWidget(self.spi_direction_select,4,2)
                self.options_layout.setColumnMinimumWidth(1,40)

        elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
            print("GPIO digital optons")
            if self.GPIO_active == False:
                self.GPIO_active = True
                self.gpio_port_label = QLabel("GPIO port", self)
                self.gpio_pin_label = QLabel("GPIO pin", self)
                self.gpio_direction_label = QLabel("GPIO direction", self)
                self.gpio_state_label = QLabel("GPIO state", self)

                self.gpio_port_select = QComboBox(self)
                self.gpio_pin_select = QLineEdit(self)
                self.gpio_direction_select = QComboBox(self)
                self.gpio_state_select = QComboBox(self)

                self.gpio_pin_select.setValidator(self.gpioValidator)
                self.gpio_pin_select.setPlaceholderText("0..15")

                self.gpio_port_select.addItem("Port A",functional_test_pb2.gpioPort.GPIO_PORT_A)
                self.gpio_port_select.addItem("Port B",functional_test_pb2.gpioPort.GPIO_PORT_B)
                self.gpio_port_select.addItem("Port C",functional_test_pb2.gpioPort.GPIO_PORT_C)

                self.gpio_direction_select.addItem("Input",functional_test_pb2.gpioDirection.GPIO_INPUT)
                self.gpio_direction_select.addItem("Output",functional_test_pb2.gpioDirection.GPIO_OUTPUT)

                self.gpio_state_select.addItem("Low",functional_test_pb2.gpioPinState.GPIO_LOW)
                self.gpio_state_select.addItem("High",functional_test_pb2.gpioPinState.GPIO_HIGH)

                self.gpio_state_select.setEnabled(False)
                self.gpio_direction_select.activated[str].connect(self.on_changed_gpio_dir)

                self.options_layout.addWidget(self.gpio_port_label,0,0)
                self.options_layout.addWidget(self.gpio_pin_label,1,0)
                self.options_layout.addWidget(self.gpio_direction_label,2,0)
                self.options_layout.addWidget(self.gpio_state_label,3,0)
                self.options_layout.addWidget(self.gpio_port_select,0,2)
                self.options_layout.addWidget(self.gpio_pin_select,1,2)
                self.options_layout.addWidget(self.gpio_direction_select,2,2)
                self.options_layout.addWidget(self.gpio_state_select,3,2)

                self.options_layout.addItem(self.spacerItem,4,0)
                self.options_layout.setColumnMinimumWidth(1,40)

        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
            print("AnalogRead optons")
            if self.AnalogRead_active == False:
                self.AnalogRead_active = True
                self.gpio_port_label = QLabel("GPIO port", self)
                self.gpio_pin_label = QLabel("GPIO pin", self)
                self.adc_resolution_label = QLabel("ADC resolution", self)
                self.available_pins_label = QLabel("Available GPIOs:", self)
                self.available_pins_label_2 = QLabel("PA0..PA7, \nPB0..PB1,\nPC0..PC5\n", self)

                self.gpio_port_select = QComboBox(self)
                self.gpio_pin_select = QLineEdit(self)
                self.adc_resolution_select = QComboBox(self)

                self.gpio_port_select.addItem("Port A",functional_test_pb2.gpioPort.GPIO_PORT_A)
                self.gpio_port_select.addItem("Port B",functional_test_pb2.gpioPort.GPIO_PORT_B)
                self.gpio_port_select.addItem("Port C",functional_test_pb2.gpioPort.GPIO_PORT_C)
                self.gpio_port_select.addItem("Temp sensor",functional_test_pb2.gpioPort.GPIO_TEMP_SENSOR)
                self.gpio_port_select.addItem("Vrefint",functional_test_pb2.gpioPort.GPIO_VREFINT)
                self.gpio_port_select.addItem("Vbat",functional_test_pb2.gpioPort.GPIO_VBAT)
                self.gpio_port_select.activated[str].connect(self.on_changed_gpio_port)

                self.gpio_pin_select.setValidator(self.gpioValidator)
                self.gpio_pin_select.setPlaceholderText("0..15")

                self.adc_resolution_select.addItem("12 bits",functional_test_pb2.ADC_RESOLUTION.ADC_12_BITS)
                self.adc_resolution_select.addItem("10 bits",functional_test_pb2.ADC_RESOLUTION.ADC_10_BITS)
                self.adc_resolution_select.addItem("8 bits",functional_test_pb2.ADC_RESOLUTION.ADC_8_BITS)
                self.adc_resolution_select.addItem("6 bits",functional_test_pb2.ADC_RESOLUTION.ADC_6_BITS)

                self.options_layout.addWidget(self.gpio_port_label,0,0)
                self.options_layout.addWidget(self.gpio_pin_label,1,0)
                self.options_layout.addWidget(self.adc_resolution_label,2,0)
                self.options_layout.addWidget(self.available_pins_label,3,0)
                self.options_layout.addWidget(self.gpio_port_select,0,2)
                self.options_layout.addWidget(self.gpio_pin_select,1,2)
                self.options_layout.addWidget(self.adc_resolution_select,2,2)
                self.options_layout.addWidget(self.available_pins_label_2,3,2)

                self.options_layout.addItem(self.spacerItem,4,0)
                self.options_layout.setColumnMinimumWidth(1,40)

        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
            print("AnalogWrite optons")
            if self.AnalogWrite_active == False:
                self.AnalogWrite_active = True
                self.gpio_port_label = QLabel("GPIO port", self)
                self.gpio_pin_label = QLabel("GPIO pin", self)
                self.pwm_freq_label= QLabel("Frequency", self)
                self.pwm_duty_label = QLabel("Duty cycle", self)

                self.gpio_port_select = QComboBox(self)
                self.gpio_pin_select = QLineEdit(self)
                self.pwm_freq_select = QLineEdit(self)
                self.pwm_duty_select = QLineEdit(self)

                self.gpio_port_select.addItem("Port A",functional_test_pb2.gpioPort.GPIO_PORT_A)
                self.gpio_port_select.addItem("Port B",functional_test_pb2.gpioPort.GPIO_PORT_B)
                self.gpio_port_select.addItem("Port C",functional_test_pb2.gpioPort.GPIO_PORT_C)

                self.gpio_pin_select.setValidator(self.gpioValidator)
                self.gpio_pin_select.setPlaceholderText("0..15")

                self.pwm_freq_select.setValidator(self.freqValidator)
                self.pwm_freq_select.setPlaceholderText("0..1000")

                self.pwm_duty_select.setValidator(self.dutyValidator)
                self.pwm_duty_select.setPlaceholderText("0..100")

                self.options_layout.addWidget(self.gpio_port_label,0,0)
                self.options_layout.addWidget(self.gpio_pin_label,1,0)
                self.options_layout.addWidget(self.pwm_freq_label,2,0)
                self.options_layout.addWidget(self.pwm_duty_label,3,0)
                self.options_layout.addWidget(self.gpio_port_select,0,2)
                self.options_layout.addWidget(self.gpio_pin_select,1,2)
                self.options_layout.addWidget(self.pwm_freq_select,2,2)
                self.options_layout.addWidget(self.pwm_duty_select,3,2)

                self.options_layout.addItem(self.spacerItem,4,0)
                self.options_layout.setColumnMinimumWidth(1,40)

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

        self.LED_active = False
        self.I2C_active = False
        self.SPI_active = False
        self.GPIO_active = False
        self.AnalogRead_active = False
        self.AnalogWrite_active = False

    # Add data depending on command type
    def add_data_depending_on_cmd_type(self, cmdType):
        print("Add data depending on cmd type")
        if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
            self.cmd.i2c.bus = self.i2c_bus_select.currentData()
            if sequence.is_empty(self.i2c_addr_select.text()):
                self.cmd.i2c.address = 0
            else:
                self.cmd.i2c.address = int(self.i2c_addr_select.text(),16)      # Convert to int
            if sequence.is_empty(self.i2c_reg_select.text()):
                self.cmd.i2c.reg = 0
            else:
                self.cmd.i2c.reg = int(self.i2c_reg_select.text(),16)           # Convert to int
            self.cmd.i2c.direction = self.i2c_rw_select.currentData()
            print("I2C Bus:", self.cmd.i2c.bus)
            print("I2C Addr:", self.cmd.i2c.address)
            print("I2C Reg:", self.cmd.i2c.reg)
            print("I2C Dir:", self.cmd.i2c.direction)

        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            self.cmd.spi.bus = self.spi_bus_select.currentData()
            self.cmd.spi.clock = self.spi_clockmode_select.currentData()
            if sequence.is_empty(self.spi_command_select.text()):
                self.cmd.spi.command = 0
            else:
                self.cmd.spi.command = int(self.spi_command_select.text(),16)
            if sequence.is_empty(self.spi_dummyclocks_select.text()):
                self.cmd.spi.dummyclocks = 0
            else:
                self.cmd.spi.dummyclocks = int(self.spi_dummyclocks_select.text(),16)
            self.cmd.spi.direction = self.spi_direction_select.currentData()
            print("SPI Bus:", self.cmd.spi.bus)
            print("SPI Clock:",self.cmd.spi.clock)
            print("SPI Cmd:",self.cmd.spi.command)
            print("SPI Dummy:",self.cmd.spi.dummyclocks)
            print("SPI Dir:",self.cmd.spi.direction)

        elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
            self.cmd.gpio.port = self.gpio_port_select.currentData()
            if sequence.is_empty(self.gpio_pin_select.text()):
                self.cmd.gpio.pin = 0                                  # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
            else:
                self.cmd.gpio.pin = int(self.gpio_pin_select.text())
            self.cmd.gpio.direction = self.gpio_direction_select.currentData()
            self.cmd.gpio.pinState = self.gpio_state_select.currentData()
            print("GPIO port:", self.cmd.gpio.port)
            print("GPIO pin:", self.cmd.gpio.pin)
            print("GPIO dir:",self.cmd.gpio.direction)
            print("GPIO state:",self.cmd.gpio.pinState)

        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
            self.cmd.analog_in.port = self.gpio_port_select.currentData()
            if self.gpio_pin_select.isEnabled():
                if sequence.is_empty(self.gpio_pin_select.text()):
                    self.cmd.analog_in.pin = 0                                  # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
                else:
                    self.cmd.analog_in.pin = int(self.gpio_pin_select.text())
            else:
                self.cmd.analog_in.pin = 0
            self.cmd.analog_in.resolution = self.adc_resolution_select.currentData()
            print("GPIO port:", self.cmd.analog_in.port)
            print("GPIO pin:", self.cmd.analog_in.pin)
            print("ADC resolution:",self.cmd.analog_in.resolution)

        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
            self.cmd.analog_out.port = self.gpio_port_select.currentData()
            if sequence.is_empty(self.gpio_pin_select.text()):
                self.cmd.analog_out.pin = 0                                  # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
            else:
                self.cmd.analog_out.pin = int(self.gpio_pin_select.text())
            if sequence.is_empty(self.pwm_freq_select.text()):
                self.cmd.analog_out.frequency = 0                                  # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
            else:
                self.cmd.analog_out.frequency= int(self.pwm_freq_select.text())
            if sequence.is_empty(self.pwm_duty_select.text()):
                self.cmd.analog_out.dutyCycle = 0                                  # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
            else:
                self.cmd.analog_out.dutyCycle = int(self.pwm_duty_select.text())
            print("GPIO port:", self.cmd.analog_out.port)
            print("GPIO pin:", self.cmd.analog_out.pin)
            print("PWM Freq",self.cmd.analog_out.frequency)
            print("PWM Duty",self.cmd.analog_out.dutyCycle)

        elif cmdType == functional_test_pb2.CommandTypeEnum.LED_test:
            print("LED test")
#            self.cmd.commandType = 6


    # Get number of response bytes depending on command type
    def read_data_depending_on_cmd_type(self, cmdType):
        print("Read data depending on cmd type:",cmdType)
        if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
            response_num = 5        # Frame:2, CmdType: 1+1, Result: 1 (register value)
                                    # Frame:2, CmdType:1+1, Result: 1 (Write_successful/failed)
        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            response_num = 5        # Frame:2, CmdType: 1+1, Result: 1 (register value)
                                    # Frame:2, CmdType:1+1, Result: 1 (Write_successful/failed)
        elif cmdType == functional_test_pb2.CommandTypeEnum.LED_test:
            response_num = 4        # Frame:2, CmdType: 1+1
        elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
            response_num = 5    # Frame:2, CmdType: 1+1, Result: 1 (pin state) ---- ide is inkabb pin config set kene
                                # Frame:2, CmdType:1+1, Result: 1 (pin set/reset)
        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
            response_num = 6    # Frame:2, CmdType: 1+1, Result: 2 (16bit value)
        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
            response_num = 6    # Frame:2, CmdType: 1+1, Result: 1 (Write_successful/failed)
        else:
            response_num = 0


        print("response_num:", response_num)
        if response_num > 0:
            response_data = self.ser.read(response_num)
            self.LL.link_unframe_data(response_data)
            response_list = []
            for i in self.LL.rx_buffer:
                i = format(i,'02X')
                response_list.append(i)
            response = ' '.join(str(e) for e in response_list)
            return response


#            last_widget = scroll_layout.itemAt(scroll_layout.count()-1).widget()
#            print(last_widget)
#            QtCore.QTimer.singleShot(0, partial(scroll.ensureWidgetVisible, last_widget))
#            self.show()
#            vbar = self.scrollArea.verticalScrollBar()
#            vbar.setValue(vbar.maximum())
#            self.show()
#            self.scrollArea.ensureWidgetVisible(label)
#            vbar = self.scrollArea.verticalScrollBar()
#            vbar.setValue(vbar.maximum())



    # Create protocol buffer encoded command
    def create_protobuf_command(self):
        self.cmd = functional_test_pb2.Command()
        self.cmd.commandType = self.cmd_box.currentData()
        self.add_data_depending_on_cmd_type(self.cmd.commandType)
        return self.cmd.SerializeToString()


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
            self.ser = serial.Serial(port=port_field, baudrate=speed, bytesize=8, parity='N', stopbits=1, timeout=0.2)
            self.ser.setDTR(1)
            is_port_open = 'Port open'
            self.connect_button.setEnabled(False)
            self.close_button.setEnabled(True)
        except serial.serialutil.SerialException:
            is_port_open = 'Error opening port'
#            self.connection_output.setStyleSheet('color: red')
        self.connection_output.setText(is_port_open)

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
        self.connection_output.setText(is_port_open)

    # Serialize command and options, then send out data via UART
    def send_command(self):
        pb = self.create_protobuf_command()    # make command
        self.LL.link_frame_data(pb)            # frame data
        print("TxBuffer: ",self.LL.tx_buffer)
        try:
            self.ser.write(self.LL.tx_buffer)
            command_send_success = 'Command sent'
            response = "Response: " + self.read_data_depending_on_cmd_type(self.cmd_box.currentData())
            responseLabel = QLabel(response)
            self.scroll_layout.addWidget(responseLabel)
        except serial.serialutil.SerialException:
            if self.ser.is_open:
                command_send_success = 'Error while sending command'
            else:
                command_send_success = 'Port is not open'
        self.cmd_output.setText(command_send_success)




if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
