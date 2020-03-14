#    Python file for test cases
#    Author: Adam Golya
#   #######################################

import functional_test_pb2
import link_layer
import serial
import sequence
import array

LL = link_layer()
ser = serial.Serial(port='COM9', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=0.2)
response_num = 20


def i2c_write(deviceAddress, register, writeValue, writeSize):
    cmd = functional_test_pb2.Command()
    cmd.commandType = functional_test_pb2.CommandTypeEnum.I2C_test
    cmd.i2c.bus = functional_test_pb2.i2cBus.I2C1;
    cmd.i2c.address = deviceAddress
    cmd.i2c.reg = register
    cmd.i2c.direction = functional_test_pb2.i2cDirection.I2C_write
    cmd.i2c.speedMode = functional_test_pb2.i2cSpeedMode.I2C_SPEED_MODE_STANDARD
    cmd.i2c.clockSpeed = 100000
    cmd.i2c.size = writeSize
    cmd.i2c.writeValue = writeValue
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    return message_data.response.responseEnum

def i2c_read(deviceAddress, register, readSize):
    cmd = functional_test_pb2.Command()
    cmd.commandType = functional_test_pb2.CommandTypeEnum.I2C_test
    cmd.i2c.bus = functional_test_pb2.i2cBus.I2C1
    cmd.i2c.address = deviceAddress
    cmd.i2c.reg = register
    cmd.i2c.direction = functional_test_pb2.i2cDirection.I2C_read
    cmd.i2c.speedMode = functional_test_pb2.i2cSpeedMode.I2C_SPEED_MODE_STANDARD
    cmd.i2c.clockSpeed = 100000
    cmd.i2c.size = readSize
    cmd.i2c.writeValue = 0
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    if message_data.response.responseEnum == functional_test_pb2.responseEnum_t.I2C_READ_FAIL:
        return message_data.response.responseEnum
    else:
        return message_data.response.responseRead

def spi_transmit_receive(command, dummyClocks, writeValue, writeSize, readSize):
    cmd = functional_test_pb2.Command()
    cmd.commandType = functional_test_pb2.CommandTypeEnum.SPI_test
    cmd.spi.bus = functional_test_pb2.spiBus.SPI1
    cmd.spi.operatingMode = functional_test_pb2.spiOperatingMode.SPI_MODE_FULL_DUPLEX_MASTER
    cmd.spi.command = command
    cmd.spi.dummyClocks = dummyClocks
    cmd.spi.writeValue = writeValue
    cmd.spi.writeSize = writeSize
    cmd.spi.slaveResponse = readSize
    cmd.spi.hardwareNSS = functional_test_pb2.spiHardwareNSS.DISABLE
    cmd.spi.frameFormat = functional_test_pb2.spiFrameFormat.SPI_FRAME_FORMAT_MOTOROLA
    cmd.spi.dataSize = functional_test_pb2.spiDataSize.SPI_DATA_SIZE_8_BITS
    cmd.spi.firstBit = functional_test_pb2.spiFirstBit.SPI_FIRST_BIT_MSB
    cmd.spi.clockMode = functional_test_pb2.clockMode.SPI_MODE_0
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    if message_data.response.responseEnum == functional_test_pb2.responseEnum_t.SPI_TRANSMISSION_OK:
        return message_data.response.responseEnum
    elif message_data.response.responseEnum == functional_test_pb2.responseEnum_t.SPI_TRANSMISSION_FAIL:
        return message_data.response.responseEnum
    else:
        return message_data.response.responseRead


def uart_tx(txWord, txSize):
    cmd = functional_test_pb2.Command()
    cmd.commandType = functional_test_pb2.Command()
    cmd.usart.bus = USART1
    cmd.usart.mode = functional_test_pb2.usartMode.USART_MODE_ASYNCHRONOUS
    cmd.usart.baudrate = 115200
    cmd.usart.wordLength = functional_test_pb2.usartWordLength.USART_8_BITS
    cmd.usart.parity = functional_test_pb2.usartParity.USART_PARITY_NONE
    cmd.usart.stopBits = functional_test_pb2.usartStopBits.USART_STOP_BITS_1
    cmd.usart.direction = functional_test_pb2.usartDirection.USART_TX
    cmd.usart.command = txWord
    cmd.usart.txSize = txSize
    cmd.usart.rxSize = 0
    cmd.hwFlowControl = functional_test_pb2.usartHardwareFlowControl.USART_HW_FLOW_DISABLE
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    return message_data.response.responseEnum

