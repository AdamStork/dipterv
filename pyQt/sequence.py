#    Python file for sequence builder
#    Author: Adam Golya
#   #######################################

import functional_test_pb2
import commands

# TODO: Ha a port/pint kijavitjuk stm.py-ban meg .protoban, akkor majd itt is !!!!!

class i2c_test:
    def __init__(self, cmdType, bus, address, register, rw):
        self.cmdType = cmdType
        self.bus = bus
        self.address = address
        self.register = register
        self.rw = rw
    def diplay(self):
# Dictionary alapjan adni egy str objektumot
        return print_object = "asd"


class spi_test:
    def __init__(self, cmdType, bus, mode, command, dummyclocks, direction):
        self.cmdType = cmdType
        self.bus = bus
        self.mode = mode
        self.command = command
        self.dummyclocks = dummyclocks
        self.direction = direction

class gpio_digital:
    def __init__(self, cmdType, port, pin, direction, state):
        self.cmdType = cmdType
        self.port = port
        self.pin = pin
        self.direction = direction
        self.state = state

class analog_read:
    def __init__(self, cmdType,  port, pin, resolution):
        self.cmdType = cmdType
        self.port = port
        self.pin = pin
        self.resolution = resolution

class analog_write:
    def __init__(self, cmdType,  port, pin, frequency, dutyCycle):
        self.cmdType = cmdType
        self.port = port
        self.pin = pin
        self.frequency = frequency
        self.dutyCycle = dutyCycle


# Add test to sequence
def add_test_to_sequence(sequence, selectedCommand):
    if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
        sequence.append( i2c_test(selectedCommand.cmdType, selectedCommand.bus, selectedCommand.address, selectedCommand.register, selectedCommand.rw) )
    elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        sequence.append( spi_test(selectedCommand.cmdType, selectedCommand.bus, selectedCommand.mode, selectedCommand.command, selectedCommand.dummyclocks, selectedCommand.direction) )
    elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        sequence.append( gpio_digital(selectedCommand.cmdType, selectedCommand.port, selectedCommand.pin, selectedCommand.direction, selectedCommand.state) )
    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        sequence.append( analog_read(selectedCommand.cmdType, selectedCommand.port, selectedCommand.pin, selectedCommand.resolution) )
    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        sequence.append( analog_write(selectedCommand.cmdType, selectedCommand.port, selectedCommand.pin, selectedCommand.frequency, selectedCommand.dutyCycle)) )

# Delete test from sequence
def delete_test_from_sequence(sequence, index):
    del sequence[index]

# Move up test in sequence (move to front / decrease index)
def move_up_test_in_sequence(sequence, index):
    if index > 0:       # Watch out for upper limit
        sequence[index], sequence[index-1] = sequence[index-1], sequence[index]
    else:
        print('Error! Index out of range!')

# Move down test in sequence (move to back / increase index)
def move_down_test_in_sequence(sequence,index):
    lastIndex = len(sequence) - 1
    if index < lastIndex:   # Watch out for lower limit
      sequence[index], sequence[index+1] = sequence[index+1], sequence[index]
    else:
        print('Error! Index out of range!')

def split_and_save_sequence:
    print('TODO')
#        save_sequence: QFileDialog, elmentes .txt, pl /t-vel elvalasztva


def load_and_print_sequence:
    print('TODO')

#        load_sequence: QFileDialog, betoltes .txt, pl /t-vel splitelve es listat csinalva belole
#   https://www.tutorialspoint.com/pyqt/pyqt_qfiledialog_widget.htm
#   setText(): beállítás

#  Delete sequence: clear list
def delete_sequence(sequence):
    sequence.clear()

def display_sequence_item:
    print('TODO')


#        send_sequence: create_command_from_sequence_row:
#            for ciklus a listan
#            osszes ID-n vegigmegy
#                uj Command
#                cmdType-ot hozzadja
#                tobbi adatot ettol fuggoen adja hozza
#                send_command
