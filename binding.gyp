{
  "targets": [
    {
      "target_name": "hamlib",
      "sources": [ 
          "src/hamlib.cpp"
          ],
      "include_dirs": [
        "include", "/usr/local/include/", "node_modules/node-addon-api/"
        ],
      "libraries": [
        "-L/usr/local/lib", "-lhamlib"
    ],
    'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    },
  ]
}