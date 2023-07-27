#include "shell.h"
int read_history(info_t *info)
{
  int i, last = 0, linecount = 0;
  ssize_t fd, rdlen, fsize = 0;
  struct stat st;
  char *buf = NULL, *filename = get_history_file(info);

  if (!filename)
    return (0);

  fd = open(filename, O_RDONLY);
  free(filename);
  if (fd == -1)
    return (0);
  if (!fstat(fd, &st))
    fsize = st.st_size;
  if (fsize < 2)
    return (0);
  buf = malloc(sizeof(char) * (fsize + 1));
  if (!buf)
    return (0);
  rdlen = read(fd, buf, fsize);
  buf[fsize] = 0;
  if (rdlen <= 0)
    return (free(buf), 0);
  close(fd);
  for (i = 0; i < fsize; i++) {
    if (buf[i] == '\n') {
      buf[i] = 0;
      build_history_list(info, buf + last, linecount++);
      last = i + 1;
    }
  }
  if (last != i)
    build_history_list(info, buf + last, linecount++);
  free(buf);
  info->histcount = linecount;
  while (info->histcount-- >= HIST_MAX)
    delete_node_at_index(&(info->history), 0);
  renumber_history(info);
  return (info->histcount);
}


int build_history_list(info_t *info, char *buf, int linecount)
{
  list_t *node = NULL;

  if (info->history)
    node = info->history;
  for (;;) {
    node = add_node_end(&node, buf, linecount);
    if (!buf[0])
      break;
    buf = buf + _strlen(buf) + 1;
  }

  if (!info->history)
    info->history = node;
  return (0);
}


int renumber_history(info_t *info)
{
  list_t *node = info->history;
  int i = 0;

  for (; node; node = node->next) {
    node->num = i++;
  }
  return (info->histcount = i);
}
