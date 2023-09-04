#include <napi.h>
#include "jank-chess/engine/include/Board.h"
#include "jank-chess/engine/include/Zobrist.h"
#include "jank-chess/engine/include/Attack.h"

#include <iostream>

namespace BoardWrapper {

    Napi::Number NativeConstructor(const Napi::CallbackInfo& info);
    Napi::Value NativeGetMoves(const Napi::CallbackInfo& info);
    Napi::Boolean NativeMakeMove(const Napi::CallbackInfo& info);
    Napi::Boolean NativeUndoMove(const Napi::CallbackInfo& info);
    Napi::String NativeGetTurn(const Napi::CallbackInfo& info);
    Napi::Number NativeGetMaterial(const Napi::CallbackInfo& info);
    Napi::String NativeGetFen(const Napi::CallbackInfo& info);
    Napi::Value NativeGetPawns(const Napi::CallbackInfo& info);
    Napi::Value NativeGetKnights(const Napi::CallbackInfo& info);
    Napi::Value NativeGetBishops(const Napi::CallbackInfo& info);
    Napi::Value NativeGetRooks(const Napi::CallbackInfo& info);
    Napi::Value NativeGetQueens(const Napi::CallbackInfo& info);
    Napi::Value NativeGetKings(const Napi::CallbackInfo& info);
    
    Napi::Object Init(Napi::Env env, Napi::Object exports);

    std::vector<Move> move_history;

}