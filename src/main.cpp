#include <iostream>

#ifdef HAVE_NGHTTP2
#include <nghttp2/nghttp2.h>
#endif

int main() {
    std::cout << "5g C++ workspace: hello\n";
#ifdef HAVE_NGHTTP2
    std::cout << "nghttp2 library detected. Version: " << nghttp2_version(0) << "\n";
#else
    std::cout << "nghttp2 not detected at compile time. Build it via [nghttp2/Makefile](/nghttp2/Makefile)\n";
#endif
    return 0;
}
