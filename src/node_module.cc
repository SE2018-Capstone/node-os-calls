#include <nan.h>

extern NAN_METHOD(whoAmI);
extern NAN_METHOD(getVolume);

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, whoAmI);
  NAN_EXPORT(target, getVolume);
}

NODE_MODULE(node_os_calls, Initialize)
