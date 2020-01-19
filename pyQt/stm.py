import time, os, sys, serial
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from decimal import Decimal

import functional_test_pb2
from link_layer import link_layer

ui_path = os.path.dirname(os.path.abspath(__file__))
Ui_MainWindow  = uic.loadUiType(os.path.join(ui_path, "stm_gui.ui"))[0]


class MyWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    # Initialization
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)
        self.connect_button.clicked.connect(self.connect)
        self.cmd_button.clicked.connect(self.send_command)
        self.close_button.clicked.connect(self.close_port)
        self.fill_cmd_box()
        self.cmd_box.activated[str].connect(self.on_changed)
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
        self.decValidator = QRegExpValidator(QRegExp("[0-9][0-9]")) # 2-digit decimal validator for input fields (0xhh format)
        self.gpioValidator = QRegExpValidator(QRegExp("[0-1][0-5]")) # 2-digit decimal validator for input fields (0xhh format)


    def __call__(self):
        return self

    # Fill combobox with commands
    def fill_cmd_box(self):
        self.cmd_box.addItem("LED test",functional_test_pb2.CommandTypeEnum.LED_test)
        self.cmd_box.addItem("I2C test",functional_test_pb2.CommandTypeEnum.I2C_test)
        self.cmd_box.addItem("SPI test",functional_test_pb2.CommandTypeEnum.SPI_test)
        self.cmd_box.addItem("GPIO digital",functional_test_pb2.CommandTypeEnum.GPIO_digital)
        self.cmd_box.addItem("Analog read",functional_test_pb2.CommandTypeEnum.Analog_read)
        self.cmd_box.addItem("PWM",functional_test_pb2.CommandTypeEnum.Analog_write)

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
                self.spi_direcion_label = QLabel("SPI direction", self)     # Needed for response (register value or write success)

                self.spi_bus_select = QComboBox(self)
                self.spi_clockmode_select = QComboBox(self)
                self.spi_command_select = QLineEdit(self)
                self.spi_dummyclocks_select = QLineEdit(self)
                self.spi_direcion_select = QComboBox(self)

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

                self.spi_direcion_select.addItem("Transmit",functional_test_pb2.spiDirection.SPI_TRANSMIT)
                self.spi_direcion_select.addItem("Receive",functional_test_pb2.spiDirection.SPI_RECEIVE)

                self.options_layout.addWidget(self.spi_bus_label,0,0)
                self.options_layout.addWidget(self.spi_clockmode_label,1,0)
                self.options_layout.addWidget(self.spi_command_label,2,0)
                self.options_layout.addWidget(self.spi_dummyclocks_label,3,0)
                self.options_layout.addWidget(self.spi_direcion_label,4,0)
                self.options_layout.addWidget(self.spi_bus_select,0,2)
                self.options_layout.addWidget(self.spi_clockmode_select,1,2)
                self.options_layout.addWidget(self.spi_command_select,2,2)
                self.options_layout.addWidget(self.spi_dummyclocks_select,3,2)
                self.options_layout.addWidget(self.spi_direcion_select,4,2)
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


#self.gridLayout.addItem(spacerItem, 1, 1, 1, 1)
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

        elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
            print("AnalogWrite_active optons")
            if self.AnalogWrite_active == False:
                self.AnalogWrite_active = True


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
            if is_empty(self.i2c_addr_select.text()):
                self.cmd.i2c.address = 0
            else:
                self.cmd.i2c.address = int(self.i2c_addr_select.text(),16)      # Convert to int
            if is_empty(self.i2c_reg_select.text()):
                self.cmd.i2c.reg = 0
            else:
                self.cmd.i2c.reg = int(self.i2c_reg_select.text(),16)           # Convert to int
            self.cmd.i2c.direction = self.i2c_rw_select.currentData()
#            print("addr:", self.cmd.i2c.address)
#            print("reg:", self.cmd.i2c.reg)

        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            self.cmd.spi.bus = self.spi_bus_select.currentData()
            self.cmd.spi.clock = self.spi_clockmode_select.currentData()
            if is_empty(self.spi_command_select.text()):
                self.cmd.spi.command = 0
            else:
                self.cmd.spi.command = int(self.spi_command_select.text(),16)
            if is_empty(self.spi_dummyclocks_select.text()):
                self.cmd.spi.dummyclocks = 0
            else:
                self.cmd.spi.dummyclocks = int(self.spi_dummyclocks_select.text(),16)
            self.cmd.spi.direction = self.spi_direcion_select.currentData()
            print("Bus:", self.cmd.spi.bus)
            print("Clock:",self.cmd.spi.clock)
            print("Cmd:",self.cmd.spi.command)
            print("Dummy:",self.cmd.spi.dummyclocks)
            print("Dir:",self.cmd.spi.direction)

        elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
            self.cmd.gpio.port = self.gpio_port_select.currentData()
            if is_empty(self.gpio_pin_select.text()):
                self.cmd.gpio.pin = 0                                  # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
            else:
                self.cmd.gpio.pin = int(self.gpio_pin_select.text())
            self.cmd.gpio.direction = self.gpio_direction_select.currentData()
            self.cmd.gpio.pinState = self.gpio_state_select.currentData()
            print("GPIO port:", self.cmd.gpio.port)
            print("GPIO pin:", self.cmd.gpio.pin)
            print("GPIO dir:",self.cmd.gpio.direction)
            print("GPIO state:",self.cmd.gpio.pinState)


    # Get number of response bytes depending on command type
    def read_data_depending_on_cmd_type(self, cmdType):
        print("Read data depending on cmd type:",cmdType)
        if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
            if self.i2c_rw_select == functional_test_pb2.i2cDirection.I2C_read:
                response_num = 5    # Frame:2, CmdType: 1+1, Result: 1 (register value)
            else:
                respone_num = 5     # Frame:2, CmdType:1+1, Result: 1 (Write_successful/failed)
        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            if self.spi_direcion_select ==functional_test_pb2.spiDirection.SPI_RECEIVE:
                response_num = 5    # Frame:2, CmdType: 1+1, Result: 1 (register value)
            else:
                response_num = 5    # Frame:2, CmdType:1+1, Result: 1 (Write_successful/failed)
        elif cmdType == functional_test_pb2.CommandTypeEnum.LED_test:
            response_num = 4        # Frame:2, CmdType: 1+1
        elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
            if self.gpio_direction_select ==functional_test_pb2.gpioDirection.GPIO_INPUT:
                response_num = 5    # Frame:2, CmdType: 1+1, Result: 1 (pin state) ---- ide is inkabb pin config set kene
            else:
                response_num = 5    # Frame:2, CmdType:1+1, Result: 1 (pin set/reset)
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
            str1 = ' '.join(str(e) for e in response_list)
            self.response_output.setText(str1)

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
            if is_empty(self.serial_line_field.text()):
                port_field = 'COM9'
            else:
               port_field = self.serial_line_field.text()
            if is_empty(self.speed_field.text()):
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
            self.read_data_depending_on_cmd_type(self.cmd_box.currentData())
        except serial.serialutil.SerialException:
            if self.ser.is_open:
                command_send_success = 'Error while sending command'
            else:
                command_send_success = 'Port is not open'
        self.cmd_output.setText(command_send_success)

def is_empty(field):
    if field == "":
        return True


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
