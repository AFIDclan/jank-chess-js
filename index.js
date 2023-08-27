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

    /**
     * Get all legal moves in UCI format
     * 
     * @returns {Array} Array of moves in UCI format
     */
    get_moves()
    {
        return jankchess["BoardWrapper::NativeGetMoves"](this._native_pointer)
    }

    /**
     * Make a move on the board
     * 
     * @param {String} move UCI move to make
     */
    move(move)
    {

        if (move)
            this.move_history.push(move)

        return jankchess["BoardWrapper::NativeMakeMove"](this._native_pointer, move)
    }

    /**
     * Undo the last move
     */
    undo()
    {
        if (this.move_history.length > 0)
        {
            this.move_history.pop()
            return jankchess["BoardWrapper::NativeUndoMove"](this._native_pointer)        
        }
    }

    /**
     * Get the current turn
     * 
     * @returns {String} "w" or "b"
     */
    turn()
    {
        return jankchess["BoardWrapper::NativeGetTurn"](this._native_pointer)
    }

    /**
     * Get the total material of a color
     * 
     * @param {String} color "w" or "b"
     * @returns {Number} Total material of the color
     */
    material(color)
    {
        return jankchess["BoardWrapper::NativeGetMaterial"](this._native_pointer, color)
    }

    /**
     * Get the fen for the current board state
     * 
     * @returns {String} FEN string
     */
    fen()
    {
        return jankchess["BoardWrapper::NativeGetFen"](this._native_pointer)
    }

    /**
     * Construct a board from a FEN string
     * 
     * @param {String} fen FEN string
     * @returns {Board} Board object
     */
    static from_fen(fen)
    {
        return new Board(fen)
    }
}


module.exports = {
    Board: Board
}