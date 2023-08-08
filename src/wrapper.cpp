#include "wrapper.h"

Napi::Object BoardWrapper::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("BoardWrapper::NativeConstructor", Napi::Function::New(env, BoardWrapper::NativeConstructor));
}

Napi::Number BoardWrapper::NativeConstructor(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Board* board = new Board();

    uintptr_t native_pointer = reinterpret_cast<uintptr_t>(board);

    return Napi::Number::New(env, native_pointer);

}