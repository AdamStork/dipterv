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
#    select_pin_for_adc_channel(adcChannelValue):


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

dict_spi_clockmode = {
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
    "P_INVALID": 100,
}


# ADC dictionaries
dict_adc_instances = {
    "ADC1": 1,
    "ADC2": 2,
    "ADC3": 3,
}


dict_adc_channels = {
    "IN0": 0,
    "IN1": 1,
    "IN2": 2,
    "IN3": 3,
    "IN4": 4,
    "IN5": 5,
    "IN6": 6,
    "IN7": 7,
    "IN8": 8,
    "IN9": 9,
    "IN10": 10,
    "IN11": 11,
    "IN12": 12,
    "IN13": 13,
    "IN14": 14,
    "IN15": 15,
}


dict_gpio_analog_pins = {   # pin values represent the ADC channel IN[0..15] values
    "PA0": 0,
    "PA1": 1,
    "PA2": 2,
    "PA3": 3,
    "PA4": 4,
    "PA5": 5,
    "PA6": 6,
    "PA7": 7,
    "PB0": 8,
    "PB1": 9,
    "PC0": 10,
    "PC1": 11,
    "PC2": 12,
    "PC3": 13,
    "PC4": 14,
    "PC5": 15,
#    "Temp": 60,
#    "Vrefint": 61,
#    "Vbat": 62
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
    "TX only": 0,
    "TX and RX": 1,
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

# PWM dictionaries
dict_pwm_time_dependency = {
    "Disabled": 0,
    "Enabled": 1,
}

# Response dictionaries
dict_response_write = {
    "I2C write OK": 0,
    "I2C write failed!": 1,
    "I2C read failed!": 2,
    "SPI transmission successful": 3,
    "SPI transmission failed": 4,
    "USART TX successful": 5,
    "USART TX failed": 6,
    "GPIO set High": 7,
    "GPIO set Low": 8,
    "GPIO set failed": 9,
    "PWM set": 10,
    "PWM reset": 11,
    "PWM set failed": 12,
}


# @brief        Make test objects from the selected options and add it to test_list.
# @param[in]    UI: user interface (e.g. MyWindow class)
# @return       test_object: created from the selected command options
def make_test_object_from_options(UI):
    cmd = functional_test_pb2.Command()
    cmd.commandType = UI.cmd_box.currentData()

    if UI.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.I2C_test:
        cmd.i2c.bus = UI.i2c_bus_select.currentData()
        cmd.i2c.direction = UI.i2c_rw_select.currentData()
        if is_empty(UI.i2c_addr_select.text()):
            cmd.i2c.address = 0
            UI.i2c_addr_select.setText("0x00")
        else:
            cmd.i2c.address = int(UI.i2c_addr_select.text(),16)      # Convert to int
        if is_empty(UI.i2c_reg_select.text()):
            cmd.i2c.reg = 0
            UI.i2c_reg_select.setText("0x00")
        else:
            cmd.i2c.reg = int(UI.i2c_reg_select.text(),16)           # Convert to int
        if UI.i2c_rw_select.currentData() == list(dict_i2c_rw.values())[0]: # If "Write" is selected, save write value as well
            if is_empty(UI.i2c_write_value_select.text()):
                cmd.i2c.writeValue = 0
                UI.i2c_write_value_select.setText("0x00")
            else:
                cmd.i2c.writeValue = int(UI.i2c_write_value_select.text(),16)      # Convert to int
        if is_empty(UI.i2c_size_select.text()):
            cmd.i2c.size = 1
            UI.i2c_size_select.setText("1")
        else:
            cmd.i2c.size = int(UI.i2c_size_select.text())
        cmd.i2c.speedMode = UI.i2c_speed_mode_select.currentData()
        cmd.i2c.clockSpeed = int(UI.i2c_clock_speed_select.text())
        if UI.i2c_speed_mode_select.currentData() == list(dict_i2c_speedmode.values())[1]:  # If 'Fast mode' is selected, save duty cycle option as well
            cmd.i2c.dutyCycle = UI.i2c_duty_cycle_select.currentData()


    elif UI.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.SPI_test:
        cmd.spi.bus = UI.spi_bus_select.currentData()
        cmd.spi.operatingMode = UI.spi_operating_mode_select.currentData()
        if is_empty(UI.spi_command_select.text()):
            cmd.spi.command = 0
            UI.spi_command_select.setText("0x00")
        else:
            cmd.spi.command = int(UI.spi_command_select.text(),16)
        if is_empty(UI.spi_dummyclocks_select.text()):
            cmd.spi.dummyClocks = 0
            UI.spi_dummyclocks_select.setText("0")
        else:
            cmd.spi.dummyClocks = int(UI.spi_dummyclocks_select.text())
        if is_empty(UI.spi_write_value_select.text()):
            cmd.spi.writeValue = 0
            UI.spi_write_value_select.setText("0")
        else:
            cmd.spi.writeValue = int(UI.spi_write_value_select.text(),16)
        if is_empty(UI.spi_write_size_select.text()):
            cmd.spi.writeSize = 0
            UI.spi_write_size_select.setText("0")
        else:
            cmd.spi.writeSize = int(UI.spi_write_size_select.text())
        if is_empty(UI.spi_slave_response_select.text()):
            cmd.spi.slaveResponse = 0
            UI.spi_slave_response_select.setText("0")
        else:
            cmd.spi.slaveResponse = int(UI.spi_slave_response_select.text())
        cmd.spi.hardwareNSS = UI.spi_hardware_nss_select.currentData()
        cmd.spi.frameFormat = UI.spi_frame_format_select.currentData()
        cmd.spi.dataSize = UI.spi_data_size_select.currentData()
        if UI.spi_frame_format_select.currentData() == list(dict_spi_frame_format.values())[0]: # If 'Motorola' option is selected, save first bit and clock settings as well
            cmd.spi.firstBit = UI.spi_first_bit_select.currentData()
            cmd.spi.clockMode = UI.spi_clockmode_select.currentData()

    elif UI.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.USART_test:
        cmd.usart.bus = UI.usart_bus_select.currentData()
        cmd.usart.mode = UI.usart_mode_select.currentData()
        if is_empty(UI.usart_baudrate_select.text()):
            cmd.usart.baudRate = 0
            UI.usart_baudrate_select.setText("0")
        else:
            cmd.usart.baudRate = int(UI.usart_baudrate_select.text())
        cmd.usart.wordLength = UI.usart_word_length_select.currentData()
        cmd.usart.parity = UI.usart_parity_select.currentData()
        cmd.usart.stopBits = UI.usart_stop_bits_select.currentData()
        cmd.usart.direction = UI.usart_direction_select.currentData()
        if is_empty(UI.usart_command_select.text()):
            cmd.usart.command = 0
            UI.usart_command_select.setText("0x00")
        else:
            cmd.usart.command = int(UI.usart_command_select.text(),16)
        if UI.usart_mode_select.currentData() == list(dict_usart_mode.values())[0]:     # If 'Asynchronous' mode is selected, save HW flow control settings
            cmd.usart.hwFlowControl = UI.usart_hw_flow_control_select.currentData()
        elif UI.usart_mode_select.currentData() == list(dict_usart_mode.values())[1]:   # If 'Synchronous' mode is selected, save clock settings
            cmd.usart.clockPolarity = UI.usart_clock_polarity_select.currentData()
            cmd.usart.clockPhase = UI.usart_clock_phase_select.currentData()
            cmd.usart.clockLastBit = UI.usart_clock_last_bit_select.currentData()

    elif UI.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        cmd.gpio.pin = UI.gpio_pin_select.currentData()
        cmd.gpio.direction = UI.gpio_direction_select.currentData()
        cmd.gpio.state = UI.gpio_state_select.currentData()
        cmd.gpio.pull = UI.gpio_pull_select.currentData()

    elif UI.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.Analog_read:
        cmd.analog_in.instance = UI.adc_instance_select.currentData()
        cmd.analog_in.channel = UI.adc_channel_select.currentData()
        cmd.analog_in.pin = list(dict_gpio_analog_pins.values())[list(dict_gpio_analog_pins.keys()).index(UI.adc_pin_select.text())]
        cmd.analog_in.resolution = UI.adc_resolution_select.currentData()
        cmd.analog_in.clockPrescaler = UI.adc_clock_prescaler_select.currentData()
        print("Analog pin:",cmd.analog_in.pin)

    elif UI.cmd_box.currentData() == functional_test_pb2.CommandTypeEnum.Analog_write:
        cmd.analog_out.pin = UI.gpio_pin_select.currentData()
        if is_empty(UI.pwm_freq_select.text()):
            cmd.analog_out.frequency = 0
            UI.pwm_freq_select.setText("0")
        else:
            cmd.analog_out.frequency = int(UI.pwm_freq_select.text())
        if is_empty(UI.pwm_duty_select.text()):
            cmd.analog_out.dutyCycle = 0
            UI.pwm_duty_select.setText("0")
        else:
            cmd.analog_out.dutyCycle = int(UI.pwm_duty_select.text())
        if UI.pwm_time_checkbox.isChecked():
            cmd.analog_out.dependency = list(dict_pwm_time_dependency.values())[1]
            if is_empty(UI.pwm_time_select.text()):
                cmd.analog_out.time = 0
                UI.pwm_time_select.setText("0")
            else:
                cmd.analog_out.time = int(UI.pwm_time_select.text())
        else:
            cmd.analog_out.dependency = list(dict_pwm_time_dependency.values())[0]

    else:
        return None

    if UI.use_config_file:
        cmd.autoConfig = True
    return cmd


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
    if test_object.commandType == functional_test_pb2.CommandTypeEnum.I2C_test:
        string += "I2C"
        string += "  Bus: " + list(dict_i2c_bus.keys())[list(dict_i2c_bus.values()).index(test_object.i2c.bus)]
        string += "  R/W: " + list(dict_i2c_rw.keys())[list(dict_i2c_rw.values()).index(test_object.i2c.direction)]
        string += "  Addr: " + "0x{:02X}".format(test_object.i2c.address)
        string += "  Reg: " + "0x{:02X}".format(test_object.i2c.reg)
        if test_object.i2c.direction == list(dict_i2c_rw.values())[0]:
            string += "  writeValue: " + "0x{:04X}".format(test_object.i2c.writeValue)
        string += "  Size: " + str(test_object.i2c.size)
        string += "  Mode: " + list(dict_i2c_speedmode.keys())[list(dict_i2c_speedmode.values()).index(test_object.i2c.speedMode)]
        string += "  Speed: " + str(test_object.i2c.clockSpeed)
        if test_object.i2c.speedMode == list(dict_i2c_speedmode.values())[1]:  # If 'Fast mode' is selected, add duty cycle as well
            string += "  Duty cycle: " + list(dict_i2c_duty_cycle.keys())[list(dict_i2c_duty_cycle.values()).index(test_object.i2c.dutyCycle)]

    elif test_object.commandType == functional_test_pb2.CommandTypeEnum.SPI_test:
        string += "SPI"
        string += "  Bus: " + list(dict_spi_bus.keys())[list(dict_spi_bus.values()).index(test_object.spi.bus)]
        string += "  Op.mode: " + list(dict_spi_operating_mode.keys())[list(dict_spi_operating_mode.values()).index(test_object.spi.operatingMode)]
        string += "  Cmd: " + "0x{:02X}".format(test_object.spi.command)
        string += "  Dummy: " + str(test_object.spi.dummyclocks)
        string += "  writeValue: " + "0x{:04X}".format(test_object.spi.writeValue)
        string += "  writeSize: " + str(test_object.spi.writeSize)
        string += "  slaveResponse: " + str(test_object.spi.slaveResponse)
        string += "  HW NSS: " + list(dict_spi_hardware_nss.keys())[list(dict_spi_hardware_nss.values()).index(test_object.spi.hardwareNSS)]
        string += "  Frame format: " + list(dict_spi_frame_format.keys())[list(dict_spi_frame_format.values()).index(test_object.spi.frameFormat)]
        string += "  Data size: " + list(dict_spi_data_size.keys())[list(dict_spi_data_size.values()).index(test_object.spi.dataSize)]
        if test_object.spi.frameFormat == list(dict_spi_frame_format.values())[0]: # If 'Motorola' option is selected
            string += "  First bit: " + list(dict_spi_first_bit.keys())[list(dict_spi_first_bit.values()).index(test_object.spi.firstBit)]
            string += "  Clock mode: " + list(dict_spi_clockmode.keys())[list(dict_spi_clockmode.values()).index(test_object.spi.clockMode)]

    elif test_object.commandType == functional_test_pb2.CommandTypeEnum.USART_test:
        string += "USART"
        string += "  Bus: " + list(dict_usart_bus.keys())[list(dict_usart_bus.values()).index(test_object.usart.bus)]
        string += "  Mode: " + list(dict_usart_mode.keys())[list(dict_usart_mode.values()).index(test_object.usart.mode)]
        string += "  baudRate: " + str(test_object.usart.baudRate)
        string += "  Word Length: " + list(dict_usart_word_length.keys())[list(dict_usart_word_length.values()).index(test_object.usart.wordLength)]
        string += "  Parity: " + list(dict_usart_parity.keys())[list(dict_usart_parity.values()).index(test_object.usart.parity)]
        string += "  Stop bits: " + list(dict_usart_stop_bits.keys())[list(dict_usart_stop_bits.values()).index(test_object.usart.stopBits)]
        string += "  Direction: " + list(dict_usart_direction.keys())[list(dict_usart_direction.values()).index(test_object.usart.direction)]
        string += "  Cmd: " + "0x{:02X}".format(test_object.usart.command)
        if test_object.usart.mode == list(dict_usart_mode.values())[0]:   # If 'Asynchronous' option is selected
            string += "  HW Flow control: " + list(dict_usart_hw_flow.keys())[list(dict_usart_hw_flow.values()).index(test_object.usart.hwFlowControl)]
        elif test_object.usart.mode == list(dict_usart_mode.values())[1]:   # If 'Synchronous' option is selected
            string += "  Clock polarity: " + list(dict_usart_clock_polarity.keys())[list(dict_usart_clock_polarity.values()).index(test_object.usart.clockPolarity)]
            string += "  Clock phase: " + list(dict_usart_clock_phase.keys())[list(dict_usart_clock_phase.values()).index(test_object.usart.clockPhase)]
            string += "  Clock last bit: " + list(dict_usart_clock_last_bit.keys())[list(dict_usart_clock_last_bit.values()).index(test_object.usart.clockLastBit)]

    elif test_object.commandType == functional_test_pb2.CommandTypeEnum.GPIO_digital:
        string += "GPIO"
        string += "  Pin: " +   list(dict_gpio_digital_pins.keys())[list(dict_gpio_digital_pins.values()).index(test_object.gpio.pin)]
        string += "  R/W: " +   list(dict_gpio_rw.keys())[list(dict_gpio_rw.values()).index(test_object.gpio.direction)]
        string += "  State: " + list(dict_gpio_state.keys())[list(dict_gpio_state.values()).index(test_object.gpio.state)]
        string += "  Pull: " + list(dict_gpio_pull.keys())[list(dict_gpio_pull.values()).index(test_object.gpio.pull)]

    elif test_object.commandType == functional_test_pb2.CommandTypeEnum.Analog_read:
        string += "Analog_read"
        string += "  Instance: " + list(dict_adc_instances.keys())[list(dict_adc_instances.values()).index(test_object.analog_in.instance)]
        string += "  Channel: " + list(dict_adc_channels.keys())[list(dict_adc_channels.values()).index(test_object.analog_in.channel)]
        string += "  Pin: " + list(dict_gpio_analog_pins.keys())[list(dict_gpio_analog_pins.values()).index(test_object.analog_in.pin)]
        string += "  Resolution: " + list(dict_adc_res.keys())[list(dict_adc_res.values()).index(test_object.analog_in.resolution)]
        string += "  Prescaler: " + list(dict_adc_clock_prescaler.keys())[list(dict_adc_clock_prescaler.values()).index(test_object.analog_in.clockPrescaler)]

    elif test_object.commandType == functional_test_pb2.CommandTypeEnum.Analog_write:
        string += "PWM"
        string += "  Pin: " + list(dict_gpio_digital_pins.keys())[list(dict_gpio_digital_pins.values()).index(test_object.analog_out.pin)]
        string += "  Freq: " + str(test_object.analog_out.frequency)
        string += "  Duty: " + str(test_object.analog_out.dutyCycle)
        string += "  Time dependency: " + list(dict_pwm_time_dependency.keys())[list(dict_pwm_time_dependency.values()).index(test_object.analog_out.dependency)]
        if test_object.analog_out.dependency == list(dict_pwm_time_dependency.values())[1]: # If time dependency is set to 'Enabled'
            string += "  Time: " + str(test_object.analog_out.time)

    return string


# @brief        Make test object from string line: split words using a double space separator. Attach only the relevant string parts to object parameters.
# @details      Lists are used to find the indexes (enum values in .proto) of strings.
# @param[in]    string
# @return       test_object
def make_test_object_from_string(string):
    words = string.split("  ")
    option = []         # Contains "BUS", "Address" etc.
    optionValue = []    # Contains "I2C1", "0x00" etc.

    # Process string: save options and given settings to different lists
    for i in range(len(words)):
        if i>0:
            newWord = words[i].split(": ")
            option.append(newWord[0])
            optionValue.append(newWord[1])

    test_object = functional_test_pb2.Command()

    if words[0] == list_cmd_types[0]:
        test_object.commandType = functional_test_pb2.CommandTypeEnum.I2C_test
        test_object.i2c.bus = list(dict_i2c_bus.values())[list(dict_i2c_bus.keys()).index(optionValue[0])]
        test_object.i2c.direction = list(dict_i2c_rw.values())[list(dict_i2c_rw.keys()).index(optionValue[1])]
        test_object.i2c.address = int(optionValue[2],16)
        test_object.i2c.reg = int(optionValue[3],16)
        if test_object.i2c.direction == list(dict_i2c_rw.values())[0]: # If 'Write' is selected, add writeValue also
            test_object.i2c.writeValue = int(optionValue[4],16)
            test_object.i2c.size = int(optionValue[5])
            test_object.i2c.speedMode = list(dict_i2c_speedmode.values())[list(dict_i2c_speedmode.keys()).index(optionValue[6])]
            test_object.i2c.clockSpeed = int(optionValue[7])
            if test_object.i2c.speedMode == list(dict_i2c_speedmode.values())[1]:  # If 'Fast mode' is selected, add duty cycle as well
                test_object.i2c.dutyCycle = list(dict_i2c_duty_cycle.values())[list(dict_i2c_duty_cycle.keys()).index(optionValue[8])]
        else:
            test_object.i2c.size = int(optionValue[4])
            test_object.i2c.speedMode = list(dict_i2c_speedmode.values())[list(dict_i2c_speedmode.keys()).index(optionValue[5])]
            test_object.i2c.clockSpeed = int(optionValue[6])
            if test_object.i2c.speedMode == list(dict_i2c_speedmode.values())[1]:  # If 'Fast mode' is selected, add duty cycle as well
                test_object.i2c.dutyCycle = list(dict_i2c_duty_cycle.values())[list(dict_i2c_duty_cycle.keys()).index(optionValue[7])]
        return test_object

    elif words[0] == list_cmd_types[1]:
        test_object.commandType = functional_test_pb2.CommandTypeEnum.SPI_test
        test_object.spi.bus = list(dict_spi_bus.values())[list(dict_spi_bus.keys()).index(optionValue[0])]
        test_object.spi.operatingMode = list(dict_spi_operating_mode.values())[list(dict_spi_operating_mode.keys()).index(optionValue[1])]
        test_object.spi.command = int(optionValue[2],16)
        test_object.spi.dummyclocks = int(optionValue[3])
        test_object.spi.writeValue = int(optionValue[4],16)
        test_object.spi.writeSize = int(optionValue[5])
        test_object.spi.slaveResponse = int(optionValue[6])
        test_object.spi.hardwareNSS = list(dict_spi_hardware_nss.values())[list(dict_spi_hardware_nss.keys()).index(optionValue[7])]
        test_object.spi.frameFormat = list(dict_spi_frame_format.values())[list(dict_spi_frame_format.keys()).index(optionValue[8])]
        test_object.spi.dataSize = list(dict_spi_data_size.values())[list(dict_spi_data_size.keys()).index(optionValue[9])]
        if test_object.spi.frameFormat == list(dict_spi_frame_format.values())[0]: # If 'Motorola' option is selected
            test_object.spi.firstBit = list(dict_spi_first_bit.values())[list(dict_spi_first_bit.keys()).index(optionValue[10])]
            test_object.spi.clockMode = list(dict_spi_clockmode.values())[list(dict_spi_clockmode.keys()).index(optionValue[11])]
        return test_object

    elif words[0] == list_cmd_types[2]:
        test_object.commandType = functional_test_pb2.CommandTypeEnum.USART_test
        test_object.usart.bus = list(dict_usart_bus.values())[list(dict_usart_bus.keys()).index(optionValue[0])]
        test_object.usart.mode = list(dict_usart_mode.values())[list(dict_usart_mode.keys()).index(optionValue[1])]
        test_object.usart.baudRate = int(optionValue[2])
        test_object.usart.wordLength = list(dict_usart_word_length.values())[list(dict_usart_word_length.keys()).index(optionValue[3])]
        test_object.usart.parity = list(dict_usart_parity.values())[list(dict_usart_parity.keys()).index(optionValue[4])]
        test_object.usart.stopBits = list(dict_usart_stop_bits.values())[list(dict_usart_stop_bits.keys()).index(optionValue[5])]
        test_object.usart.direction = list(dict_usart_direction.values())[list(dict_usart_direction.keys()).index(optionValue[6])]
        test_object.usart.command = int(optionValue[7],16)
        if test_object.usart.mode == list(dict_usart_mode.values())[0]:   # If 'Asynchronous' option is selected
            test_object.usart.hwFlowControl = list(dict_usart_hw_flow.values())[list(dict_usart_hw_flow.keys()).index(optionValue[8])]
        elif test_object.usart.mode == list(dict_usart_mode.values())[1]:   # If 'Synchronous' option is selected
            test_object.usart.clockPolarity = list(dict_usart_clock_polarity.values())[list(dict_usart_clock_polarity.keys()).index(optionValue[8])]
            test_object.usart.clockPhase = list(dict_usart_clock_phase.values())[list(dict_usart_clock_phase.keys()).index(optionValue[9])]
            test_object.usart.clockLastBit = list(dict_usart_clock_last_bit.values())[list(dict_usart_clock_last_bit.keys()).index(optionValue[10])]
        return test_object

    elif words[0] == list_cmd_types[3]:
        test_object.commandType = functional_test_pb2.CommandTypeEnum.GPIO_digital
        test_object.gpio.pin = list(dict_gpio_digital_pins.values())[list(dict_gpio_digital_pins.keys()).index(optionValue[0])]
        test_object.gpio.direction = list(dict_gpio_rw.values())[list(dict_gpio_rw.keys()).index(optionValue[1])]
        test_object.gpio.state = list(dict_gpio_state.values())[list(dict_gpio_state.keys()).index(optionValue[2])]
        test_object.gpio.pull = list(dict_gpio_pull.values())[list(dict_gpio_pull.keys()).index(optionValue[3])]
        return test_object

    elif words[0] == list_cmd_types[4]:
        test_object.commandType = functional_test_pb2.CommandTypeEnum.Analog_read
        test_object.analog_in.instance = list(dict_adc_instances.values())[list(dict_adc_instances.keys()).index(optionValue[0])]
        test_object.analog_in.channel = list(dict_adc_channels.values())[list(dict_adc_channels.keys()).index(optionValue[1])]
        test_object.analog_in.pin = list(dict_gpio_analog_pins.values())[list(dict_gpio_analog_pins.keys()).index(optionValue[2])]
        test_object.analog_in.resolution = list(dict_adc_res.values())[list(dict_adc_res.keys()).index(optionValue[3])]
        test_object.analog_in.clockPrescaler = list(dict_adc_clock_prescaler.values())[list(dict_adc_clock_prescaler.keys()).index(optionValue[4])]
        return test_object

    elif words[0] == list_cmd_types[5]:
        test_object.commandType = functional_test_pb2.CommandTypeEnum.Analog_write
        test_object.analog_out.pin = list(dict_gpio_digital_pins.values())[list(dict_gpio_digital_pins.keys()).index(optionValue[0])]
        test_object.analog_out.frequency = int(optionValue[1])
        test_object.analog_out.dutyCycle = int(optionValue[2])
        test_object.analog_out.dependency = list(dict_pwm_time_dependency.values())[list(dict_pwm_time_dependency.keys()).index(optionValue[3])]
        if test_object.analog_out.dependency == list(dict_pwm_time_dependency.values())[1]: # If time dependency is set to 'Enabled'
            test_object.analog_out.time = int(optionValue[4])
        return test_object



# @brief        Make protobuf command from test object
# @param[in]    test_object
# @return       Encoded message
def make_protobuf_command_from_test_object(test_object):
    return test_object.SerializeToString()


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


# @brief    Select pin for ADC channel
# @param    adcChannelValue: value for ADC channel taken from dictionary
def select_pin_for_adc_channel(adcChannelValue):
    pin = list(dict_gpio_analog_pins.keys())[list(dict_gpio_analog_pins.values()).index(adcChannelValue)]
    return pin
