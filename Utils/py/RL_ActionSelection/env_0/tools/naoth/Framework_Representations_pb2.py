# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Framework-Representations.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import CommonTypes_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='Framework-Representations.proto',
  package='naothmessages',
  serialized_pb=_b('\n\x1f\x46ramework-Representations.proto\x12\rnaothmessages\x1a\x11\x43ommonTypes.proto\"\xd1\x01\n\x05Image\x12\x0c\n\x04\x64\x61ta\x18\x01 \x02(\x0c\x12\x12\n\x05width\x18\x02 \x01(\x05:\x03\x33\x32\x30\x12\x13\n\x06height\x18\x03 \x01(\x05:\x03\x32\x34\x30\x12-\n\ncameraInfo\x18\x04 \x01(\x0b\x32\x19.naothmessages.CameraInfo\x12\x30\n\x06\x66ormat\x18\x05 \x01(\x0e\x32\x1b.naothmessages.Image.Format:\x03YUV\x12\x11\n\ttimestamp\x18\x06 \x01(\r\"\x1d\n\x06\x46ormat\x12\x07\n\x03YUV\x10\x00\x12\n\n\x06YUV422\x10\x01\"\xd2\x04\n\nCameraInfo\x12\x17\n\x0fresolutionWidth\x18\x01 \x02(\x05\x12\x18\n\x10resolutionHeight\x18\x02 \x02(\x05\x12\x31\n\x08\x63\x61meraID\x18\x04 \x01(\x0e\x32\x17.naothmessages.CameraID:\x06\x62ottom\x12\x17\n\x0b\x66ocalLength\x18\x05 \x01(\x01\x42\x02\x18\x01\x12\x1d\n\x11openingAngleWidth\x18\x06 \x01(\x01\x42\x02\x18\x01\x12\x1e\n\x12openingAngleHeight\x18\x07 \x01(\x01\x42\x02\x18\x01\x12\x1a\n\x0eopticalCenterX\x18\x08 \x01(\x01\x42\x02\x18\x01\x12\x1a\n\x0eopticalCenterY\x18\t \x01(\x01\x42\x02\x18\x01\x12\x10\n\x04size\x18\n \x01(\x03\x42\x02\x18\x01\x12\x16\n\nmemorysize\x18\x0b \x01(\x03\x42\x02\x18\x01\x12\x1c\n\x10\x63\x61meraRollOffset\x18\x0c \x01(\x01\x42\x02\x18\x01\x12\x1c\n\x10\x63\x61meraTiltOffset\x18\r \x01(\x01\x42\x02\x18\x01\x12:\n\x10\x63orrectionOffset\x18\x12 \x03(\x0b\x32\x1c.naothmessages.DoubleVector2B\x02\x18\x01\x12\x39\n\x0fheadJointOffset\x18\x13 \x03(\x0b\x32\x1c.naothmessages.DoubleVector2B\x02\x18\x01\x12\x31\n\x0etransformation\x18\x0e \x03(\x0b\x32\x15.naothmessages.Pose3DB\x02\x18\x01\x12\x1c\n\x14openingAngleDiagonal\x18\x0f \x01(\x01\x12\x11\n\tpixelSize\x18\x10 \x01(\x01\x12\r\n\x05\x66ocus\x18\x11 \x01(\x01\"I\n\tJointData\x12\x10\n\x08position\x18\x01 \x03(\x01\x12\x11\n\tstiffness\x18\x02 \x03(\x01\x12\n\n\x02\x64p\x18\x03 \x03(\x01\x12\x0b\n\x03\x64\x64p\x18\x04 \x03(\x01\"l\n\x0fSensorJointData\x12+\n\tjointData\x18\x01 \x02(\x0b\x32\x18.naothmessages.JointData\x12\x13\n\x0btemperature\x18\x02 \x03(\x01\x12\x17\n\x0f\x65lectricCurrent\x18\x03 \x03(\x01\"i\n\x15UltraSoundReceiveData\x12\x1a\n\x12ultraSoundTimeStep\x18\x01 \x01(\r\x12\x0f\n\x07rawdata\x18\x02 \x02(\x01\x12\x10\n\x08\x64\x61taLeft\x18\x03 \x03(\x01\x12\x11\n\tdataRight\x18\x04 \x03(\x01\".\n\tFrameInfo\x12\x13\n\x0b\x66rameNumber\x18\x01 \x02(\r\x12\x0c\n\x04time\x18\x02 \x02(\r\"p\n\tRobotInfo\x12\x10\n\x08platform\x18\x01 \x01(\t\x12\x14\n\x0c\x62odyNickName\x18\x02 \x01(\t\x12\x14\n\x0cheadNickName\x18\x03 \x01(\t\x12\x0e\n\x06\x62odyID\x18\x04 \x01(\t\x12\x15\n\rbasicTimeStep\x18\x05 \x01(\r\"=\n\x07\x46SRData\x12\x11\n\x05\x66orce\x18\x01 \x03(\x01\x42\x02\x18\x01\x12\x0c\n\x04\x64\x61ta\x18\x02 \x03(\x01\x12\x11\n\x05valid\x18\x03 \x03(\x08\x42\x02\x18\x01\"\x8c\x01\n\x11\x41\x63\x63\x65lerometerData\x12\x1c\n\x10legacyPackedData\x18\x01 \x03(\x01\x42\x02\x18\x01\x12*\n\x04\x64\x61ta\x18\x02 \x01(\x0b\x32\x1c.naothmessages.DoubleVector3\x12-\n\x07rawData\x18\x03 \x01(\x0b\x32\x1c.naothmessages.DoubleVector3\"\x95\x01\n\rGyrometerData\x12\x1c\n\x10legacyPackedData\x18\x01 \x03(\x01\x42\x02\x18\x01\x12*\n\x04\x64\x61ta\x18\x02 \x01(\x0b\x32\x1c.naothmessages.DoubleVector3\x12-\n\x07rawData\x18\x03 \x01(\x0b\x32\x1c.naothmessages.DoubleVector3\x12\x0b\n\x03ref\x18\x04 \x01(\x01\"^\n\x12InertialSensorData\x12\x1c\n\x10legacyPackedData\x18\x01 \x03(\x01\x42\x02\x18\x01\x12*\n\x04\x64\x61ta\x18\x02 \x01(\x0b\x32\x1c.naothmessages.DoubleVector2B\x16\n\x14\x64\x65.naoth.rc.messages')
  ,
  dependencies=[CommonTypes_pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_IMAGE_FORMAT = _descriptor.EnumDescriptor(
  name='Format',
  full_name='naothmessages.Image.Format',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='YUV', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='YUV422', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=250,
  serialized_end=279,
)
_sym_db.RegisterEnumDescriptor(_IMAGE_FORMAT)


_IMAGE = _descriptor.Descriptor(
  name='Image',
  full_name='naothmessages.Image',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='data', full_name='naothmessages.Image.data', index=0,
      number=1, type=12, cpp_type=9, label=2,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='width', full_name='naothmessages.Image.width', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=320,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='height', full_name='naothmessages.Image.height', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=240,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='cameraInfo', full_name='naothmessages.Image.cameraInfo', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='format', full_name='naothmessages.Image.format', index=4,
      number=5, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='naothmessages.Image.timestamp', index=5,
      number=6, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _IMAGE_FORMAT,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=70,
  serialized_end=279,
)


_CAMERAINFO = _descriptor.Descriptor(
  name='CameraInfo',
  full_name='naothmessages.CameraInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='resolutionWidth', full_name='naothmessages.CameraInfo.resolutionWidth', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='resolutionHeight', full_name='naothmessages.CameraInfo.resolutionHeight', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='cameraID', full_name='naothmessages.CameraInfo.cameraID', index=2,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='focalLength', full_name='naothmessages.CameraInfo.focalLength', index=3,
      number=5, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='openingAngleWidth', full_name='naothmessages.CameraInfo.openingAngleWidth', index=4,
      number=6, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='openingAngleHeight', full_name='naothmessages.CameraInfo.openingAngleHeight', index=5,
      number=7, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='opticalCenterX', full_name='naothmessages.CameraInfo.opticalCenterX', index=6,
      number=8, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='opticalCenterY', full_name='naothmessages.CameraInfo.opticalCenterY', index=7,
      number=9, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='size', full_name='naothmessages.CameraInfo.size', index=8,
      number=10, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='memorysize', full_name='naothmessages.CameraInfo.memorysize', index=9,
      number=11, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='cameraRollOffset', full_name='naothmessages.CameraInfo.cameraRollOffset', index=10,
      number=12, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='cameraTiltOffset', full_name='naothmessages.CameraInfo.cameraTiltOffset', index=11,
      number=13, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='correctionOffset', full_name='naothmessages.CameraInfo.correctionOffset', index=12,
      number=18, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='headJointOffset', full_name='naothmessages.CameraInfo.headJointOffset', index=13,
      number=19, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='transformation', full_name='naothmessages.CameraInfo.transformation', index=14,
      number=14, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='openingAngleDiagonal', full_name='naothmessages.CameraInfo.openingAngleDiagonal', index=15,
      number=15, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='pixelSize', full_name='naothmessages.CameraInfo.pixelSize', index=16,
      number=16, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='focus', full_name='naothmessages.CameraInfo.focus', index=17,
      number=17, type=1, cpp_type=5, label=1,
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
  serialized_start=282,
  serialized_end=876,
)


_JOINTDATA = _descriptor.Descriptor(
  name='JointData',
  full_name='naothmessages.JointData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='position', full_name='naothmessages.JointData.position', index=0,
      number=1, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='stiffness', full_name='naothmessages.JointData.stiffness', index=1,
      number=2, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dp', full_name='naothmessages.JointData.dp', index=2,
      number=3, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ddp', full_name='naothmessages.JointData.ddp', index=3,
      number=4, type=1, cpp_type=5, label=3,
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
  serialized_start=878,
  serialized_end=951,
)


_SENSORJOINTDATA = _descriptor.Descriptor(
  name='SensorJointData',
  full_name='naothmessages.SensorJointData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='jointData', full_name='naothmessages.SensorJointData.jointData', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='temperature', full_name='naothmessages.SensorJointData.temperature', index=1,
      number=2, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='electricCurrent', full_name='naothmessages.SensorJointData.electricCurrent', index=2,
      number=3, type=1, cpp_type=5, label=3,
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
  serialized_start=953,
  serialized_end=1061,
)


_ULTRASOUNDRECEIVEDATA = _descriptor.Descriptor(
  name='UltraSoundReceiveData',
  full_name='naothmessages.UltraSoundReceiveData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='ultraSoundTimeStep', full_name='naothmessages.UltraSoundReceiveData.ultraSoundTimeStep', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rawdata', full_name='naothmessages.UltraSoundReceiveData.rawdata', index=1,
      number=2, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dataLeft', full_name='naothmessages.UltraSoundReceiveData.dataLeft', index=2,
      number=3, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dataRight', full_name='naothmessages.UltraSoundReceiveData.dataRight', index=3,
      number=4, type=1, cpp_type=5, label=3,
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
  serialized_start=1063,
  serialized_end=1168,
)


_FRAMEINFO = _descriptor.Descriptor(
  name='FrameInfo',
  full_name='naothmessages.FrameInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='frameNumber', full_name='naothmessages.FrameInfo.frameNumber', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='time', full_name='naothmessages.FrameInfo.time', index=1,
      number=2, type=13, cpp_type=3, label=2,
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
  serialized_start=1170,
  serialized_end=1216,
)


_ROBOTINFO = _descriptor.Descriptor(
  name='RobotInfo',
  full_name='naothmessages.RobotInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='platform', full_name='naothmessages.RobotInfo.platform', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='bodyNickName', full_name='naothmessages.RobotInfo.bodyNickName', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='headNickName', full_name='naothmessages.RobotInfo.headNickName', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='bodyID', full_name='naothmessages.RobotInfo.bodyID', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='basicTimeStep', full_name='naothmessages.RobotInfo.basicTimeStep', index=4,
      number=5, type=13, cpp_type=3, label=1,
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
  serialized_start=1218,
  serialized_end=1330,
)


_FSRDATA = _descriptor.Descriptor(
  name='FSRData',
  full_name='naothmessages.FSRData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='force', full_name='naothmessages.FSRData.force', index=0,
      number=1, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='data', full_name='naothmessages.FSRData.data', index=1,
      number=2, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='valid', full_name='naothmessages.FSRData.valid', index=2,
      number=3, type=8, cpp_type=7, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
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
  serialized_start=1332,
  serialized_end=1393,
)


_ACCELEROMETERDATA = _descriptor.Descriptor(
  name='AccelerometerData',
  full_name='naothmessages.AccelerometerData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='legacyPackedData', full_name='naothmessages.AccelerometerData.legacyPackedData', index=0,
      number=1, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='data', full_name='naothmessages.AccelerometerData.data', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rawData', full_name='naothmessages.AccelerometerData.rawData', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
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
  serialized_start=1396,
  serialized_end=1536,
)


_GYROMETERDATA = _descriptor.Descriptor(
  name='GyrometerData',
  full_name='naothmessages.GyrometerData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='legacyPackedData', full_name='naothmessages.GyrometerData.legacyPackedData', index=0,
      number=1, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='data', full_name='naothmessages.GyrometerData.data', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='rawData', full_name='naothmessages.GyrometerData.rawData', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ref', full_name='naothmessages.GyrometerData.ref', index=3,
      number=4, type=1, cpp_type=5, label=1,
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
  serialized_start=1539,
  serialized_end=1688,
)


_INERTIALSENSORDATA = _descriptor.Descriptor(
  name='InertialSensorData',
  full_name='naothmessages.InertialSensorData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='legacyPackedData', full_name='naothmessages.InertialSensorData.legacyPackedData', index=0,
      number=1, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=_descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))),
    _descriptor.FieldDescriptor(
      name='data', full_name='naothmessages.InertialSensorData.data', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
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
  serialized_start=1690,
  serialized_end=1784,
)

