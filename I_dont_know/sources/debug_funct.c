#include "cub3d.h"


void print_attributes(t_game *Game)
{
    printf("PRINTING attr\n");
    printf("NO [%s]\n", Game->attr.no);
    printf("SO [%s]\n", Game->attr.so);
    printf("WE [%s]\n", Game->attr.we);
    printf("EA [%s]\n", Game->attr.ea);
    printf("F [%s]\n", Game->attr.f);
    printf("C [%s]\n", Game->attr.c);
}

void ft_print_map(t_game *Game) 
{
    int i;

    i = 0;
    printf("Printing map\n");
    while (i < Game->height)
    {
        printf("%s", Game->map[i]);
        i++;
    }
    printf("Height: %d\n", Game->height);
    printf("Width: %d\n", Game->width);
}

