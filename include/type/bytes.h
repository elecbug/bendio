#pragma once
#include <string>
#include <cstring>
#include <memory>

namespace type {

    class bytes {
    public:
        bytes();
        bytes(const char* data, size_t len);
        bytes(const std::string& str);

        bytes(const bytes& other);
        bytes& operator=(const bytes& other);

        bytes(bytes&& other) noexcept;
        bytes& operator=(bytes&& other) noexcept;

        ~bytes();

        bytes clone() const;

        const char* data() const;
        size_t size() const;

        std::string to_string() const;

    private:
        char* _data;
        size_t _size;

        void copy_from(const char* src, size_t len);
        void cleanup();
    };

}