def uart_rx(rxSize):
    cmd = functional_test_pb2.Command()
    cmd.commandType = functional_test_pb2.Command()
    cmd.usart.bus = USART1
    cmd.usart.mode = functional_test_pb2.usartMode.USART_MODE_ASYNCHRONOUS
    cmd.usart.baudrate = 115200
    cmd.usart.wordLength = functional_test_pb2.usartWordLength.USART_8_BITS
    cmd.usart.parity = functional_test_pb2.usartParity.USART_PARITY_NONE
    cmd.usart.stopBits = functional_test_pb2.usartStopBits.USART_STOP_BITS_1
    cmd.usart.direction = functional_test_pb2.usartDirection.USART_RX
    cmd.usart.command = 0
    cmd.usart.txSize = 0
    cmd.usart.rxSize = rxSize
    cmd.hwFlowControl = functional_test_pb2.usartHardwareFlowControl.USART_HW_FLOW_DISABLE
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    if message_data.response.responseEnum == functional_test_pb2.responseEnum_t.USART_RX_FAIL:
        return message_data.response.responseEnum
    else:
        return message_data.response.responseRead

def uart_tx_rx(txWord, txSize, rxSize):
    cmd = functional_test_pb2.Command()
    cmd.commandType = functional_test_pb2.Command()
    cmd.usart.bus = USART1
    cmd.usart.mode = functional_test_pb2.usartMode.USART_MODE_ASYNCHRONOUS
    cmd.usart.baudrate = 115200
    cmd.usart.wordLength = functional_test_pb2.usartWordLength.USART_8_BITS
    cmd.usart.parity = functional_test_pb2.usartParity.USART_PARITY_NONE
    cmd.usart.stopBits = functional_test_pb2.usartStopBits.USART_STOP_BITS_1
    cmd.usart.direction = functional_test_pb2.usartDirection.USART_RX
    cmd.usart.command = txWord
    cmd.usart.txSize = txSize
    cmd.usart.rxSize = rxSize
    cmd.hwFlowControl = functional_test_pb2.usartHardwareFlowControl.USART_HW_FLOW_DISABLE
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    if message_data.response.responseEnum == functional_test_pb2.responseEnum_t.USART_TX_RX_FAIL:
        return message_data.response.responseEnum
    else:
        return message_data.response.responseRead

def gpio_write(pin, state):
    cmd = functional_test_pb2.Command()
    cmd.gpio.pin = pin
    cmd.gpio.direction = functional_test_pb2.gpioDirection.GPIO_OUTPUT
    cmd.gpio.state = state
    cmd.gpio.pull = functional_test_pb2.gpioPull.GPIO_NO_PULL
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    return message_data.response.responseEnum


def gpio_read(pin):
    cmd = functional_test_pb2.Command()
    cmd.gpio.pin = pin
    cmd.gpio.direction = functional_test_pb2.gpioDirection.GPIO_INPUT
    cmd.gpio.state = state
    cmd.gpio.pull = functional_test_pb2.gpioPull.GPIO_NO_PULL
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    return message_data.response.responseRead

def analog_read(channel):
    cmd = functional_test_pb2.Command()
    cmd.analog_in.instance = functional_test_pb2.adcInstance.ADC1
    cmd.analog_in.channel = channel
    cmd.analog_in.pin = sequence.select_pin_for_adc_channel(channel)
    cmd.gpio.direction = functional_test_pb2.gpioDirection.GPIO_INPUT
    cmd.gpio.state = state
    cmd.gpio.pull = functional_test_pb2.gpioPull.GPIO_NO_PULL
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    return message_data.response.responseRead


def pwm(pin, frequency, dutyCycle):
    cmd = functional_test_pb2.Command()
    cmd.analog_out.pin = pin
    cmd.analog_out.frequency = frequency
    cmd.analog_out.dutyCycle = dutyCycle
    cmd.analog_out.dependency = functional_test_pb2.pwmTimeDependency.PWM_TIME_DEPENDENCY_DISABLED
    # Send message
    encode_and_send(cmd)
    # Get response
    message_data = receive_and_decode()
    return message_data.response.responseEnum


def encode_and_send(cmd):
    pb = cmd.SerializeToString()
    LL.link_frame_data(pb)
    ser.write(LL.tx_buffer)

def receive_and_decode():
    response_data = ser.read(response_num)              # Read response data
    LL.link_unframe_data(response_data)                 # Unframe response data
    pb = array.array('B',LL.rx_buffer).tobytes()        # Make string from response data
    message_data = functional_test_pb2.Command()
    message_data.ParseFromString(pb)                        # Deserialize response data into data structure
    return message_data
