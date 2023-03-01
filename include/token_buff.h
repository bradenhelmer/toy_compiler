// token_buff.h
// ~~~~~~~~~~~~
// Defines the token buffer
#ifndef TOKEN_BUFF_H
#define TOKEN_BUFF_H
#include <cstring>

class TokenBuffer {
public:
  TokenBuffer();
  ~TokenBuffer();

  void append(char c);
  const char *str() const;
  size_t length() const;

private:
  char *buffer_;
  size_t size_;
  size_t length_;
};

#endif
