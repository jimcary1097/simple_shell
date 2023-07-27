#include "shell.h"
int interactive(info_t *info)
{
  int is_interactive = 0;
  for (char c = getchar(); c != EOF; c = getchar()) {
    if (isatty(STDIN_FILENO) && info->readfd <= 2) {
      is_interactive = 1;
      break;
    }
  }
  return is_interactive;
}

int is_delim(char c, char *delim)
{
  int is_delim = 0;
  for (; *delim; delim++) {
    if (*delim == c) {
      is_delim = 1;
      break;
    }
  }
  return is_delim;
}

int _myexit(info_t *info)
{
  int exitcheck = -1;

  if (info->argv[1]) {
    exitcheck = _erratoi(info->argv[1]);
    if (exitcheck == -1) {
      info->status = 2;
      print_error(info, "Illegal number: ");
      _eputs(info->argv[1]);
      _eputchar('\n');
      return 1;
    }
  }
  info->err_num = exitcheck;
  return -2;
}

int _mycd(info_t *info)
{
  char *s, *dir, buffer[1024];
  int chdir_ret = -1;

  s = getcwd(buffer, 1024);
  if (!s)
    _puts("TODO: >>getcwd failure emsg here<<\n");

  if (!info->argv[1]) {
    dir = _getenv(info, "HOME=");
    if (!dir)
      chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
    else
      chdir_ret = chdir(dir);
  }
  else if (_strcmp(info->argv[1], "-") == 0) {
    if (!_getenv(info, "OLDPWD=")) {
      _puts(s);
      _putchar('\n');
      return 1;
    }
    _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
    chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
  }
  else
    chdir_ret = chdir(info->argv[1]);

  if (chdir_ret == -1) {
    print_error(info, "can't cd to ");
    _eputs(info->argv[1]), _eputchar('\n');
  }
  else {
    _setenv(info, "OLDPWD", _getenv(info, "PWD="));
    _setenv(info, "PWD", getcwd(buffer, 1024));
  }
  return 0;
}

