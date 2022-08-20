#pragma once

#include "portaudio.h"
#include <napi.h>

class Decoder : public Napi::ObjectWrap<Decoder> {
 public:
  Decoder(const Napi::CallbackInfo&);
  Napi::Value Close(const Napi::CallbackInfo&);
  Napi::Value ListDevices(const Napi::CallbackInfo&);
  Napi::Value SetInputDevice(const Napi::CallbackInfo&);
  Napi::Value SetOutputDevice(const Napi::CallbackInfo&);
  Napi::Value Open(const Napi::CallbackInfo&);

  static Napi::Function GetClass(Napi::Env);

 private:
  bool rig_is_open = false;
  PaStreamParameters  inputParameters, outputParameters;
  PaStream *stream;
};