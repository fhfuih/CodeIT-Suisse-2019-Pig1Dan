#include <napi.h>

namespace hello {
    std::string hello(const std::string & name);
    Napi::String helloWrapped(const Napi::CallbackInfo& info);
    Napi::Object Init(Napi::Env env, Napi::Object exports);
}

std::string hello::hello(const std::string & name) {
    return "Hello " + name;
}

Napi::String hello::helloWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }
    Napi::String name = info[0].As<Napi::String>();
    Napi::String returnValue = Napi::String::New(env, hello::hello(name.Utf8Value()));

    return returnValue;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("hello", Napi::Function::New(env, hello::helloWrapped));
    return exports;
}
