// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CameraInfo.proto

#ifndef PROTOBUF_CameraInfo_2eproto__INCLUDED
#define PROTOBUF_CameraInfo_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace naothmessages {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CameraInfo_2eproto();
void protobuf_AssignDesc_CameraInfo_2eproto();
void protobuf_ShutdownFile_CameraInfo_2eproto();

class CameraInfo;

enum CameraInfo_CameraID {
  CameraInfo_CameraID_top = 0,
  CameraInfo_CameraID_bottom = 1
};
bool CameraInfo_CameraID_IsValid(int value);
const CameraInfo_CameraID CameraInfo_CameraID_CameraID_MIN = CameraInfo_CameraID_top;
const CameraInfo_CameraID CameraInfo_CameraID_CameraID_MAX = CameraInfo_CameraID_bottom;
const int CameraInfo_CameraID_CameraID_ARRAYSIZE = CameraInfo_CameraID_CameraID_MAX + 1;

const ::google::protobuf::EnumDescriptor* CameraInfo_CameraID_descriptor();
inline const ::std::string& CameraInfo_CameraID_Name(CameraInfo_CameraID value) {
  return ::google::protobuf::internal::NameOfEnum(
    CameraInfo_CameraID_descriptor(), value);
}
inline bool CameraInfo_CameraID_Parse(
    const ::std::string& name, CameraInfo_CameraID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CameraInfo_CameraID>(
    CameraInfo_CameraID_descriptor(), name, value);
}
// ===================================================================

class CameraInfo : public ::google::protobuf::Message {
 public:
  CameraInfo();
  virtual ~CameraInfo();
  
  CameraInfo(const CameraInfo& from);
  
