#    Python file for sequence builder - test object and list handling
#    Author: Adam Golya
#   #######################################

import functional_test_pb2

# @Note: For value <-> string conversion dictionaries are used, which are converted to lists during the key-value search.
#        The reason for this kind of storage is that the management of dictionaries are easy. (Adding, removing items, dynamic handling etc.)

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


# List of command types
list_cmd_types = ["I2C","SPI","USART","GPIO","Analog_read","PWM"]


# I2C dictionaries
dict_i2c_rw = {
    "Write": 0,
    "Read": 1
}

dict_i2c_bus = {
    "I2C1": 1,
    "I2C2": 2,
    "I2C3": 3
}

dict_i2c_speedmode = {
    "Standard": 0,
    "Fast": 1,
}

dict_i2c_duty_cycle = {
    "T_low/T_high = 2": 0,
    "T_low/T_high = 16/9": 1,
}


dict_spi_bus = {
    "SPI1": 1,
    "SPI2": 2,
    "SPI3": 3
}

dict_spi_mode = {
    "Mode 0": 0,
    "Mode 1": 1,
    "Mode 2": 2,
    "Mode 3": 3
}

dict_spi_operating_mode = {
    "Full Duplex Master": 0,
    "Half Duplex Master": 1,
    "Transmit Only Master": 2
}

dict_spi_frame_format = {
    "Motorola": 0,
    "TI": 1
}

dict_spi_data_size = {
    "8 bits": 0,
    "16 bits": 1,
}

dict_spi_hardware_nss = {
    "Disable": 0,
    "NSS Input": 1,
    "NSS Output": 2
}

dict_spi_first_bit = {
    "MSB first": 0,
    "LSB first": 1,
}

# GPIO dictionaries
dict_gpio_rw = {
    "Output": 0,
    "Input": 1
}

dict_gpio_state = {
    "Low": 0,
    "High": 1,
    "N/A": 2
}

dict_gpio_pull = {
    "No Pull": 0,
    "Pull-up": 1,
    "Pull-down": 2
}

dict_gpio_digital_pins = {
    "PA0": 0,
    "PA1": 1,
    "PA2": 2,
    "PA3": 3,
    "PA4": 4,
    "PA5": 5,
    "PA6": 6,
    "PA7": 7,
    "PA8": 8,
    "PA9": 9,
    "PA10": 10,
    "PA11": 11,
    "PA12": 12,
    "PA13": 13,
    "PA14": 14,
    "PA15": 15,
    "PB0": 20,
    "PB1": 21,
    "PB2": 22,
    "PB3": 23,
    "PB4": 24,
    "PB5": 25,
    "PB6": 26,
    "PB7": 27,
    "PB8": 28,
    "PB9": 29,
    "PB10": 30,
    "PB11": 31,
    "PB12": 32,
    "PB13": 33,
    "PB14": 34,
    "PB15": 35,
    "PC0": 40,
    "PC1": 41,
    "PC2": 42,
    "PC3": 43,
    "PC4": 44,
    "PC5": 45,
    "PC6": 46,
    "PC7": 47,
    "PC8": 48,
    "PC9": 49,
    "PC10": 50,
    "PC11": 51,
    "PC12": 52,
    "PC13": 53,
    "PC14": 54,
    "PC15": 55,
}


# ADC dictionaries
dict_adc_instances = {
    "ADC1": 1,
    "ADC2": 2,
    "ADC3": 3,
}

dict_gpio_analog_pins = {
    "PA0": 0,
    "PA1": 1,
    "PA2": 2,
    "PA3": 3,
    "PA4": 4,
    "PA5": 5,
    "PA6": 6,
    "PA7": 7,
    "PB0": 20,
    "PB1": 21,
    "PC0": 40,
    "PA1": 41,
    "PC2": 42,
    "PC3": 43,
    "PC4": 44,
    "PC5": 45,
    "Temp": 60,
    "Vrefint": 61,
    "Vbat": 62
}

