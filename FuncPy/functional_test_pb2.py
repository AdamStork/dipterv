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
  serialized_pb=_b('\n\x15\x66unctional_test.proto\">\n\x07i2cTest\x12\x11\n\tdirection\x18\x01 \x02(\x08\x12\x0f\n\x07regAddr\x18\x02 \x02(\r\x12\x0f\n\x07regData\x18\x03 \x01(\r\"M\n\x07spiTest\x12 \n\tdirection\x18\x01 \x02(\x0e\x32\r.spiDirection\x12\x0f\n\x07regData\x18\x02 \x01(\r\x12\x0f\n\x07spiMode\x18\x03 \x01(\r\"e\n\x08gpioTest\x12\x15\n\x03pin\x18\x01 \x02(\x0e\x32\x08.gpioPin\x12!\n\tdirection\x18\x02 \x02(\x0e\x32\x0e.gpioDirection\x12\x1f\n\x08pinState\x18\x03 \x02(\x0e\x32\r.gpioPinState\"O\n\ttimerTest\x12!\n\tdirection\x18\x01 \x02(\x0e\x32\x0e.gpioDirection\x12\x1f\n\x08pinState\x18\x02 \x02(\x0e\x32\r.gpioPinState\"F\n\x07pwmTest\x12\x15\n\x03pin\x18\x01 \x02(\x0e\x32\x08.gpioPin\x12\x11\n\tfrequency\x18\x02 \x02(\r\x12\x11\n\tdutyCycle\x18\x03 \x02(\r\"l\n\x07ledTest\x12\x10\n\x08ledState\x18\x01 \x02(\x08\x12\x10\n\x08gpioPort\x18\x02 \x01(\r\x12\x0f\n\x07gpioPin\x18\x03 \x01(\r\x12\x19\n\x11\x62linkingFrequency\x18\x04 \x01(\r\x12\x11\n\tluminance\x18\x05 \x01(\r\"\xef\x01\n\x07\x43ommand\x12%\n\x0b\x63ommandType\x18\x01 \x02(\x0e\x32\x10.CommandTypeEnum\x12\x1d\n\x0bi2cTestType\x18\x02 \x01(\x0b\x32\x08.i2cTest\x12\x1d\n\x0bspiTestType\x18\x03 \x01(\x0b\x32\x08.spiTest\x12\x1f\n\x0cgpioTestType\x18\x05 \x01(\x0b\x32\t.gpioTest\x12!\n\rtimerTestType\x18\x06 \x01(\x0b\x32\n.timerTest\x12\x1d\n\x0bpwmTestType\x18\x07 \x01(\x0b\x32\x08.pwmTest\x12\x1c\n\nledTesType\x18\n \x01(\x0b\x32\x08.ledTest*\x9d\x01\n\x0f\x43ommandTypeEnum\x12\x15\n\x11STOP_CURRENT_TEST\x10\x00\x12\x0c\n\x08\x41\x44\x43_test\x10\x01\x12\x0c\n\x08I2C_test\x10\x02\x12\x0c\n\x08SPI_test\x10\x04\x12\x0c\n\x08LED_test\x10\x06\x12\r\n\tGPIO_test\x10\x07\x12\x15\n\x11TIMER_SINGLE_SHOT\x10\x08\x12\x0c\n\x08RTC_test\x10\t\x12\x07\n\x03PWM\x10\n*\xd0\x01\n\x0cspiDirection\x12\x16\n\x12\x46ULL_DUPLEX_MASTER\x10\x00\x12\x15\n\x11\x46ULL_DUPLEX_SLAVE\x10\x01\x12\x16\n\x12HALF_DUPLEX_MASTER\x10\x02\x12\x15\n\x11HALF_DUPLEX_SLAVE\x10\x03\x12\x17\n\x13RECEIVE_ONLY_MASTER\x10\x04\x12\x16\n\x12RECEIVE_ONLY_SLAVE\x10\x05\x12\x18\n\x14TRANSMIT_ONLY_MASTER\x10\x06\x12\x17\n\x13TRANSMIT_ONLY_SLAVE\x10\x07*\xcb\x03\n\x07gpioPin\x12\x07\n\x03PA0\x10\x00\x12\x07\n\x03PA1\x10\x01\x12\x07\n\x03PA2\x10\x02\x12\x07\n\x03PA3\x10\x03\x12\x07\n\x03PA4\x10\x04\x12\x07\n\x03PA5\x10\x05\x12\x07\n\x03PA6\x10\x06\x12\x07\n\x03PA7\x10\x07\x12\x07\n\x03PA8\x10\x08\x12\x07\n\x03PA9\x10\t\x12\x08\n\x04PA10\x10\n\x12\x08\n\x04PA11\x10\x0b\x12\x08\n\x04PA12\x10\x0c\x12\x08\n\x04PA13\x10\r\x12\x08\n\x04PA14\x10\x0e\x12\x08\n\x04PA15\x10\x0f\x12\x07\n\x03PB0\x10\x14\x12\x07\n\x03PB1\x10\x15\x12\x07\n\x03PB2\x10\x16\x12\x07\n\x03PB3\x10\x17\x12\x07\n\x03PB4\x10\x18\x12\x07\n\x03PB5\x10\x19\x12\x07\n\x03PB6\x10\x1a\x12\x07\n\x03PB7\x10\x1b\x12\x07\n\x03PB8\x10\x1c\x12\x07\n\x03PB9\x10\x1d\x12\x08\n\x04PB10\x10\x1e\x12\x08\n\x04PB11\x10\x1f\x12\x08\n\x04PB12\x10 \x12\x08\n\x04PB13\x10!\x12\x08\n\x04PB14\x10\"\x12\x08\n\x04PB15\x10#\x12\x07\n\x03PC0\x10(\x12\x07\n\x03PC1\x10)\x12\x07\n\x03PC2\x10*\x12\x07\n\x03PC3\x10+\x12\x07\n\x03PC4\x10,\x12\x07\n\x03PC5\x10-\x12\x07\n\x03PC6\x10.\x12\x07\n\x03PC7\x10/\x12\x07\n\x03PC8\x10\x30\x12\x07\n\x03PC9\x10\x31\x12\x08\n\x04PC10\x10\x32\x12\x08\n\x04PC11\x10\x33\x12\x08\n\x04PC12\x10\x34\x12\x08\n\x04PC13\x10\x35\x12\x08\n\x04PC14\x10\x36\x12\x08\n\x04PC15\x10\x37*0\n\rgpioDirection\x12\x0e\n\nGPIO_INPUT\x10\x00\x12\x0f\n\x0bGPIO_OUTPUT\x10\x01*!\n\x0cgpioPinState\x12\x07\n\x03LOW\x10\x00\x12\x08\n\x04HIGH\x10\x01')
)