_IMAGE.fields_by_name['cameraInfo'].message_type = _CAMERAINFO
_IMAGE.fields_by_name['format'].enum_type = _IMAGE_FORMAT
_IMAGE_FORMAT.containing_type = _IMAGE
_CAMERAINFO.fields_by_name['cameraID'].enum_type = CommonTypes_pb2._CAMERAID
_CAMERAINFO.fields_by_name['correctionOffset'].message_type = CommonTypes_pb2._DOUBLEVECTOR2
_CAMERAINFO.fields_by_name['headJointOffset'].message_type = CommonTypes_pb2._DOUBLEVECTOR2
_CAMERAINFO.fields_by_name['transformation'].message_type = CommonTypes_pb2._POSE3D
_SENSORJOINTDATA.fields_by_name['jointData'].message_type = _JOINTDATA
_ACCELEROMETERDATA.fields_by_name['data'].message_type = CommonTypes_pb2._DOUBLEVECTOR3
_ACCELEROMETERDATA.fields_by_name['rawData'].message_type = CommonTypes_pb2._DOUBLEVECTOR3
_GYROMETERDATA.fields_by_name['data'].message_type = CommonTypes_pb2._DOUBLEVECTOR3
_GYROMETERDATA.fields_by_name['rawData'].message_type = CommonTypes_pb2._DOUBLEVECTOR3
_INERTIALSENSORDATA.fields_by_name['data'].message_type = CommonTypes_pb2._DOUBLEVECTOR2
DESCRIPTOR.message_types_by_name['Image'] = _IMAGE
DESCRIPTOR.message_types_by_name['CameraInfo'] = _CAMERAINFO
DESCRIPTOR.message_types_by_name['JointData'] = _JOINTDATA
DESCRIPTOR.message_types_by_name['SensorJointData'] = _SENSORJOINTDATA
DESCRIPTOR.message_types_by_name['UltraSoundReceiveData'] = _ULTRASOUNDRECEIVEDATA
DESCRIPTOR.message_types_by_name['FrameInfo'] = _FRAMEINFO
DESCRIPTOR.message_types_by_name['RobotInfo'] = _ROBOTINFO
DESCRIPTOR.message_types_by_name['FSRData'] = _FSRDATA
DESCRIPTOR.message_types_by_name['AccelerometerData'] = _ACCELEROMETERDATA
DESCRIPTOR.message_types_by_name['GyrometerData'] = _GYROMETERDATA
DESCRIPTOR.message_types_by_name['InertialSensorData'] = _INERTIALSENSORDATA

