const jankchess = require('./build/Release/jankchess.node')

class Board
{
    constructor(fen=null)
    {
        if (fen)
            this._native_pointer = jankchess["BoardWrapper::NativeConstructor"](fen)
        else
            this._native_pointer = jankchess["BoardWrapper::NativeConstructor"]()

        this.move_history = []
        
    }

    get_moves()
    {
        return jankchess["BoardWrapper::NativeGetMoves"](this._native_pointer)
    }

    move(move)
    {

        let legal_moves = this.get_moves()

        if (move)
            this.move_history.push(move)

        return jankchess["BoardWrapper::NativeMakeMove"](this._native_pointer, move)
    }

    undo_move(move)
    {
        return jankchess["BoardWrapper::NativeUnmakeMove"](this._native_pointer, move)
    }

    undo()
    {
        if (this.move_history.length > 0)
        {
            this.undo_move(this.move_history.pop())
                    
        }
    }

    turn()
    {
        return jankchess["BoardWrapper::NativeGetTurn"](this._native_pointer)
    }

    material(color)
    {
        return jankchess["BoardWrapper::NativeGetMaterial"](this._native_pointer, color)
    }

    static from_fen(fen)
    {
        return new Board(fen)
    }
}


module.exports = {
    Board: Board
}