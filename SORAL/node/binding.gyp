{
  "targets": [
    {
      "target_name": "soral",
      "include_dirs": [ '../C++/', '<!@(ls -ld -1 ~/.node-gyp/*/include/)'],
      "libraries": [ "../../C++/libSoral.a" ],
      "sources": [ "soral_wrap.cpp" ]
    }
  ]
}