_COMMANDTYPEENUM = _descriptor.EnumDescriptor(
  name='CommandTypeEnum',
  full_name='CommandTypeEnum',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='STOP_CURRENT_TEST', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ADC_test', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='I2C_test', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SPI_test', index=3, number=4,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LED_test', index=4, number=6,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GPIO_test', index=5, number=7,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TIMER_SINGLE_SHOT', index=6, number=8,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RTC_test', index=7, number=9,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PWM', index=8, number=10,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=777,
  serialized_end=934,
)
_sym_db.RegisterEnumDescriptor(_COMMANDTYPEENUM)

CommandTypeEnum = enum_type_wrapper.EnumTypeWrapper(_COMMANDTYPEENUM)
_SPIDIRECTION = _descriptor.EnumDescriptor(
  name='spiDirection',
  full_name='spiDirection',
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
  serialized_start=937,
  serialized_end=1145,
)
_sym_db.RegisterEnumDescriptor(_SPIDIRECTION)

spiDirection = enum_type_wrapper.EnumTypeWrapper(_SPIDIRECTION)
_GPIOPIN = _descriptor.EnumDescriptor(
  name='gpioPin',
  full_name='gpioPin',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='PA0', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA1', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA2', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA3', index=3, number=3,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA4', index=4, number=4,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA5', index=5, number=5,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA6', index=6, number=6,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA7', index=7, number=7,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA8', index=8, number=8,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA9', index=9, number=9,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA10', index=10, number=10,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA11', index=11, number=11,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA12', index=12, number=12,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA13', index=13, number=13,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA14', index=14, number=14,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PA15', index=15, number=15,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB0', index=16, number=20,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB1', index=17, number=21,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB2', index=18, number=22,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB3', index=19, number=23,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB4', index=20, number=24,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB5', index=21, number=25,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB6', index=22, number=26,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB7', index=23, number=27,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB8', index=24, number=28,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB9', index=25, number=29,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB10', index=26, number=30,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB11', index=27, number=31,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB12', index=28, number=32,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB13', index=29, number=33,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB14', index=30, number=34,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PB15', index=31, number=35,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC0', index=32, number=40,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC1', index=33, number=41,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC2', index=34, number=42,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC3', index=35, number=43,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC4', index=36, number=44,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC5', index=37, number=45,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC6', index=38, number=46,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC7', index=39, number=47,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC8', index=40, number=48,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC9', index=41, number=49,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC10', index=42, number=50,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC11', index=43, number=51,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC12', index=44, number=52,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC13', index=45, number=53,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC14', index=46, number=54,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PC15', index=47, number=55,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1148,
  serialized_end=1607,
)
_sym_db.RegisterEnumDescriptor(_GPIOPIN)

