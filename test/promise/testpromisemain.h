#include "futures_promise.h"

class FuTestImpl : public org::gdbus::codegen::glibmm::FuTest {
public:
  FuTestImpl();

  void FuTestVariant(Glib::VariantBase Param1, FuTestMessageHelper invocation);
  void FuTestByteStringArray(std::vector<std::string> Param1,
                             FuTestMessageHelper invocation);
  void FuTestObjectPathArray(std::vector<std::string> Param1,
                             FuTestMessageHelper invocation);
  void FuTestStringArray(std::vector<std::string> Param1,
                         FuTestMessageHelper invocation);
  void FuTestByteString(std::string Param1, FuTestMessageHelper invocation);
  void FuTestSignature(std::string Param1, FuTestMessageHelper invocation);
  void FuTestObjectPath(std::string Param1, FuTestMessageHelper invocation);
  void FuTestString(std::string Param1, FuTestMessageHelper invocation);
  void FuTestDouble(double Param1, FuTestMessageHelper invocation);
  void FuTestUInt64(guint64 Param1, FuTestMessageHelper invocation);
  void FuTestInt64(gint64 Param1, FuTestMessageHelper invocation);
  void FuTestUInt(guint32 Param1, FuTestMessageHelper invocation);
  void FuTestInt(gint32 Param1, FuTestMessageHelper invocation);
  void FuTestUInt16(guint16 Param1, FuTestMessageHelper invocation);
  void FuTestInt16(gint16 Param1, FuTestMessageHelper invocation);
  void FuTestChar(guchar Param1, FuTestMessageHelper invocation);
  void FuTestBoolean(bool Param1, FuTestMessageHelper invocation);
  void FuTestAll(std::vector<std::string> in_Param1,
                 std::vector<std::string> in_Param2,
                 std::vector<std::string> in_Param3, std::string in_Param4,
                 std::string in_Param5, std::string in_Param6,
                 std::string in_Param7, double in_Param8, guint64 in_Param9,
                 gint64 in_Param10, guint32 in_Param11, gint32 in_Param12,
                 guint16 in_Param13, gint16 in_Param14, guchar in_Param15,
                 bool in_Param16, FuTestMessageHelper invocation);
  void FuTestTriggerInternalPropertyChange(gint32 newValue,
                                           FuTestMessageHelper invocation);

