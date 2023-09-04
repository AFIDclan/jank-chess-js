const { expect } = require("chai");
const { Board } = require("./");


// TODO: These test were outlined but never completed. Need to actually check return values


describe("Chess Board Operations", function () {
  let board = new Board();

  beforeEach(function () {
    board = new Board();
  });

  it("should get available moves", function () {
    const moves = board.get_moves();
    expect(moves).to.be.an("array");
  });

  it("should make a move and get FEN", function () {
    board.move("d2d4");
    const fen = board.fen();
    expect(fen).to.be.a("string");
  });

  it("should make another move and get FEN", function () {
    board.move("d2d4");
    board.move("e7e5");
    const fen = board.fen();
    expect(fen).to.be.a("string");
  });

  it("should get available moves after 2 moves", function () {
    board.move("d2d4");
    board.move("e7e5");
    const moves = board.get_moves();
    expect(moves).to.be.an("array");
  });

  it("should undo the last move", function () {
    board.move("d2d4");
    board.undo();
    const fen = board.fen();
    expect(fen).to.be.a("string");
  });

  it("should determine the current turn", function () {
    const turn = board.turn();
    expect(turn).to.be.a("string");
  });

  it("should calculate the material value for black", function () {
    const materialBlack = board.material("b");
    expect(materialBlack).to.be.a("number");
  });

  it("should measure performance", function () {
    const startTime = Date.now();
    // ... (code for measuring performance)
    const endTime = Date.now();
    const averageTimePerMove = (endTime - startTime) / 1000000;
    expect(averageTimePerMove).to.be.a("number");
  });
});

describe("Custom Chess Board", function () {
  let board;

  beforeEach(function () {
    board = new Board("8/8/8/8/8/2K5/8/Q2Bk3 w - - 11 11");
  });

  it("should have a custom FEN", function () {
    const fen = board.fen();
    expect(fen).to.be.a("string");
  });

  it("should get available moves on the custom board", function () {
    const moves = board.get_moves();
    expect(moves).to.be.an("array");
  });

  it("should find the positions of white kings and black knights", function () {
    const whiteKings = board.get_kings("w");
    const blackKnights = board.get_knights("b");
    expect(whiteKings).to.be.an("array");
    expect(blackKnights).to.be.an("array");
  });
});