gpioPin = enum_type_wrapper.EnumTypeWrapper(_GPIOPIN)
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
  serialized_start=1609,
  serialized_end=1657,
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
      name='LOW', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HIGH', index=1, number=1,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1659,
  serialized_end=1692,
)
_sym_db.RegisterEnumDescriptor(_GPIOPINSTATE)

gpioPinState = enum_type_wrapper.EnumTypeWrapper(_GPIOPINSTATE)
STOP_CURRENT_TEST = 0
ADC_test = 1
I2C_test = 2
SPI_test = 4
LED_test = 6
GPIO_test = 7
TIMER_SINGLE_SHOT = 8
RTC_test = 9
PWM = 10
FULL_DUPLEX_MASTER = 0
FULL_DUPLEX_SLAVE = 1
HALF_DUPLEX_MASTER = 2
HALF_DUPLEX_SLAVE = 3
RECEIVE_ONLY_MASTER = 4
RECEIVE_ONLY_SLAVE = 5
TRANSMIT_ONLY_MASTER = 6
TRANSMIT_ONLY_SLAVE = 7
PA0 = 0
PA1 = 1
PA2 = 2
PA3 = 3
PA4 = 4
PA5 = 5
PA6 = 6
PA7 = 7
PA8 = 8
PA9 = 9
PA10 = 10
PA11 = 11
PA12 = 12
PA13 = 13
PA14 = 14
PA15 = 15
PB0 = 20
PB1 = 21
PB2 = 22
PB3 = 23
PB4 = 24
PB5 = 25
PB6 = 26
PB7 = 27
PB8 = 28
PB9 = 29
PB10 = 30
PB11 = 31
PB12 = 32
PB13 = 33
PB14 = 34
PB15 = 35
PC0 = 40
PC1 = 41
PC2 = 42
PC3 = 43
PC4 = 44
PC5 = 45
PC6 = 46
PC7 = 47
PC8 = 48
PC9 = 49
PC10 = 50
PC11 = 51
PC12 = 52
PC13 = 53
PC14 = 54
PC15 = 55
GPIO_INPUT = 0
GPIO_OUTPUT = 1
LOW = 0
HIGH = 1



_I2CTEST = _descriptor.Descriptor(
  name='i2cTest',
  full_name='i2cTest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='direction', full_name='i2cTest.direction', index=0,
      number=1, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='regAddr', full_name='i2cTest.regAddr', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='regData', full_name='i2cTest.regData', index=2,
      number=3, type=13, cpp_type=3, label=1,
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
  serialized_end=87,
)


_SPITEST = _descriptor.Descriptor(
  name='spiTest',
  full_name='spiTest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='direction', full_name='spiTest.direction', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='regData', full_name='spiTest.regData', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='spiMode', full_name='spiTest.spiMode', index=2,
      number=3, type=13, cpp_type=3, label=1,
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
  serialized_start=89,
  serialized_end=166,
)


_GPIOTEST = _descriptor.Descriptor(
  name='gpioTest',
  full_name='gpioTest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='pin', full_name='gpioTest.pin', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='direction', full_name='gpioTest.direction', index=1,
      number=2, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pinState', full_name='gpioTest.pinState', index=2,
      number=3, type=14, cpp_type=8, label=2,
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
  serialized_start=168,
  serialized_end=269,
)


_TIMERTEST = _descriptor.Descriptor(
  name='timerTest',
  full_name='timerTest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='direction', full_name='timerTest.direction', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pinState', full_name='timerTest.pinState', index=1,
      number=2, type=14, cpp_type=8, label=2,
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
  serialized_start=271,
  serialized_end=350,
)


_PWMTEST = _descriptor.Descriptor(
  name='pwmTest',
  full_name='pwmTest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='pin', full_name='pwmTest.pin', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='frequency', full_name='pwmTest.frequency', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='dutyCycle', full_name='pwmTest.dutyCycle', index=2,
      number=3, type=13, cpp_type=3, label=2,
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
  serialized_start=352,
  serialized_end=422,
)


