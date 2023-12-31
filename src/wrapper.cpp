#include "wrapper.h"

const std::string piece[8] = {"p", "n", "b", "r", "q", "k"};

Napi::Array BBoard2Array(Napi::Env env, BBOARD b) {
    
    std::vector<int> peice_indexes;

    int i = 0;

    while ( b ) 
        peice_indexes.push_back(BBoard::LS1Idx(BBoard::popLS1B(&b)));

    
    Napi::Array arr = Napi::Array::New(env, peice_indexes.size());

    for (int i = 0; i < peice_indexes.size(); i++) 
        arr[i] = Napi::Number::New(env, peice_indexes[i]);

    return arr;
}

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
    exports.Set("BoardWrapper::NativeUndoMove", Napi::Function::New(env, BoardWrapper::NativeUndoMove));
    exports.Set("BoardWrapper::NativeGetTurn", Napi::Function::New(env, BoardWrapper::NativeGetTurn));
    exports.Set("BoardWrapper::NativeGetMaterial", Napi::Function::New(env, BoardWrapper::NativeGetMaterial));
    exports.Set("BoardWrapper::NativeGetFen", Napi::Function::New(env, BoardWrapper::NativeGetFen));

    exports.Set("BoardWrapper::NativeGetPawns", Napi::Function::New(env, BoardWrapper::NativeGetPawns));
    exports.Set("BoardWrapper::NativeGetKnights", Napi::Function::New(env, BoardWrapper::NativeGetKnights));
    exports.Set("BoardWrapper::NativeGetBishops", Napi::Function::New(env, BoardWrapper::NativeGetBishops));
    exports.Set("BoardWrapper::NativeGetRooks", Napi::Function::New(env, BoardWrapper::NativeGetRooks));
    exports.Set("BoardWrapper::NativeGetQueens", Napi::Function::New(env, BoardWrapper::NativeGetQueens));
    exports.Set("BoardWrapper::NativeGetKings", Napi::Function::New(env, BoardWrapper::NativeGetKings));

    return exports;
}


Napi::Value BoardWrapper::NativeGetPawns(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string color = info[1].As<Napi::String>().Utf8Value();

    Color c = color == "w" ? Color::white : Color::black;
    

    BBOARD b = board->getPawns(c);

    return BBoard2Array(env, b);
}

Napi::Value BoardWrapper::NativeGetKnights(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string color = info[1].As<Napi::String>().Utf8Value();

    Color c = color == "w" ? Color::white : Color::black;
    

    BBOARD b = board->getKnights(c);

    return BBoard2Array(env, b);
}

Napi::Value BoardWrapper::NativeGetBishops(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string color = info[1].As<Napi::String>().Utf8Value();

    Color c = color == "w" ? Color::white : Color::black;
    

    BBOARD b = board->getBishops(c);

    return BBoard2Array(env, b);
}

Napi::Value BoardWrapper::NativeGetRooks(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string color = info[1].As<Napi::String>().Utf8Value();

    Color c = color == "w" ? Color::white : Color::black;
    

    BBOARD b = board->getRooks(c);

    return BBoard2Array(env, b);
}

Napi::Value BoardWrapper::NativeGetQueens(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string color = info[1].As<Napi::String>().Utf8Value();

    Color c = color == "w" ? Color::white : Color::black;
    

    BBOARD b = board->getQueens(c);

    return BBoard2Array(env, b);
}

Napi::Value BoardWrapper::NativeGetKings(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string color = info[1].As<Napi::String>().Utf8Value();

    Color c = color == "w" ? Color::white : Color::black;
    

    BBOARD b = board->getKings(c);

    return BBoard2Array(env, b);
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

Napi::Number BoardWrapper::NativeGetMaterial(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string color = info[1].As<Napi::String>().Utf8Value();

    Color turn = color == "w" ? Color::white : Color::black;

    int material = board->material(turn);

    return Napi::Number::New(env, material);
}

Napi::String BoardWrapper::NativeGetFen(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string fen = board->fen();

    return Napi::String::New(env, fen);
}

Napi::String BoardWrapper::NativeGetTurn(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    Color turn = board->getSideToMove();
    return Napi::String::New(env, turn == Color::white ? "w" : "b");
}

Napi::Boolean BoardWrapper::NativeUndoMove(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    Move m = BoardWrapper::move_history.back();
    BoardWrapper::move_history.pop_back();

    board->unmake(&m);

    return Napi::Boolean::New(env, true);
}

Napi::Boolean BoardWrapper::NativeMakeMove(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Board* board = getBoard(info);

    std::string move = info[1].As<Napi::String>().Utf8Value();

    Move m = board->parseUCIMove(move);

    try {
        board->make(&m);
        BoardWrapper::move_history.push_back(m);

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