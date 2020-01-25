#    Python file for sequence builder - list handling
#    Author: Adam Golya
#   #######################################

import functional_test_pb2
import commands


#gTabSize = 0
# TODO: Ha a port/pint kijavitjuk stm.py-ban meg .protoban, akkor majd itt is !!!!!

class i2c_test:
    def __init__(self, cmdType = None, bus = None, address = None, register = None, rw = None):
        self.cmdType = cmdType
        self.bus = bus
        self.address = address
        self.register = register
        self.rw = rw
#    def diplay(self):
## Dictionary alapjan adni egy str objektumot
#        return print_object = "asd"


class spi_test:
    def __init__(self, cmdType = None, bus = None, mode = None, command = None, dummyclocks = None, direction = None):
        self.cmdType = cmdType
        self.bus = bus
        self.mode = mode
        self.command = command
        self.dummyclocks = dummyclocks
        self.direction = direction

class gpio_digital:
    def __init__(self, cmdType = None, port = None, pin = None, direction = None, state = None):
        self.cmdType = cmdType
        self.port = port
        self.pin = pin
        self.direction = direction
        self.state = state

class analog_read:
    def __init__(self, cmdType = None,  port = None, pin = None, resolution = None):
        self.cmdType = cmdType
        self.port = port
        self.pin = pin
        self.resolution = resolution

class analog_write:
    def __init__(self, cmdType = None,  port = None, pin = None, frequency = None, dutyCycle = None):
        self.cmdType = cmdType
        self.port = port
        self.pin = pin
        self.frequency = frequency
        self.dutyCycle = dutyCycle


#def add_test_using_cmd_options(UI, test_list):
#    cmdType = UI.cmd_box.currentData()
#    if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
#        test_list.append( )


#    elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
#    elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
#    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
#    elif cmdType == functional_test_pb2.CommandTypeEnum.analog_write:



# Add test to sequence list
def add_test_to_sequence(UI, sequence):
    cmdType = UI.cmd_box.currentData()

    if cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
        selectedCommand = i2c_test()
        selectedCommand.cmdType = cmdType
        selectedCommand.bus = UI.i2c_bus_select.currentData()
        if is_empty(UI.i2c_addr_select.text()):
            selectedCommand.address = 0
        else:
            selectedCommand.address = int(UI.i2c_addr_select.text(),16)      # Convert to int
        if is_empty(UI.i2c_reg_select.text()):
            selectedCommand.register = 0
        else:
            selectedCommand.register = int(UI.i2c_reg_select.text(),16)           # Convert to int
        selectedCommand.rw = UI.i2c_rw_select.currentData()
        sequence.append(selectedCommand)

    elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        selectedCommand = spi_test()
        selectedCommand.cmdType = cmdType
        selectedCommand.bus = UI.spi_bus_select.currentData()
        selectedCommand.mode = UI.spi_clockmode_select.currentData()
        if is_empty(UI.spi_command_select.text()):
            selectedCommand.command = 0
        else:
            selectedCommand.command = int(UI.spi_command_select.text(),16)
        if is_empty(UI.spi_dummyclocks_select.text()):
            selectedCommand.dummyclocks = 0
        else:
            selectedCommand.dummyclocks = int(UI.spi_dummyclocks_select.text())
        selectedCommand.direction = UI.spi_direction_select.currentData()
        sequence.append(selectedCommand)

    elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        selectedCommand = gpio_digital()
        selectedCommand.cmdType = cmdType
        selectedCommand.port = UI.gpio_port_select.currentData()
        if is_empty(UI.gpio_pin_select.text()):
            selectedCommand.pin = 0                               # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
        else:
            selectedCommand.pin = int(UI.gpio_pin_select.text())
        selectedCommand.direction = UI.gpio_direction_select.currentData()
        selectedCommand.state = UI.gpio_state_select.currentData()
        sequence.append(selectedCommand)

    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        selectedCommand = analog_read()
        selectedCommand.cmdType = cmdType
        selectedCommand.port = UI.gpio_port_select.currentData()
        if is_empty(UI.gpio_pin_select.text()):
            selectedCommand.pin = 0                               # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
        else:
            selectedCommand.pin = int(UI.gpio_pin_select.text())
        selectedCommand.resolution = UI.adc_resolution_select.currentData()
        sequence.append(selectedCommand)

    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        selectedCommand = analog_write()
        selectedCommand.cmdType = cmdType
        selectedCommand.port = UI.gpio_port_select.currentData()
        if is_empty(UI.gpio_pin_select.text()):
            selectedCommand.pin = 0                               # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
        else:
            selectedCommand.pin = int(UI.gpio_pin_select.text())
        if is_empty(UI.pwm_freq_select.text()):
            selectedCommand.frequency = 0                               # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
        else:
            selectedCommand.frequency = int(UI.pwm_freq_select.text())
        if is_empty(UI.pwm_duty_select.text()):
            selectedCommand.dutyCycle = 0                               # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
        else:
            selectedCommand.dutyCycle = int(UI.pwm_duty_select.text())
        sequence.append(selectedCommand)
        print(selectedCommand.dutyCycle)

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

