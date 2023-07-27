#include "shell.h"
void clear_info(info_t *info)
{
  info->arg = NULL;
  info->argv = NULL;
  info->path = NULL;
  info->argc = 0;
}


void set_info(info_t *info, char **av)
{
  int i = 0;

  info->fname = av[0];
  if (info->arg) {
    info->argv = strtow(info->arg, " \t");
    if (!info->argv) {
      info->argv = malloc(sizeof(char *) * 2);
      if (info->argv) {
        info->argv[0] = _strdup(info->arg);
        info->argv[1] = NULL;
      }
    }
    for (i = 0; info->argv && info->argv[i]; i++)
      ;
    info->argc = i;

    replace_alias(info);
    replace_vars(info);
  }
}

void free_info(info_t *info, int all)
{
  if (all) {
    if (!info->cmd_buf)
      free(info->arg);
    if (info->env)
      free_list(&(info->env));
    if (info->history)
      free_list(&(info->history));
    if (info->alias)
      free_list(&(info->alias));
    ffree(info->environ);
    info->environ = NULL;
    bfree((void **)info->cmd_buf);
    if (info->readfd > 2)
      close(info->readfd);
    _putchar(BUF_FLUSH);
  }
  ffree(info->argv);
  info->argv = NULL;
  info->path = NULL;
}

char *get_history_file(info_t *info)
{
  char *buf, *dir;

  dir = _getenv(info, "HOME=");
  if (!dir)
    return (NULL);
  buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
  if (!buf)
    return (NULL);
  buf[0] = 0;
  _strcpy(buf, dir);
  _strcat(buf, "/");
  _strcat(buf, HIST_FILE);
  return (buf);
}


int write_history(info_t *info)
{
  ssize_t fd;
  char *filename = get_history_file(info);
  list_t *node = NULL;

  if (!filename)
    return (-1);

  for (fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644), node = info->history; node; node = node->next) {
    _putsfd(node->str, fd);
    _putfd('\n', fd);
  }
  _putfd(BUF_FLUSH, fd);
  close(fd);
  free(filename);
  return (1);
}
