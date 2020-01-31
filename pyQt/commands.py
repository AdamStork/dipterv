#   Python file for test functions
#    i2c_read()
#    i2c_write()
#    spi_receive()
#    spi_transmit()
#    gpio_digital_write()
#    gpio_digital_read()
#    analog_read()
#    analog_write()

# teszt fuggvenyek: create_command, add_data_depending_on... reszet lehetne kulonbontani ide.


import functional_test_pb2
import sequence

# Make protobuf encoded command for i2c read
def command_i2c(test_object):
    command = functional_test_pb2.Command()
    command.commandType = test_object.commandType





# layoutbol kimentés lokális változokba és paraméterként átadás i2c_read fvnek pl.
# i2c_read fv: cmd = Command(), cmd.commandType= ... return command? ezt a commandot meg ki lehet mar kuldeni serialon keresztul
