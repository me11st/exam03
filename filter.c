#include <unistd.h>

#define BUF_SIZE 4096

size_t cus_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

void cus_putstr(const char *s)
{
    while (*s)
        write(STDOUT_FILENO, s++, 1);
}

int cus_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *p1 = s1;
    const unsigned char *p2 = s2;

    while (n--)
    {
        if (*p1 != *p2)
            return *p1 - *p2;
        p1++;
        p2++;
    }
    return 0;
}

void *cus_memmem(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len)
{
    if (needle_len == 0)
        return (void *)haystack;

    if (haystack_len < needle_len)
        return NULL;

    const unsigned char *h = haystack;
    const unsigned char *n = needle;
    size_t limit = haystack_len - needle_len + 1;

    size_t i = 0;
    while (i < limit)
    {
        if (h[i] == n[0] && !cus_memcmp(h + i, n, needle_len))
            return (void *)(h + i);
        ++i;
    }
    return NULL;
}


int main(int ac, char **av)
{
    if (ac != 2)
    {
        cus_putstr("please, put down only one string\n");
        return 1;
    }
    char *str_search = av[1];
    size_t search_len = cus_strlen(str_search);
    if (search_len == 0)
    {
        cus_putstr("please, search string shouldn't be empty\n");
        return 1;
    }
    char buffer[BUF_SIZE];
    ssize_t bytes_read;
    ssize_t i;
    while ((bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0)
    {
        i = 0;
        while (i < bytes_read)
        {
            char *pos = cus_memmem(buffer + i, bytes_read - i, str_search, search_len);
            if (pos != NULL)
            {
                write(STDOUT_FILENO, buffer + i, pos - (buffer + i));
                for (size_t j = 0; j < search_len; j++)
                    write(STDOUT_FILENO, "*", 1);
                i = pos - buffer + search_len;
            }
            else
            {
                write(STDOUT_FILENO, buffer + i, bytes_read - i);
                break;
            }
        }
    }
    if (bytes_read == -1)
    {
        cus_putstr("error: read failed\n");
        return 1;
    }
    return 0;
}