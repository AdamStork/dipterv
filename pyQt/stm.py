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

ser = serial.Serial()

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
        self.LL = link_layer()

    def __call__(self):
        return self

    # Fill combobox with commands
    def fill_cmd_box(self):
        self.cmd_box.addItem("STOP_CURRENT_TEST",functional_test_pb2.CommandTypeEnum.STOP_CURRENT_TEST)
        self.cmd_box.addItem("ADC_test",functional_test_pb2.CommandTypeEnum.ADC_test)
        self.cmd_box.addItem("I2C_test",functional_test_pb2.CommandTypeEnum.I2C_test)
        self.cmd_box.addItem("SPI_test",functional_test_pb2.CommandTypeEnum.SPI_test)
        self.cmd_box.addItem("LED_test",functional_test_pb2.CommandTypeEnum.LED_test)
        self.cmd_box.addItem("GPIO_test",functional_test_pb2.CommandTypeEnum.GPIO_test)
        self.cmd_box.addItem("TIMER_SINGLE_SHOT",functional_test_pb2.CommandTypeEnum.TIMER_SINGLE_SHOT)
        self.cmd_box.addItem("RTC_test",functional_test_pb2.CommandTypeEnum.RTC_test)
        self.cmd_box.addItem("PWM_test",functional_test_pb2.CommandTypeEnum.PWM)

    # Called whenever a command is selected
    def on_changed(self,text):
        print("CmdType:",self.cmd_box.currentData())
        self.delete_all_child_widget(self.options_layout)
        self.show_data_depending_on_cmd_type(self.cmd_box.currentData())
        self.show()

    def on_changed_rw(self):
        print("R/W selection:", self.i2c_rw_select.currentData())

    # Show data depending on the command type selected
    def show_data_depending_on_cmd_type(self,cmdType):
        if cmdType == functional_test_pb2.CommandTypeEnum.LED_test:
            print("LED options")
            if self.LED_active == False:
                self.LED_active = True
                self.led_label = QLabel("Label test", self)
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
                self.i2c_rw_select.activated[str].connect(self.on_changed_rw)
                validator = QRegExpValidator(QRegExp("0x[0-9A-Fa-f][0-9A-Fa-f]"))
                self.i2c_addr_select.setValidator(validator)
                self.i2c_reg_select.setValidator(validator)
                self.i2c_addr_select.setPlaceholderText("0xFF")
                self.i2c_reg_select.setPlaceholderText("0xFF")
                self.options_layout.addWidget(self.i2c_bus_label,0,0)
                self.options_layout.addWidget(self.i2c_addr_label,1,0)
                self.options_layout.addWidget(self.i2c_reg_label,2,0)
                self.options_layout.addWidget(self.i2c_rw_label,3,0)
                self.options_layout.addWidget(self.i2c_bus_select,0,2)
                self.options_layout.addWidget(self.i2c_addr_select,1,2)
                self.options_layout.addWidget(self.i2c_reg_select,2,2)
                self.options_layout.addWidget(self.i2c_rw_select,3,2)

        elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
            print("SPI options")

    # Delete all child widget from a layout
    def delete_all_child_widget(self, layout):
        for i in reversed(range(layout.count())):
            layout.itemAt(i).widget().setParent(None)
        self.LED_active = False
        self.I2C_active = False

    # Add data depending on command type
    def add_data_depending_on_cmd_type(self, cmdType):
        print("Add data depending on cmd type")
        if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
            self.cmd.i2c.bus = self.i2c_bus_select.currentData()
            self.cmd.i2c.address = int(self.i2c_addr_select.text(),16)      # Convert to int
            self.cmd.i2c.reg = int(self.i2c_reg_select.text(),16)           # Convert to int
            self.cmd.i2c.direction = self.i2c_rw_select.currentData()
#            print("addr:", self.cmd.i2c.address)
#            print("reg:", self.cmd.i2c.reg)

    # Read data depending on command type
    def read_data_depending_on_cmd_type(self, cmdType):
        print("Read data depending on cmd type")

    # Create protocol buffer encoded command
    def create_protobuf_command(self):
        self.cmd = functional_test_pb2.Command()
        self.cmd.commandType = self.cmd_box.currentData()
        self.add_data_depending_on_cmd_type(self.cmd.commandType)
        return self.cmd.SerializeToString()


    # Connect to a serial port
    def connect(self):
        try:
            global ser
            ser = serial.Serial(port='COM9', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=1)
            ser.setDTR(1)
            is_port_open = 'Port open'
        except serial.serialutil.SerialException:
            if ser.is_open:
                is_port_open = 'Port is already open'
            else:
                is_port_open = 'Error opening port'
        self.connection_output.setText(is_port_open)

    # Close serial port
    def close_port(self):
        if ser.is_open:
            try:
                ser.close()
                is_port_open = 'Port closed'
            except serial.serialutil.SerialException:
                is_port_open = 'Error closing port'
        else:
            is_port_open = 'Port is not open'
        self.connection_output.setText(is_port_open)

    # Serialize command and options, then send out data via UART
    def send_command(self):
        global ser
        pb = self.create_protobuf_command()    # make command
        self.LL.link_frame_data(pb)            # frame data
        print("TxBuffer: ",self.LL.tx_buffer)
        try:
            ser.write(self.LL.tx_buffer)
            command_send_success = 'Command sent'
            # Bajtszam beolvasas attol fugg --> read_data_depending_on_cmd_type - return: bajtszam,
            # csak ha nagyobb mint 0
            response_data = ser.read(4)
            self.LL.link_unframe_data(response_data)
            response_list = []
            for i in self.LL.rx_buffer:
                i = format(i,'02X')
                response_list.append(i)
            str1 = ' '.join(str(e) for e in response_list)
            self.response_output.setText(str1)
#ParseFromString()
        except serial.serialutil.SerialException:
            if ser.is_open:
                command_send_success = 'Error while sending command'
            else:
                command_send_success = 'Port is not open'
        self.cmd_output.setText(command_send_success)




if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
