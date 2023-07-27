#include "shell.h"
char *_strdup(const char *str)
{
  int length = 0;
  char *ret;

  if (str == NULL)
    return (NULL);
  for (; *str; str++)
    length++;
  ret = malloc(sizeof(char) * (length + 1));
  if (!ret)
    return (NULL);
  for (length++; length--;)
    ret[length] = *--str;
  return (ret);
}

void _puts(char *str)
{
  int i = 0;

  if (!str)
    return;
  for (; str[i] != '\0'; i++)
    _putchar(str[i]);
}

int _putchar(char c)
{
  static int i;
  static char buf[WRITE_BUF_SIZE];

  if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
    write(1, buf, i);
    i = 0;
  }
  if (c != BUF_FLUSH)
    buf[i++] = c;
  return (1);
}

char **strtow(char *str, char *d)
{
  int i, j, k, m, numwords = 0;
  char **s;

  if (str == NULL || str[0] == 0)
    return (NULL);
  if (!d)
    d = " ";
  for (i = 0; str[i] != '\0'; i++)
    if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
      numwords++;

  if (numwords == 0)
    return (NULL);
  s = malloc((1 + numwords) * sizeof(char *));
  if (!s)
    return (NULL);
  for (i = 0, j = 0; j < numwords; j++) {
    for (; is_delim(str[i], d); i++);
    k = 0;
    for (; !is_delim(str[i + k], d) && str[i + k]; k++);
    s[j] = malloc((k + 1) * sizeof(char));
    if (!s[j]) {
      for (k = 0; k < j; k++)
        free(s[k]);
      free(s);
      return (NULL);
    }
    for (m = 0; m < k; m++)
      s[j][m] = str[i++];
    s[j][m] = 0;
  }
  s[j] = NULL;
  return (s);
}