_LEDTEST = _descriptor.Descriptor(
  name='ledTest',
  full_name='ledTest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='ledState', full_name='ledTest.ledState', index=0,
      number=1, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='gpioPort', full_name='ledTest.gpioPort', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='gpioPin', full_name='ledTest.gpioPin', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='blinkingFrequency', full_name='ledTest.blinkingFrequency', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='luminance', full_name='ledTest.luminance', index=4,
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
  serialized_start=424,
  serialized_end=532,
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
      name='i2cTestType', full_name='Command.i2cTestType', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='spiTestType', full_name='Command.spiTestType', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='gpioTestType', full_name='Command.gpioTestType', index=3,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='timerTestType', full_name='Command.timerTestType', index=4,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pwmTestType', full_name='Command.pwmTestType', index=5,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='ledTesType', full_name='Command.ledTesType', index=6,
      number=10, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
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
  serialized_start=535,
  serialized_end=774,
)

_SPITEST.fields_by_name['direction'].enum_type = _SPIDIRECTION
_GPIOTEST.fields_by_name['pin'].enum_type = _GPIOPIN
_GPIOTEST.fields_by_name['direction'].enum_type = _GPIODIRECTION
_GPIOTEST.fields_by_name['pinState'].enum_type = _GPIOPINSTATE
_TIMERTEST.fields_by_name['direction'].enum_type = _GPIODIRECTION
_TIMERTEST.fields_by_name['pinState'].enum_type = _GPIOPINSTATE
_PWMTEST.fields_by_name['pin'].enum_type = _GPIOPIN
_COMMAND.fields_by_name['commandType'].enum_type = _COMMANDTYPEENUM
_COMMAND.fields_by_name['i2cTestType'].message_type = _I2CTEST
_COMMAND.fields_by_name['spiTestType'].message_type = _SPITEST
_COMMAND.fields_by_name['gpioTestType'].message_type = _GPIOTEST
_COMMAND.fields_by_name['timerTestType'].message_type = _TIMERTEST
_COMMAND.fields_by_name['pwmTestType'].message_type = _PWMTEST
_COMMAND.fields_by_name['ledTesType'].message_type = _LEDTEST
DESCRIPTOR.message_types_by_name['i2cTest'] = _I2CTEST
DESCRIPTOR.message_types_by_name['spiTest'] = _SPITEST
DESCRIPTOR.message_types_by_name['gpioTest'] = _GPIOTEST
DESCRIPTOR.message_types_by_name['timerTest'] = _TIMERTEST
DESCRIPTOR.message_types_by_name['pwmTest'] = _PWMTEST
DESCRIPTOR.message_types_by_name['ledTest'] = _LEDTEST
DESCRIPTOR.message_types_by_name['Command'] = _COMMAND
DESCRIPTOR.enum_types_by_name['CommandTypeEnum'] = _COMMANDTYPEENUM
DESCRIPTOR.enum_types_by_name['spiDirection'] = _SPIDIRECTION
DESCRIPTOR.enum_types_by_name['gpioPin'] = _GPIOPIN
DESCRIPTOR.enum_types_by_name['gpioDirection'] = _GPIODIRECTION
DESCRIPTOR.enum_types_by_name['gpioPinState'] = _GPIOPINSTATE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

i2cTest = _reflection.GeneratedProtocolMessageType('i2cTest', (_message.Message,), dict(
  DESCRIPTOR = _I2CTEST,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:i2cTest)
  ))
_sym_db.RegisterMessage(i2cTest)

spiTest = _reflection.GeneratedProtocolMessageType('spiTest', (_message.Message,), dict(
  DESCRIPTOR = _SPITEST,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:spiTest)
  ))
_sym_db.RegisterMessage(spiTest)

gpioTest = _reflection.GeneratedProtocolMessageType('gpioTest', (_message.Message,), dict(
  DESCRIPTOR = _GPIOTEST,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:gpioTest)
  ))
_sym_db.RegisterMessage(gpioTest)

timerTest = _reflection.GeneratedProtocolMessageType('timerTest', (_message.Message,), dict(
  DESCRIPTOR = _TIMERTEST,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:timerTest)
  ))
_sym_db.RegisterMessage(timerTest)

pwmTest = _reflection.GeneratedProtocolMessageType('pwmTest', (_message.Message,), dict(
  DESCRIPTOR = _PWMTEST,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:pwmTest)
  ))
_sym_db.RegisterMessage(pwmTest)

ledTest = _reflection.GeneratedProtocolMessageType('ledTest', (_message.Message,), dict(
  DESCRIPTOR = _LEDTEST,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:ledTest)
  ))
_sym_db.RegisterMessage(ledTest)

Command = _reflection.GeneratedProtocolMessageType('Command', (_message.Message,), dict(
  DESCRIPTOR = _COMMAND,
  __module__ = 'functional_test_pb2'
  # @@protoc_insertion_point(class_scope:Command)
  ))
_sym_db.RegisterMessage(Command)


# @@protoc_insertion_point(module_scope)
