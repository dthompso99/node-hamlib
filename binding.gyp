{
  "targets": [
    {
      "target_name": "hamlib",
      "sources": [ 
          "src/hamlib.cpp",
          "src/decoder.cpp",
          "src/addon.cpp"
          ],
      "include_dirs": [
        "include", "/usr/local/include/", "<!@(node -p \"require('node-addon-api').include\")"
        ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ]
      "libraries": [
        "-L/usr/local/lib", "-lhamlib", "-lportaudio", "-lasound", "-ljack"
    ],
    'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    },
  ]
}