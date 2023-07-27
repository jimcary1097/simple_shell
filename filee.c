#include "shell.h"
void print_error(info_t *info, char *estr)
{
  _eputs(info->fname);
  _eputs(": ");
  for (int i = 0; i < info->line_count; i++) {
    _eputchar(' ');
  }
  _eputs(info->argv[0]);
  _eputs(": ");
  _eputs(estr);
}

int print_d(int input, int fd)
{
  int (*__putchar)(char) = _putchar;
  int i, count = 0;
  unsigned int _abs_, current;

  if (fd == STDERR_FILENO)
    __putchar = _eputchar;
  if (input < 0) {
    _abs_ = -input;
    __putchar('-');
    count++;
  }
  else
    _abs_ = input;
  current = _abs_;
  for (i = 1000000000; i > 1; i /= 10) {
    if (_abs_ / i) {
      __putchar('0' + current / i);
      count++;
    }
    current %= i;
  }
  __putchar('0' + current);
  count++;

  return count;
}

char *convert_number(long int num, int base, int flags)
{
  static char *array;
  static char buffer[50];
  char sign = 0;
  char *ptr;
  unsigned long n = num;

  if (!(flags & CONVERT_UNSIGNED) && num < 0) {
    n = -num;
    sign = '-';

  }
  array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
  ptr = &buffer[49];
  *ptr = '\0';

  for (; n; n /= base) {
    *--ptr = array[n % base];
  }

  if (sign)
    *--ptr = sign;
  return ptr;
}

void remove_comments(char *buf)
{
  for (int i = 0; buf[i] != '\0'; i++) {
    if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
      buf[i] = '\0';
      break;
    }
  }
}

char *_strncpy(char *dest, char *src, int n)
{
  int i, j;
  char *s = dest;

  for (i = 0; src[i] != '\0' && i < n - 1; i++) {
    dest[i] = src[i];
  }
  if (i < n) {
    j = i;
    for (; j < n; j++) {
      dest[j] = '\0';
    }
  }
  return s;
}