Image = _reflection.GeneratedProtocolMessageType('Image', (_message.Message,), dict(
  DESCRIPTOR = _IMAGE,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.Image)
  ))
_sym_db.RegisterMessage(Image)

CameraInfo = _reflection.GeneratedProtocolMessageType('CameraInfo', (_message.Message,), dict(
  DESCRIPTOR = _CAMERAINFO,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.CameraInfo)
  ))
_sym_db.RegisterMessage(CameraInfo)

JointData = _reflection.GeneratedProtocolMessageType('JointData', (_message.Message,), dict(
  DESCRIPTOR = _JOINTDATA,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.JointData)
  ))
_sym_db.RegisterMessage(JointData)

SensorJointData = _reflection.GeneratedProtocolMessageType('SensorJointData', (_message.Message,), dict(
  DESCRIPTOR = _SENSORJOINTDATA,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.SensorJointData)
  ))
_sym_db.RegisterMessage(SensorJointData)

UltraSoundReceiveData = _reflection.GeneratedProtocolMessageType('UltraSoundReceiveData', (_message.Message,), dict(
  DESCRIPTOR = _ULTRASOUNDRECEIVEDATA,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.UltraSoundReceiveData)
  ))
_sym_db.RegisterMessage(UltraSoundReceiveData)

FrameInfo = _reflection.GeneratedProtocolMessageType('FrameInfo', (_message.Message,), dict(
  DESCRIPTOR = _FRAMEINFO,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.FrameInfo)
  ))