def make_string_from_test_object(test_object):
    string = ""
    if test_object.cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
        string += "I2C"
        string += "  BUS" + str(test_object.bus)
        string += "  Addr: " + "0x{:02X}".format(test_object.address)
        string += "  Reg: " + "0x{:02X}".format(test_object.register)
        string += "  R/W: " + rw_i2c_string_from_value(test_object.rw)

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        string += "SPI"
        string += "  BUS" + str(test_object.bus)
        string += "  Mode: " + str(test_object.mode)
        string += "  Cmd: " + "0x{:02X}".format(test_object.command)
        string += "  Dummy: " + str(test_object.dummyclocks)
        string += "  R/W: " + rw_spi_string_from_value(test_object.direction)

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        string += "GPIO"
        string += "  Port: " + str(test_object.port)
        string += "  Pin: " + str(test_object.pin)
        string += "  R/W: " + rw_gpio_string_from_value(test_object.direction)
        string += "  State: " + state_gpio_string_from_value(test_object.state)

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        string += "Analog_read"
        string += "  Port: " + str(test_object.port)
        string += "  Pin: " + str(test_object.pin)
        string += "  Res: " + res_adc_string_from_value(test_object.resolution)

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        string += "PWM"
        string += "  Port: " + str(test_object.port)
        string += "  Pin: " + str(test_object.pin)
        string += "  Freq: " + str(test_object.frequency)
        string += "  Duty: " + str(test_object.dutyCycle)

    return string


#def load_and_print_sequence:
#    print('TODO')

#        load_sequence: QFileDialog, betoltes .txt, pl /t-vel splitelve es listat csinalva belole
#   https://www.tutorialspoint.com/pyqt/pyqt_qfiledialog_widget.htm
#   setText(): beállítás

#  Delete sequence: clear list
def delete_sequence(sequence):
    sequence.clear()

#def display_sequence_item:
#    print('TODO')


#        send_sequence: create_command_from_sequence_row:
#            for ciklus a listan
#            osszes ID-n vegigmegy
#                uj Command
#                cmdType-ot hozzadja
#                tobbi adatot ettol fuggoen adja hozza
#                send_command

def is_empty(field):
    if field == "":
        return True


def rw_i2c_string_from_value(value):
    str = ""
    if value == 0:
        str = "Write"
    elif value == 1:
        str = "Read"
    else:
        str = "Error"
    return str


def rw_spi_string_from_value(value):
    str = ""
    if value == 0:
        str = "Transmit"
    elif value == 1:
        str = "Receive"
    else:
        str = "Error"
    return str

def rw_gpio_string_from_value(value):
    str = ""
    if value == 0:
        str = "Input"
    elif value == 1:
        str = "Output"
    else:
        str = "Error"
    return str

def state_gpio_string_from_value(value):
    str = ""
    if value == 0:
        str = "Low"
    elif value == 1:
        str = "High"
    else:
        str = "Error"
    return str


def res_adc_string_from_value(value):
    str = ""
    if value == 0:
        str = "12 bits"
    elif value == 1:
        str = "10 bits"
    elif value == 2:
        str = "8 bits"
    elif value == 3:
        str = "6 bits"
    else:
        str = "Error"
    return str
