#include "cub3d.h"

#include <string.h>


int main(int argc, char **argv) 
{
   t_game Game;

    ft_check_argc_and_name(argc, argv);
    ft_get_map(argv[1], &Game); 
    check_attr_count(&Game);
    check_attr_identif(&Game);
    ft_check_map(&Game); 
    print_attributes(&Game);

   // ft_print_map(&Game);
    printf("MAP IS VALID\n");
    printf("Player position: %d %d\n", Game.player.x, Game.player.y);
    printf("height %d\n width %d\n", Game.height, Game.width);

    
    free_map(&Game);
    free_attributes(&Game);
    return 0;
}


void free_map(t_game *Game)
{
    int i;

    i = 0;
    if (!Game->map)
        return ;
    if (Game->map != NULL)
    {
        while (i < Game->height)
        {
            free(Game->map[i]);
            i++;
        }
        free(Game->map);
    }
}


void get_map_size(int fd, t_game *Game)
{
    int max_width = 0;
    int line_len = 0;
    char *line = NULL;

    while ((line = get_next_line(fd)) != NULL)
    {
        Game->height++;  
        line_len = strlen(line);
        if (line_len > max_width)
        {
            max_width = line_len;
            Game->width = max_width; 
        }
        free(line);
    }
}

void allocate_map_memory(t_game *Game)
{
    Game->map = (char **)calloc(Game->height, sizeof(char *));

    if (Game->map == NULL) 
    {
        ft_put_error("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }
}





void check_map_size(t_game *Game)
{
   if (Game->height < 3 || Game->width < 2)
     {
            ft_put_error("Error: Invalid map size\n");
            exit(EXIT_FAILURE);
     }
}


void copy_map_lines(int fd, t_game *Game)
{
    char *line = NULL;
    int line_count = 0;

    check_map_size(Game);
    while ((line = get_next_line(fd)))
    {
        if (inv_sym(line))
        {
            ft_put_error("Error: Invalid symbol found");
            exit(EXIT_FAILURE);
        }
        Game->map[line_count] = calloc(Game->width + 1, sizeof(char)); // +1  null
        if (Game->map[line_count] == NULL) 
        {
            ft_put_error("Error: Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        strncpy(Game->map[line_count], line, strlen(line)); 
        free(line);
        line_count++;
    }
}




void ft_get_map(char *argv, t_game *Game)
{
    int fd;
    int map_start;
    char *line;

    line = NULL;
    map_start = 0;
    init_attributes(Game); 
    check_file_exists(argv, &fd);
    pars_attributes(Game, fd, &map_start);
    get_map_size(fd, Game);
    close(fd); 
    allocate_map_memory(Game);
    fd = open(argv, O_RDONLY);
    check_file_exists(argv, &fd);
    while ((line = get_next_line(fd)) && map_start > 1)
    {
        free(line); // Skipping attribute lines
        map_start--;
    }
    copy_map_lines(fd, Game);
    close(fd);
}


void	ft_put_error(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		write(STDERR_FILENO, &string[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