dict_adc_res = {
    "12 bits": 0,
    "10 bits": 1,
    "8 bits": 2,
    "6 bits": 3,
}

dict_adc_clock_prescaler = {
    "PCLK2/4": 0,
    "PCLK2/6": 1,
    "PCLK2/8": 2,
}


# USART dictionaries
dict_usart_bus = {
    "USART1": 1,
    "USART2": 2,
    "USART3": 3,
    "USART4": 4,
    "USART5": 5,
    "USART6": 6,
}

dict_usart_direction = {
    "RX and TX": 0,
    "RX only": 1,
    "TX only": 2,
}

dict_usart_word_length = {
    "8 bits": 0,
    "9 bits": 1,
}

dict_usart_parity = {
    "None": 0,
    "Even": 1,
    "Odd": 2,
}

dict_usart_stop_bits = {
    "1 bit": 1,
    "2 bits": 2,
}

dict_usart_mode = {
    "Asynchronous": 0,
    "Synchronous": 1,
}

dict_usart_hw_flow = {
    "Disable": 0,
    "CTS only": 1,
    "RTS only": 2,
    "CTS and RTS": 3,
}

dict_usart_clock_polarity = {
    "Low": 0,
    "High": 1,
}

dict_usart_clock_phase = {
    "One Edge": 0,
    "Two Edge": 1,
}

dict_usart_clock_last_bit = {
    "Disable": 0,
    "Enable": 1,
}


# @brief     Classes that represent the tests
class i2c_test:
    def __init__(self, cmdType = None, bus = None, address = None, register = None, direction = None, speedMode = None, clockSpeed = None, dutyCycle = None):
        self.cmdType = cmdType
        self.bus = bus
        self.address = address
        self.register = register
        self.direction = direction
        self.speedMode = speedMode
        self.clockSpeed = clockSpeed
        self.dutyCycle = dutyCycle

class spi_test:
    def __init__(self, cmdType = None, bus = None, mode = None, command = None, dummyclocks = None, operatingMode = None, hardwareNSS = None, frameFormat = None,
    dataSize = None, firstBit = None):
        self.cmdType = cmdType
        self.bus = bus
        self.mode = mode
        self.command = command
        self.dummyclocks = dummyclocks
        self.operatingMode = operatingMode
        self.hardwareNSS = hardwareNSS
        self.frameFormat = frameFormat
        self.dataSize = dataSize
        self.firstBit = firstBit

class usart_test:
    def __init__(self, cmdType = None, bus = None, mode = None, baudRate = None, wordLength = None, parity = None, stopBits = None, direction = None,
    clockPolarity = None, clockPhase = None, clockLastBit = None, hwFlowControl = None):
        self.cmdType = cmdType
        self.bus = bus
        self.mode = mode
        self.baudRate = baudRate
        self.wordLength = wordLength
        self.parity = parity
        self.stopBits = stopBits
        self.direction = direction
        self.clockPolarity = clockPolarity
        self.clockPhase = clockPhase
        self.clockLastBit = clockLastBit
        self.hwFlowControl = hwFlowControl


class gpio_digital:
    def __init__(self, cmdType = None, pin = None, direction = None, state = None, pull = None):
        self.cmdType = cmdType
        self.pin = pin
        self.direction = direction
        self.state = state
        self.pull = pull

