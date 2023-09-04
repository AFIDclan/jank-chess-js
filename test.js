const { Board } = require('./')

let board = new Board()

let start = Date.now()

// for (let i = 0; i < 1000000; i++)
// {
//     let moves = board.get_moves()
// }
    
console.log("Get Moves")
let moves = board.get_moves()
console.log(moves)

console.log("Move")
board.move("d2d4")

let fen = board.fen()

console.log(fen)

console.log("Move")
board.move("e7e5")

fen = board.fen()

console.log(fen)

console.log("Get Moves")
moves = board.get_moves()

console.log(board.fen())

console.log("UNDO")
board.undo()
console.log(board.fen())

console.log("UNDO")
board.undo()
console.log(board.fen())


console.log(board.fen())

let turn = board.turn()
console.log("Turn:", turn)

let material_black = board.material("b")

console.log("Material Black:", material_black)

let end = Date.now()

console.log((end - start) / 1000000, "ms per move")

let board2 = new Board("8/8/8/8/8/2K5/8/Q2Bk3 w - - 11 11")

console.log(board2.fen())

console.log(board2.get_moves())

console.log(board.get_kings("w"))

console.log(board.get_knights("b"))
