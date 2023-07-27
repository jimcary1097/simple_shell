#include "shell.h"
char *dup_chars(char *pathstr, int start, int stop)
{
  static char buf[1024];
  int i, k;

  for (i = start, k = 0; i < stop; i++) {
    if (pathstr[i] != ':')
      buf[k++] = pathstr[i];
  }
  buf[k] = 0;
  return (buf);
}


char *find_path(info_t *info, char *pathstr, char *cmd)
{
  int i, curr_pos = 0;
  char *path;

  for (i = 0; pathstr[i]; i++) {
    if (!pathstr[i] || pathstr[i] == ':') {
      path = dup_chars(pathstr, curr_pos, i);
      if (!path[0])
        _strcat(path, cmd);
      else {
        _strcat(path, "/");
        _strcat(path, cmd);
      }
      if (is_cmd(info, path))
        return (path);
      if (!pathstr[i])
        break;
      curr_pos = i;
    }
  }
  return (NULL);
}

void _memset(char *s, char b, unsigned int n)
{
  for (unsigned int i = 0; i < n; i++)
    s[i] = b;
  return (s);
}

void ffree(char **pp)
{
  char **a = pp;

  if (!pp)
    return;
  for (; *pp; pp++)
    free(*pp++);
  free(a);
}


void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
  char *p;

  if (!ptr)
    return (malloc(new_size));
  if (!new_size)
    return (free(ptr), NULL);
  if (new_size == old_size)
    return (ptr);

  p = malloc(new_size);
  if (!p)
    return (NULL);

  old_size = old_size < new_size ? old_size : new_size;
  for (unsigned int i = 0; i < old_size; i++)
    p[i] = ((char *)ptr)[i];
  free(ptr);
  return (p);
}
