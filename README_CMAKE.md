# 5g C++ CMake example

This is a minimal C++ project configured with CMake.

Build Instructions:

```sh
mkdir -p build
cd build
cmake ..
make
```

If `nghttp2` is installed and detectable via pkg-config or system paths, the binary will be linked with it and print the version at runtime. Otherwise the binary will still build and print a message that `nghttp2` wasn't detected.

There's an `nghttp2/Makefile` in the repo root that may be used to build nghttp2 locally if needed.
