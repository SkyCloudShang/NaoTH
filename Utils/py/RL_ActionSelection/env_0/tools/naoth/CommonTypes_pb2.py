# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: CommonTypes.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='CommonTypes.proto',
  package='naothmessages',
  serialized_pb=_b('\n\x11\x43ommonTypes.proto\x12\rnaothmessages\"$\n\x0c\x46loatVector2\x12\t\n\x01x\x18\x01 \x02(\x02\x12\t\n\x01y\x18\x02 \x02(\x02\"%\n\rDoubleVector2\x12\t\n\x01x\x18\x01 \x02(\x01\x12\t\n\x01y\x18\x02 \x02(\x01\"\"\n\nIntVector2\x12\t\n\x01x\x18\x01 \x02(\x05\x12\t\n\x01y\x18\x02 \x02(\x05\"M\n\x06Pose2D\x12\x31\n\x0btranslation\x18\x01 \x02(\x0b\x32\x1c.naothmessages.DoubleVector2\x12\x10\n\x08rotation\x18\x02 \x02(\x01\"0\n\rDoubleVector3\x12\t\n\x01x\x18\x01 \x02(\x01\x12\t\n\x01y\x18\x02 \x02(\x01\x12\t\n\x01z\x18\x03 \x02(\x01\"\x19\n\x0c\x44oubleVector\x12\t\n\x01v\x18\x01 \x03(\x01\"k\n\x06Pose3D\x12\x31\n\x0btranslation\x18\x01 \x02(\x0b\x32\x1c.naothmessages.DoubleVector3\x12.\n\x08rotation\x18\x02 \x03(\x0b\x32\x1c.naothmessages.DoubleVector3\"z\n\x0bLineSegment\x12*\n\x04\x62\x61se\x18\x01 \x02(\x0b\x32\x1c.naothmessages.DoubleVector2\x12/\n\tdirection\x18\x02 \x02(\x0b\x32\x1c.naothmessages.DoubleVector2\x12\x0e\n\x06length\x18\x03 \x02(\x01\"\xdf\x02\n\x0cIntersection\x12\x30\n\nposInImage\x18\x01 \x01(\x0b\x32\x1c.naothmessages.DoubleVector2\x12\x30\n\nposOnField\x18\x02 \x01(\x0b\x32\x1c.naothmessages.DoubleVector2\x12:\n\x04type\x18\x03 \x01(\x0e\x32,.naothmessages.Intersection.IntersectionType\x12\x17\n\x0fsegmentOneIndex\x18\x06 \x01(\r\x12\x17\n\x0fsegmentTwoIndex\x18\x07 \x01(\r\x12\x1a\n\x12segmentOneDistance\x18\x08 \x01(\x01\x12\x1a\n\x12segmentTwoDistance\x18\t \x01(\x01\"E\n\x10IntersectionType\x12\x0b\n\x07unknown\x10\x00\x12\x05\n\x01T\x10\x01\x12\x05\n\x01L\x10\x02\x12\x05\n\x01\x43\x10\x03\x12\x08\n\x04none\x10\x04\x12\x05\n\x01X\x10\x05*\x90\x01\n\x05\x43olor\x12\x08\n\x04none\x10\x00\x12\n\n\x06orange\x10\x01\x12\n\n\x06yellow\x10\x02\x12\x0b\n\x07skyblue\x10\x03\x12\t\n\x05white\x10\x04\x12\x07\n\x03red\x10\x05\x12\x08\n\x04\x62lue\x10\x06\x12\t\n\x05green\x10\x07\x12\t\n\x05\x62lack\x10\x08\x12\x08\n\x04pink\x10\t\x12\x08\n\x04gray\x10\n\x12\x10\n\x0cyellowOrange\x10\x0b*\x1f\n\x08\x43\x61meraID\x12\x07\n\x03top\x10\x00\x12\n\n\x06\x62ottom\x10\x01*\xa5\x03\n\x07JointID\x12\r\n\tHeadPitch\x10\x00\x12\x0b\n\x07HeadYaw\x10\x01\x12\x11\n\rRShoulderRoll\x10\x02\x12\x11\n\rLShoulderRoll\x10\x03\x12\x12\n\x0eRShoulderPitch\x10\x04\x12\x12\n\x0eLShoulderPitch\x10\x05\x12\x0e\n\nRElbowRoll\x10\x06\x12\x0e\n\nLElbowRoll\x10\x07\x12\r\n\tRElbowYaw\x10\x08\x12\r\n\tLElbowYaw\x10\t\x12\x10\n\x0cRHipYawPitch\x10\n\x12\x10\n\x0cLHipYawPitch\x10\x0b\x12\r\n\tRHipPitch\x10\x0c\x12\r\n\tLHipPitch\x10\r\x12\x0c\n\x08RHipRoll\x10\x0e\x12\x0c\n\x08LHipRoll\x10\x0f\x12\x0e\n\nRKneePitch\x10\x10\x12\x0e\n\nLKneePitch\x10\x11\x12\x0f\n\x0bRAnklePitch\x10\x12\x12\x0f\n\x0bLAnklePitch\x10\x13\x12\x0e\n\nRAnkleRoll\x10\x14\x12\x0e\n\nLAnkleRoll\x10\x15\x12\r\n\tLWristYaw\x10\x16\x12\r\n\tRWristYaw\x10\x17\x12\t\n\x05LHand\x10\x18\x12\t\n\x05RHand\x10\x19\x42\x16\n\x14\x64\x65.naoth.rc.messages')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_COLOR = _descriptor.EnumDescriptor(
  name='Color',
  full_name='naothmessages.Color',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='none', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='orange', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='yellow', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='skyblue', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='white', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='red', index=5, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='blue', index=6, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='green', index=7, number=7,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='black', index=8, number=8,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='pink', index=9, number=9,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='gray', index=10, number=10,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='yellowOrange', index=11, number=11,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=893,
  serialized_end=1037,
)
_sym_db.RegisterEnumDescriptor(_COLOR)

