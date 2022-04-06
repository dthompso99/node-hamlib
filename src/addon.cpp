#include <napi.h>
#include "hamlib.h"
#include "decoder.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {

  Napi::String name = Napi::String::New(env, "HamLib");
  exports.Set(name, NodeHamLib::GetClass(env));


  Napi::String decoder_name = Napi::String::New(env, "Decoder");
  exports.Set(decoder_name, Decoder::GetClass(env));

  return exports;
}

NODE_API_MODULE(radio, Init)