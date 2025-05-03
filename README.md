# BendIO

**BendIO** is a lightweight C++ backend utility library providing asynchronous threading and TCP networking primitives.  
It is designed for modularity, portability, and ease of integration into other C++ projects, including game engines or server backends.

---

## 📦 Features

- Modern async thread abstraction (`async::Thread`, `async::Task<T>`)
- Lightweight TCP networking interface (`net::TcpClient`, `net::TcpServer`)
- Utility types for byte buffers and IP endpoint management (`net::bytes`, `net::IPEndPoint`)
- Clean public interface via modular headers (`<bendio/net.h>`, `<bendio/async.h>`)

---

## 🛠 Installation

```bash
sudo ./install.sh
````

This will install:

* Static library: `/usr/local/lib/libbendio.a`
* Headers: `/usr/local/include/bendio`
* CMake config: `/usr/local/lib/cmake/bendio/`

To use it in your project:

```cmake
find_package(bendio REQUIRED)

target_link_libraries(your_target PRIVATE bendio::bendio)
```

---

## 📚 Example Usage

```cpp
#include <bendio/net.h>
#include <bendio/async.h>
#include <iostream>

int main() {
    net::IPEndPoint ep("127.0.0.1:8000");
    std::cout << ep.to_string() << std::endl;

    async::Thread::lock(/* mutex */, []() {
        // your thread-safe logic
    });

    return 0;
}
```

---

## 🔧 Build Instructions

```bash
mkdir build && cd build
cmake ..
make
```

Run the test binary:

```bash
./test.sh
```

---

## 📝 License

MIT License.
