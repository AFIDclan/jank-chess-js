const jankchess = require('./build/Release/jankchess.node')

class Board
{
    constructor(fen=null)
    {
        if (fen)
            this._native_pointer = jankchess["BoardWrapper::NativeConstructor"](fen)
        else
            this._native_pointer = jankchess["BoardWrapper::NativeConstructor"]()
    }

    get_moves()
    {
        return jankchess["BoardWrapper::NativeGetMoves"](this._native_pointer)
    }
}


let board = new Board()

let start = Date.now()

// for (let i = 0; i < 1000000; i++)
// {
//     let moves = board.get_moves()
// }
    
let moves = board.get_moves()
console.log(moves)

let end = Date.now()

console.log((end - start) / 1000000, "ms per move")

