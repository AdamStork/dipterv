# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: functional_test.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='functional_test.proto',
  package='',
  syntax='proto2',
  serialized_options=None,
  serialized_pb=_b('\n\x15\x66unctional_test.proto\"b\n\ni2cMessage\x12\x14\n\x03\x62us\x18\x01 \x02(\x0e\x32\x07.i2cBus\x12\x0f\n\x07\x61\x64\x64ress\x18\x02 \x02(\r\x12\x0b\n\x03reg\x18\x03 \x02(\r\x12 \n\tdirection\x18\x04 \x02(\x0e\x32\r.i2cDirection\"\x9d\x01\n\nspiMessage\x12\x14\n\x03\x62us\x18\x01 \x02(\x0e\x32\x07.spiBus\x12\x16\n\x04mode\x18\x02 \x01(\x0e\x32\x08.spiMode\x12\x19\n\x05\x63lock\x18\x03 \x02(\x0e\x32\n.clockMode\x12\x0f\n\x07\x63ommand\x18\x04 \x02(\r\x12 \n\tdirection\x18\x05 \x02(\x0e\x32\r.spiDirection\x12\x13\n\x0b\x64ummyclocks\x18\x06 \x01(\r\"w\n\x0b\x64igitalGPIO\x12\x17\n\x04port\x18\x01 \x02(\x0e\x32\t.gpioPort\x12\x0b\n\x03pin\x18\x02 \x02(\r\x12!\n\tdirection\x18\x03 \x02(\x0e\x32\x0e.gpioDirection\x12\x1f\n\x08pinState\x18\x04 \x02(\x0e\x32\r.gpioPinState\"v\n\x08\x61nalogIN\x12\x1a\n\x02\x66s\x18\x01 \x02(\x0e\x32\x0e.ADC_FULLSCALE\x12\x15\n\x03mpx\x18\x02 \x02(\x0e\x32\x08.ADC_MPX\x12\x17\n\x04port\x18\x03 \x02(\x0e\x32\t.gpioPort\x12\x0b\n\x03pin\x18\x04 \x02(\r\x12\x11\n\tdutyCycle\x18\x05 \x01(\r\"W\n\tanalogOUT\x12\x17\n\x04port\x18\x01 \x02(\x0e\x32\t.gpioPort\x12\x0b\n\x03pin\x18\x02 \x02(\r\x12\x11\n\tfrequency\x18\x03 \x02(\r\x12\x11\n\tdutyCycle\x18\x04 \x02(\r\"\xfd\x01\n\x07\x43ommand\x12%\n\x0b\x63ommandType\x18\x01 \x02(\x0e\x32\x10.CommandTypeEnum\x12\x18\n\x03i2c\x18\x02 \x01(\x0b\x32\x0b.i2cMessage\x12\x18\n\x03spi\x18\x03 \x01(\x0b\x32\x0b.spiMessage\x12\x1a\n\x04gpio\x18\x04 \x01(\x0b\x32\x0c.digitalGPIO\x12\x1c\n\tanalog_in\x18\x06 \x01(\x0b\x32\t.analogIN\x12\x1e\n\nanalog_out\x18\x07 \x01(\x0b\x32\n.analogOUT\x12\x14\n\x0cresponseRead\x18\n \x01(\r\x12\'\n\rresponseWrite\x18\x0b \x01(\x0e\x32\x10.successfulWrite*p\n\x0f\x43ommandTypeEnum\x12\x0c\n\x08LED_test\x10\x00\x12\x0c\n\x08I2C_test\x10\x01\x12\x0c\n\x08SPI_test\x10\x02\x12\x10\n\x0cGPIO_digital\x10\x03\x12\x0f\n\x0b\x41nalog_read\x10\x04\x12\x10\n\x0c\x41nalog_write\x10\x05*+\n\x0ci2cDirection\x12\r\n\tI2C_write\x10\x00\x12\x0c\n\x08I2C_read\x10\x01*&\n\x06i2cBus\x12\x08\n\x04I2C1\x10\x01\x12\x08\n\x04I2C2\x10\x02\x12\x08\n\x04I2C3\x10\x03*\xcb\x01\n\x07spiMode\x12\x16\n\x12\x46ULL_DUPLEX_MASTER\x10\x00\x12\x15\n\x11\x46ULL_DUPLEX_SLAVE\x10\x01\x12\x16\n\x12HALF_DUPLEX_MASTER\x10\x02\x12\x15\n\x11HALF_DUPLEX_SLAVE\x10\x03\x12\x17\n\x13RECEIVE_ONLY_MASTER\x10\x04\x12\x16\n\x12RECEIVE_ONLY_SLAVE\x10\x05\x12\x18\n\x14TRANSMIT_ONLY_MASTER\x10\x06\x12\x17\n\x13TRANSMIT_ONLY_SLAVE\x10\x07*1\n\x0cspiDirection\x12\x10\n\x0cSPI_TRANSMIT\x10\x00\x12\x0f\n\x0bSPI_RECEIVE\x10\x01*;\n\tclockMode\x12\n\n\x06MODE_0\x10\x00\x12\n\n\x06MODE_1\x10\x01\x12\n\n\x06MODE_2\x10\x02\x12\n\n\x06MODE_3\x10\x03*9\n\x0bhardwareNSS\x12\x0b\n\x07\x44ISABLE\x10\x00\x12\r\n\tNSS_INPUT\x10\x01\x12\x0e\n\nNSS_OUTPUT\x10\x02*&\n\x06spiBus\x12\x08\n\x04SPI1\x10\x01\x12\x08\n\x04SPI2\x10\x02\x12\x08\n\x04SPI3\x10\x03*0\n\rgpioDirection\x12\x0e\n\nGPIO_INPUT\x10\x00\x12\x0f\n\x0bGPIO_OUTPUT\x10\x01*+\n\x0cgpioPinState\x12\x0c\n\x08GPIO_LOW\x10\x00\x12\r\n\tGPIO_HIGH\x10\x01*=\n\x08gpioPort\x12\x0f\n\x0bGPIO_PORT_A\x10\x00\x12\x0f\n\x0bGPIO_PORT_B\x10\x01\x12\x0f\n\x0bGPIO_PORT_C\x10\x02*\x1d\n\rADC_FULLSCALE\x12\x0c\n\x08\x46S_4P096\x10\x00*\x18\n\x07\x41\x44\x43_MPX\x12\r\n\tMPX_P0_NG\x10\x00*\xa4\x01\n\x0fsuccessfulWrite\x12\x0b\n\x07LED_SET\x10\x00\x12\x10\n\x0cI2C_WRITE_OK\x10\x01\x12\x12\n\x0eI2C_WRITE_FAIL\x10\x02\x12\x10\n\x0cSPI_WRITE_OK\x10\x03\x12\x12\n\x0eSPI_WRITE_FAIL\x10\x04\x12\x0c\n\x08GPIO_SET\x10\x05\x12\x0e\n\nGPIO_RESET\x10\x06\x12\x0b\n\x07PWM_SET\x10\x07\x12\r\n\tPWM_RESET\x10\x08')
)

