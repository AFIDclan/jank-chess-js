#include <napi.h>
#include "jank-chess/engine/include/Board.h"
#include "jank-chess/engine/include/Zobrist.h"
#include "jank-chess/engine/include/Attack.h"

#include <iostream>

namespace BoardWrapper {

    Napi::Number NativeConstructor(const Napi::CallbackInfo& info);
    Napi::Value NativeGetMoves(const Napi::CallbackInfo& info);
    Napi::Object Init(Napi::Env env, Napi::Object exports);
}