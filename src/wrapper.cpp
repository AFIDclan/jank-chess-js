#include "wrapper.h"

Napi::Object BoardWrapper::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("BoardWrapper::NativeConstructor", Napi::Function::New(env, BoardWrapper::NativeConstructor));
    exports.Set("BoardWrapper::NativeGetMoves", Napi::Function::New(env, BoardWrapper::NativeGetMoves));

    return exports;
}

Napi::Number BoardWrapper::NativeConstructor(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Attack::init();
    Zobrist::init();
    
    Board* board;

    if (info.Length() > 0 && info[0].IsString() ) {
        std::cout << "Loading FEN: " << info[0].As<Napi::String>().Utf8Value() << "\n";
        board = new Board(info[0].As<Napi::String>().Utf8Value());
    } else {
        board = new Board();
    }

    uintptr_t native_pointer = reinterpret_cast<uintptr_t>(board);

    return Napi::Number::New(env, native_pointer);

}

Napi::Value BoardWrapper::NativeGetMoves(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "BoardWrapper::NativeGetMoves expects a Board pointer as its first argument").ThrowAsJavaScriptException();
    }

    Board* board = reinterpret_cast<Board*>(info[0].As<Napi::Number>().Int64Value());


    std::vector<Move> moves;
    board->generatePsudoLegalMoves();


    for ( Move* mptr2 = board->moveListBegin(); mptr2 < board->moveListEnd(); mptr2++ ) {

        board->make(mptr2);
        if ( !board->leftInCheck() ) {
            moves.push_back(*mptr2);
        }
        board->unmake(mptr2);
    }
    
    // Create a JavaScript array to store the UCI strings
    Napi::Array js_moves = Napi::Array::New(env, moves.size());

    for (int i = 0; i < moves.size(); i++) 
        js_moves[i] = moves[i].toUCI();

    return js_moves;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

    BoardWrapper::Init(env, exports);

    return exports;
}

NODE_API_MODULE(jankchess, InitAll)