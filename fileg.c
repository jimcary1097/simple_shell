#include "shell.h"
int _getline(info_t *info, char **ptr, size_t *length)
{
  static char buf[READ_BUF_SIZE];
  static size_t i, len;
  size_t k;
  ssize_t r = 0, s = 0;
  char *p = NULL, *new_p = NULL, *c;

  p = *ptr;
  if (p && length)
    s = *length;
  if (i == len)
    i = len = 0;

  for (;;) {
    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
      return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
      return (p ? free(p), -1 : -1);

    if (s)
      _strncat(new_p, buf + i, k - i);
    else
      _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (c)
      break;
  }

  if (length)
    *length = s;
  *ptr = p;
  return (s);
}

void sigintHandler(__attribute__((unused))int sig_num)
{
  _puts("\n");
  _puts("$ ");
  _putchar(BUF_FLUSH);
}

char **get_environ(info_t *info)
{
  if (!info->environ || info->env_changed) {
    info->environ = list_to_strings(info->env);
    info->env_changed = 0;
  }

  return (info->environ);
}


int _unsetenv(info_t *info, char *var)
{
  list_t *node = info->env;
  size_t i = 0;
  char *p;

  if (!node || !var)
    return (0);

  for (; node; node = node->next) {
    p = starts_with(node->str, var);
    if (p && *p == '=') {
      info->env_changed = delete_node_at_index(&(info->env), i);
      i = 0;
      node = info->env;
      continue;
    }
    i++;
  }
  return (info->env_changed);
}

int _setenv(info_t *info, char *var, char *value)
{
  char *buf = NULL;
  list_t *node;
  char *p;

  if (!var || !value)
    return (0);

  buf = malloc(_strlen(var) + _strlen(value) + 2);
  if (!buf)
    return (1);
  _strcpy(buf, var);
  _strcat(buf, "=");
  _strcat(buf, value);
  node = info->env;
  for (; node; node = node->next) {
    p = starts_with(node->str, var);
    if (p && *p == '=') {
      free(node->str);
      node->str = buf;
      info->env_changed = 1;
      return (0);
    }
  }
  add_node_end(&(info->env), buf, 0);
  free(buf);
  info->env_changed = 1;
  return (0);
}