_COMMANDTYPEENUM = _descriptor.EnumDescriptor(
  name='CommandTypeEnum',
  full_name='CommandTypeEnum',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='LED_test', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='I2C_test', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPI_test', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_digital', index=3, number=3,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Analog_read', index=4, number=4,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Analog_write', index=5, number=5,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=871,
  serialized_end=983,
)
_sym_db.RegisterEnumDescriptor(_COMMANDTYPEENUM)

CommandTypeEnum = enum_type_wrapper.EnumTypeWrapper(_COMMANDTYPEENUM)
_I2CDIRECTION = _descriptor.EnumDescriptor(
  name='i2cDirection',
  full_name='i2cDirection',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='I2C_write', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='I2C_read', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=985,
  serialized_end=1028,
)
_sym_db.RegisterEnumDescriptor(_I2CDIRECTION)

i2cDirection = enum_type_wrapper.EnumTypeWrapper(_I2CDIRECTION)
_I2CBUS = _descriptor.EnumDescriptor(
  name='i2cBus',
  full_name='i2cBus',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='I2C1', index=0, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='I2C2', index=1, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='I2C3', index=2, number=3,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1030,
  serialized_end=1068,
)
_sym_db.RegisterEnumDescriptor(_I2CBUS)

i2cBus = enum_type_wrapper.EnumTypeWrapper(_I2CBUS)
_SPIMODE = _descriptor.EnumDescriptor(
  name='spiMode',
  full_name='spiMode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='FULL_DUPLEX_MASTER', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='FULL_DUPLEX_SLAVE', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HALF_DUPLEX_MASTER', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HALF_DUPLEX_SLAVE', index=3, number=3,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RECEIVE_ONLY_MASTER', index=4, number=4,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RECEIVE_ONLY_SLAVE', index=5, number=5,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TRANSMIT_ONLY_MASTER', index=6, number=6,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TRANSMIT_ONLY_SLAVE', index=7, number=7,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1071,
  serialized_end=1274,
)
_sym_db.RegisterEnumDescriptor(_SPIMODE)

