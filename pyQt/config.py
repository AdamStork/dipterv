#    Python file for reading in and processing CubeMX configuration file
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

import sequence

#Function list:
#    process_config_file(path)
#    check_dataline_for_available_buses(data_line)
#    check_data_line_for_available_pins(data_line)


dict_available_i2c_buses = {}
dict_available_spi_buses = {}
dict_available_adc_instances = {}
dict_available_usart_buses = {}
dict_available_digital_pins = {}
dict_available_analog_pins = {}
dict_mcu_info = {}



# Process config file line-by-line
def process_config_file(path):
    try:
        file = open(path, 'r')
        with file:
            data_line = file.readlines()
            for i in range(len(data_line)):
                data_line[i] = data_line[i].rstrip()     # Remove trailing characters: \n
                check_dataline_for_available_buses(data_line[i])
                check_dataline_for_available_pins(data_line[i])
                check_dataline_for_mcu_info(data_line[i])
            print("Available I2C buses:", dict_available_i2c_buses)
            print("Available SPI buses:", dict_available_spi_buses)
            print("Available USART buses:", dict_available_usart_buses)
            print("Available ADC channels:", dict_available_adc_instances)
            print("Available GPIO digital pins:", dict_available_digital_pins)
            print("Available ADC pins:", dict_available_analog_pins)
            print("MCU info:",dict_mcu_info)
            file.close()
        return True
    except:
        return False


# Check data line from file for available i2c/spi/usart buses and ADC channels
def check_dataline_for_available_buses(data_line):
    words = data_line.split(".")            # There are lines where there is no '=', so split must be first done for '.'
    if words[0] == "Mcu":
        new_words = words[1].split("=")
        possible_bus = new_words[1]

        if possible_bus in sequence.dict_i2c_bus:
            # If search was successful in dicionary, add it to a dictionary which contains the available buses.
            i2c_bus_key = possible_bus   # Search through the i2c bus dictionary
            i2c_bus_value = list(sequence.dict_i2c_bus.values())[list(sequence.dict_i2c_bus.keys()).index(possible_bus)]
            dict_available_i2c_buses[i2c_bus_key] = i2c_bus_value

        if possible_bus in sequence.dict_spi_bus:
            # If search was successful in dicionary, add it to a dictionary which contains the available buses.
            spi_bus_key = possible_bus   # Search through the spi bus dictionary
            spi_bus_value = list(sequence.dict_spi_bus.values())[list(sequence.dict_spi_bus.keys()).index(possible_bus)]
            dict_available_spi_buses[spi_bus_key] = spi_bus_value

        if possible_bus in sequence.dict_adc_instances:
            # If search was successful in dicionary, add it to a dictionary which contains the available buses.
            adc_instance_key = possible_bus   # Search through the adc instance dictionary
            adc_instance_value = list(sequence.dict_adc_instances.values())[list(sequence.dict_adc_instances.keys()).index(possible_bus)]
            dict_available_adc_instances[adc_instance_key] = adc_instance_value

        if possible_bus in sequence.dict_usart_bus:
            # If search was successful in dicionary, add it to a dictionary which contains the available buses.
            usart_bus_key = possible_bus   # Search through the usart bus dictionary
            usart_bus_value = list(sequence.dict_usart_bus.values())[list(sequence.dict_usart_bus.keys()).index(possible_bus)]
            dict_available_usart_buses[usart_bus_key] = usart_bus_value



# Check data line from file for available digital/analog pins
def check_dataline_for_available_pins(data_line):
    words = data_line.split(".")
    if words[0] in sequence.dict_gpio_digital_pins:
        new_words = words[1].split("=")
        possible_pin_type = new_words[1]
        possible_pin = words[0]

        if possible_pin_type == "GPIO_Output" or possible_pin_type == "GPIO_Input":
            gpio_digital_key = possible_pin
            gpio_digital_value = list(sequence.dict_gpio_digital_pins.values())[list(sequence.dict_gpio_digital_pins.keys()).index(possible_pin)]
            dict_available_digital_pins[gpio_digital_key] = gpio_digital_value

        if possible_pin_type[:4] == "ADCx":
            gpio_analog_key = possible_pin
            gpio_analog_value = list(sequence.dict_gpio_analog_pins.values())[list(sequence.dict_gpio_analog_pins.keys()).index(possible_pin)]
            dict_available_analog_pins[gpio_analog_key] = gpio_analog_value


# Check data line from file for MCU Family info
def check_dataline_for_mcu_info(data_line):
    words = data_line.split(".")            # There are lines where there is no '=', so split must be first done for '.'
    if words[0] == "Mcu":
        new_words = words[1].split("=")
        if new_words[0] == "Family":
            dict_mcu_info[new_words[0]] = new_words[1]


