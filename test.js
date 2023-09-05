const { expect } = require("chai");
const { Board } = require("./");


describe("Chess Board Operations", ()=>{
  let board = new Board();

  beforeEach(()=>{
    board = new Board();
  });

  it("should get available moves", ()=>{
    const moves = board.get_moves();
    expect(moves.length).to.equal(20);
  });

  it("should make a move and get FEN", ()=>{
    board.move("d2d4");
    const fen = board.fen();
    expect(fen).to.equal("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1");
  });


  it("should undo the last move", ()=>{
    board.move("d2d4");
    board.undo();
    const fen = board.fen();

    expect(fen).to.equal("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  });

  it("should determine the current turn", ()=>{
    const turn = board.turn();
    expect(turn).to.equal("w");
  });

  it("should calculate the material value for black", ()=>{
    const m = board.material("b");
    expect(m).to.equal(39);
  });

  it("should be performant ( < 0.01ms per move query)", ()=>{
    const start = Date.now();
    
    for (let i = 0; i < 10000; i++)
    {
      board.get_moves();
    }

    const end = Date.now();
    const avg = (end - start) / 10000;

    expect(avg).to.be.below(0.01);
  });
});

describe("Loading from FEN", ()=>{
  let board;

  beforeEach(()=>{
    board = new Board("8/8/8/8/8/2K5/8/Q2Bk3 w - - 11 11");
  });

  it("should load from a FEN", ()=>{
    const fen = board.fen();

    expect(fen).to.equal("8/8/8/8/8/2K5/8/Q2Bk3 w - - 11 11");
  });

  it("should get available moves on the custom board", ()=>{
    const moves = board.get_moves();
    expect(moves.length).to.equal(24);
  });

});

describe("Piece Position Querying", ()=>{
  let board;

  beforeEach(()=>{
    board = new Board();
  });
  
  it("should find the positions of white kings", ()=>{
    const k = board.get_kings("w");
    expect(k[0]).to.equal(5);
  });

  it("should find the positions of black kings", ()=>{
    const k = board.get_kings("b");
    expect(k[0]).to.equal(60);
  });

  it("should find the positions of white queens", ()=>{
    const q = board.get_queens("w");
    expect(q[0]).to.equal(3);
  });

  it("should find the positions of black queens", ()=>{
    const q = board.get_queens("b");
    expect(q[0]).to.equal(59);
  });

  it("should find the positions of white rooks", ()=>{
    const r = board.get_rooks("w");
    expect(r[0]).to.equal(0);
    expect(r[1]).to.equal(7);
  });

  it("should find the positions of black rooks", ()=>{
    const r = board.get_rooks("b");
    expect(r[0]).to.equal(56);
    expect(r[1]).to.equal(63);
  });

  it("should find the positions of white bishops", ()=>{
    const b = board.get_bishops("w");
    expect(b[0]).to.equal(2);
    expect(b[1]).to.equal(5);
  });

  it("should find the positions of black bishops", ()=>{
    const b = board.get_bishops("b");
    expect(b[0]).to.equal(58);
    expect(b[1]).to.equal(61);
  });

  it("should find the positions of white knights", ()=>{
    const n = board.get_knights("w");
    expect(n[0]).to.equal(1);
    expect(n[1]).to.equal(6);
  });

  it("should find the positions of black knights", ()=>{
    const n = board.get_knights("b");
    expect(n[0]).to.equal(57);
    expect(n[1]).to.equal(62);
  });

  it("should find the positions of white pawns", ()=>{
    const p = board.get_pawns("w");
    expect(p[0]).to.equal(8);
    expect(p[1]).to.equal(9);
    expect(p[2]).to.equal(10);
    expect(p[3]).to.equal(11);
    expect(p[4]).to.equal(12);
    expect(p[5]).to.equal(13);
    expect(p[6]).to.equal(14);
    expect(p[7]).to.equal(15);
  });

  it("should find the positions of black pawns", ()=>{
    const p = board.get_pawns("b");
    expect(p[0]).to.equal(48);
    expect(p[1]).to.equal(49);
    expect(p[2]).to.equal(50);
    expect(p[3]).to.equal(51);
    expect(p[4]).to.equal(52);
    expect(p[5]).to.equal(53);
    expect(p[6]).to.equal(54);
    expect(p[7]).to.equal(55);
  });

});
