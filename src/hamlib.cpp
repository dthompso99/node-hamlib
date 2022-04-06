#include "hamlib.h"

#include <hamlib/rig.h>

using namespace Napi;

NodeHamLib::NodeHamLib(const Napi::CallbackInfo & info): ObjectWrap(info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return;
  }

  if (info.Length() < 2) {
    rig_set_debug_level(RIG_DEBUG_NONE);
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "Invalid Rig number").ThrowAsJavaScriptException();
    return;
  }
  //rig_model_t myrig_model;
  //   hamlib_port_t myport;
  // /* may be overriden by backend probe */
  // myport.type.rig = RIG_PORT_SERIAL;
  // myport.parm.serial.rate = 38400;
  // myport.parm.serial.data_bits = 8;
  // myport.parm.serial.stop_bits = 2;
  // myport.parm.serial.parity = RIG_PARITY_NONE;
  // myport.parm.serial.handshake = RIG_HANDSHAKE_HARDWARE;
  // strncpy(myport.pathname, "/dev/ttyUSB0", FILPATHLEN - 1);

  // rig_load_all_backends();
  // myrig_model = rig_probe(&myport);
  // fprintf(stderr, "Got Rig Model %d \n", myrig_model);

  rig_model_t myrig_model = info[0].As < Napi::Number > ().DoubleValue();

  my_rig = rig_init(myrig_model);
  if (!my_rig) {
    fprintf(stderr, "Unknown rig num: %d\n", myrig_model);
    fprintf(stderr, "Please check riglist.h\n");
    Napi::TypeError::New(env, "Unable to Init Rig").ThrowAsJavaScriptException();
  }
  strncpy(my_rig -> state.rigport.pathname, "/dev/ttyUSB0", FILPATHLEN - 1);
  rig_is_open = false;
}

Napi::Value NodeHamLib::Open(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();

  int retcode = rig_open(my_rig);
  if (retcode != RIG_OK) {
    printf("rig_open: error = %s\n", rigerror(retcode));
    // Napi::TypeError::New(env, "Unable to open rig")
    // .ThrowAsJavaScriptException();
  }
  rig_is_open = true;
  return Napi::Number::New(env, retcode);
}

Napi::Value NodeHamLib::SetVFO(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;

  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Must Specify VFO-A or VFO-B")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Must Specify VFO-A or VFO-B as a string")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  auto name = info[0].As < Napi::String > ().Utf8Value().c_str();
  if (strcmp(name, "VFO-A") == 0) {
    retcode = rig_set_vfo(my_rig, RIG_VFO_A);
  } else if (strcmp(name, "VFO-B") == 0) {
    retcode = rig_set_vfo(my_rig, RIG_VFO_B);
  } else {
    retcode = 1;
  }
  return Napi::Number::New(env, retcode);
}

Napi::Value NodeHamLib::SetFrequency(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Must Specify VFO-A or VFO-B")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "Frequency must be specified as an integer")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  auto freq = info[0].As < Napi::Number > ().Int32Value();
  retcode = rig_set_freq(my_rig, RIG_VFO_CURR, freq);
  return Napi::Number::New(env, retcode);
}

