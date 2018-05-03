#include "testpromisemain.h"
#include "tools.h"
#include <iostream>

FuTestImpl::FuTestImpl() {
  m_PropReadByteStringArrayValue.push_back("Value1");
  m_PropReadByteStringArrayValue.push_back("Value2");
  m_PropReadObjectPathArrayValue.push_back("Value3");
  m_PropReadObjectPathArrayValue.push_back("Value4");
  m_PropReadStringArrayValue.push_back("Value5");
  m_PropReadStringArrayValue.push_back("Value6");
  m_PropReadByteStringValue = "Value7";
  m_PropReadSignatureValue = "Value8";
  m_PropReadObjectPathValue = "Value9";
  m_PropReadStringValue = "Value10";
  m_PropReadDoubleValue = 1337;
  m_PropReadUInt64Value = 1338;
  m_PropReadInt64Value = 1339;
  m_PropReadUIntValue = 1340;
  m_PropReadIntValue = 1341;
  m_PropReadUInt16Value = 1342;
  m_PropReadInt16Value = 1343;
  m_PropReadCharValue = 'A';
  m_PropReadBooleanValue = true;
  m_PropWriteByteStringArrayValue.push_back("Value11");
  m_PropWriteByteStringArrayValue.push_back("Value12");
  m_PropWriteObjectPathArratValue.push_back("Value13");
  m_PropWriteObjectPathArratValue.push_back("Value14");
  m_PropWriteObjectPathArratValue.push_back("Value15");
  m_PropWriteStringArrayValue.push_back("Value16");
  m_PropWriteByteStringValue = "Value17";
  m_PropWriteSignatureValue = "Value18";
  m_PropWriteObjectPathValue = "Value19";
  m_PropWriteStringValue = "Value20";
  m_PropWriteDoubleValue = 1344;
  m_PropWriteUInt64Value = 1345;
  m_PropWriteInt64Value = 1346;
  m_PropWriteUIntValue = 1347;
  m_PropWriteIntValue = 1348;
  m_PropWriteUInt16Value = 1349;
  m_PropWriteInt16Value = 1350;
  m_PropWriteCharValue = 'B';
  m_PropWriteBooleanValue = false;
  m_PropReadWriteByteStringArrayValue.push_back("Value21");
  m_PropReadWriteByteStringArrayValue.push_back("Value22");
  m_PropReadWriteObjectPathArrayValue.push_back("/object/path");
  m_PropReadWriteStringArrayValue.push_back("Value24");
  m_PropReadWriteByteStringValue = "Value25";
  m_PropReadWriteSignatureValue = "Value26";
  m_PropReadWriteObjectPathValue = "Value27";
  m_PropReadWriteStringValue = "Value28";
  m_PropReadWriteDoubleValue = 1351;
  m_PropReadWriteUInt64Value = 1352;
  m_PropReadWriteInt64Value = 1353;
  m_PropReadWriteUIntValue = 1354;
  m_PropReadWriteIntValue = 1355;
  m_PropReadWriteUInt16Value = 1356;
  m_PropReadWriteInt16Value = 1357;
  m_PropReadWriteCharValue = 'C';
  m_PropReadWriteBooleanValue = true;
}

void FuTestImpl::FuTestVariant(Glib::VariantBase Param1,
                           FuTestMessageHelper invocation) {
  std::string value;
  try {
    Glib::Variant<Glib::ustring> res =
        Glib::VariantBase::cast_dynamic<Glib::Variant<Glib::ustring>>(Param1);
    value = res.get();
  } catch (std::bad_cast e) {
    std::cout << e.what() << std::endl;
  }

  Glib::Variant<Glib::Variant<Glib::ustring>> variantValue;
  variantValue = Glib::Variant<Glib::Variant<Glib::ustring>>::create(
      Glib::Variant<Glib::ustring>::create(value));

  invocation.ret(variantValue);
}

