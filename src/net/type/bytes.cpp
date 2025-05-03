#include "net/type/bytes.h"

namespace net {

    bytes::bytes() : _data(nullptr), _size(0) {}

    bytes::bytes(const char* data, size_t len) {
        copy_from(data, len);
    }

    bytes::bytes(const std::string& str) {
        copy_from(str.data(), str.size());
    }

    bytes::bytes(const bytes& other) {
        copy_from(other._data, other._size);
    }

    bytes& bytes::operator=(const bytes& other) {
        if (this != &other) {
            cleanup();
            copy_from(other._data, other._size);
        }

        return *this;
    }

    bytes::bytes(bytes&& other) noexcept : _data(other._data), _size(other._size) {
        other._data = nullptr;
        other._size = 0;
    }

    bytes& bytes::operator=(bytes&& other) noexcept {
        if (this != &other) {
            cleanup();

            _data = other._data;
            _size = other._size;
            
            other._data = nullptr;
            other._size = 0;
        }
        return *this;
    }

    bytes::~bytes() {
        cleanup();
    }

    void bytes::copy_from(const char* src, size_t len) {
        _size = len;
        _data = new char[_size];

        std::memcpy(_data, src, _size);
    }

    void bytes::cleanup() {
        delete[] _data;
        
        _data = nullptr;
        _size = 0;
    }

    const char* bytes::data() const {
        return _data;
    }

    size_t bytes::size() const {
        return _size;
    }

    bytes bytes::clone() const {
        return bytes(_data, _size);
    }

    std::string bytes::to_string() const {
        return std::string(_data, _size);
    }

}
