#include "futures_promise.h"

class FutureTest : public org::gdbus::codegen::glibmm::Test {
  virtual void TestTriggerInternalPropertyChange(gint32 newValue,
                                                 TestMessageHelper invocation);
};