void FuTestImpl::FuTestByteStringArray(std::vector<std::string> Param1,
                                   FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestObjectPathArray(std::vector<std::string> Param1,
                                   FuTestMessageHelper invocation) {

  std::vector<Glib::VariantBase> list;
  GVariantBuilder builder;
  g_variant_builder_init(&builder, G_VARIANT_TYPE("ao"));
  for (int i = 0; i < Param1.size(); i++) {
    g_variant_builder_add(&builder, "o", Param1[i].c_str());
  }
  Glib::VariantBase ret = Glib::wrap(g_variant_builder_end(&builder));

  invocation.ret(ret);
}

void FuTestImpl::FuTestStringArray(std::vector<std::string> Param1,
                               FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestByteString(std::string Param1,
                              FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestSignature(std::string Param1, FuTestMessageHelper invocation) {
  invocation.ret(Glib::wrap(g_variant_new_signature(Param1.c_str())));
}

void FuTestImpl::FuTestObjectPath(std::string Param1,
                              FuTestMessageHelper invocation) {
  invocation.ret(Glib::wrap(g_variant_new_object_path(Param1.c_str())));
}

void FuTestImpl::FuTestString(std::string Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestDouble(double Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestUInt64(guint64 Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestInt64(gint64 Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestUInt(guint32 Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestInt(gint32 Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestUInt16(guint16 Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestInt16(gint16 Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestChar(guchar Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestBoolean(bool Param1, FuTestMessageHelper invocation) {
  invocation.ret(Param1);
}

void FuTestImpl::FuTestAll(std::vector<std::string> in_Param1,
                       std::vector<std::string> in_Param2,
                       std::vector<std::string> in_Param3,
                       std::string in_Param4, std::string in_Param5,
                       std::string in_Param6, std::string in_Param7,
                       double in_Param8, guint64 in_Param9, gint64 in_Param10,
                       guint32 in_Param11, gint32 in_Param12,
                       guint16 in_Param13, gint16 in_Param14, guchar in_Param15,
                       bool in_Param16, FuTestMessageHelper invocation) {}

void FuTestImpl::FuTestTriggerInternalPropertyChange(gint32 newValue,
                                                 FuTestMessageHelper invocation) {
  FuTestPropInternalReadPropertyChange_set(newValue);
  FuTestPropInternalReadWritePropertyChange_set(newValue);
  invocation.ret();
}

std::vector<std::string> FuTestImpl::FuTestPropReadByteStringArray_get() {
  return m_PropReadByteStringArrayValue;
}
std::vector<std::string> FuTestImpl::FuTestPropReadObjectPathArray_get() {
  return m_PropReadObjectPathArrayValue;
}
std::vector<std::string> FuTestImpl::FuTestPropReadStringArray_get() {
  return m_PropReadStringArrayValue;
}
std::string FuTestImpl::FuTestPropReadByteString_get() {
  return m_PropReadByteStringValue;
}
std::string FuTestImpl::FuTestPropReadSignature_get() {
  return m_PropReadSignatureValue;
}
std::string FuTestImpl::FuTestPropReadObjectPath_get() {
  return m_PropReadObjectPathValue;
}
std::string FuTestImpl::FuTestPropReadString_get() { return m_PropReadStringValue; }
double FuTestImpl::FuTestPropReadDouble_get() { return m_PropReadDoubleValue; }
guint64 FuTestImpl::FuTestPropReadUInt64_get() { return m_PropReadUInt64Value; }
gint64 FuTestImpl::FuTestPropReadInt64_get() { return m_PropReadInt64Value; }
guint32 FuTestImpl::FuTestPropReadUInt_get() { return m_PropReadUIntValue; }
gint32 FuTestImpl::FuTestPropReadInt_get() { return m_PropReadIntValue; }
guint16 FuTestImpl::FuTestPropReadUInt16_get() { return m_PropReadUInt16Value; }
gint16 FuTestImpl::FuTestPropReadInt16_get() { return m_PropReadInt16Value; }
guchar FuTestImpl::FuTestPropReadChar_get() { return m_PropReadCharValue; }
bool FuTestImpl::FuTestPropReadBoolean_get() { return m_PropReadBooleanValue; }
std::vector<std::string> FuTestImpl::FuTestPropWriteByteStringArray_get() {
  return m_PropWriteByteStringArrayValue;
}
std::vector<std::string> FuTestImpl::FuTestPropWriteObjectPathArray_get() {
  return m_PropWriteObjectPathArratValue;
}
std::vector<std::string> FuTestImpl::FuTestPropWriteStringArray_get() {
  return m_PropWriteStringArrayValue;
}
std::string FuTestImpl::FuTestPropWriteByteString_get() {
  return m_PropWriteByteStringValue;
}
std::string FuTestImpl::FuTestPropWriteSignature_get() {
  return m_PropWriteSignatureValue;
}
std::string FuTestImpl::FuTestPropWriteObjectPath_get() {
  return m_PropWriteObjectPathValue;
}
std::string FuTestImpl::FuTestPropWriteString_get() {
  return m_PropWriteStringValue;
}
double FuTestImpl::FuTestPropWriteDouble_get() { return m_PropWriteDoubleValue; }
guint64 FuTestImpl::FuTestPropWriteUInt64_get() { return m_PropWriteUInt64Value; }
gint64 FuTestImpl::FuTestPropWriteInt64_get() { return m_PropWriteInt64Value; }
guint32 FuTestImpl::FuTestPropWriteUInt_get() { return m_PropWriteUIntValue; }
gint32 FuTestImpl::FuTestPropWriteInt_get() { return m_PropWriteIntValue; }
guint16 FuTestImpl::FuTestPropWriteUInt16_get() { return m_PropWriteUInt16Value; }
gint16 FuTestImpl::FuTestPropWriteInt16_get() { return m_PropWriteInt16Value; }
guchar FuTestImpl::FuTestPropWriteChar_get() { return m_PropWriteCharValue; }
bool FuTestImpl::FuTestPropWriteBoolean_get() { return m_PropWriteBooleanValue; }
std::vector<std::string> FuTestImpl::FuTestPropReadWriteByteStringArray_get() {
  return m_PropReadWriteByteStringArrayValue;
}
std::vector<std::string> FuTestImpl::FuTestPropReadWriteObjectPathArray_get() {
  return m_PropReadWriteObjectPathArrayValue;
}
std::vector<std::string> FuTestImpl::FuTestPropReadWriteStringArray_get() {
  return m_PropReadWriteStringArrayValue;
}
std::string FuTestImpl::FuTestPropReadWriteByteString_get() {
  return m_PropReadWriteByteStringValue;
}
std::string FuTestImpl::FuTestPropReadWriteSignature_get() {
  return m_PropReadWriteSignatureValue;
}
std::string FuTestImpl::FuTestPropReadWriteObjectPath_get() {
  return m_PropReadWriteObjectPathValue;
}
std::string FuTestImpl::FuTestPropReadWriteString_get() {
  return m_PropReadWriteStringValue;
}
double FuTestImpl::FuTestPropReadWriteDouble_get() {
  return m_PropReadWriteDoubleValue;
}
guint64 FuTestImpl::FuTestPropReadWriteUInt64_get() {
  return m_PropReadWriteUInt64Value;
}
gint64 FuTestImpl::FuTestPropReadWriteInt64_get() {
  return m_PropReadWriteInt64Value;
}
guint32 FuTestImpl::FuTestPropReadWriteUInt_get() {
  return m_PropReadWriteUIntValue;
}
gint32 FuTestImpl::FuTestPropReadWriteInt_get() { return m_PropReadWriteIntValue; }
guint16 FuTestImpl::FuTestPropReadWriteUInt16_get() {
  return m_PropReadWriteUInt16Value;
}
gint16 FuTestImpl::FuTestPropReadWriteInt16_get() {
  return m_PropReadWriteInt16Value;
}
guchar FuTestImpl::FuTestPropReadWriteChar_get() {
  return m_PropReadWriteCharValue;
}
bool FuTestImpl::FuTestPropReadWriteBoolean_get() {
  return m_PropReadWriteBooleanValue;
}
gint32 FuTestImpl::FuTestPropInternalReadPropertyChange_get() {
  return m_FuTestPropInternalReadPropertyChangeValue;
}
gint32 FuTestImpl::FuTestPropInternalReadWritePropertyChange_get() {
  return m_FuTestPropInternalReadWritePropertyChangeValue;
}

/* These are not used, so we just return a dummy value here */
bool FuTestImpl::FuTestPropWriteByteStringArray_setHandler(
    std::vector<std::string> value) {
  return false;
}
bool FuTestImpl::FuTestPropWriteObjectPathArray_setHandler(
    std::vector<std::string> value) {
  return false;
}
bool FuTestImpl::FuTestPropWriteStringArray_setHandler(
    std::vector<std::string> value) {
  return false;
}
bool FuTestImpl::FuTestPropWriteByteString_setHandler(std::string value) {
  return false;
}
bool FuTestImpl::FuTestPropWriteSignature_setHandler(std::string value) {
  return false;
}
bool FuTestImpl::FuTestPropWriteObjectPath_setHandler(std::string value) {
  return false;
}
bool FuTestImpl::FuTestPropWriteString_setHandler(std::string value) {
  return false;
}
bool FuTestImpl::FuTestPropWriteDouble_setHandler(double value) { return false; }
bool FuTestImpl::FuTestPropWriteUInt64_setHandler(guint64 value) { return false; }
bool FuTestImpl::FuTestPropWriteInt64_setHandler(gint64 value) { return false; }
bool FuTestImpl::FuTestPropWriteUInt_setHandler(guint32 value) { return false; }
bool FuTestImpl::FuTestPropWriteInt_setHandler(gint32 value) { return false; }
bool FuTestImpl::FuTestPropWriteUInt16_setHandler(guint16 value) { return false; }
bool FuTestImpl::FuTestPropWriteInt16_setHandler(gint16 value) { return false; }
bool FuTestImpl::FuTestPropWriteChar_setHandler(guchar value) { return false; }
bool FuTestImpl::FuTestPropWriteBoolean_setHandler(bool value) { return false; }
/* End return dummy value warning */

bool FuTestImpl::FuTestPropReadWriteByteStringArray_setHandler(
    std::vector<std::string> value) {
  m_PropReadWriteByteStringArrayValue = value;
  FuTestSignalByteStringArray_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteObjectPathArray_setHandler(
    std::vector<std::string> value) {
  m_PropReadWriteObjectPathArrayValue = value;
  FuTestSignalObjectPathArray_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteStringArray_setHandler(
    std::vector<std::string> value) {
  m_PropReadWriteStringArrayValue = value;
  FuTestSignalStringArray_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteByteString_setHandler(std::string value) {
  m_PropReadWriteByteStringValue = value;
  FuTestSignalByteString_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteSignature_setHandler(std::string value) {
  m_PropReadWriteSignatureValue = value;
  FuTestSignalSignature_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteObjectPath_setHandler(std::string value) {
  m_PropReadWriteObjectPathValue = value;
  FuTestSignalObjectPath_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteString_setHandler(std::string value) {
  m_PropReadWriteStringValue = value;
  FuTestSignalString_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteDouble_setHandler(double value) {
  m_PropReadWriteDoubleValue = value;
  FuTestSignalDouble_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteUInt64_setHandler(guint64 value) {
  m_PropReadWriteUInt64Value = value;
  FuTestSignalUInt64_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteInt64_setHandler(gint64 value) {
  m_PropReadWriteInt64Value = value;
  FuTestSignalInt64_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteUInt_setHandler(guint32 value) {
  m_PropReadWriteUIntValue = value;
  FuTestSignalUInt_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteInt_setHandler(gint32 value) {
  m_PropReadWriteIntValue = value;
  FuTestSignalInt_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteUInt16_setHandler(guint16 value) {
  m_PropReadWriteUInt16Value = value;
  FuTestSignalUInt16_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteInt16_setHandler(gint16 value) {
  m_PropReadWriteInt16Value = value;
  FuTestSignalInt16_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteChar_setHandler(guchar value) {
  m_PropReadWriteCharValue = value;
  FuTestSignalChar_signal.emit(value);
  return true;
}
bool FuTestImpl::FuTestPropReadWriteBoolean_setHandler(bool value) {
  m_PropReadWriteBooleanValue = value;
  FuTestSignalBoolean_signal.emit(value);
  return true;
}

bool FuTestImpl::FuTestPropInternalReadPropertyChange_setHandler(gint32 value) {
  m_FuTestPropInternalReadPropertyChangeValue = value;
  return true;
}

bool FuTestImpl::FuTestPropInternalReadWritePropertyChange_setHandler(
    gint32 value) {
  m_FuTestPropInternalReadWritePropertyChangeValue = value;
  return true;
}

int main() {
  Glib::init();
  Gio::init();

  FuTestImpl impl;
  impl.connect(Gio::DBus::BUS_TYPE_SESSION, "org.gdbus.codegen.glibmm.FuTest");

  Glib::RefPtr<Glib::MainLoop> ml = Glib::MainLoop::create();
  ml->run();
}
