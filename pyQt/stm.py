import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import QComboBox
from decimal import Decimal

import serial
import functional_test_pb2
from link_layer import link_layer

import time

qtcreator_file  = "D:/Work/dipterv/pyQt/stm_gui.ui" # Enter file here.
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtcreator_file)

ser = serial.Serial()


class MyWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)
        self.connect_button.clicked.connect(self.connect)
        self.command_button.clicked.connect(self.send_command)
        self.close_button.clicked.connect(self.close_port)
        self.fill_cmd_box()
        self.cmd_box.activated[str].connect(self.onChanged)

    def __call__(self):
        return self        

    def fill_cmd_box(self):
        self.cmd_box.addItem("LED_test",functional_test_pb2.CommandTypeEnum.LED_test)
        self.cmd_box.addItem("I2C_test",functional_test_pb2.CommandTypeEnum.I2C_test)

    def onChanged(self,text):
        # Ha I2C akkor jelenjenek meg ujabb input mezok stb
#        self.qlabel.setText(text)
        print(self.cmd_box.currentData())
        self.show()

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

    def send_command(self):
        global ser
        cmd = functional_test_pb2.Command()
        cmd.commandType = self.cmd_box.currentData()
#        print(cmd.commandType)
        pb = cmd.SerializeToString()
        LL = link_layer()
        LL.link_frame_data(pb)   # frame data
        print(LL.tx_buffer)
        try:
            ser.write(LL.tx_buffer)
            command_send_success = 'Command sent'
            response_data = ser.read(4)
            LL.link_unframe_data(response_data)
            response_list = []
            for i in LL.rx_buffer:
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
        self.command_output.setText(command_send_success)


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
    
