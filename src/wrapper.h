#include <napi.h>
#include "jank-chess/engine/include/Board.h"

#include <iostream>

namespace BoardWrapper {

    Napi::Number NativeConstructor(const Napi::CallbackInfo& info);
    Napi::Object Init(Napi::Env env, Napi::Object exports);
}