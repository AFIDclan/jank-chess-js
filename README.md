
# Jank Chess JS

A very preformant native c++ chess engine wrapped in nodejs for fun and profit!


## Tests

![example workflow](https://github.com/AFIDclan/jank-chess-js/actions/workflows/mocha-tests.yml/badge.svg)

## Installation

Install jank-chess with npm

```bash
npm install jank-chess
```

## Usage/Examples

```javascript
const { Board } = require("jank-chess");

let board = new Board();

board.move("d2d4");

let moves = board.get_moves(); // Array of all available moves
let turn = board.turn(); // w or b
let pawns = board.get_pawns("w"); // Array of all pawn locations for white


```


## Acknowledgements
- C++ engine written by Jonathan Van Schenck, and can be found [here](https://github.com/jonathanvanschenck/jank-chess). Check it out!
- Many thanks to the [Chess Programming Wiki](https://www.chessprogramming.org), upon which most of this project is based.


## Authors

- [Jonathan Van Schenck](https://github.com/jonathanvanschenck)
- [Sean Sullivan](https://github.com/AFIDclan)

