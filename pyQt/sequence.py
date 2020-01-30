#    Python file for sequence builder - test object and list handling
#    Author: Adam Golya
#   #######################################

import functional_test_pb2
import commands

# @Note: For value <-> string conversion lists are used.

#Function list:
#    make_test_object_from_options(UI)
#    delete_test_from_sequence(sequence, index)
#    move_up_test_in_sequence(sequence, index)
#    move_down_test_in_sequence(sequence,index)
#    make_string_from_test_object(test_object)
#    make_test_object_from_string(string)
#    add_test_object_to_test_list(test_object, test_list)
#    delete_test_list(test_list)
#    is_empty(field)
#    make_protobuf_command_from_test_object(test_object)




# @brief    List of strings for value <-> string conversion
list_cmd_types = ["I2C","SPI","GPIO","Analog_read","PWM"]
list_i2c_rw = ["Write","Read"]
list_i2c_bus = ["Invalid","I2C1","I2C2", "I2C3"]

list_spi_bus = ["Invalid","SPI1","SPI2", "SPI3"]
list_spi_mode = ["0", "1", "2", "3"]
list_spi_rw = ["Transmit","Receive"]

list_gpio_rw = ["Output","Input"]
list_gpio_state = ["Low", "High"]
list_gpio_pins = ["PA0","PA1","PA4","PA5", "PA6", "PA7","PB0","PB1", "PC0", "PC1","PC2","PC3", "PC4", "PC5","Temp","Vrefint", "Vbat"]

list_adc_res = ["12 bits", "10 bits", "8 bits", "6 bits"]


# @rief     Classes that represent the tests
class i2c_test:
    def __init__(self, cmdType = None, bus = None, address = None, register = None, rw = None):
        self.cmdType = cmdType
        self.bus = bus
        self.address = address
        self.register = register
        self.rw = rw

class spi_test:
    def __init__(self, cmdType = None, bus = None, mode = None, command = None, dummyclocks = None, direction = None):
        self.cmdType = cmdType
        self.bus = bus
        self.mode = mode
        self.command = command
        self.dummyclocks = dummyclocks
        self.direction = direction

class gpio_digital:
    def __init__(self, cmdType = None, pin = None, direction = None, state = None):
        self.cmdType = cmdType
        self.pin = pin
        self.direction = direction
        self.state = state

class analog_read:
    def __init__(self, cmdType = None, pin = None, resolution = None):
        self.cmdType = cmdType
        self.pin = pin
        self.resolution = resolution

class analog_write:
    def __init__(self, cmdType = None, pin = None, frequency = None, dutyCycle = None):
        self.cmdType = cmdType
        self.pin = pin
        self.frequency = frequency
        self.dutyCycle = dutyCycle



# @brief        Make test objects from the selected options and add it to test_list.
# @param[in]    UI: user interface (e.g. MyWindow class)
# @return       test_object: created from the selected command options
def make_test_object_from_options(UI):
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
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

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
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

    elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        selectedCommand = gpio_digital()
        selectedCommand.cmdType = cmdType
        selectedCommand.pin = UI.gpio_pin_select.currentData()
        selectedCommand.direction = UI.gpio_direction_select.currentData()
        selectedCommand.state = UI.gpio_state_select.currentData()
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        selectedCommand = analog_read()
        selectedCommand.cmdType = cmdType
        selectedCommand.pin = UI.gpio_pin_select.currentData()
        selectedCommand.resolution = UI.adc_resolution_select.currentData()
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        selectedCommand = analog_write()
        selectedCommand.cmdType = cmdType
        selectedCommand.pin = UI.gpio_pin_select.currentData()
        if is_empty(UI.pwm_freq_select.text()):
            selectedCommand.frequency = 0                               # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
        else:
            selectedCommand.frequency = int(UI.pwm_freq_select.text())
        if is_empty(UI.pwm_duty_select.text()):
            selectedCommand.dutyCycle = 0                               # !!!!!! IDE egy flaget ami jelzi h empty, es hibat dob, ne engedje kikuldeni
        else:
            selectedCommand.dutyCycle = int(UI.pwm_duty_select.text())
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)


# @brief            Delete test object from test_list on given index
# @param[in,out]    test_list
# @param[in]        index
def delete_test_object_from_test_list(test_list, index):
    del test_list[index]


# @brief            Move up test object in test_list (move to front / decrease index)
# @param[in,out]    test_list
# @param[in]        index
def move_up_test_in_sequence(test_list, index):
    if index > 0:       # Watch out for upper limit
        test_list[index], test_list[index-1] = test_list[index-1], test_list[index]
    else:
        print('Error! Index out of range!')


# @brief            Move down test object in test_list (move to back / increase index)
# @param[in,out]    test_list
# @param[in]        index
def move_down_test_in_sequence(test_list,index):
    lastIndex = len(test_list) - 1
    if index < lastIndex:   # Watch out for lower limit
      test_list[index], test_list[index+1] = test_list[index+1], test_list[index]
    else:
        print('Error! Index out of range!')


