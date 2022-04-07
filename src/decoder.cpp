#include "decoder.h"
#include "portaudio.h"

using namespace Napi;

Decoder::Decoder(const Napi::CallbackInfo & info): ObjectWrap(info) {
  //Napi::Env env = info.Env();
    PaError err;
      err = Pa_Initialize();
  if (err != paNoError) {
    printf("ERROR: Pa_Initialize returned 0x%x\n", err);
  }
}

Napi::Value Decoder::Close(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode = 0;
  Pa_Terminate();
  return Napi::Number::New(env, retcode);
}

Napi::Value Decoder::ListDevices(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  
  int numDevices;
  const PaDeviceInfo * deviceInfo;
  numDevices = Pa_GetDeviceCount();
  Napi::Array arrDevices = Napi::Array::New(env);
  for (int i = 0; i < numDevices; i++) {
    deviceInfo = Pa_GetDeviceInfo(i);
    arrDevices.Set(i, Napi::String::New(env, deviceInfo -> name));
  }
  return arrDevices;
}

Napi::Value Decoder::SetInputDevice(const Napi::CallbackInfo & info) {

    return Napi::Number::New(env, 0);
}

Napi::Value Decoder::SetOutputDevice(const Napi::CallbackInfo & info) {

    return Napi::Number::New(env, 0);
}

Napi::Function Decoder::GetClass(Napi::Env env) {
  return DefineClass(
    env,
    "Decoder", {
      Decoder::InstanceMethod("close", & Decoder::Close),
      Decoder::InstanceMethod("listDevices", & Decoder::ListDevices),
      Decoder::InstanceMethod("setInputDevice", & Decoder::SetInputDevice),
      Decoder::InstanceMethod("setOutputDevice", & Decoder::SetOutputDevice),
    });
}