class analog_read:
    def __init__(self, cmdType = None, instance = None, pin = None, resolution = None, clockPrescaler = None):
        self.cmdType = cmdType
        self.instance = instance
        self.pin = pin
        self.resolution = resolution
        self.clockPrescaler = clockPrescaler

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
            UI.i2c_addr_select.setText("0x00")
        else:
            selectedCommand.address = int(UI.i2c_addr_select.text(),16)      # Convert to int
        if is_empty(UI.i2c_reg_select.text()):
            selectedCommand.register = 0
            UI.i2c_reg_select.setText("0x00")
        else:
            selectedCommand.register = int(UI.i2c_reg_select.text(),16)           # Convert to int
        selectedCommand.direction = UI.i2c_rw_select.currentData()
        selectedCommand.speedMode = UI.i2c_speed_mode_select.currentData()
        selectedCommand.clockSpeed = int(UI.i2c_clock_speed_select.text())
        if UI.i2c_speed_mode_select.currentData() == list(dict_i2c_speedmode.values())[1]:  # If 'Fast mode' is selected, save duty cycle option as well
            selectedCommand.dutyCycle = UI.i2c_duty_cycle_select.currentData()

        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

    elif cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        selectedCommand = spi_test()
        selectedCommand.cmdType = cmdType
        selectedCommand.bus = UI.spi_bus_select.currentData()
        if is_empty(UI.spi_command_select.text()):
            selectedCommand.command = 0
            UI.spi_command_select.setText("0x00")
        else:
            selectedCommand.command = int(UI.spi_command_select.text(),16)
        if is_empty(UI.spi_dummyclocks_select.text()):
            selectedCommand.dummyclocks = 0
            UI.spi_dummyclocks_select.setText("0")
        else:
            selectedCommand.dummyclocks = int(UI.spi_dummyclocks_select.text())
        selectedCommand.operatingMode = UI.spi_operating_mode_select.currentData()
        selectedCommand.hardwareNSS = UI.spi_hardware_nss_select.currentData()
        selectedCommand.frameFormat = UI.spi_frame_format_select.currentData()
        selectedCommand.dataSize = UI.spi_data_size_select.currentData()
        if UI.spi_frame_format_select.currentData() == list(dict_spi_frame_format.values())[0]: # If 'Motorola' option is selected, save first bit and clock settings as well
            selectedCommand.firstBit = UI.spi_first_bit_select.currentData()
            selectedCommand.mode = UI.spi_clockmode_select.currentData()
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

    elif cmdType == functional_test_pb2.CommandTypeEnum.USART_test:
        selectedCommand = usart_test()
        selectedCommand.cmdType = cmdType
        selectedCommand.bus = UI.usart_bus_select.currentData()
        selectedCommand.mode = UI.usart_mode_select.currentData()
        if is_empty(UI.usart_baudrate_select.text()):
            selectedCommand.baudRate = 0
            UI.usart_baudrate_select.setText("0")
        else:
            selectedCommand.baudRate = int(UI.usart_baudrate_select.text())
        selectedCommand.wordLength = UI.usart_word_length_select.currentData()
        selectedCommand.parity = UI.usart_parity_select.currentData()
        selectedCommand.stopBits = UI.usart_stop_bits_select.currentData()
        selectedCommand.direction = UI.usart_direction_select.currentData()
        if UI.usart_mode_select.currentData() == list(dict_usart_mode.values())[0]:     # If 'Asynchronous' mode is selected, save HW flow control settings
            selectedCommand.hwFlowControl = UI.usart_hw_flow_control_select.currentData()
        elif UI.usart_mode_select.currentData() == list(dict_usart_mode.values())[1]:   # If 'Synchronous' mode is selected, save clock settings
            selectedCommand.clockPolarity = UI.usart_clock_polarity_select.currentData()
            selectedCommand.clockPhase = UI.usart_clock_phase_select.currentData()
            selectedCommand.clockLastBit = UI.usart_clock_last_bit_select.currentData()

    elif cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        selectedCommand = gpio_digital()
        selectedCommand.cmdType = cmdType
        selectedCommand.pin = UI.gpio_pin_select.currentData()
        selectedCommand.direction = UI.gpio_direction_select.currentData()
        selectedCommand.state = UI.gpio_state_select.currentData()
        selectedCommand.pull = UI.gpio_pull_select.currentData()
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        selectedCommand = analog_read()
        selectedCommand.cmdType = cmdType
        selectedCommand.instance = UI.adc_instance_select.currentData()
        selectedCommand.pin = UI.gpio_pin_select.currentData()
        selectedCommand.resolution = UI.adc_resolution_select.currentData()
        selectedCommand.clockPrescaler = UI.adc_clock_prescaler_select.currentData()
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)

    elif cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        selectedCommand = analog_write()
        selectedCommand.cmdType = cmdType
        selectedCommand.pin = UI.gpio_pin_select.currentData()
        if is_empty(UI.pwm_freq_select.text()):
            selectedCommand.frequency = 0
            UI.pwm_freq_select.setText("0")
        else:
            selectedCommand.frequency = int(UI.pwm_freq_select.text())
        if is_empty(UI.pwm_duty_select.text()):
            selectedCommand.dutyCycle = 0
            UI.pwm_duty_select.setText("0")
        else:
            selectedCommand.dutyCycle = int(UI.pwm_duty_select.text())
        return selectedCommand
