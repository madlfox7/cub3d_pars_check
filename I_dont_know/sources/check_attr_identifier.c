#include "cub3d.h"
#include <ctype.h>
#include <string.h>

int ft_isdigit(int c) 
{
    return (c >= '0' && c <= '9');
}

int simple_atoi(char *str)
{
    int result;
    int sign;
    int i;

    result = 0;
    sign = 1;
    i = 0;
    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] != '\0')
    {
        int digit = str[i] - '0';
        result = result * 10 + digit;
        i++;
    }
    return sign * result;
}

int invalid_color(char *token) 
{
    int value;
    int i;

    i = 0;
    while (token[i] != '\0')
    {
        if (!ft_isdigit(token[i]))
            return 1;
        i++;
    }
    value = simple_atoi(token);
    if (value < 0 || value > 255)
        return 1;
    return 0;
}


int check_color(char *line) 
{
    char *token;
    char *color;
    size_t length;
    int counter;

    counter = 0;
    color = strdup(line);
    length = ft_strlen(color);
    token = my_strtok(color, ",");
    if (color[length - 1] == ',') 
        return 0;
    while (token != NULL)
    {
        if (invalid_color(token))
            return 0;
        token = my_strtok(NULL, ",");
        counter++;
    }
    if (counter != 3)
        return 0;
    return 1;
}


void check_attr_identif(t_game *Game)
{
    (void)Game;
    if (!check_color(Game->attr.f) || !check_color(Game->attr.c)) {
        ft_put_error("\nInvalid color\n");
        exit(1);
    }

    // Check other attribute paths like 'no', 'so', 'ea', 'we'
    // If they are not valid or don't end with '.xpm', exit(1)

    return ;
}
