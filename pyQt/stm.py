import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from decimal import Decimal

import serial
import functional_test_pb2
from link_layer import link_layer

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

    def __call__(self):
        return self        

    def connect(self):
        try:
            global ser
            ser = serial.Serial(port='COM9', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=0)
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
        cmd.commandType = functional_test_pb2.CommandTypeEnum.LED_test
        pb = cmd.SerializeToString()
        LL = link_layer()
        LL.link_send_data(pb)   # frame data
        print(LL.tx_buffer)
        try:
            ser.write(LL.tx_buffer)
            command_send_success = 'Command sent'
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
    