  inline CameraInfo& operator=(const CameraInfo& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const CameraInfo& default_instance();
  
  void Swap(CameraInfo* other);
  
  // implements Message ----------------------------------------------
  
  CameraInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CameraInfo& from);
  void MergeFrom(const CameraInfo& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef CameraInfo_CameraID CameraID;
  static const CameraID top = CameraInfo_CameraID_top;
  static const CameraID bottom = CameraInfo_CameraID_bottom;
  static inline bool CameraID_IsValid(int value) {
    return CameraInfo_CameraID_IsValid(value);
  }
  static const CameraID CameraID_MIN =
    CameraInfo_CameraID_CameraID_MIN;
  static const CameraID CameraID_MAX =
    CameraInfo_CameraID_CameraID_MAX;
  static const int CameraID_ARRAYSIZE =
    CameraInfo_CameraID_CameraID_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CameraID_descriptor() {
    return CameraInfo_CameraID_descriptor();
  }
  static inline const ::std::string& CameraID_Name(CameraID value) {
    return CameraInfo_CameraID_Name(value);
  }
  static inline bool CameraID_Parse(const ::std::string& name,
      CameraID* value) {
    return CameraInfo_CameraID_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 resolutionWidth = 1;
  inline bool has_resolutionwidth() const;
  inline void clear_resolutionwidth();
  static const int kResolutionWidthFieldNumber = 1;
  inline ::google::protobuf::int32 resolutionwidth() const;
  inline void set_resolutionwidth(::google::protobuf::int32 value);
  
  // required int32 resolutionHeight = 2;
  inline bool has_resolutionheight() const;
  inline void clear_resolutionheight();
  static const int kResolutionHeightFieldNumber = 2;
  inline ::google::protobuf::int32 resolutionheight() const;
  inline void set_resolutionheight(::google::protobuf::int32 value);
  
  // optional .naothmessages.CameraInfo.CameraID cameraID = 4 [default = bottom];
  inline bool has_cameraid() const;
  inline void clear_cameraid();
  static const int kCameraIDFieldNumber = 4;
  inline ::naothmessages::CameraInfo_CameraID cameraid() const;
  inline void set_cameraid(::naothmessages::CameraInfo_CameraID value);
  
  // optional double focalLength = 5;
  inline bool has_focallength() const;
  inline void clear_focallength();
  static const int kFocalLengthFieldNumber = 5;
  inline double focallength() const;
  inline void set_focallength(double value);
  
  // optional double openingAngleWidth = 6;
  inline bool has_openinganglewidth() const;
  inline void clear_openinganglewidth();
  static const int kOpeningAngleWidthFieldNumber = 6;
  inline double openinganglewidth() const;
  inline void set_openinganglewidth(double value);
  
  // optional double openingAngleHeight = 7;
  inline bool has_openingangleheight() const;
  inline void clear_openingangleheight();
  static const int kOpeningAngleHeightFieldNumber = 7;
  inline double openingangleheight() const;
  inline void set_openingangleheight(double value);
  
  // optional double opticalCenterX = 8;
  inline bool has_opticalcenterx() const;
  inline void clear_opticalcenterx();
  static const int kOpticalCenterXFieldNumber = 8;
  inline double opticalcenterx() const;
  inline void set_opticalcenterx(double value);
  
  // optional double opticalCenterY = 9;
  inline bool has_opticalcentery() const;
  inline void clear_opticalcentery();
  static const int kOpticalCenterYFieldNumber = 9;
  inline double opticalcentery() const;
  inline void set_opticalcentery(double value);
  
  // optional int64 size = 10;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 10;
  inline ::google::protobuf::int64 size() const;
  inline void set_size(::google::protobuf::int64 value);
  
  // optional int64 memorysize = 11;
  inline bool has_memorysize() const;
  inline void clear_memorysize();
  static const int kMemorysizeFieldNumber = 11;
  inline ::google::protobuf::int64 memorysize() const;
  inline void set_memorysize(::google::protobuf::int64 value);
  
  // optional double cameraRollOffset = 12;
  inline bool has_camerarolloffset() const;
  inline void clear_camerarolloffset();
  static const int kCameraRollOffsetFieldNumber = 12;
  inline double camerarolloffset() const;
  inline void set_camerarolloffset(double value);
  
  // optional double cameraTiltOffset = 13;
  inline bool has_cameratiltoffset() const;
  inline void clear_cameratiltoffset();
  static const int kCameraTiltOffsetFieldNumber = 13;
  inline double cameratiltoffset() const;
  inline void set_cameratiltoffset(double value);
  
  // @@protoc_insertion_point(class_scope:naothmessages.CameraInfo)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::int32 resolutionwidth_;
  ::google::protobuf::int32 resolutionheight_;
  int cameraid_;
  double focallength_;
  double openinganglewidth_;
  double openingangleheight_;
  double opticalcenterx_;
  double opticalcentery_;
  ::google::protobuf::int64 size_;
  ::google::protobuf::int64 memorysize_;
  double camerarolloffset_;
  double cameratiltoffset_;
  friend void  protobuf_AddDesc_CameraInfo_2eproto();
  friend void protobuf_AssignDesc_CameraInfo_2eproto();
  friend void protobuf_ShutdownFile_CameraInfo_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(12 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static CameraInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// CameraInfo

// required int32 resolutionWidth = 1;
inline bool CameraInfo::has_resolutionwidth() const {
  return _has_bit(0);
}
inline void CameraInfo::clear_resolutionwidth() {
  resolutionwidth_ = 0;
  _clear_bit(0);
}
inline ::google::protobuf::int32 CameraInfo::resolutionwidth() const {
  return resolutionwidth_;
}
inline void CameraInfo::set_resolutionwidth(::google::protobuf::int32 value) {
  _set_bit(0);
  resolutionwidth_ = value;
}

// required int32 resolutionHeight = 2;
inline bool CameraInfo::has_resolutionheight() const {
  return _has_bit(1);
}
inline void CameraInfo::clear_resolutionheight() {
  resolutionheight_ = 0;
  _clear_bit(1);
}
inline ::google::protobuf::int32 CameraInfo::resolutionheight() const {
  return resolutionheight_;
}
inline void CameraInfo::set_resolutionheight(::google::protobuf::int32 value) {
  _set_bit(1);
  resolutionheight_ = value;
}

// optional .naothmessages.CameraInfo.CameraID cameraID = 4 [default = bottom];
inline bool CameraInfo::has_cameraid() const {
  return _has_bit(2);
}
inline void CameraInfo::clear_cameraid() {
  cameraid_ = 1;
  _clear_bit(2);
}
inline ::naothmessages::CameraInfo_CameraID CameraInfo::cameraid() const {
  return static_cast< ::naothmessages::CameraInfo_CameraID >(cameraid_);
}
inline void CameraInfo::set_cameraid(::naothmessages::CameraInfo_CameraID value) {
  GOOGLE_DCHECK(::naothmessages::CameraInfo_CameraID_IsValid(value));
  _set_bit(2);
  cameraid_ = value;
}

// optional double focalLength = 5;
inline bool CameraInfo::has_focallength() const {
  return _has_bit(3);
}
inline void CameraInfo::clear_focallength() {
  focallength_ = 0;
  _clear_bit(3);
}
inline double CameraInfo::focallength() const {
  return focallength_;
}
inline void CameraInfo::set_focallength(double value) {
  _set_bit(3);
  focallength_ = value;
}

// optional double openingAngleWidth = 6;
inline bool CameraInfo::has_openinganglewidth() const {
  return _has_bit(4);
}
inline void CameraInfo::clear_openinganglewidth() {
  openinganglewidth_ = 0;
  _clear_bit(4);
}
inline double CameraInfo::openinganglewidth() const {
  return openinganglewidth_;
}
inline void CameraInfo::set_openinganglewidth(double value) {
  _set_bit(4);
  openinganglewidth_ = value;
}

// optional double openingAngleHeight = 7;
inline bool CameraInfo::has_openingangleheight() const {
  return _has_bit(5);
}
inline void CameraInfo::clear_openingangleheight() {
  openingangleheight_ = 0;
  _clear_bit(5);
}
inline double CameraInfo::openingangleheight() const {
  return openingangleheight_;
}
inline void CameraInfo::set_openingangleheight(double value) {
  _set_bit(5);
  openingangleheight_ = value;
}

// optional double opticalCenterX = 8;
inline bool CameraInfo::has_opticalcenterx() const {
  return _has_bit(6);
}
inline void CameraInfo::clear_opticalcenterx() {
  opticalcenterx_ = 0;
  _clear_bit(6);
}
inline double CameraInfo::opticalcenterx() const {
  return opticalcenterx_;
}
inline void CameraInfo::set_opticalcenterx(double value) {
  _set_bit(6);
  opticalcenterx_ = value;
}

// optional double opticalCenterY = 9;
inline bool CameraInfo::has_opticalcentery() const {
  return _has_bit(7);
}
inline void CameraInfo::clear_opticalcentery() {
  opticalcentery_ = 0;
  _clear_bit(7);
}
inline double CameraInfo::opticalcentery() const {
  return opticalcentery_;
}
inline void CameraInfo::set_opticalcentery(double value) {
  _set_bit(7);
  opticalcentery_ = value;
}

// optional int64 size = 10;
inline bool CameraInfo::has_size() const {
  return _has_bit(8);
}
inline void CameraInfo::clear_size() {
  size_ = GOOGLE_LONGLONG(0);
  _clear_bit(8);
}
inline ::google::protobuf::int64 CameraInfo::size() const {
  return size_;
}
inline void CameraInfo::set_size(::google::protobuf::int64 value) {
  _set_bit(8);
  size_ = value;
}

// optional int64 memorysize = 11;
inline bool CameraInfo::has_memorysize() const {
  return _has_bit(9);
}
inline void CameraInfo::clear_memorysize() {
  memorysize_ = GOOGLE_LONGLONG(0);
  _clear_bit(9);
}
inline ::google::protobuf::int64 CameraInfo::memorysize() const {
  return memorysize_;
}
inline void CameraInfo::set_memorysize(::google::protobuf::int64 value) {
  _set_bit(9);
  memorysize_ = value;
}

// optional double cameraRollOffset = 12;
inline bool CameraInfo::has_camerarolloffset() const {
  return _has_bit(10);
}
inline void CameraInfo::clear_camerarolloffset() {
  camerarolloffset_ = 0;
  _clear_bit(10);
}
inline double CameraInfo::camerarolloffset() const {
  return camerarolloffset_;
}
inline void CameraInfo::set_camerarolloffset(double value) {
  _set_bit(10);
  camerarolloffset_ = value;
}

// optional double cameraTiltOffset = 13;
inline bool CameraInfo::has_cameratiltoffset() const {
  return _has_bit(11);
}
inline void CameraInfo::clear_cameratiltoffset() {
  cameratiltoffset_ = 0;
  _clear_bit(11);
}
inline double CameraInfo::cameratiltoffset() const {
  return cameratiltoffset_;
}
inline void CameraInfo::set_cameratiltoffset(double value) {
  _set_bit(11);
  cameratiltoffset_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace naothmessages

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::naothmessages::CameraInfo_CameraID>() {
  return ::naothmessages::CameraInfo_CameraID_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CameraInfo_2eproto__INCLUDED