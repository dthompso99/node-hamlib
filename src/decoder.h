#pragma once

#include <napi.h>

class Decoder : public Napi::ObjectWrap<Decoder> {
 public:
  Decoder(const Napi::CallbackInfo&);
  Napi::Value Open(const Napi::CallbackInfo&);

  static Napi::Function GetClass(Napi::Env);

 private:
  bool rig_is_open = false;
};