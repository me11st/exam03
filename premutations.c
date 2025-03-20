#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    int len = 0;
    while (s[len])
        len++;
    return len;
}

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

void ft_strcpy(char *dst, char *src)
{
    while (*src)
        *dst++ = *src++;
    *dst = '\0';
}

void ft_swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void	ft_swap_str(char **a, char **b)
{
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

int factorial(int n)
{
    int result = 1;
    while (n > 1)
        result *= n--;
    return result;
}

void premute(char *s, int left, int right, char **perms, int *count)
{
    if (left == right)
    {
        ft_strcpy(perms[*count], s);
        (*count)++;
        return ;
    }
    
    char visit[256] = {0};
    for (int i = left; i <= right; i++)
    {
        if (visit[(unsigned char)s[i]])
            continue;
        visit[(unsigned char)s[i]] = 1;
        ft_swap(&s[left], &s[i]);
        premute(s, left + 1, right, perms, count);
        ft_swap(&s[left], &s[i]);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        puts("I need a string\n");
        return 1;
    }

    int len = ft_strlen(av[1]);
    int total = factorial(len);
    char **perms = malloc(sizeof(char *) * total);
	if (!perms || !perms[0])
		return 1; 
    for (int i = 0; i < total; i++)
        perms[i] = malloc(sizeof(char) * (len + 1));
    int count = 0;
    premute(av[1], 0, len - 1, perms, &count);
    for (int i = 0; i < total - 1; i++)
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            if (ft_strcmp(perms[j], perms[j + 1]) > 0)
				ft_swap_str(&perms[j], &perms[j + 1]);
        }
    }
    for (int i = 0; i < total; i++)
        puts(perms[i]);
    for (int i = 0; i < total; i++)
        free(perms[i]);
    free(perms);
    return (0);
}