#        sequence.append(selectedCommand)
#        add_test_object_to_test_list(selectedCommand, test_list)
    else:
        return None


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
        string += "  Bus: " + list(dict_i2c_bus.keys())[list(dict_i2c_bus.values()).index(test_object.bus)]
        string += "  Addr: " + "0x{:02X}".format(test_object.address)
        string += "  Reg: " + "0x{:02X}".format(test_object.register)
        string += "  R/W: " + list(dict_i2c_rw.keys())[list(dict_i2c_rw.values()).index(test_object.direction)]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        string += "SPI"
        string += "  Bus: " + list(dict_spi_bus.keys())[list(dict_spi_bus.values()).index(test_object.bus)]
        string += "  Mode: " + list(dict_spi_mode.keys())[list(dict_spi_mode.values()).index(test_object.mode)]
        string += "  Cmd: " + "0x{:02X}".format(test_object.command)
        string += "  Dummy: " + str(test_object.dummyclocks)
#        string += "  R/W: " + list(dict_spi_rw.keys())[list(dict_spi_rw.values()).index(test_object.direction)]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        string += "GPIO"
        string += "  Pin: " +   list(dict_gpio_digital_pins.keys())[list(dict_gpio_digital_pins.values()).index(test_object.pin)]
        string += "  R/W: " +   list(dict_gpio_rw.keys())[list(dict_gpio_rw.values()).index(test_object.direction)]
        string += "  State: " + list(dict_gpio_state.keys())[list(dict_gpio_state.values()).index(test_object.state)]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        string += "Analog_read"
        string += "  Pin: " + list(dict_gpio_analog_pins.keys())[list(dict_gpio_analog_pins.values()).index(test_object.pin)]
        string += "  Res: " + list(dict_adc_res.keys())[list(dict_adc_res.values()).index(test_object.resolution)]

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_write:
        string += "PWM"
        string += "  Pin: " + list(dict_gpio_digital_pins.keys())[list(dict_gpio_digital_pins.values()).index(test_object.pin)]
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
        test_object.bus = list(dict_i2c_bus.values())[list(dict_i2c_bus.keys()).index(words[1][5:])]
        test_object.address = int(words[2][6:],16)
        test_object.register = int(words[3][5:],16)
        test_object.direction = list(dict_i2c_rw.values())[list(dict_i2c_rw.keys()).index(words[4][5:])]
        return test_object
#        print("Test object:")
#        print("cmd:",test_object.cmdType)
#        print("bus:",test_object.bus)
#        print("address:",test_object.address)
#        print("register:",test_object.register)
#        print("rw:",test_object.direction)
    elif words[0] == list_cmd_types[1]:
        test_object = spi_test()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.SPI_test
        test_object.bus = list(dict_spi_bus.values())[list(dict_spi_bus.keys()).index(words[1][5:])]
        test_object.mode = list(dict_spi_mode.values())[list(dict_spi_mode.keys()).index(words[2][6:])]
        test_object.command = int(words[3][7:],16)
        test_object.dummyclocks = int(words[4][7:])
        test_object.direction = list(dict_spi_rw.values())[list(dict_spi_rw.keys()).index(words[5][5:])]
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
        test_object.pin = list(dict_gpio_digital_pins.values())[list(dict_gpio_digital_pins.keys()).index(words[1][5:])]
        test_object.direction = list(dict_gpio_rw.values())[list(dict_gpio_rw.keys()).index(words[2][5:])]
        test_object.state = list(dict_gpio_state.values())[list(dict_gpio_state.keys()).index(words[3][7:])]
        return test_object