spiMode = enum_type_wrapper.EnumTypeWrapper(_SPIMODE)
_SPIDIRECTION = _descriptor.EnumDescriptor(
  name='spiDirection',
  full_name='spiDirection',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SPI_TRANSMIT', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPI_RECEIVE', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1276,
  serialized_end=1325,
)
_sym_db.RegisterEnumDescriptor(_SPIDIRECTION)

spiDirection = enum_type_wrapper.EnumTypeWrapper(_SPIDIRECTION)
_CLOCKMODE = _descriptor.EnumDescriptor(
  name='clockMode',
  full_name='clockMode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='MODE_0', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MODE_1', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MODE_2', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MODE_3', index=3, number=3,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1327,
  serialized_end=1386,
)
_sym_db.RegisterEnumDescriptor(_CLOCKMODE)

clockMode = enum_type_wrapper.EnumTypeWrapper(_CLOCKMODE)
_HARDWARENSS = _descriptor.EnumDescriptor(
  name='hardwareNSS',
  full_name='hardwareNSS',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='DISABLE', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NSS_INPUT', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NSS_OUTPUT', index=2, number=2,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1388,
  serialized_end=1445,
)
_sym_db.RegisterEnumDescriptor(_HARDWARENSS)

hardwareNSS = enum_type_wrapper.EnumTypeWrapper(_HARDWARENSS)
_SPIBUS = _descriptor.EnumDescriptor(
  name='spiBus',
  full_name='spiBus',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SPI1', index=0, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPI2', index=1, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPI3', index=2, number=3,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1447,
  serialized_end=1485,
)
_sym_db.RegisterEnumDescriptor(_SPIBUS)

spiBus = enum_type_wrapper.EnumTypeWrapper(_SPIBUS)
_GPIODIRECTION = _descriptor.EnumDescriptor(
  name='gpioDirection',
  full_name='gpioDirection',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='GPIO_INPUT', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_OUTPUT', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1487,
  serialized_end=1535,
)
_sym_db.RegisterEnumDescriptor(_GPIODIRECTION)

gpioDirection = enum_type_wrapper.EnumTypeWrapper(_GPIODIRECTION)
_GPIOPINSTATE = _descriptor.EnumDescriptor(
  name='gpioPinState',
  full_name='gpioPinState',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='GPIO_LOW', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_HIGH', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1537,
  serialized_end=1580,
)
_sym_db.RegisterEnumDescriptor(_GPIOPINSTATE)

gpioPinState = enum_type_wrapper.EnumTypeWrapper(_GPIOPINSTATE)
_GPIOPORT = _descriptor.EnumDescriptor(
  name='gpioPort',
  full_name='gpioPort',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='GPIO_PORT_A', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_PORT_B', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_PORT_C', index=2, number=2,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1582,
  serialized_end=1643,
)
_sym_db.RegisterEnumDescriptor(_GPIOPORT)

gpioPort = enum_type_wrapper.EnumTypeWrapper(_GPIOPORT)
_ADC_FULLSCALE = _descriptor.EnumDescriptor(
  name='ADC_FULLSCALE',
  full_name='ADC_FULLSCALE',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='FS_4P096', index=0, number=0,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1645,
  serialized_end=1674,
)
_sym_db.RegisterEnumDescriptor(_ADC_FULLSCALE)

ADC_FULLSCALE = enum_type_wrapper.EnumTypeWrapper(_ADC_FULLSCALE)
_ADC_MPX = _descriptor.EnumDescriptor(
  name='ADC_MPX',
  full_name='ADC_MPX',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='MPX_P0_NG', index=0, number=0,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1676,
  serialized_end=1700,
)
_sym_db.RegisterEnumDescriptor(_ADC_MPX)

ADC_MPX = enum_type_wrapper.EnumTypeWrapper(_ADC_MPX)
_SUCCESSFULWRITE = _descriptor.EnumDescriptor(
  name='successfulWrite',
  full_name='successfulWrite',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='LED_SET', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='I2C_WRITE_OK', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='I2C_WRITE_FAIL', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPI_WRITE_OK', index=3, number=3,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPI_WRITE_FAIL', index=4, number=4,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_SET', index=5, number=5,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_RESET', index=6, number=6,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PWM_SET', index=7, number=7,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PWM_RESET', index=8, number=8,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1703,
  serialized_end=1867,
)
_sym_db.RegisterEnumDescriptor(_SUCCESSFULWRITE)

