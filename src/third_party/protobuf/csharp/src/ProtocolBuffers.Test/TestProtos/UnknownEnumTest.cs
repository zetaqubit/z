// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unknown_enum_test.proto
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.ProtocolBuffers;
using pbc = global::Google.ProtocolBuffers.Collections;
using pbd = global::Google.ProtocolBuffers.Descriptors;
using scg = global::System.Collections.Generic;
namespace Google.ProtocolBuffers.TestProtos {

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
  public static partial class UnknownEnumTest {

    #region Extension registration
    public static void RegisterAllExtensions(pb::ExtensionRegistry registry) {
    }
    #endregion
    #region Static variables
    internal static pbd::MessageDescriptor internal__static_google_protobuf_util_DownRevision__Descriptor;
    internal static pb::FieldAccess.FieldAccessorTable<global::Google.ProtocolBuffers.TestProtos.DownRevision, global::Google.ProtocolBuffers.TestProtos.DownRevision.Builder> internal__static_google_protobuf_util_DownRevision__FieldAccessorTable;
    internal static pbd::MessageDescriptor internal__static_google_protobuf_util_UpRevision__Descriptor;
    internal static pb::FieldAccess.FieldAccessorTable<global::Google.ProtocolBuffers.TestProtos.UpRevision, global::Google.ProtocolBuffers.TestProtos.UpRevision.Builder> internal__static_google_protobuf_util_UpRevision__FieldAccessorTable;
    #endregion
    #region Descriptor
    public static pbd::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbd::FileDescriptor descriptor;

