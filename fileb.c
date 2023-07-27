#include "shell.h"
int _myhelp(info_t *info)
{
  _puts("help call works. Function not yet implemented \n");
  return 0;
}

int _myhistory(info_t *info)
{
  print_list(info->history);
  return 0;
}

int unset_alias(info_t *info, char *str)
{
  char *p, c;
  int ret = 0, i = 0;

  for (i = 0; info->alias->str[i]; i++) {
    if (info->alias->str[i] == str[0]) {
      p = &info->alias->str[i];
      while (str[i] && p[i] == str[i]) {
        i++;
      }
      if (!str[i]) {
        c = *p;
        *p = 0;
        ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *p = c;
        break;
      }
    }
  }
  return ret;
}

int set_alias(info_t *info, char *str)
{
  char *p;
  int ret = 0;

  p = strchr(str, '=');
  if (!p)
    return 1;
  if (!*++p)
    return unset_alias(info, str);

  unset_alias(info, str);
  ret = add_node_end(&(info->alias), str, 0) == NULL;
  return ret;
}

int _myalias(info_t *info)
{
  int i = 0;
  char *p = NULL;
  list_t *node = NULL;

  if (info->argc == 1) {
    node = info->alias;
    for (; node; node = node->next) {
      print_alias(node);
    }
    return 0;
  }
  for (i = 1; info->argv[i]; i++) {
    p = strchr(info->argv[i], '=');
    if (p)
      set_alias(info, info->argv[i]);
    else
      print_alias(node_starts_with(info->alias, info->argv[i], '='));
  }

  return 0;
}