#        print("Test object: ")
#        print("cmd:",test_object.cmdType)
#        print("pin:",test_object.pin)
#        print("rw:",test_object.direction)
#        print("state:", test_object.state)
    elif words[0] == list_cmd_types[3]:
        test_object = analog_read()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.Analog_read
        test_object.pin = list(dict_gpio_analog_pins.values())[list(dict_gpio_analog_pins.keys()).index(words[1][5:])]
        test_object.resolution = list(dict_adc_res.values())[list(dict_adc_res.keys()).index(words[2][5:])]
        return test_object
#        print("Test object:")
#        print("cmd:",test_object.cmdType)
#        print("pin:",test_object.pin)
#        print("Res:",test_object.resolution)
    elif words[0] == list_cmd_types[4]:
        test_object = analog_write()
        test_object.cmdType = functional_test_pb2.CommandTypeEnum.Analog_write
        test_object.pin = list(dict_gpio_digital_pins.values())[list(dict_gpio_digital_pins.keys()).index(words[1][5:])]
        test_object.frequency = int(words[2][6:])
        test_object.dutyCycle = int(words[3][6:])
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
        cmd.i2c.register = test_object.register
        cmd.i2c.direction = test_object.direction
        cmd.i2c.speedMode = test_object.speedMode
        cmd.i2c.clockSpeed = test_object.clockSpeed
        if test_object.speedMode == list(dict_i2c_speedmode.values())[1]:
            cmd.i2c.dutyCycle = test_object.dutyCycle

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.SPI_test:
        cmd.spi.bus = test_object.bus
        cmd.spi.mode = test_object.mode
        cmd.spi.command = test_object.command
        cmd.spi.dummyclocks = test_object.dummyclocks
        cmd.spi.operatingMode = test_object.operatingMode
        cmd.spi.hardwareNSS = test_object.hardwareNSS
        cmd.spi.frameFormat = test_object.frameFormat
        cmd.spi.dataSize = test_object.dataSize
        if test_object.frameFormat == list(dict_spi_frame_format.values())[0]:
            cmd.spi.firstBit = test_object.firstBit
            cmd.spi.mode = test_object.mode

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.USART_test:
        cmd.usart.bus = test_object.bus
        cmd.usart.mode = test_object.mode
        cmd.usart.baudRate = test_object.baudRate
        cmd.usart.wordLength = test_object.wordLength
        cmd.usart.parity = test_object.parity
        cmd.usart.stopBits = test_object.stopBits
        cmd.usart.direction = test_object.direction
        if test_object.mode == list(dict_usart_mode.values())[0]:
            cmd.usart.hwFlowControl = test_object.hwFlowControl
        elif test_object.mode == list(dict_usart_mode.values())[1]:
            cmd.usart.clockPolarity = test_object.clockPolarity
            cmd.usart.clockPhase = test_object.clockPhase
            cmd.usart.clockLastBit = test_object.clockLastBit

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        cmd.gpio.pin = test_object.pin
        cmd.gpio.direction = test_object.direction
        cmd.gpio.state = test_object.state
        cmd.gpio.pull = test_object.pull

    elif test_object.cmdType == functional_test_pb2.CommandTypeEnum.Analog_read:
        cmd.analog_in.instance = test_object.instance
        cmd.analog_in.pin  = test_object.pin
        cmd.analog_in.resolution = test_object.resolution
        cmd.analog_in.clockPrescaler = test_object.clockPrescaler

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