Color = enum_type_wrapper.EnumTypeWrapper(_COLOR)
_CAMERAID = _descriptor.EnumDescriptor(
  name='CameraID',
  full_name='naothmessages.CameraID',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='top', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='bottom', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1039,
  serialized_end=1070,
)
_sym_db.RegisterEnumDescriptor(_CAMERAID)

CameraID = enum_type_wrapper.EnumTypeWrapper(_CAMERAID)
_JOINTID = _descriptor.EnumDescriptor(
  name='JointID',
  full_name='naothmessages.JointID',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='HeadPitch', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HeadYaw', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RShoulderRoll', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LShoulderRoll', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RShoulderPitch', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LShoulderPitch', index=5, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RElbowRoll', index=6, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LElbowRoll', index=7, number=7,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RElbowYaw', index=8, number=8,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LElbowYaw', index=9, number=9,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RHipYawPitch', index=10, number=10,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LHipYawPitch', index=11, number=11,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RHipPitch', index=12, number=12,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LHipPitch', index=13, number=13,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RHipRoll', index=14, number=14,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LHipRoll', index=15, number=15,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RKneePitch', index=16, number=16,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LKneePitch', index=17, number=17,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RAnklePitch', index=18, number=18,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LAnklePitch', index=19, number=19,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RAnkleRoll', index=20, number=20,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LAnkleRoll', index=21, number=21,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LWristYaw', index=22, number=22,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RWristYaw', index=23, number=23,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LHand', index=24, number=24,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RHand', index=25, number=25,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1073,
  serialized_end=1494,
)
_sym_db.RegisterEnumDescriptor(_JOINTID)

JointID = enum_type_wrapper.EnumTypeWrapper(_JOINTID)
none = 0
orange = 1
yellow = 2
skyblue = 3
white = 4
red = 5
blue = 6
green = 7
black = 8
pink = 9
gray = 10
yellowOrange = 11
top = 0
bottom = 1
HeadPitch = 0
HeadYaw = 1
RShoulderRoll = 2
LShoulderRoll = 3
RShoulderPitch = 4
LShoulderPitch = 5
RElbowRoll = 6
LElbowRoll = 7
RElbowYaw = 8
LElbowYaw = 9
RHipYawPitch = 10
LHipYawPitch = 11
RHipPitch = 12
LHipPitch = 13
RHipRoll = 14
LHipRoll = 15
RKneePitch = 16
LKneePitch = 17
RAnklePitch = 18
LAnklePitch = 19
RAnkleRoll = 20
LAnkleRoll = 21
LWristYaw = 22
RWristYaw = 23
LHand = 24
RHand = 25


