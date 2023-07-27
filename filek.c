#include "shell.h"
size_t print_list(const list_t *h)
{
  size_t i = 0;

  for (; h; h = h->next) {
    _puts(convert_number(h->num, 10, 0));
    _putchar(':');
    _putchar(' ');
    _puts(h->str ? h->str : "(nil)");
    _puts("\n");
    i++;
  }
  return (i);
}


list_t *node_starts_with(list_t *node, char *prefix, char c)
{
  for (; node; node = node->next) {
    char *p = starts_with(node->str, prefix);
    if (p && ((c == -1) || (*p == c)))
      return (node);
  }
  return (NULL);
}

ssize_t get_node_index(list_t *head, list_t *node)
{
  size_t i = 0;

  for (; head; head = head->next) {
    if (head == node)
      return (i);
    i++;
  }
  return (-1);
}

int bfree(void **ptr)
{
  if (ptr && *ptr) {
    free(*ptr);
    *ptr = NULL;
    return (1);
  }
  return (0);
}

int is_cmd(info_t *info, char *path)
{
  (void)info;
  if (!path || stat(path, &st))
    return (0);

  if (st.st_mode & S_IFREG)
    return (1);
  return (0);
}
