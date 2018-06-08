#include "testpromisemain.h"
#include "tools.h"
#include <iostream>
#include <string>
#include <vector>

using namespace org::gdbus::codegen::glibmm;
using namespace std;

//*
void setupProperties(Test &ft) {
  auto v1 = vector<string>{"Value1", "Value2"};
  ft.TestPropReadByteStringArray_set(v1);
  ft.TestPropReadObjectPathArray_set(vector<string>{"Value3", "Value4"});
  ft.TestPropReadStringArray_set(vector<string>{"Value5", "Value6"});

  ft.TestPropReadByteString_set("Value7");
  ft.TestPropReadSignature_set("Value8");
  ft.TestPropReadObjectPath_set("Value9");
  ft.TestPropReadString_set("Value10");
  ft.TestPropReadDouble_set(1337);
  ft.TestPropReadUInt64_set(1338);
  ft.TestPropReadInt64_set(1339);
  ft.TestPropReadUInt_set(1340);
  ft.TestPropReadInt_set(1341);
  ft.TestPropReadUInt16_set(1342);
  ft.TestPropReadInt16_set(1343);
  ft.TestPropReadChar_set('A');
  ft.TestPropReadBoolean_set(true);

  ft.TestPropWriteByteStringArray_set(vector<string>{"Value11", "Value12"});
  ft.TestPropWriteObjectPathArray_set(
      vector<string>{"Value13", "Value14", "Value15"});
  ft.TestPropWriteStringArray_set(vector<string>{"Value16"});

  ft.TestPropReadWriteByteStringArray_set(vector<string>{"Value21", "Value22"});
  ft.TestPropReadWriteObjectPathArray_set(vector<string>{"/object/path"});
  ft.TestPropReadWriteStringArray_set(vector<string>{"Value24"});

  ft.TestPropWriteByteString_set("Value17");
  ft.TestPropWriteSignature_set("Value18");
  ft.TestPropWriteObjectPath_set("Value19");
  ft.TestPropWriteString_set("Value20");
  ft.TestPropReadWriteByteString_set("Value25");
  ft.TestPropReadWriteSignature_set("Value26");
  ft.TestPropReadWriteObjectPath_set("Value27");
  ft.TestPropReadWriteString_set("Value28");

  ft.TestPropWriteDouble_set(1344);
  ft.TestPropWriteUInt_set(641345);
  ft.TestPropWriteInt_set(641346);
  ft.TestPropWriteUInt_set(1347);
  ft.TestPropWriteInt_set(1348);
  ft.TestPropWriteUInt_set(161349);
  ft.TestPropWriteInt_set(161350);
  ft.TestPropWriteBoolean_set(false);
  ft.TestPropReadWriteDouble_set(1351);
  ft.TestPropReadWriteUInt64_set(1352);
  ft.TestPropReadWriteInt64_set(1353);
  ft.TestPropReadWriteUInt_set(1354);
  ft.TestPropReadWriteInt_set(1355);
  ft.TestPropReadWriteUInt16_set(1356);
  ft.TestPropReadWriteInt16_set(1357);
  ft.TestPropWriteChar_set('B');
  ft.TestPropReadWriteChar_set('C');

  ft.TestPropReadWriteBoolean_set(true);
} //*/

int main() {
  Glib::init();
  Gio::init();

  Test ft;

  ft.connect(Gio::DBus::BUS_TYPE_SESSION, "org.gdbus.codegen.glibmm.Test");
  
  Glib::RefPtr<Glib::MainLoop> ml = Glib::MainLoop::create();
  setupProperties(ft);
  
  ml->run();
}
