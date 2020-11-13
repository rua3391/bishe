// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Proto/Common.proto

#include "Proto/Common.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_Proto_2fCommon_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Camera_Proto_Proto_2fCommon_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_Proto_2fCommon_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Shader_Proto_Proto_2fCommon_2eproto;
namespace Proto {
namespace Common {
class EngineDataDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<EngineData> _instance;
} _EngineData_default_instance_;
class Camera_ProtoDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Camera_Proto> _instance;
} _Camera_Proto_default_instance_;
class Shader_ProtoDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Shader_Proto> _instance;
} _Shader_Proto_default_instance_;
}  // namespace Common
}  // namespace Proto
static void InitDefaultsscc_info_Camera_Proto_Proto_2fCommon_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Proto::Common::_Camera_Proto_default_instance_;
    new (ptr) ::Proto::Common::Camera_Proto();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Camera_Proto_Proto_2fCommon_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Camera_Proto_Proto_2fCommon_2eproto}, {}};

static void InitDefaultsscc_info_EngineData_Proto_2fCommon_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Proto::Common::_EngineData_default_instance_;
    new (ptr) ::Proto::Common::EngineData();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<2> scc_info_EngineData_Proto_2fCommon_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 2, 0, InitDefaultsscc_info_EngineData_Proto_2fCommon_2eproto}, {
      &scc_info_Camera_Proto_Proto_2fCommon_2eproto.base,
      &scc_info_Shader_Proto_Proto_2fCommon_2eproto.base,}};

static void InitDefaultsscc_info_Shader_Proto_Proto_2fCommon_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Proto::Common::_Shader_Proto_default_instance_;
    new (ptr) ::Proto::Common::Shader_Proto();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Shader_Proto_Proto_2fCommon_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Shader_Proto_Proto_2fCommon_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Proto_2fCommon_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Proto_2fCommon_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Proto_2fCommon_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Proto_2fCommon_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Proto::Common::EngineData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Proto::Common::EngineData, camera_),
  PROTOBUF_FIELD_OFFSET(::Proto::Common::EngineData, shader_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Proto::Common::Camera_Proto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Proto::Common::Shader_Proto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Proto::Common::EngineData)},
  { 7, -1, sizeof(::Proto::Common::Camera_Proto)},
  { 12, -1, sizeof(::Proto::Common::Shader_Proto)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Proto::Common::_EngineData_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Proto::Common::_Camera_Proto_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Proto::Common::_Shader_Proto_default_instance_),
};

const char descriptor_table_protodef_Proto_2fCommon_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\022Proto/Common.proto\022\014Proto.Common\"d\n\nEn"
  "gineData\022*\n\006camera\030\001 \001(\0132\032.Proto.Common."
  "Camera_Proto\022*\n\006shader\030\002 \001(\0132\032.Proto.Com"
  "mon.Shader_Proto\"\016\n\014Camera_Proto\"\016\n\014Shad"
  "er_Protob\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_Proto_2fCommon_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_Proto_2fCommon_2eproto_sccs[3] = {
  &scc_info_Camera_Proto_Proto_2fCommon_2eproto.base,
  &scc_info_EngineData_Proto_2fCommon_2eproto.base,
  &scc_info_Shader_Proto_Proto_2fCommon_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Proto_2fCommon_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Proto_2fCommon_2eproto = {
  false, false, descriptor_table_protodef_Proto_2fCommon_2eproto, "Proto/Common.proto", 176,
  &descriptor_table_Proto_2fCommon_2eproto_once, descriptor_table_Proto_2fCommon_2eproto_sccs, descriptor_table_Proto_2fCommon_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_Proto_2fCommon_2eproto::offsets,
  file_level_metadata_Proto_2fCommon_2eproto, 3, file_level_enum_descriptors_Proto_2fCommon_2eproto, file_level_service_descriptors_Proto_2fCommon_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Proto_2fCommon_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_Proto_2fCommon_2eproto)), true);