successfulWrite = enum_type_wrapper.EnumTypeWrapper(_SUCCESSFULWRITE)
LED_test = 0
I2C_test = 1
SPI_test = 2
GPIO_digital = 3
Analog_read = 4
Analog_write = 5
I2C_write = 0
I2C_read = 1
I2C1 = 1
I2C2 = 2
I2C3 = 3
FULL_DUPLEX_MASTER = 0
FULL_DUPLEX_SLAVE = 1
HALF_DUPLEX_MASTER = 2
HALF_DUPLEX_SLAVE = 3
RECEIVE_ONLY_MASTER = 4
RECEIVE_ONLY_SLAVE = 5
TRANSMIT_ONLY_MASTER = 6
TRANSMIT_ONLY_SLAVE = 7
SPI_TRANSMIT = 0
SPI_RECEIVE = 1
MODE_0 = 0
MODE_1 = 1
MODE_2 = 2
MODE_3 = 3
DISABLE = 0
NSS_INPUT = 1
NSS_OUTPUT = 2
SPI1 = 1
SPI2 = 2
SPI3 = 3
GPIO_INPUT = 0
GPIO_OUTPUT = 1
GPIO_LOW = 0
GPIO_HIGH = 1
GPIO_PORT_A = 0
GPIO_PORT_B = 1
GPIO_PORT_C = 2
FS_4P096 = 0
MPX_P0_NG = 0
LED_SET = 0
I2C_WRITE_OK = 1
I2C_WRITE_FAIL = 2
SPI_WRITE_OK = 3
SPI_WRITE_FAIL = 4
GPIO_SET = 5
GPIO_RESET = 6
PWM_SET = 7
PWM_RESET = 8



_I2CMESSAGE = _descriptor.Descriptor(
  name='i2cMessage',
  full_name='i2cMessage',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='bus', full_name='i2cMessage.bus', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='address', full_name='i2cMessage.address', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='reg', full_name='i2cMessage.reg', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='direction', full_name='i2cMessage.direction', index=3,
      number=4, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=25,
  serialized_end=123,
)


_SPIMESSAGE = _descriptor.Descriptor(
  name='spiMessage',
  full_name='spiMessage',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='bus', full_name='spiMessage.bus', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='mode', full_name='spiMessage.mode', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='clock', full_name='spiMessage.clock', index=2,
      number=3, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='command', full_name='spiMessage.command', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='direction', full_name='spiMessage.direction', index=4,
      number=5, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='dummyclocks', full_name='spiMessage.dummyclocks', index=5,
      number=6, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=126,
  serialized_end=283,
)


_DIGITALGPIO = _descriptor.Descriptor(
  name='digitalGPIO',
  full_name='digitalGPIO',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='port', full_name='digitalGPIO.port', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pin', full_name='digitalGPIO.pin', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='direction', full_name='digitalGPIO.direction', index=2,
      number=3, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pinState', full_name='digitalGPIO.pinState', index=3,
      number=4, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=285,
  serialized_end=404,
)


_ANALOGIN = _descriptor.Descriptor(
  name='analogIN',
  full_name='analogIN',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='fs', full_name='analogIN.fs', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='mpx', full_name='analogIN.mpx', index=1,
      number=2, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='port', full_name='analogIN.port', index=2,
      number=3, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pin', full_name='analogIN.pin', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='dutyCycle', full_name='analogIN.dutyCycle', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=406,
  serialized_end=524,
)


_ANALOGOUT = _descriptor.Descriptor(
  name='analogOUT',
  full_name='analogOUT',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='port', full_name='analogOUT.port', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pin', full_name='analogOUT.pin', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='frequency', full_name='analogOUT.frequency', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='dutyCycle', full_name='analogOUT.dutyCycle', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=526,
  serialized_end=613,
)


_COMMAND = _descriptor.Descriptor(
  name='Command',
  full_name='Command',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='commandType', full_name='Command.commandType', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='i2c', full_name='Command.i2c', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='spi', full_name='Command.spi', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='gpio', full_name='Command.gpio', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='analog_in', full_name='Command.analog_in', index=4,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='analog_out', full_name='Command.analog_out', index=5,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='responseRead', full_name='Command.responseRead', index=6,
      number=10, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='responseWrite', full_name='Command.responseWrite', index=7,
      number=11, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=616,
  serialized_end=869,
)

