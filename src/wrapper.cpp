#include "wrapper.h"

const std::string piece[8] = {"p", "n", "b", "r", "q", "k"};


Board* getBoard(const Napi::CallbackInfo& info) {

    if (info.Length() < 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(info.Env(), "BoardWrapper::NativeGetMoves expects a Board pointer as its first argument").ThrowAsJavaScriptException();
    }

    Board* board = reinterpret_cast<Board*>(info[0].As<Napi::Number>().Int64Value());

    return board;
}

Napi::Object BoardWrapper::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("BoardWrapper::NativeConstructor", Napi::Function::New(env, BoardWrapper::NativeConstructor));
    exports.Set("BoardWrapper::NativeGetMoves", Napi::Function::New(env, BoardWrapper::NativeGetMoves));
    exports.Set("BoardWrapper::NativeMakeMove", Napi::Function::New(env, BoardWrapper::NativeMakeMove));

    return exports;
}

Napi::Number BoardWrapper::NativeConstructor(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Attack::init();
    Zobrist::init();
    
    Board* board;

    if (info.Length() > 0 && info[0].IsString() ) {
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

    Board* board = getBoard(info);

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

Napi::Boolean BoardWrapper::NativeMakeMove(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string move = info[1].As<Napi::String>().Utf8Value();

    if (move.length() < 4)
        Napi::TypeError::New(env, "BoardWrapper::NativeMakeMove move must be at least 4 chars long").ThrowAsJavaScriptException();

    int from_file = move[0] - 'a';
    int from_rank = move[1] - '1';
    int from = from_file + from_rank * 8;

    int to_file = move[2] - 'a';
    int to_rank = move[3] - '1';
    int to = to_file + to_rank * 8;

    if (from < 0 || from > 63 || to < 0 || to > 63)
        Napi::TypeError::New(env, "BoardWrapper::NativeMakeMove invalid move").ThrowAsJavaScriptException();

    Move m;
    
    if (move.length() == 5)
    {
        Piece promotion = static_cast<Piece>(piece->find(move.substr(4,1)));
        m = Move(from, to, promotion);
    } else {
        m = Move(from, to);
    }
   
    try {
        board->make(&m);
    } catch (std::exception& e) {
        Napi::TypeError::New(env, "Invalid Move: " + move).ThrowAsJavaScriptException();
    }
    

    return Napi::Boolean::New(env, true);
}


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

    BoardWrapper::Init(env, exports);

    return exports;
}

NODE_API_MODULE(jankchess, InitAll)