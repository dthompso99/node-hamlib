#pragma once

#include <napi.h>
#include <hamlib/rig.h>
//forward declarations
//typedef struct s_rig RIG;
//typedef unsigned int 	vfo_t;
//typedef double freq_t;


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

  static int freq_change_cb(RIG*, vfo_t, freq_t, void*);

 private:
  RIG *my_rig;
  bool rig_is_open = false;
  int count = 0;
  void* freq_emit_cb;
  static Napi::FunctionReference constructor;
  Napi::CallbackInfo * m_currentInfo;
};