_I2CMESSAGE.fields_by_name['bus'].enum_type = _I2CBUS
_I2CMESSAGE.fields_by_name['direction'].enum_type = _I2CDIRECTION
_SPIMESSAGE.fields_by_name['bus'].enum_type = _SPIBUS
_SPIMESSAGE.fields_by_name['mode'].enum_type = _SPIMODE
_SPIMESSAGE.fields_by_name['clock'].enum_type = _CLOCKMODE
_SPIMESSAGE.fields_by_name['direction'].enum_type = _SPIDIRECTION
_DIGITALGPIO.fields_by_name['port'].enum_type = _GPIOPORT
_DIGITALGPIO.fields_by_name['direction'].enum_type = _GPIODIRECTION
_DIGITALGPIO.fields_by_name['pinState'].enum_type = _GPIOPINSTATE
_ANALOGIN.fields_by_name['fs'].enum_type = _ADC_FULLSCALE
_ANALOGIN.fields_by_name['mpx'].enum_type = _ADC_MPX
_ANALOGIN.fields_by_name['port'].enum_type = _GPIOPORT
_ANALOGOUT.fields_by_name['port'].enum_type = _GPIOPORT
_COMMAND.fields_by_name['commandType'].enum_type = _COMMANDTYPEENUM
_COMMAND.fields_by_name['i2c'].message_type = _I2CMESSAGE
_COMMAND.fields_by_name['spi'].message_type = _SPIMESSAGE
_COMMAND.fields_by_name['gpio'].message_type = _DIGITALGPIO
_COMMAND.fields_by_name['analog_in'].message_type = _ANALOGIN
_COMMAND.fields_by_name['analog_out'].message_type = _ANALOGOUT
_COMMAND.fields_by_name['responseWrite'].enum_type = _SUCCESSFULWRITE
DESCRIPTOR.message_types_by_name['i2cMessage'] = _I2CMESSAGE
DESCRIPTOR.message_types_by_name['spiMessage'] = _SPIMESSAGE
DESCRIPTOR.message_types_by_name['digitalGPIO'] = _DIGITALGPIO
DESCRIPTOR.message_types_by_name['analogIN'] = _ANALOGIN
DESCRIPTOR.message_types_by_name['analogOUT'] = _ANALOGOUT
DESCRIPTOR.message_types_by_name['Command'] = _COMMAND
DESCRIPTOR.enum_types_by_name['CommandTypeEnum'] = _COMMANDTYPEENUM
DESCRIPTOR.enum_types_by_name['i2cDirection'] = _I2CDIRECTION
DESCRIPTOR.enum_types_by_name['i2cBus'] = _I2CBUS
DESCRIPTOR.enum_types_by_name['spiMode'] = _SPIMODE
DESCRIPTOR.enum_types_by_name['spiDirection'] = _SPIDIRECTION
DESCRIPTOR.enum_types_by_name['clockMode'] = _CLOCKMODE
DESCRIPTOR.enum_types_by_name['hardwareNSS'] = _HARDWARENSS
DESCRIPTOR.enum_types_by_name['spiBus'] = _SPIBUS
DESCRIPTOR.enum_types_by_name['gpioDirection'] = _GPIODIRECTION
DESCRIPTOR.enum_types_by_name['gpioPinState'] = _GPIOPINSTATE
DESCRIPTOR.enum_types_by_name['gpioPort'] = _GPIOPORT
DESCRIPTOR.enum_types_by_name['ADC_FULLSCALE'] = _ADC_FULLSCALE
DESCRIPTOR.enum_types_by_name['ADC_MPX'] = _ADC_MPX
DESCRIPTOR.enum_types_by_name['successfulWrite'] = _SUCCESSFULWRITE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

i2cMessage = _reflection.GeneratedProtocolMessageType('i2cMessage', (_message.Message,), dict(
  DESCRIPTOR = _I2CMESSAGE,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:i2cMessage)
  ))
_sym_db.RegisterMessage(i2cMessage)

spiMessage = _reflection.GeneratedProtocolMessageType('spiMessage', (_message.Message,), dict(
  DESCRIPTOR = _SPIMESSAGE,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:spiMessage)
  ))
_sym_db.RegisterMessage(spiMessage)

digitalGPIO = _reflection.GeneratedProtocolMessageType('digitalGPIO', (_message.Message,), dict(
  DESCRIPTOR = _DIGITALGPIO,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:digitalGPIO)
  ))
_sym_db.RegisterMessage(digitalGPIO)

analogIN = _reflection.GeneratedProtocolMessageType('analogIN', (_message.Message,), dict(
  DESCRIPTOR = _ANALOGIN,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:analogIN)
  ))
_sym_db.RegisterMessage(analogIN)

analogOUT = _reflection.GeneratedProtocolMessageType('analogOUT', (_message.Message,), dict(
  DESCRIPTOR = _ANALOGOUT,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:analogOUT)
  ))
_sym_db.RegisterMessage(analogOUT)

Command = _reflection.GeneratedProtocolMessageType('Command', (_message.Message,), dict(
  DESCRIPTOR = _COMMAND,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:Command)
  ))
_sym_db.RegisterMessage(Command)


# @@protoc_insertion_point(module_scope)
