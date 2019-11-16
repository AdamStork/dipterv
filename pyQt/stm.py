import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from decimal import Decimal

import serial
import functional_test_pb2

qtcreator_file  = "stm_gui.ui" # Enter file here.
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtcreator_file)

ser = serial

class MyWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)
        self.connect_button.clicked.connect(self.connect)
        self.command_button.clicked.connect(self.send_command)
    def connect(self):
        try:
            ser = serial.Serial(port='COM9', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=0)
            is_port_open = 'Port open' 
        except serial.serialutil.SerialException:         
            is_port_open = 'Error opening port'
        self.connection_output.setText(is_port_open)
    def send_command(self):
        ser.write(pb)

def initialize_pb(void):
    

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())