_sym_db.RegisterMessage(FrameInfo)

RobotInfo = _reflection.GeneratedProtocolMessageType('RobotInfo', (_message.Message,), dict(
  DESCRIPTOR = _ROBOTINFO,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.RobotInfo)
  ))
_sym_db.RegisterMessage(RobotInfo)

FSRData = _reflection.GeneratedProtocolMessageType('FSRData', (_message.Message,), dict(
  DESCRIPTOR = _FSRDATA,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.FSRData)
  ))
_sym_db.RegisterMessage(FSRData)

AccelerometerData = _reflection.GeneratedProtocolMessageType('AccelerometerData', (_message.Message,), dict(
  DESCRIPTOR = _ACCELEROMETERDATA,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.AccelerometerData)
  ))
_sym_db.RegisterMessage(AccelerometerData)

GyrometerData = _reflection.GeneratedProtocolMessageType('GyrometerData', (_message.Message,), dict(
  DESCRIPTOR = _GYROMETERDATA,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.GyrometerData)
  ))
_sym_db.RegisterMessage(GyrometerData)

InertialSensorData = _reflection.GeneratedProtocolMessageType('InertialSensorData', (_message.Message,), dict(
  DESCRIPTOR = _INERTIALSENSORDATA,
  __module__ = 'Framework_Representations_pb2'
  # @@protoc_insertion_point(class_scope:naothmessages.InertialSensorData)
  ))
