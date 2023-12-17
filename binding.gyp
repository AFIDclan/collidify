{
    "targets": [{
        "target_name": "collidify",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/wrappers/wrapper.cpp",
            "src/wrappers/Vector2Wrapper.cpp",
            "src/wrappers/CollisionWrapper.cpp",
            "src/wrappers/PolygonWrapper.cpp",
            "src/Vector2.cpp",
            "src/Polygon.cpp",
            "src/RotationMatrix.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}