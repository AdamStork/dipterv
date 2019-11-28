# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: test.proto

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
  name='test.proto',
  package='',
  syntax='proto2',
  serialized_options=None,
  serialized_pb=_b('\n\ntest.proto\"0\n\x07\x43ommand\x12%\n\x0b\x63ommandType\x18\x01 \x02(\x0e\x32\x10.CommandTypeEnum*<\n\x0f\x43ommandTypeEnum\x12\x0c\n\x08TEST_ADC\x10\x00\x12\x0c\n\x08TEST_I2C\x10\x01\x12\r\n\tTEST_GPIO\x10\x02')
)

_COMMANDTYPEENUM = _descriptor.EnumDescriptor(
  name='CommandTypeEnum',
  full_name='CommandTypeEnum',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TEST_ADC', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TEST_I2C', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TEST_GPIO', index=2, number=2,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=64,
  serialized_end=124,
)
_sym_db.RegisterEnumDescriptor(_COMMANDTYPEENUM)

CommandTypeEnum = enum_type_wrapper.EnumTypeWrapper(_COMMANDTYPEENUM)
TEST_ADC = 0
TEST_I2C = 1
TEST_GPIO = 2



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
  serialized_start=14,
  serialized_end=62,
)

_COMMAND.fields_by_name['commandType'].enum_type = _COMMANDTYPEENUM
DESCRIPTOR.message_types_by_name['Command'] = _COMMAND
DESCRIPTOR.enum_types_by_name['CommandTypeEnum'] = _COMMANDTYPEENUM
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Command = _reflection.GeneratedProtocolMessageType('Command', (_message.Message,), dict(
  DESCRIPTOR = _COMMAND,
  __module__ = 'test_pb2'
  # @@protoc_insertion_point(class_scope:Command)
  ))
_sym_db.RegisterMessage(Command)


# @@protoc_insertion_point(module_scope)