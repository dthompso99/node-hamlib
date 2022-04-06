#include "decoder.h"


using namespace Napi;

Decoder::Decoder(const Napi::CallbackInfo & info): ObjectWrap(info) {
  Napi::Env env = info.Env();
}

Napi::Value Decoder::Open(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode = 0;
  printf("\n**Decoder Open Called**\n");
  return Napi::Number::New(env, retcode);
}

Napi::Function Decoder::GetClass(Napi::Env env) {
  return DefineClass(
    env,
    "Decoder", {
      Decoder::InstanceMethod("open", & Decoder::Open),
    });
}

