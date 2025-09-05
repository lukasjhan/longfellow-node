#include <napi.h>
#include <cstdint>

// 퍼블릭 API 헤더(공식 가이드에서 제시)
#include "/home/lukasjhan/longfellow-zk/install/include/mdoc_zk.h"

Napi::Value ping(const Napi::CallbackInfo& info) {
  return Napi::String::New(info.Env(), "longfellow-ok");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("ping", Napi::Function::New(env, ping));
  return exports;
}
NODE_API_MODULE(addon, Init)