  std::vector<std::string> FuTestPropReadByteStringArray_get();
  std::vector<std::string> FuTestPropReadObjectPathArray_get();
  std::vector<std::string> FuTestPropReadStringArray_get();
  std::string FuTestPropReadByteString_get();
  std::string FuTestPropReadSignature_get();
  std::string FuTestPropReadObjectPath_get();
  std::string FuTestPropReadString_get();
  double FuTestPropReadDouble_get();
  guint64 FuTestPropReadUInt64_get();
  gint64 FuTestPropReadInt64_get();
  guint32 FuTestPropReadUInt_get();
  gint32 FuTestPropReadInt_get();
  guint16 FuTestPropReadUInt16_get();
  gint16 FuTestPropReadInt16_get();
  guchar FuTestPropReadChar_get();
  bool FuTestPropReadBoolean_get();
  std::vector<std::string> FuTestPropWriteByteStringArray_get();
  std::vector<std::string> FuTestPropWriteObjectPathArray_get();
  std::vector<std::string> FuTestPropWriteStringArray_get();
  std::string FuTestPropWriteByteString_get();
  std::string FuTestPropWriteSignature_get();
  std::string FuTestPropWriteObjectPath_get();
  std::string FuTestPropWriteString_get();
  double FuTestPropWriteDouble_get();
  guint64 FuTestPropWriteUInt64_get();
  gint64 FuTestPropWriteInt64_get();
  guint32 FuTestPropWriteUInt_get();
  gint32 FuTestPropWriteInt_get();
  guint16 FuTestPropWriteUInt16_get();
  gint16 FuTestPropWriteInt16_get();
  guchar FuTestPropWriteChar_get();
  bool FuTestPropWriteBoolean_get();
  std::vector<std::string> FuTestPropReadWriteByteStringArray_get();
  std::vector<std::string> FuTestPropReadWriteObjectPathArray_get();
  std::vector<std::string> FuTestPropReadWriteStringArray_get();
  std::string FuTestPropReadWriteByteString_get();
  std::string FuTestPropReadWriteSignature_get();
  std::string FuTestPropReadWriteObjectPath_get();
  std::string FuTestPropReadWriteString_get();
  double FuTestPropReadWriteDouble_get();
  guint64 FuTestPropReadWriteUInt64_get();
  gint64 FuTestPropReadWriteInt64_get();
  guint32 FuTestPropReadWriteUInt_get();
  gint32 FuTestPropReadWriteInt_get();
  guint16 FuTestPropReadWriteUInt16_get();
  gint16 FuTestPropReadWriteInt16_get();
  guchar FuTestPropReadWriteChar_get();
  bool FuTestPropReadWriteBoolean_get();
  gint32 FuTestPropInternalReadPropertyChange_get();
  gint32 FuTestPropInternalReadWritePropertyChange_get();

private:
  std::vector<std::string> m_PropReadByteStringArrayValue;
  std::vector<std::string> m_PropReadObjectPathArrayValue;
  std::vector<std::string> m_PropReadStringArrayValue;
  std::string m_PropReadByteStringValue;
  std::string m_PropReadSignatureValue;
  std::string m_PropReadObjectPathValue;
  std::string m_PropReadStringValue;
  double m_PropReadDoubleValue;
  guint64 m_PropReadUInt64Value;
  gint64 m_PropReadInt64Value;
  guint32 m_PropReadUIntValue;
  gint32 m_PropReadIntValue;
  guint16 m_PropReadUInt16Value;
  gint16 m_PropReadInt16Value;
  guchar m_PropReadCharValue;
  bool m_PropReadBooleanValue;
  std::vector<std::string> m_PropWriteByteStringArrayValue;
  std::vector<std::string> m_PropWriteObjectPathArratValue;
  std::vector<std::string> m_PropWriteStringArrayValue;
  std::string m_PropWriteByteStringValue;
  std::string m_PropWriteSignatureValue;
  std::string m_PropWriteObjectPathValue;
  std::string m_PropWriteStringValue;
  double m_PropWriteDoubleValue;
  guint64 m_PropWriteUInt64Value;
  gint64 m_PropWriteInt64Value;
  guint32 m_PropWriteUIntValue;
  gint32 m_PropWriteIntValue;
  guint16 m_PropWriteUInt16Value;
  gint16 m_PropWriteInt16Value;
  guchar m_PropWriteCharValue;
  bool m_PropWriteBooleanValue;
  std::vector<std::string> m_PropReadWriteByteStringArrayValue;
  std::vector<std::string> m_PropReadWriteObjectPathArrayValue;
  std::vector<std::string> m_PropReadWriteStringArrayValue;
  std::string m_PropReadWriteByteStringValue;
  std::string m_PropReadWriteSignatureValue;
  std::string m_PropReadWriteObjectPathValue;
  std::string m_PropReadWriteStringValue;
  double m_PropReadWriteDoubleValue;
  guint64 m_PropReadWriteUInt64Value;
  gint64 m_PropReadWriteInt64Value;
  guint32 m_PropReadWriteUIntValue;
  gint32 m_PropReadWriteIntValue;
  guint16 m_PropReadWriteUInt16Value;
  gint16 m_PropReadWriteInt16Value;
  guchar m_PropReadWriteCharValue;
  bool m_PropReadWriteBooleanValue;
  gint32 m_FuTestPropInternalReadPropertyChangeValue;
  gint32 m_FuTestPropInternalReadWritePropertyChangeValue;
};