# @brief        Make string from test object
# @param[in]    test_object
# @return       string
def make_string_from_test_object(test_object):
    string = ""
    if test_object.cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
        string += "I2C"
        string += "  Bus: " + list_i2c_bus[test_object.bus]
        string += "  Addr: " + "0x{:02X}".format(test_object.address)
        string += "  Reg: " + "0x{:02X}".format(test_object.register)
        string += "  R/W: " + list_i2c_rw[test_object.rw]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        string += "SPI"
        string += "  Bus: " + list_spi_bus[test_object.bus]
        string += "  Mode: " + str(test_object.mode)
        string += "  Cmd: " + "0x{:02X}".format(test_object.command)
        string += "  Dummy: " + str(test_object.dummyclocks)
        string += "  R/W: " + list_spi_rw[test_object.direction]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        string += "GPIO"
        string += "  Pin: " + list_gpio_pins[test_object.pin]
        string += "  R/W: " + list_gpio_rw[test_object.direction]
        string += "  State: " + list_gpio_state[test_object.state]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        string += "Analog_read"
        string += "  Pin: " + list_gpio_pins[test_object.pin]
        string += "  Res: " + list_adc_res[test_object.resolution]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        string += "PWM"
        string += "  Pin: " + list_gpio_pins[test_object.pin]
        string += "  Freq: " + str(test_object.frequency)
        string += "  Duty: " + str(test_object.dutyCycle)

    return string


# @brief        Make test object from string line: split words using a double space separator. Attach only the relevant string parts to object parameters.
# @details      Lists are used to find the indexes (enum values in .proto) of strings.
# @param[in]    string
# @return       test_object
def make_test_object_from_string(string):
    words = string.split("  ")
    if words[0] == list_cmd_types[0]:
        test_object = i2c_test()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.I2C_test
        test_object.bus = list_i2c_bus.index( words[1][5:]) # Get relevant part of string and find index in list. The same number is defined as enum in .proto
        test_object.address = int(words[2][6:],16)
        test_object.register = int(words[3][5:],16)
        test_object.rw = list_i2c_rw.index(words[4][5:])
        return test_object
#        print("Test object:")
#        print("cmd:",test_object.cmdType)
#        print("bus:",test_object.bus)
#        print("address:",test_object.address)
#        print("register:",test_object.register)
#        print("rw:",test_object.rw)
    elif words[0] == list_cmd_types[1]:
        test_object = spi_test()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.SPI_test
        test_object.bus = list_spi_bus.index( words[1][5:]) # Get relevant part of string and find index in list. The same number is defined as enum in .proto
        test_object.mode = list_spi_mode.index(words[2][6:])
        test_object.command = int(words[3][7:],16)
        test_object.dummyclocks = int(words[4][7:])
        test_object.direction = list_spi_rw.index(words[5][5:])
        return test_object
#        print("Test object: ")
#        print("cmd:",test_object.cmdType)
#        print("bus:",test_object.bus)
#        print("mode:",test_object.mode)
#        print("cmd:",test_object.command)
#        print("dum:", test_object.dummyclocks)
#        print("rw:",test_object.direction)
    elif words[0] == list_cmd_types[2]:
        test_object = gpio_digital()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.GPIO_digital
        test_object.pin = list_gpio_pins.index(words[2][5:])
        test_object.direction = list_gpio_rw.index(words[3][5:])
        test_object.state = list_gpio_state.index(words[4][7:])
        return test_object
#        print("Test object: ")
#        print("cmd:",test_object.cmdType)
#        print("pin:",test_object.pin)
#        print("rw:",test_object.direction)
#        print("state:", test_object.state)
    elif words[0] == list_cmd_types[3]:
        test_object = analog_read()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.Analog_read
        test_object.pin = list_gpio_pins.index(words[2][5:])
        test_object.resolution = list_adc_res.index(words[3][5:])
        return test_object
#        print("Test object:")
#        print("cmd:",test_object.cmdType)
#        print("pin:",test_object.pin)
#        print("Res:",test_object.resolution)
    elif words[0] == list_cmd_types[4]:
        test_object = analog_write()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.Analog_write
        test_object.pin = list_gpio_pins.index(words[2][5:])
        test_object.frequency = int(words[3][6:])
        test_object.dutyCycle = int(words[4][6:])
        return test_object
#        print("Test object:")
#        print("cmd:",test_object.cmdType)
#        print("pin:",test_object.pin)
#        print("Res:",test_object.frequency)
#        print("Freq:",test_object.dutyCycle)


# @brief        Make protobuf command from test object
# @param[in]    test_object
# @return       Encoded message
def make_protobuf_command_from_test_object(test_object):
    cmd = functional_test_pb2.Command()
    cmd.commandType = test_object.cmdType

    if test_object.cmdType == functional_test_pb2.CommandTypeEnum.I2C_test:
        cmd.i2c.bus = test_object.bus
        cmd.i2c.address = test_object.address
        cmd.i2c.reg = test_object.register
        cmd.i2c.direction = test_object.rw

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        cmd.spi.bus = test_object.bus
        cmd.spi.clock = test_object.mode
        cmd.spi.command = test_object.command
        cmd.spi.dummyclocks = test_object.dummyclocks
        cmd.spi.direction = test_object.direction

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        cmd.gpio.pin = test_object.pin
        cmd.gpio.direction = test_object.direction
        cmd.gpio.pinState = test_object.state

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        cmd.analog_in.pin  = test_object.pin
        cmd.analog_in.resolution = test_object.resolution

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        cmd.analog_out.pin = test_object.pin
        cmd.analog_out.frequency = test_object.frequency
        cmd.analog_out.dutyCycle = test_object.dutyCycle

    return cmd.SerializeToString()


# @brief            Add test object to test list
# @param[in]        test_object
# @param[in,out]    test_list
def add_test_object_to_test_list(test_object, test_list):
    test_list.append(test_object)


# @brief            Delete sequence: clear list
# @param[in,out]    test_list
def delete_test_list(test_list):
    test_list.clear()


# @brief        Check whether input field is empty
# @param[in]    field: input field
# @return       True: if field is empty
def is_empty(field):
    if field == "":
        return True

