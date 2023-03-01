// token_buff.cpp
// ~~~~~~~~~~~~~~
// Implements token buffer
#include "token_buff.h"

TokenBuffer::TokenBuffer() : size_(16), length_(0) {
  buffer_ = new char[size_];
  buffer_[0] = '\0';
}

TokenBuffer::~TokenBuffer() { delete[] buffer_; }

void TokenBuffer::append(char c) {
  if (length_ + 1 >= size_) {
    size_ *= 2;
    char *new_buffer = new char[size_];
    std::memcpy(new_buffer, buffer_, length_);
    delete[] buffer_;
    buffer_ = new_buffer;
  }
  buffer_[length_] = c;
  length_++;
  buffer_[length_] = '\0';
}

const char *TokenBuffer::str() const { return buffer_; }

size_t TokenBuffer::length() const { return length_; }
