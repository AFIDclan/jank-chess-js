const { Board } = require('./')

let board = new Board()

let start = Date.now()

// for (let i = 0; i < 1000000; i++)
// {
//     let moves = board.get_moves()
// }
    
let moves = board.get_moves()

let move = moves[0]
console.log("Making:", move)
board.move(move)

moves = board.get_moves()

console.log(moves)

let turn = board.turn()
console.log("Turn:", turn)

let material_black = board.material("b")

console.log("Material Black:", material_black)

let end = Date.now()

console.log((end - start) / 1000000, "ms per move")