namespace Proto {
namespace Common {

// ===================================================================

class EngineData::_Internal {
 public:
  static const ::Proto::Common::Camera_Proto& camera(const EngineData* msg);
  static const ::Proto::Common::Shader_Proto& shader(const EngineData* msg);
};

const ::Proto::Common::Camera_Proto&
EngineData::_Internal::camera(const EngineData* msg) {
  return *msg->camera_;
}
const ::Proto::Common::Shader_Proto&
EngineData::_Internal::shader(const EngineData* msg) {
  return *msg->shader_;
}
EngineData::EngineData(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Proto.Common.EngineData)
}
EngineData::EngineData(const EngineData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_camera()) {
    camera_ = new ::Proto::Common::Camera_Proto(*from.camera_);
  } else {
    camera_ = nullptr;
  }
  if (from._internal_has_shader()) {
    shader_ = new ::Proto::Common::Shader_Proto(*from.shader_);
  } else {
    shader_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:Proto.Common.EngineData)
}

void EngineData::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_EngineData_Proto_2fCommon_2eproto.base);
  ::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
      reinterpret_cast<char*>(&camera_) - reinterpret_cast<char*>(this)),
      0, static_cast<size_t>(reinterpret_cast<char*>(&shader_) -
      reinterpret_cast<char*>(&camera_)) + sizeof(shader_));
}

EngineData::~EngineData() {
  // @@protoc_insertion_point(destructor:Proto.Common.EngineData)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void EngineData::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  if (this != internal_default_instance()) delete camera_;
  if (this != internal_default_instance()) delete shader_;
}

void EngineData::ArenaDtor(void* object) {
  EngineData* _this = reinterpret_cast< EngineData* >(object);
  (void)_this;
}
void EngineData::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void EngineData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const EngineData& EngineData::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_EngineData_Proto_2fCommon_2eproto.base);
  return *internal_default_instance();
}


void EngineData::Clear() {
// @@protoc_insertion_point(message_clear_start:Proto.Common.EngineData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArena() == nullptr && camera_ != nullptr) {
    delete camera_;
  }
  camera_ = nullptr;
  if (GetArena() == nullptr && shader_ != nullptr) {
    delete shader_;
  }
  shader_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* EngineData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .Proto.Common.Camera_Proto camera = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_camera(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .Proto.Common.Shader_Proto shader = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_shader(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* EngineData::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Proto.Common.EngineData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .Proto.Common.Camera_Proto camera = 1;
  if (this->has_camera()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::camera(this), target, stream);
  }

  // .Proto.Common.Shader_Proto shader = 2;
  if (this->has_shader()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::shader(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Proto.Common.EngineData)
  return target;
}

size_t EngineData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Proto.Common.EngineData)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .Proto.Common.Camera_Proto camera = 1;
  if (this->has_camera()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *camera_);
  }

  // .Proto.Common.Shader_Proto shader = 2;
  if (this->has_shader()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *shader_);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void EngineData::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Proto.Common.EngineData)
  GOOGLE_DCHECK_NE(&from, this);
  const EngineData* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<EngineData>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Proto.Common.EngineData)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Proto.Common.EngineData)
    MergeFrom(*source);
  }
}

void EngineData::MergeFrom(const EngineData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Proto.Common.EngineData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_camera()) {
    _internal_mutable_camera()->::Proto::Common::Camera_Proto::MergeFrom(from._internal_camera());
  }
  if (from.has_shader()) {
    _internal_mutable_shader()->::Proto::Common::Shader_Proto::MergeFrom(from._internal_shader());
  }
}

void EngineData::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Proto.Common.EngineData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void EngineData::CopyFrom(const EngineData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Proto.Common.EngineData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EngineData::IsInitialized() const {
  return true;
}

void EngineData::InternalSwap(EngineData* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(EngineData, shader_)
      + sizeof(EngineData::shader_)
      - PROTOBUF_FIELD_OFFSET(EngineData, camera_)>(
          reinterpret_cast<char*>(&camera_),
          reinterpret_cast<char*>(&other->camera_));
}

::PROTOBUF_NAMESPACE_ID::Metadata EngineData::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class Camera_Proto::_Internal {
 public:
};

Camera_Proto::Camera_Proto(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Proto.Common.Camera_Proto)
}
Camera_Proto::Camera_Proto(const Camera_Proto& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Proto.Common.Camera_Proto)
}

