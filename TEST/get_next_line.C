#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static size_t   ft_strlen(const char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return i;
}

static char     *ft_strchr(const char *s, int c)
{
    size_t i = 0;
    while (s[i] && s[i] != (char)c)
        i++;
    if (s[i] == (char)c)
        return (char *)(s + i);
    return NULL;
}

static void     *ft_memmove(void *dst, const void *src, size_t n)
{
    unsigned char       *d = (unsigned char*)dst;
    const unsigned char *s = (const unsigned char*)src;

    if (dst == src || n == 0)
        return dst;
    if (d < s)
    {
        size_t i = 0;
        while (i < n) { d[i] = s[i]; i++; }
    }
    else
    {
        while (n > 0) { n--; d[n] = s[n]; }
    }
    return dst;
}

static int      str_append_mem(char **s1, const char *s2, size_t size2)
{
    size_t  size1 = (*s1) ? ft_strlen(*s1) : 0;
    char    *tmp = (char *)malloc(size1 + size2 + 1);
    size_t  i = 0;

    if (!tmp)
        return 0;
    while (i < size1) { tmp[i] = (*s1)[i]; i++; }
    i = 0;
    while (i < size2) { tmp[size1 + i] = s2[i]; i++; }
    tmp[size1 + size2] = '\0';
    if (*s1)
        free(*s1);
    *s1 = tmp;
    return 1;
}

static int      str_append_str(char **s1, const char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}

char            *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1];
    char        *ret = NULL;
    char        *nl;
    ssize_t     r;

    while (1)
    {
        nl = ft_strchr(b, '\n');
        if (nl)
        {
            if (!str_append_mem(&ret, b, (size_t)(nl - b + 1)))
            { free(ret); return NULL; }
            ft_memmove(b, nl + 1, ft_strlen(nl + 1) + 1);
            return ret;
        }
        if (b[0] != '\0')
        {
            if (!str_append_str(&ret, b))
            { free(ret); return NULL; }
            b[0] = '\0';
        }
        r = read(fd, b, BUFFER_SIZE);
        if (r <= 0)
        {
            if (r < 0) { free(ret); return NULL; }
            if (ret && ret[0] != '\0')
                return ret;
            free(ret);
            return NULL;
        }
        b[r] = '\0';
    }
}
