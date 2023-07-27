#include "shell.h"
int _strlen(char *s)
{
  int i = 0;

  if (!s)
    return (0);

  for (; *s; s++)
    i++;
  return (i);
}


int _strcmp(char *s1, char *s2)
{
  for (; *s1 && *s2; s1++, s2++) {
    if (*s1 != *s2)
      return (*s1 - *s2);
  }
  if (*s1 == *s2)
    return (0);
  else
    return (*s1 < *s2 ? -1 : 1);
}

char *starts_with(const char *haystack, const char *needle)
{
  for (; *needle; needle++, haystack++) {
    if (*needle != *haystack)
      return (NULL);
  }
  return ((char *)haystack);
}

char *_strcat(char *dest, char *src)
{
  char *ret = dest;

  for (; *dest; dest++);
  for (; *src; src++)
    *dest++ = *src;
  *dest = *src;
  return (ret);
}

char *_strcpy(char *dest, char *src)
{
  for (int i = 0; src[i]; i++)
    dest[i] = src[i];
  dest[i] = '\0';
  return (dest);
}
