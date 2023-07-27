#include "shell.h"

void _eputs(char *str)
{
  for (int i = 0; str[i]; i++) {
    _eputchar(str[i]);
  }
}

int _eputchar(char c)
{
  static int i = 0;
  static char buf[WRITE_BUF_SIZE];

  if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
    write(2, buf, i);
    i = 0;
  }
  if (c != BUF_FLUSH) {
    buf[i++] = c;
  }
  return 1;
}

int _putfd(char c, int fd)
{
  static int i = 0;
  static char buf[WRITE_BUF_SIZE];

  if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
    write(fd, buf, i);
    i = 0;
  }
  if (c != BUF_FLUSH) {
    buf[i++] = c;
  }
  return 1;
}

int _putsfd(char *str, int fd)
{
  int i = 0;

  if (!str)
    return 0;
  for (; *str; str++) {
    i += _putfd(*str, fd);
  }
  return i;
}

int _erratoi(char *s)
{
  unsigned long int result = 0;

  if (*s == '+')
    s++;
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] >= '0' && s[i] <= '9') {
      result *= 10;
      result += (s[i] - '0');
      if (result > INT_MAX)
        return -1;
    }
    else
      return -1;
  }
  return result;
}
