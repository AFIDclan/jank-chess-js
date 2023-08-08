{
    "targets": [{
        "target_name": "testaddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/wrapper.cpp",
            "src/jank-chess/engine/src/Attack.cpp",
            "src/jank-chess/engine/src/Bboard.cpp",
            "src/jank-chess/engine/src/Board.cpp",
            "src/jank-chess/engine/src/FindMagic.cpp",
            "src/jank-chess/engine/src/Game.cpp",
            "src/jank-chess/engine/src/Magic.cpp",
            "src/jank-chess/engine/src/Move.cpp",
            "src/jank-chess/engine/src/Transposition.cpp",
            "src/jank-chess/engine/src/Zobrist.cpp",
            
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "src/jank-chess/engine/include"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}