    static UnknownEnumTest() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "Cidnb29nbGUvcHJvdG9idWYvdW5rbm93bl9lbnVtX3Rlc3QucHJvdG8SFGdv", 
            "b2dsZS5wcm90b2J1Zi51dGlsIr8BCgxEb3duUmV2aXNpb24SRQoFdmFsdWUY", 
            "ASABKA4yJy5nb29nbGUucHJvdG9idWYudXRpbC5Eb3duUmV2aXNpb24uRW51", 
            "bToNREVGQVVMVF9WQUxVRRI3CgZ2YWx1ZXMYAiADKA4yJy5nb29nbGUucHJv", 
            "dG9idWYudXRpbC5Eb3duUmV2aXNpb24uRW51bSIvCgRFbnVtEhEKDURFRkFV", 
            "TFRfVkFMVUUQAhIUChBOT05ERUZBVUxUX1ZBTFVFEAMi6gEKClVwUmV2aXNp", 
            "b24SQwoFdmFsdWUYASABKA4yJS5nb29nbGUucHJvdG9idWYudXRpbC5VcFJl", 
            "dmlzaW9uLkVudW06DURFRkFVTFRfVkFMVUUSNQoGdmFsdWVzGAIgAygOMiUu", 
            "Z29vZ2xlLnByb3RvYnVmLnV0aWwuVXBSZXZpc2lvbi5FbnVtImAKBEVudW0S", 
            "EQoNREVGQVVMVF9WQUxVRRACEhQKEE5PTkRFRkFVTFRfVkFMVUUQAxINCglO", 
            "RVdfVkFMVUUQBBIPCgtORVdfVkFMVUVfMhAFEg8KC05FV19WQUxVRV8zEAZC", 
          "JKoCIUdvb2dsZS5Qcm90b2NvbEJ1ZmZlcnMuVGVzdFByb3Rvcw=="));
      pbd::FileDescriptor.InternalDescriptorAssigner assigner = delegate(pbd::FileDescriptor root) {
        descriptor = root;
        internal__static_google_protobuf_util_DownRevision__Descriptor = Descriptor.MessageTypes[0];
        internal__static_google_protobuf_util_DownRevision__FieldAccessorTable = 
            new pb::FieldAccess.FieldAccessorTable<global::Google.ProtocolBuffers.TestProtos.DownRevision, global::Google.ProtocolBuffers.TestProtos.DownRevision.Builder>(internal__static_google_protobuf_util_DownRevision__Descriptor,
                new string[] { "Value", "Values", });
        internal__static_google_protobuf_util_UpRevision__Descriptor = Descriptor.MessageTypes[1];
        internal__static_google_protobuf_util_UpRevision__FieldAccessorTable = 
            new pb::FieldAccess.FieldAccessorTable<global::Google.ProtocolBuffers.TestProtos.UpRevision, global::Google.ProtocolBuffers.TestProtos.UpRevision.Builder>(internal__static_google_protobuf_util_UpRevision__Descriptor,
                new string[] { "Value", "Values", });
        pb::ExtensionRegistry registry = pb::ExtensionRegistry.CreateInstance();
        RegisterAllExtensions(registry);
        return registry;
      };
      pbd::FileDescriptor.InternalBuildGeneratedFileFrom(descriptorData,
          new pbd::FileDescriptor[] {
          }, assigner);
    }
    #endregion

  }
  #region Messages
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
  public sealed partial class DownRevision : pb::GeneratedMessage<DownRevision, DownRevision.Builder> {
    private DownRevision() { }
    private static readonly DownRevision defaultInstance = new DownRevision().MakeReadOnly();
    private static readonly string[] _downRevisionFieldNames = new string[] { "value", "values" };
    private static readonly uint[] _downRevisionFieldTags = new uint[] { 8, 16 };
    public static DownRevision DefaultInstance {
      get { return defaultInstance; }
    }

    public override DownRevision DefaultInstanceForType {
      get { return DefaultInstance; }
    }

    protected override DownRevision ThisMessage {
      get { return this; }
    }

    public static pbd::MessageDescriptor Descriptor {
      get { return global::Google.ProtocolBuffers.TestProtos.UnknownEnumTest.internal__static_google_protobuf_util_DownRevision__Descriptor; }
    }

    protected override pb::FieldAccess.FieldAccessorTable<DownRevision, DownRevision.Builder> InternalFieldAccessors {
      get { return global::Google.ProtocolBuffers.TestProtos.UnknownEnumTest.internal__static_google_protobuf_util_DownRevision__FieldAccessorTable; }
    }

    #region Nested types
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    public static partial class Types {
      public enum Enum {
        DEFAULT_VALUE = 2,
        NONDEFAULT_VALUE = 3,
      }

    }
    #endregion

    public const int ValueFieldNumber = 1;
    private bool hasValue;
    private global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum value_ = global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum.DEFAULT_VALUE;
    public bool HasValue {
      get { return hasValue; }
    }
    public global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum Value {
      get { return value_; }
    }

    public const int ValuesFieldNumber = 2;
    private pbc::PopsicleList<global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum> values_ = new pbc::PopsicleList<global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum>();
    public scg::IList<global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum> ValuesList {
      get { return pbc::Lists.AsReadOnly(values_); }
    }
    public int ValuesCount {
      get { return values_.Count; }
    }
    public global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum GetValues(int index) {
      return values_[index];
    }

    public override bool IsInitialized {
      get {
        return true;
      }
    }

    public override void WriteTo(pb::ICodedOutputStream output) {
      CalcSerializedSize();
      string[] field_names = _downRevisionFieldNames;
      if (hasValue) {
        output.WriteEnum(1, field_names[0], (int) Value, Value);
      }
      if (values_.Count > 0) {
        output.WriteEnumArray(2, field_names[1], values_);
      }
      UnknownFields.WriteTo(output);
    }

    private int memoizedSerializedSize = -1;
    public override int SerializedSize {
      get {
        int size = memoizedSerializedSize;
        if (size != -1) return size;
        return CalcSerializedSize();
      }
    }

    private int CalcSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      if (hasValue) {
        size += pb::CodedOutputStream.ComputeEnumSize(1, (int) Value);
      }
      {
        int dataSize = 0;
        if (values_.Count > 0) {
          foreach (global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum element in values_) {
            dataSize += pb::CodedOutputStream.ComputeEnumSizeNoTag((int) element);
          }
          size += dataSize;
          size += 1 * values_.Count;
        }
      }
      size += UnknownFields.SerializedSize;
      memoizedSerializedSize = size;
      return size;
    }
    public static DownRevision ParseFrom(pb::ByteString data) {
      return ((Builder) CreateBuilder().MergeFrom(data)).BuildParsed();
    }
    public static DownRevision ParseFrom(pb::ByteString data, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(data, extensionRegistry)).BuildParsed();
    }
    public static DownRevision ParseFrom(byte[] data) {
      return ((Builder) CreateBuilder().MergeFrom(data)).BuildParsed();
    }
    public static DownRevision ParseFrom(byte[] data, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(data, extensionRegistry)).BuildParsed();
    }
    public static DownRevision ParseFrom(global::System.IO.Stream input) {
      return ((Builder) CreateBuilder().MergeFrom(input)).BuildParsed();
    }
    public static DownRevision ParseFrom(global::System.IO.Stream input, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(input, extensionRegistry)).BuildParsed();
    }
    public static DownRevision ParseDelimitedFrom(global::System.IO.Stream input) {
      return CreateBuilder().MergeDelimitedFrom(input).BuildParsed();
    }
    public static DownRevision ParseDelimitedFrom(global::System.IO.Stream input, pb::ExtensionRegistry extensionRegistry) {
      return CreateBuilder().MergeDelimitedFrom(input, extensionRegistry).BuildParsed();
    }
    public static DownRevision ParseFrom(pb::ICodedInputStream input) {
      return ((Builder) CreateBuilder().MergeFrom(input)).BuildParsed();
    }
    public static DownRevision ParseFrom(pb::ICodedInputStream input, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(input, extensionRegistry)).BuildParsed();
    }
    private DownRevision MakeReadOnly() {
      values_.MakeReadOnly();
      return this;
    }

    public static Builder CreateBuilder() { return new Builder(); }
    public override Builder ToBuilder() { return CreateBuilder(this); }
    public override Builder CreateBuilderForType() { return new Builder(); }
    public static Builder CreateBuilder(DownRevision prototype) {
      return new Builder(prototype);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    public sealed partial class Builder : pb::GeneratedBuilder<DownRevision, Builder> {
      protected override Builder ThisBuilder {
        get { return this; }
      }
      public Builder() {
        result = DefaultInstance;
        resultIsReadOnly = true;
      }
      internal Builder(DownRevision cloneFrom) {
        result = cloneFrom;
        resultIsReadOnly = true;
      }

      private bool resultIsReadOnly;
      private DownRevision result;

      private DownRevision PrepareBuilder() {
        if (resultIsReadOnly) {
          DownRevision original = result;
          result = new DownRevision();
          resultIsReadOnly = false;
          MergeFrom(original);
        }
        return result;
      }

      public override bool IsInitialized {
        get { return result.IsInitialized; }
      }

      protected override DownRevision MessageBeingBuilt {
        get { return PrepareBuilder(); }
      }

      public override Builder Clear() {
        result = DefaultInstance;
        resultIsReadOnly = true;
        return this;
      }

      public override Builder Clone() {
        if (resultIsReadOnly) {
          return new Builder(result);
        } else {
          return new Builder().MergeFrom(result);
        }
      }

      public override pbd::MessageDescriptor DescriptorForType {
        get { return global::Google.ProtocolBuffers.TestProtos.DownRevision.Descriptor; }
      }

      public override DownRevision DefaultInstanceForType {
        get { return global::Google.ProtocolBuffers.TestProtos.DownRevision.DefaultInstance; }
      }

      public override DownRevision BuildPartial() {
        if (resultIsReadOnly) {
          return result;
        }
        resultIsReadOnly = true;
        return result.MakeReadOnly();
      }

      public override Builder MergeFrom(pb::IMessage other) {
        if (other is DownRevision) {
          return MergeFrom((DownRevision) other);
        } else {
          base.MergeFrom(other);
          return this;
        }
      }

      public override Builder MergeFrom(DownRevision other) {
        if (other == global::Google.ProtocolBuffers.TestProtos.DownRevision.DefaultInstance) return this;
        PrepareBuilder();
        if (other.HasValue) {
          Value = other.Value;
        }
        if (other.values_.Count != 0) {
          result.values_.Add(other.values_);
        }
        this.MergeUnknownFields(other.UnknownFields);
        return this;
      }

      public override Builder MergeFrom(pb::ICodedInputStream input) {
        return MergeFrom(input, pb::ExtensionRegistry.Empty);
      }

      public override Builder MergeFrom(pb::ICodedInputStream input, pb::ExtensionRegistry extensionRegistry) {
        PrepareBuilder();
        pb::UnknownFieldSet.Builder unknownFields = null;
        uint tag;
        string field_name;
        while (input.ReadTag(out tag, out field_name)) {
          if(tag == 0 && field_name != null) {
            int field_ordinal = global::System.Array.BinarySearch(_downRevisionFieldNames, field_name, global::System.StringComparer.Ordinal);
            if(field_ordinal >= 0)
              tag = _downRevisionFieldTags[field_ordinal];
            else {
              if (unknownFields == null) {
                unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
              }
              ParseUnknownField(input, unknownFields, extensionRegistry, tag, field_name);
              continue;
            }
          }
          switch (tag) {
            case 0: {
              throw pb::InvalidProtocolBufferException.InvalidTag();
            }
            default: {
              if (pb::WireFormat.IsEndGroupTag(tag)) {
                if (unknownFields != null) {
                  this.UnknownFields = unknownFields.Build();
                }
                return this;
              }
              if (unknownFields == null) {
                unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
              }
              ParseUnknownField(input, unknownFields, extensionRegistry, tag, field_name);
              break;
            }
            case 8: {
              object unknown;
              if(input.ReadEnum(ref result.value_, out unknown)) {
                result.hasValue = true;
              } else if(unknown is int) {
                if (unknownFields == null) {
                  unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
                }
                unknownFields.MergeVarintField(1, (ulong)(int)unknown);
              }
              break;
            }
            case 18:
            case 16: {
              scg::ICollection<object> unknownItems;
              input.ReadEnumArray<global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum>(tag, field_name, result.values_, out unknownItems);
              if (unknownItems != null) {
                if (unknownFields == null) {
                  unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
                }
                foreach (object rawValue in unknownItems)
                  if (rawValue is int)
                    unknownFields.MergeVarintField(2, (ulong)(int)rawValue);
              }
              break;
            }
          }
        }

        if (unknownFields != null) {
          this.UnknownFields = unknownFields.Build();
        }
        return this;
      }


      public bool HasValue {
        get { return result.hasValue; }
      }
      public global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum Value {
        get { return result.Value; }
        set { SetValue(value); }
      }
      public Builder SetValue(global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum value) {
        PrepareBuilder();
        result.hasValue = true;
        result.value_ = value;
        return this;
      }
      public Builder ClearValue() {
        PrepareBuilder();
        result.hasValue = false;
        result.value_ = global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum.DEFAULT_VALUE;
        return this;
      }

      public pbc::IPopsicleList<global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum> ValuesList {
        get { return PrepareBuilder().values_; }
      }
      public int ValuesCount {
        get { return result.ValuesCount; }
      }
      public global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum GetValues(int index) {
        return result.GetValues(index);
      }
      public Builder SetValues(int index, global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum value) {
        PrepareBuilder();
        result.values_[index] = value;
        return this;
      }
      public Builder AddValues(global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum value) {
        PrepareBuilder();
        result.values_.Add(value);
        return this;
      }
      public Builder AddRangeValues(scg::IEnumerable<global::Google.ProtocolBuffers.TestProtos.DownRevision.Types.Enum> values) {
        PrepareBuilder();
        result.values_.Add(values);
        return this;
      }
      public Builder ClearValues() {
        PrepareBuilder();
        result.values_.Clear();
        return this;
      }
    }
    static DownRevision() {
      object.ReferenceEquals(global::Google.ProtocolBuffers.TestProtos.UnknownEnumTest.Descriptor, null);
    }
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
  public sealed partial class UpRevision : pb::GeneratedMessage<UpRevision, UpRevision.Builder> {
    private UpRevision() { }
    private static readonly UpRevision defaultInstance = new UpRevision().MakeReadOnly();
    private static readonly string[] _upRevisionFieldNames = new string[] { "value", "values" };
    private static readonly uint[] _upRevisionFieldTags = new uint[] { 8, 16 };
    public static UpRevision DefaultInstance {
      get { return defaultInstance; }
    }

    public override UpRevision DefaultInstanceForType {
      get { return DefaultInstance; }
    }

    protected override UpRevision ThisMessage {
      get { return this; }
    }

    public static pbd::MessageDescriptor Descriptor {
      get { return global::Google.ProtocolBuffers.TestProtos.UnknownEnumTest.internal__static_google_protobuf_util_UpRevision__Descriptor; }
    }

    protected override pb::FieldAccess.FieldAccessorTable<UpRevision, UpRevision.Builder> InternalFieldAccessors {
      get { return global::Google.ProtocolBuffers.TestProtos.UnknownEnumTest.internal__static_google_protobuf_util_UpRevision__FieldAccessorTable; }
    }

    #region Nested types
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    public static partial class Types {
      public enum Enum {
        DEFAULT_VALUE = 2,
        NONDEFAULT_VALUE = 3,
        NEW_VALUE = 4,
        NEW_VALUE_2 = 5,
        NEW_VALUE_3 = 6,
      }

    }
    #endregion

    public const int ValueFieldNumber = 1;
    private bool hasValue;
    private global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum value_ = global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum.DEFAULT_VALUE;
    public bool HasValue {
      get { return hasValue; }
    }
    public global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum Value {
      get { return value_; }
    }

    public const int ValuesFieldNumber = 2;
    private pbc::PopsicleList<global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum> values_ = new pbc::PopsicleList<global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum>();
    public scg::IList<global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum> ValuesList {
      get { return pbc::Lists.AsReadOnly(values_); }
    }
    public int ValuesCount {
      get { return values_.Count; }
    }
    public global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum GetValues(int index) {
      return values_[index];
    }

    public override bool IsInitialized {
      get {
        return true;
      }
    }

    public override void WriteTo(pb::ICodedOutputStream output) {
      CalcSerializedSize();
      string[] field_names = _upRevisionFieldNames;
      if (hasValue) {
        output.WriteEnum(1, field_names[0], (int) Value, Value);
      }
      if (values_.Count > 0) {
        output.WriteEnumArray(2, field_names[1], values_);
      }
      UnknownFields.WriteTo(output);
    }

    private int memoizedSerializedSize = -1;
    public override int SerializedSize {
      get {
        int size = memoizedSerializedSize;
        if (size != -1) return size;
        return CalcSerializedSize();
      }
    }

    private int CalcSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      if (hasValue) {
        size += pb::CodedOutputStream.ComputeEnumSize(1, (int) Value);
      }
      {
        int dataSize = 0;
        if (values_.Count > 0) {
          foreach (global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum element in values_) {
            dataSize += pb::CodedOutputStream.ComputeEnumSizeNoTag((int) element);
          }
          size += dataSize;
          size += 1 * values_.Count;
        }
      }
      size += UnknownFields.SerializedSize;
      memoizedSerializedSize = size;
      return size;
    }
    public static UpRevision ParseFrom(pb::ByteString data) {
      return ((Builder) CreateBuilder().MergeFrom(data)).BuildParsed();
    }
    public static UpRevision ParseFrom(pb::ByteString data, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(data, extensionRegistry)).BuildParsed();
    }
    public static UpRevision ParseFrom(byte[] data) {
      return ((Builder) CreateBuilder().MergeFrom(data)).BuildParsed();
    }
    public static UpRevision ParseFrom(byte[] data, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(data, extensionRegistry)).BuildParsed();
    }
    public static UpRevision ParseFrom(global::System.IO.Stream input) {
      return ((Builder) CreateBuilder().MergeFrom(input)).BuildParsed();
    }
    public static UpRevision ParseFrom(global::System.IO.Stream input, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(input, extensionRegistry)).BuildParsed();
    }
    public static UpRevision ParseDelimitedFrom(global::System.IO.Stream input) {
      return CreateBuilder().MergeDelimitedFrom(input).BuildParsed();
    }
    public static UpRevision ParseDelimitedFrom(global::System.IO.Stream input, pb::ExtensionRegistry extensionRegistry) {
      return CreateBuilder().MergeDelimitedFrom(input, extensionRegistry).BuildParsed();
    }
    public static UpRevision ParseFrom(pb::ICodedInputStream input) {
      return ((Builder) CreateBuilder().MergeFrom(input)).BuildParsed();
    }
    public static UpRevision ParseFrom(pb::ICodedInputStream input, pb::ExtensionRegistry extensionRegistry) {
      return ((Builder) CreateBuilder().MergeFrom(input, extensionRegistry)).BuildParsed();
    }
    private UpRevision MakeReadOnly() {
      values_.MakeReadOnly();
      return this;
    }

    public static Builder CreateBuilder() { return new Builder(); }
    public override Builder ToBuilder() { return CreateBuilder(this); }
    public override Builder CreateBuilderForType() { return new Builder(); }
    public static Builder CreateBuilder(UpRevision prototype) {
      return new Builder(prototype);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    public sealed partial class Builder : pb::GeneratedBuilder<UpRevision, Builder> {
      protected override Builder ThisBuilder {
        get { return this; }
      }
      public Builder() {
        result = DefaultInstance;
        resultIsReadOnly = true;
      }
      internal Builder(UpRevision cloneFrom) {
        result = cloneFrom;
        resultIsReadOnly = true;
      }

      private bool resultIsReadOnly;
      private UpRevision result;

      private UpRevision PrepareBuilder() {
        if (resultIsReadOnly) {
          UpRevision original = result;
          result = new UpRevision();
          resultIsReadOnly = false;
          MergeFrom(original);
        }
        return result;
      }

      public override bool IsInitialized {
        get { return result.IsInitialized; }
      }

      protected override UpRevision MessageBeingBuilt {
        get { return PrepareBuilder(); }
      }

      public override Builder Clear() {
        result = DefaultInstance;
        resultIsReadOnly = true;
        return this;
      }

      public override Builder Clone() {
        if (resultIsReadOnly) {
          return new Builder(result);
        } else {
          return new Builder().MergeFrom(result);
        }
      }

      public override pbd::MessageDescriptor DescriptorForType {
        get { return global::Google.ProtocolBuffers.TestProtos.UpRevision.Descriptor; }
      }

      public override UpRevision DefaultInstanceForType {
        get { return global::Google.ProtocolBuffers.TestProtos.UpRevision.DefaultInstance; }
      }

      public override UpRevision BuildPartial() {
        if (resultIsReadOnly) {
          return result;
        }
        resultIsReadOnly = true;
        return result.MakeReadOnly();
      }

      public override Builder MergeFrom(pb::IMessage other) {
        if (other is UpRevision) {
          return MergeFrom((UpRevision) other);
        } else {
          base.MergeFrom(other);
          return this;
        }
      }

      public override Builder MergeFrom(UpRevision other) {
        if (other == global::Google.ProtocolBuffers.TestProtos.UpRevision.DefaultInstance) return this;
        PrepareBuilder();
        if (other.HasValue) {
          Value = other.Value;
        }
        if (other.values_.Count != 0) {
          result.values_.Add(other.values_);
        }
        this.MergeUnknownFields(other.UnknownFields);
        return this;
      }

      public override Builder MergeFrom(pb::ICodedInputStream input) {
        return MergeFrom(input, pb::ExtensionRegistry.Empty);
      }

      public override Builder MergeFrom(pb::ICodedInputStream input, pb::ExtensionRegistry extensionRegistry) {
        PrepareBuilder();
        pb::UnknownFieldSet.Builder unknownFields = null;
        uint tag;
        string field_name;
        while (input.ReadTag(out tag, out field_name)) {
          if(tag == 0 && field_name != null) {
            int field_ordinal = global::System.Array.BinarySearch(_upRevisionFieldNames, field_name, global::System.StringComparer.Ordinal);
            if(field_ordinal >= 0)
              tag = _upRevisionFieldTags[field_ordinal];
            else {
              if (unknownFields == null) {
                unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
              }
              ParseUnknownField(input, unknownFields, extensionRegistry, tag, field_name);
              continue;
            }
          }
          switch (tag) {
            case 0: {
              throw pb::InvalidProtocolBufferException.InvalidTag();
            }
            default: {
              if (pb::WireFormat.IsEndGroupTag(tag)) {
                if (unknownFields != null) {
                  this.UnknownFields = unknownFields.Build();
                }
                return this;
              }
              if (unknownFields == null) {
                unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
              }
              ParseUnknownField(input, unknownFields, extensionRegistry, tag, field_name);
              break;
            }
            case 8: {
              object unknown;
              if(input.ReadEnum(ref result.value_, out unknown)) {
                result.hasValue = true;
              } else if(unknown is int) {
                if (unknownFields == null) {
                  unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
                }
                unknownFields.MergeVarintField(1, (ulong)(int)unknown);
              }
              break;
            }
            case 18:
            case 16: {
              scg::ICollection<object> unknownItems;
              input.ReadEnumArray<global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum>(tag, field_name, result.values_, out unknownItems);
              if (unknownItems != null) {
                if (unknownFields == null) {
                  unknownFields = pb::UnknownFieldSet.CreateBuilder(this.UnknownFields);
                }
                foreach (object rawValue in unknownItems)
                  if (rawValue is int)
                    unknownFields.MergeVarintField(2, (ulong)(int)rawValue);
              }
              break;
            }
          }
        }

        if (unknownFields != null) {
          this.UnknownFields = unknownFields.Build();
        }
        return this;
      }


      public bool HasValue {
        get { return result.hasValue; }
      }
      public global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum Value {
        get { return result.Value; }
        set { SetValue(value); }
      }
      public Builder SetValue(global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum value) {
        PrepareBuilder();
        result.hasValue = true;
        result.value_ = value;
        return this;
      }
      public Builder ClearValue() {
        PrepareBuilder();
        result.hasValue = false;
        result.value_ = global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum.DEFAULT_VALUE;
        return this;
      }

      public pbc::IPopsicleList<global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum> ValuesList {
        get { return PrepareBuilder().values_; }
      }
      public int ValuesCount {
        get { return result.ValuesCount; }
      }
      public global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum GetValues(int index) {
        return result.GetValues(index);
      }
      public Builder SetValues(int index, global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum value) {
        PrepareBuilder();
        result.values_[index] = value;
        return this;
      }
      public Builder AddValues(global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum value) {
        PrepareBuilder();
        result.values_.Add(value);
        return this;
      }
      public Builder AddRangeValues(scg::IEnumerable<global::Google.ProtocolBuffers.TestProtos.UpRevision.Types.Enum> values) {
        PrepareBuilder();
        result.values_.Add(values);
        return this;
      }
      public Builder ClearValues() {
        PrepareBuilder();
        result.values_.Clear();
        return this;
      }
    }
    static UpRevision() {
      object.ReferenceEquals(global::Google.ProtocolBuffers.TestProtos.UnknownEnumTest.Descriptor, null);
    }
  }

  #endregion

}

#endregion Designer generated code
