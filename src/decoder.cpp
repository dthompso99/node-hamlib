// #include "decoder.h"
// #include "portaudio.h"
// #include <stdio.h>

// //https://github.com/Streampunk/naudiodon -- perhaps should just use this?

// #define SAMPLE_RATE  (44100)
// #define FRAMES_PER_BUFFER (512)

// #define PA_SAMPLE_TYPE  paFloat32
// typedef float SAMPLE;
// #define SAMPLE_SILENCE  (0.0f)
// #define PRINTF_S_FORMAT "%.8f"

// using namespace Napi;

// Decoder::Decoder(const Napi::CallbackInfo & info): ObjectWrap(info) {
//   //Napi::Env env = info.Env();
//     PaError err;
//     //suppress output from pa_initialize
//     fclose(stderr);
//     err = Pa_Initialize();
//     freopen("CON", "w", stderr);
//   if (err != paNoError) {
//     printf("ERROR: Pa_Initialize returned 0x%x\n", err);
//   }
// }

// Napi::Value Decoder::Close(const Napi::CallbackInfo & info) {
//   Napi::Env env = info.Env();
//   int retcode = 0;
//   Pa_Terminate();
//   return Napi::Number::New(env, retcode);
// }

// Napi::Value Decoder::ListDevices(const Napi::CallbackInfo & info) {
//   Napi::Env env = info.Env();
  
//   int numDevices;
//   const PaDeviceInfo * deviceInfo;
//   numDevices = Pa_GetDeviceCount();
//   Napi::Array arrDevices = Napi::Array::New(env);
//   for (int i = 0; i < numDevices; i++) {
//     deviceInfo = Pa_GetDeviceInfo(i);
//     printf("Source: %s  -- inputs: %i outputs: %i\n", deviceInfo->name, deviceInfo->maxInputChannels, deviceInfo->maxOutputChannels);
//     arrDevices.Set(i, Napi::String::New(env, deviceInfo -> name));
//   }
//   return arrDevices;
// }

// static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
// {
//   (void)outputBuffer;
//   const float *finput = static_cast<const float *>(inputBuffer);
//   printf("callback called! float: %.8f : frames: %i\n", finput, framesPerBuffer);
//   Decoder *decoder = static_cast<Decoder *>(userData);
//   return paContinue;
// }

//  Napi::Value Decoder::SetInputDevice(const Napi::CallbackInfo &info)
//  {
//    Napi::Env env = info.Env();
//    if (!info[0].IsNumber())
//    {
//      Napi::TypeError::New(env, "Device number must be an integer").ThrowAsJavaScriptException();
//      return env.Null();
//    }
//    // begin test
//    inputParameters.device = info[0].As<Napi::Number>().Int32Value();
//    inputParameters.channelCount = 1;
//    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
//    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
//    inputParameters.hostApiSpecificStreamInfo = NULL;
//    return Napi::Number::New(env, 0);
//  }

// Napi::Value Decoder::SetOutputDevice(const Napi::CallbackInfo &info)
// {
//   Napi::Env env = info.Env();
//   if (!info[0].IsNumber())
//   {
//     Napi::TypeError::New(env, "Device number must be an integer").ThrowAsJavaScriptException();
//     return env.Null();
//   }
//   outputParameters.device = info[0].As<Napi::Number>().Int32Value();
//   outputParameters.channelCount = 1;
//   outputParameters.sampleFormat = PA_SAMPLE_TYPE;
//   outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowInputLatency;
//   outputParameters.hostApiSpecificStreamInfo = NULL;
//   return Napi::Number::New(env, 0);
// }

// Napi::Value Decoder::Open(const Napi::CallbackInfo &info)
// {
//   Napi::Env env = info.Env();
//   PaError err = paNoError;
//   err = Pa_OpenStream(
//       &stream,
//       &inputParameters,
//       &outputParameters,
//       SAMPLE_RATE,
//       FRAMES_PER_BUFFER,
//       paClipOff, /* we won't output out of range samples so don't bother clipping them */
//       recordCallback,
//       static_cast<void *>(this));
//   if (err != paNoError)
//   {
//     Napi::TypeError::New(env, "Unable to open input!").ThrowAsJavaScriptException();
//     return env.Null();
//   }
//   else
//   {
//     err = Pa_StartStream(stream);
//     return Napi::Number::New(env, 0);
//   }
// }

// Napi::Function Decoder::GetClass(Napi::Env env) {
//   return DefineClass(
//     env,
//     "Decoder", {
//       Decoder::InstanceMethod("close", & Decoder::Close),
//       Decoder::InstanceMethod("listDevices", & Decoder::ListDevices),
//       Decoder::InstanceMethod("setInputDevice", & Decoder::SetInputDevice),
//       Decoder::InstanceMethod("setOutputDevice", & Decoder::SetOutputDevice),
//       Decoder::InstanceMethod("open", & Decoder::Open)
//     });
// }