_INTERSECTION_INTERSECTIONTYPE = _descriptor.EnumDescriptor(
  name='IntersectionType',
  full_name='naothmessages.Intersection.IntersectionType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='unknown', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='T', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='L', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='C', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='none', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='X', index=5, number=5,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=821,
  serialized_end=890,
)
_sym_db.RegisterEnumDescriptor(_INTERSECTION_INTERSECTIONTYPE)


_FLOATVECTOR2 = _descriptor.Descriptor(
  name='FloatVector2',
  full_name='naothmessages.FloatVector2',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='naothmessages.FloatVector2.x', index=0,
      number=1, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='naothmessages.FloatVector2.y', index=1,
      number=2, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=36,
  serialized_end=72,
)


_DOUBLEVECTOR2 = _descriptor.Descriptor(
  name='DoubleVector2',
  full_name='naothmessages.DoubleVector2',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='naothmessages.DoubleVector2.x', index=0,
      number=1, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='naothmessages.DoubleVector2.y', index=1,
      number=2, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=74,
  serialized_end=111,
)


_INTVECTOR2 = _descriptor.Descriptor(
  name='IntVector2',
  full_name='naothmessages.IntVector2',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='naothmessages.IntVector2.x', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='naothmessages.IntVector2.y', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=113,
  serialized_end=147,
)


_POSE2D = _descriptor.Descriptor(
  name='Pose2D',
  full_name='naothmessages.Pose2D',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='translation', full_name='naothmessages.Pose2D.translation', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rotation', full_name='naothmessages.Pose2D.rotation', index=1,
      number=2, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=149,
  serialized_end=226,
)


_DOUBLEVECTOR3 = _descriptor.Descriptor(
  name='DoubleVector3',
  full_name='naothmessages.DoubleVector3',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='naothmessages.DoubleVector3.x', index=0,
      number=1, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='naothmessages.DoubleVector3.y', index=1,
      number=2, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='z', full_name='naothmessages.DoubleVector3.z', index=2,
      number=3, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=228,
  serialized_end=276,
)


_DOUBLEVECTOR = _descriptor.Descriptor(
  name='DoubleVector',
  full_name='naothmessages.DoubleVector',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='v', full_name='naothmessages.DoubleVector.v', index=0,
      number=1, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=278,
  serialized_end=303,
)


_POSE3D = _descriptor.Descriptor(
  name='Pose3D',
  full_name='naothmessages.Pose3D',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='translation', full_name='naothmessages.Pose3D.translation', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rotation', full_name='naothmessages.Pose3D.rotation', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=305,
  serialized_end=412,
)


_LINESEGMENT = _descriptor.Descriptor(
  name='LineSegment',
  full_name='naothmessages.LineSegment',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='base', full_name='naothmessages.LineSegment.base', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='direction', full_name='naothmessages.LineSegment.direction', index=1,
      number=2, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='length', full_name='naothmessages.LineSegment.length', index=2,
      number=3, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=414,
  serialized_end=536,
)


_INTERSECTION = _descriptor.Descriptor(
  name='Intersection',
  full_name='naothmessages.Intersection',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='posInImage', full_name='naothmessages.Intersection.posInImage', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='posOnField', full_name='naothmessages.Intersection.posOnField', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='type', full_name='naothmessages.Intersection.type', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='segmentOneIndex', full_name='naothmessages.Intersection.segmentOneIndex', index=3,
      number=6, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='segmentTwoIndex', full_name='naothmessages.Intersection.segmentTwoIndex', index=4,
      number=7, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='segmentOneDistance', full_name='naothmessages.Intersection.segmentOneDistance', index=5,
      number=8, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='segmentTwoDistance', full_name='naothmessages.Intersection.segmentTwoDistance', index=6,
      number=9, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _INTERSECTION_INTERSECTIONTYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=539,
  serialized_end=890,
)

