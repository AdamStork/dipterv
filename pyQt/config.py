#    Python file for reading in and processing CubeMX configuration file
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

import sequence

dict_available_i2c_buses = {}
dict_available_spi_buses = {}
dict_available_adc_channels = {}
dict_available_usart_buses = {}
dict_available_digital_pins = {}
dict_available_analog_pins = {}



# Process config file line-by-line
def process_config_file(path):
    file = open(path, 'r')
    with file:
        data_line = file.readlines()
        for i in range(len(data_line)):
            data_line[i] = data_line[i].rstrip()     # Remove trailing characters: \n
            check_dataline_for_available_buses(data_line[i])
#            check_data_line_for_available_pins(data_line[i])
        print("Available I2C buses:", dict_available_i2c_buses)
        print("Available SPI buses:", dict_available_spi_buses)
        print("Available USART buses:", dict_available_usart_buses)
        print("Available ADC channels:", dict_available_adc_channels)
        file.close()


# Check data line from file for available i2c/spi/usart buses and ADC channels
def check_dataline_for_available_buses(data_line):
    words = data_line.split(".")
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

        if possible_bus in sequence.dict_adc_channels:
            # If search was successful in dicionary, add it to a dictionary which contains the available buses.
            adc_channel_key = possible_bus   # Search through the adc channel dictionary
            adc_channel_value = list(sequence.dict_adc_channels.values())[list(sequence.dict_adc_channels.keys()).index(possible_bus)]
            dict_available_adc_channels[adc_channel_key] = adc_channel_value

        if possible_bus in sequence.dict_usart_bus:
            # If search was successful in dicionary, add it to a dictionary which contains the available buses.
            usart_bus_key = possible_bus   # Search through the adc channel dictionary
            usart_bus_value = list(sequence.dict_usart_bus.values())[list(sequence.dict_usart_bus.keys()).index(possible_bus)]
            dict_available_usart_buses[usart_bus_key] = usart_bus_value



# Check data line from file for available digital/analog pins
def check_dataline_for_available_buses(data_line):
    print("TODO: output analog etc")