void Camera_Proto::SharedCtor() {
}

Camera_Proto::~Camera_Proto() {
  // @@protoc_insertion_point(destructor:Proto.Common.Camera_Proto)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Camera_Proto::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void Camera_Proto::ArenaDtor(void* object) {
  Camera_Proto* _this = reinterpret_cast< Camera_Proto* >(object);
  (void)_this;
}
void Camera_Proto::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Camera_Proto::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Camera_Proto& Camera_Proto::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Camera_Proto_Proto_2fCommon_2eproto.base);
  return *internal_default_instance();
}


void Camera_Proto::Clear() {
// @@protoc_insertion_point(message_clear_start:Proto.Common.Camera_Proto)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Camera_Proto::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Camera_Proto::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Proto.Common.Camera_Proto)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Proto.Common.Camera_Proto)
  return target;
}

size_t Camera_Proto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Proto.Common.Camera_Proto)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Camera_Proto::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Proto.Common.Camera_Proto)
  GOOGLE_DCHECK_NE(&from, this);
  const Camera_Proto* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Camera_Proto>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Proto.Common.Camera_Proto)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Proto.Common.Camera_Proto)
    MergeFrom(*source);
  }
}

void Camera_Proto::MergeFrom(const Camera_Proto& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Proto.Common.Camera_Proto)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void Camera_Proto::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Proto.Common.Camera_Proto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Camera_Proto::CopyFrom(const Camera_Proto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Proto.Common.Camera_Proto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Camera_Proto::IsInitialized() const {
  return true;
}

void Camera_Proto::InternalSwap(Camera_Proto* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Camera_Proto::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class Shader_Proto::_Internal {
 public:
};

Shader_Proto::Shader_Proto(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Proto.Common.Shader_Proto)
}
Shader_Proto::Shader_Proto(const Shader_Proto& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Proto.Common.Shader_Proto)
}

void Shader_Proto::SharedCtor() {
}

Shader_Proto::~Shader_Proto() {
  // @@protoc_insertion_point(destructor:Proto.Common.Shader_Proto)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Shader_Proto::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void Shader_Proto::ArenaDtor(void* object) {
  Shader_Proto* _this = reinterpret_cast< Shader_Proto* >(object);
  (void)_this;
}
void Shader_Proto::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Shader_Proto::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Shader_Proto& Shader_Proto::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Shader_Proto_Proto_2fCommon_2eproto.base);
  return *internal_default_instance();
}


void Shader_Proto::Clear() {
// @@protoc_insertion_point(message_clear_start:Proto.Common.Shader_Proto)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Shader_Proto::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Shader_Proto::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Proto.Common.Shader_Proto)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Proto.Common.Shader_Proto)
  return target;
}

size_t Shader_Proto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Proto.Common.Shader_Proto)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Shader_Proto::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Proto.Common.Shader_Proto)
  GOOGLE_DCHECK_NE(&from, this);
  const Shader_Proto* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Shader_Proto>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Proto.Common.Shader_Proto)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Proto.Common.Shader_Proto)
    MergeFrom(*source);
  }
}

void Shader_Proto::MergeFrom(const Shader_Proto& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Proto.Common.Shader_Proto)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void Shader_Proto::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Proto.Common.Shader_Proto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Shader_Proto::CopyFrom(const Shader_Proto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Proto.Common.Shader_Proto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Shader_Proto::IsInitialized() const {
  return true;
}

void Shader_Proto::InternalSwap(Shader_Proto* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Shader_Proto::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Common
}  // namespace Proto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Proto::Common::EngineData* Arena::CreateMaybeMessage< ::Proto::Common::EngineData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Proto::Common::EngineData >(arena);
}
template<> PROTOBUF_NOINLINE ::Proto::Common::Camera_Proto* Arena::CreateMaybeMessage< ::Proto::Common::Camera_Proto >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Proto::Common::Camera_Proto >(arena);
}
template<> PROTOBUF_NOINLINE ::Proto::Common::Shader_Proto* Arena::CreateMaybeMessage< ::Proto::Common::Shader_Proto >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Proto::Common::Shader_Proto >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
