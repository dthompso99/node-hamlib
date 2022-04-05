#pragma once

#include <napi.h>

typedef struct s_rig RIG;

class NodeHamLib : public Napi::ObjectWrap<NodeHamLib> {
 public:
  NodeHamLib(const Napi::CallbackInfo&);
  Napi::Value Open(const Napi::CallbackInfo&);
  Napi::Value SetVFO(const Napi::CallbackInfo&);
  Napi::Value SetFrequency(const Napi::CallbackInfo&);
  Napi::Value SetMode(const Napi::CallbackInfo&);
  Napi::Value SetPtt(const Napi::CallbackInfo&);
  Napi::Value GetFrequency(const Napi::CallbackInfo&);
  Napi::Value GetVFO(const Napi::CallbackInfo&);
  Napi::Value GetMode(const Napi::CallbackInfo&);
  Napi::Value GetStrength(const Napi::CallbackInfo&);

  Napi::Value Close(const Napi::CallbackInfo&);
  Napi::Value Destroy(const Napi::CallbackInfo&);
  static Napi::Function GetClass(Napi::Env);

 private:
  RIG *my_rig;
};