_sym_db.RegisterMessage(InertialSensorData)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\n\024de.naoth.rc.messages'))
_CAMERAINFO.fields_by_name['focalLength'].has_options = True
_CAMERAINFO.fields_by_name['focalLength']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['openingAngleWidth'].has_options = True
_CAMERAINFO.fields_by_name['openingAngleWidth']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['openingAngleHeight'].has_options = True
_CAMERAINFO.fields_by_name['openingAngleHeight']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['opticalCenterX'].has_options = True
_CAMERAINFO.fields_by_name['opticalCenterX']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['opticalCenterY'].has_options = True
_CAMERAINFO.fields_by_name['opticalCenterY']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['size'].has_options = True
_CAMERAINFO.fields_by_name['size']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['memorysize'].has_options = True
_CAMERAINFO.fields_by_name['memorysize']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['cameraRollOffset'].has_options = True
_CAMERAINFO.fields_by_name['cameraRollOffset']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['cameraTiltOffset'].has_options = True
_CAMERAINFO.fields_by_name['cameraTiltOffset']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['correctionOffset'].has_options = True
_CAMERAINFO.fields_by_name['correctionOffset']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['headJointOffset'].has_options = True
_CAMERAINFO.fields_by_name['headJointOffset']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_CAMERAINFO.fields_by_name['transformation'].has_options = True
_CAMERAINFO.fields_by_name['transformation']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_FSRDATA.fields_by_name['force'].has_options = True
_FSRDATA.fields_by_name['force']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_FSRDATA.fields_by_name['valid'].has_options = True
_FSRDATA.fields_by_name['valid']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_ACCELEROMETERDATA.fields_by_name['legacyPackedData'].has_options = True
_ACCELEROMETERDATA.fields_by_name['legacyPackedData']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_GYROMETERDATA.fields_by_name['legacyPackedData'].has_options = True
_GYROMETERDATA.fields_by_name['legacyPackedData']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
_INERTIALSENSORDATA.fields_by_name['legacyPackedData'].has_options = True
_INERTIALSENSORDATA.fields_by_name['legacyPackedData']._options = _descriptor._ParseOptions(descriptor_pb2.FieldOptions(), _b('\030\001'))
# @@protoc_insertion_point(module_scope)