Napi::Value NodeHamLib::SetMode(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;
  pbwidth_t bandwidth;
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Must Specify Mode")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Must Specify Mode as string")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  auto modestr = info[0].As < Napi::String > ().Utf8Value().c_str();
  auto mode = rig_parse_mode(modestr);

  if (info.Length() > 1) {
    if (!info[1].IsString()) {
      Napi::TypeError::New(env, "Must Specify Mode as string")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    auto bandstr = info[1].As < Napi::String > ().Utf8Value().c_str();
    if (strcmp(bandstr, "narrow") == 0) {
      bandwidth = rig_passband_narrow(my_rig, mode);
    } else if (strcmp(bandstr, "wide") == 0) {
      bandwidth = rig_passband_wide(my_rig, mode);
    } else {
      bandwidth = RIG_PASSBAND_NORMAL;
    }
  } else {
    bandwidth = RIG_PASSBAND_NORMAL;
  }

  retcode = rig_set_mode(my_rig, RIG_VFO_CURR, mode, bandwidth);
  if (retcode != RIG_OK) {

    Napi::TypeError::New(env, rigerror(retcode))
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  return Napi::Number::New(env, retcode);
}

Napi::Value NodeHamLib::SetPtt(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;
  bool ptt_state;
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Specify true or false for ppt state")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsBoolean()) {
    Napi::TypeError::New(env, "PTT state is not boolean")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  ptt_state = info[0].As < Napi::Boolean > ();
  if (ptt_state) {
    retcode = rig_set_ptt(my_rig, RIG_VFO_CURR, RIG_PTT_ON);
  } else {
    retcode = rig_set_ptt(my_rig, RIG_VFO_CURR, RIG_PTT_OFF);
  }
  if (retcode != RIG_OK) {

    Napi::TypeError::New(env, rigerror(retcode))
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  return Napi::Number::New(env, retcode);
}

Napi::Value NodeHamLib::GetVFO(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;
  vfo_t vfo;
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  retcode = rig_get_vfo(my_rig, & vfo);
  if (retcode == RIG_OK) {
    return Napi::Number::New(env, vfo);
  } else {
    //dont throw an exception here, not every radio reports vfo
    Napi::Error::New(env, rigerror(retcode));
    return env.Null();
  }

}

Napi::Value NodeHamLib::GetFrequency(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;
  freq_t freq;
  retcode = rig_get_freq(my_rig, RIG_VFO_CURR, & freq);
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (retcode == RIG_OK) {
    return Napi::Number::New(env, freq);
  } else {
    Napi::Error::New(env, rigerror(retcode));
    return env.Null();
  }
}

Napi::Value NodeHamLib::GetMode(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;
  rmode_t rmode;
  pbwidth_t width;
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  retcode = rig_get_mode(my_rig, RIG_VFO_CURR, & rmode, & width);
  if (retcode == RIG_OK) {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set(Napi::String::New(env, "mode"), rmode);
    obj.Set(Napi::String::New(env, "width"), width);
    return obj;
  } else {
    Napi::Error::New(env, rigerror(retcode));
    return env.Null();
  }
}

Napi::Value NodeHamLib::GetStrength(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  int retcode;
  int strength;
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  retcode = rig_get_strength(my_rig, RIG_VFO_CURR, & strength);
  if (retcode == RIG_OK) {
    return Napi::Number::New(env, strength);
  } else {
    Napi::Error::New(env, rigerror(retcode));
    return env.Null();
  }
}

Napi::Value NodeHamLib::Close(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  if (!rig_is_open) {
    Napi::TypeError::New(env, "Rig is not open!")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  int retcode = rig_close(my_rig);
  if (retcode != RIG_OK) {
    Napi::TypeError::New(env, "Unable to open rig")
      .ThrowAsJavaScriptException();
  }
  rig_is_open = false;
  return Napi::Number::New(env, retcode);
}

Napi::Value NodeHamLib::Destroy(const Napi::CallbackInfo & info) {
  Napi::Env env = info.Env();
  if (rig_is_open) {
    rig_close(my_rig);
  }
  int retcode = rig_cleanup(my_rig);
  if (retcode != RIG_OK) {

    Napi::TypeError::New(env, rigerror(retcode))
      .ThrowAsJavaScriptException();
  }
  rig_is_open = false;
  return Napi::Number::New(env, retcode);
}

Napi::Function NodeHamLib::GetClass(Napi::Env env) {
  return DefineClass(
    env,
    "HamLib", {
      NodeHamLib::InstanceMethod("open", & NodeHamLib::Open),
      NodeHamLib::InstanceMethod("setVfo", & NodeHamLib::SetVFO),
      NodeHamLib::InstanceMethod("setFrequency", & NodeHamLib::SetFrequency),
      NodeHamLib::InstanceMethod("setMode", & NodeHamLib::SetMode),
      NodeHamLib::InstanceMethod("setPtt", & NodeHamLib::SetPtt),
      NodeHamLib::InstanceMethod("getVfo", & NodeHamLib::GetVFO),
      NodeHamLib::InstanceMethod("getFrequency", & NodeHamLib::GetFrequency),
      NodeHamLib::InstanceMethod("getMode", & NodeHamLib::GetMode),
      NodeHamLib::InstanceMethod("getStrength", & NodeHamLib::GetStrength),
      NodeHamLib::InstanceMethod("close", & NodeHamLib::Close),
      NodeHamLib::InstanceMethod("destroy", & NodeHamLib::Destroy),
    });
}