_POSE2D.fields_by_name['translation'].message_type = _DOUBLEVECTOR2
_POSE3D.fields_by_name['translation'].message_type = _DOUBLEVECTOR3
_POSE3D.fields_by_name['rotation'].message_type = _DOUBLEVECTOR3
_LINESEGMENT.fields_by_name['base'].message_type = _DOUBLEVECTOR2
_LINESEGMENT.fields_by_name['direction'].message_type = _DOUBLEVECTOR2
_INTERSECTION.fields_by_name['posInImage'].message_type = _DOUBLEVECTOR2
_INTERSECTION.fields_by_name['posOnField'].message_type = _DOUBLEVECTOR2
_INTERSECTION.fields_by_name['type'].enum_type = _INTERSECTION_INTERSECTIONTYPE
_INTERSECTION_INTERSECTIONTYPE.containing_type = _INTERSECTION
DESCRIPTOR.message_types_by_name['FloatVector2'] = _FLOATVECTOR2
DESCRIPTOR.message_types_by_name['DoubleVector2'] = _DOUBLEVECTOR2
DESCRIPTOR.message_types_by_name['IntVector2'] = _INTVECTOR2
DESCRIPTOR.message_types_by_name['Pose2D'] = _POSE2D
DESCRIPTOR.message_types_by_name['DoubleVector3'] = _DOUBLEVECTOR3
DESCRIPTOR.message_types_by_name['DoubleVector'] = _DOUBLEVECTOR
DESCRIPTOR.message_types_by_name['Pose3D'] = _POSE3D
DESCRIPTOR.message_types_by_name['LineSegment'] = _LINESEGMENT
DESCRIPTOR.message_types_by_name['Intersection'] = _INTERSECTION
DESCRIPTOR.enum_types_by_name['Color'] = _COLOR
DESCRIPTOR.enum_types_by_name['CameraID'] = _CAMERAID
DESCRIPTOR.enum_types_by_name['JointID'] = _JOINTID

FloatVector2 = _reflection.GeneratedProtocolMessageType('FloatVector2', (_message.Message,), dict(
  DESCRIPTOR = _FLOATVECTOR2,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.FloatVector2)
  ))
_sym_db.RegisterMessage(FloatVector2)

DoubleVector2 = _reflection.GeneratedProtocolMessageType('DoubleVector2', (_message.Message,), dict(
  DESCRIPTOR = _DOUBLEVECTOR2,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.DoubleVector2)
  ))
_sym_db.RegisterMessage(DoubleVector2)

IntVector2 = _reflection.GeneratedProtocolMessageType('IntVector2', (_message.Message,), dict(
  DESCRIPTOR = _INTVECTOR2,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.IntVector2)
  ))
_sym_db.RegisterMessage(IntVector2)

Pose2D = _reflection.GeneratedProtocolMessageType('Pose2D', (_message.Message,), dict(
  DESCRIPTOR = _POSE2D,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.Pose2D)
  ))
_sym_db.RegisterMessage(Pose2D)

DoubleVector3 = _reflection.GeneratedProtocolMessageType('DoubleVector3', (_message.Message,), dict(
  DESCRIPTOR = _DOUBLEVECTOR3,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.DoubleVector3)
  ))
_sym_db.RegisterMessage(DoubleVector3)

DoubleVector = _reflection.GeneratedProtocolMessageType('DoubleVector', (_message.Message,), dict(
  DESCRIPTOR = _DOUBLEVECTOR,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.DoubleVector)
  ))
_sym_db.RegisterMessage(DoubleVector)

Pose3D = _reflection.GeneratedProtocolMessageType('Pose3D', (_message.Message,), dict(
  DESCRIPTOR = _POSE3D,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.Pose3D)
  ))
_sym_db.RegisterMessage(Pose3D)

LineSegment = _reflection.GeneratedProtocolMessageType('LineSegment', (_message.Message,), dict(
  DESCRIPTOR = _LINESEGMENT,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.LineSegment)
  ))
_sym_db.RegisterMessage(LineSegment)

Intersection = _reflection.GeneratedProtocolMessageType('Intersection', (_message.Message,), dict(
  DESCRIPTOR = _INTERSECTION,
  __module__ = 'CommonTypes_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.Intersection)
  ))
_sym_db.RegisterMessage(Intersection)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\n\024de.naoth.rc.messages'))
# @@protoc_insertion_point(module_scope)
