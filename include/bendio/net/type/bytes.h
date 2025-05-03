#pragma once

#include <cstring>
#include <memory>
#include <string>

namespace net {

    // A simple dynamic byte buffer class for managing raw data
    class bytes {
    public:
        // Default constructor (empty buffer)
        bytes();

        // Construct from raw char pointer and length (makes deep copy)
        bytes(const char* data, size_t len);

        // Construct from std::string (makes deep copy)
        bytes(const std::string& str);

        // Copy constructor
        bytes(const bytes& other);

        // Move constructor
        bytes(bytes&& other) noexcept;

        // Destructor: releases allocated memory
        ~bytes();

        // Clone this byte buffer (deep copy)
        bytes clone() const;

        // Get raw pointer to internal data (const)
        const char* data() const;

        // Get size of buffer
        size_t size() const;

        // Convert buffer contents to std::string
        std::string to_string() const;

        // Copy assignment
        bytes& operator=(const bytes& other);

        // Move assignment
        bytes& operator=(bytes&& other) noexcept;

    private:
        char* _data;     // Raw buffer pointer
        size_t _size;    // Length of the buffer

        // Internal helper to copy data
        void copy_from(const char* src, size_t len);

        // Internal helper to deallocate memory
        void cleanup();
    };

}
