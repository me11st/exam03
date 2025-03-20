#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int count_unbalanced(char *s)
{
    int open = 0;
    int close = 0;
    int i = 0;
    
    while (s[i])
    {
        if (s[i] == '(')
            open++;
        else if (s[i] == ')')
        {
            if (open == 0)
                close++;
            else
                open--;
        }
        i++;
    }
    return open + close;
}

void try_remove_rec(char *s, int start, int to_remove)
{
    char tmp[100];
    int i;
    
    if (to_remove == 0)
    {
        if (count_unbalanced(s) == 0)
            puts(s);
        return;
    }
    
    i = 0;
    while (s[i])
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    
    i = start;
    while (tmp[i])
    {
        if (tmp[i] == '(' || tmp[i] == ')')
        {
            tmp[i] = ' ';
            try_remove_rec(tmp, i + 1, to_remove - 1);
            tmp[i] = s[i];
        }
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    
    if (count_unbalanced(av[1]) == 0)
        puts(av[1]);
    else
    {
        int to_remove = count_unbalanced(av[1]);
        try_remove_rec(av[1], 0, to_remove);
    }
    return 0;
}