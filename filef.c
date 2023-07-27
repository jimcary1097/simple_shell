#include "shell.h"
char *_strncat(char *dest, char *src, int n)
{
  int i, j;
  char *s = dest;

  for (i = 0; dest[i] != '\0'; i++) {
  }
  for (j = 0; src[j] != '\0' && j < n; j++) {
    dest[i] = src[j];
    i++;
  }
  if (j < n)
    dest[i] = '\0';
  return s;
}

char *_strchr(char *s, char c)
{
  for (; *s != '\0'; s++) {
    if (*s == c)
      return s;
  }

  return NULL;
}

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
  ssize_t r = 0;
  size_t len_p = 0;

  if (!*len) /* if nothing left in the buffer, fill it */
  {
    /*bfree((void **)info->cmd_buf);*/
    free(*buf);
    *buf = NULL;
    for (;;) {
      signal(SIGINT, sigintHandler);
#if USE_GETLINE
      r = getline(buf, &len_p, stdin);
#else
      r = _getline(info, buf, &len_p);
#endif
      if (r > 0) {
        if ((*buf)[r - 1] == '\n') {
          (*buf)[r - 1] = '\0'; /* remove trailing newline */
          r--;
        }
        info->linecount_flag = 1;
        remove_comments(*buf);
        build_history_list(info, *buf, info->histcount++);
        /* if (_strchr(*buf, ';')) is this a command chain? */
        {
          *len = r;
          info->cmd_buf = buf;
          break;
        }
      }
      else if (r == -1) {
        return -1;
      }
    }
  }
  return r;
}


ssize_t get_input(info_t *info)
{
  static char *buf; /* the ';' command chain buffer */
  static size_t i, j, len;
  ssize_t r = 0;
  char **buf_p = &(info->arg), *p;

  _putchar(BUF_FLUSH);
  r = input_buf(info, &buf, &len);
  if (r == -1) /* EOF */
    return -1;
  if (len)	/* we have commands left in the chain buffer */
  {
    j = i; /* init new iterator to current buf position */
    p = buf + i; /* get pointer for return */

    check_chain(info, buf, &j, i, len);
    for (; j < len; j++) {
      if (is_chain(info, buf, &j))
        break;
    }

    i = j + 1; /* increment past nulled ';'' */
    if (i >= len) /* reached end of buffer? */
    {
      i = len = 0; /* reset position and length */
      info->cmd_buf_type = CMD_NORM;
    }

    *buf_p = p; /* pass back pointer to current command position */
    return (_strlen(p)); /* return length of current command */
  }

  *buf_p = buf; /* else not a chain, pass back buffer from _getline() */
  return (r); /* return length of buffer from _getline() */
}
