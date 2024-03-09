#include "cub3d.h"




int is_valid(int row, int col, t_game *Game)
{
    return (row >= 0 && row < Game->height && col >= 0 && col < Game->width);
}



int is_pl_pos(char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}


void assign_direct(int **moves)
{
    moves[0][0] = -1; 
    moves[0][1] = 0;   // Up
    moves[1][0] = -1; 
    moves[1][1] = -1;  // Up-Left
    moves[2][0] = -1; 
    moves[2][1] = 1;   // Up-Right
    moves[3][0] = 1;  
    moves[3][1] = 0;   // Down
    moves[4][0] = 1;  
    moves[4][1] = -1;  // Down-Left
    moves[5][0] = 1;  
    moves[5][1] = 1;   // Down-Right
    moves[6][0] = 0;  
    moves[6][1] = -1;  // Left
    moves[7][0] = 0;  
    moves[7][1] = 1;   // Right
}

void free_arr(int **arr)
{
    int i;

    i = 0;
    while (i < 8)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void check_borders(t_game *Game, int ind, int jind)
{
    int **moves;
    int i;

    i = 0;
    moves = malloc(8 * sizeof(int *));
    while(i < 8) 
    {
        moves[i] = malloc(2 * sizeof(int));
        i++;
    }
    assign_direct(moves);

    i = 0;
    int new_ind;
    int new_jind;
    while (i < 8)
    {
        new_ind = ind + moves[i][0];
        new_jind = jind + moves[i][1];
        if (is_valid(new_ind, new_jind, Game) && (Game->map[new_ind][new_jind] == '0' 
        || is_pl_pos(Game->map[new_ind][new_jind])))
        {
            printf("i [%d] j [%d]\n", ind, jind);
            ft_put_error("Error: map is not closed\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    free_arr(moves);    
}
