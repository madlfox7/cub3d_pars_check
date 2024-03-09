#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> // read(); write();
# include <fcntl.h> // open();
# include <stdlib.h> // malloc(); free(); exit();
# include <stdio.h> // perror();
# include <math.h>




typedef struct attr_count
{
    int no_count;
    int so_count;
    int ea_count;
    int we_count;
    int c_count;
    int f_count;
} t_count;

typedef struct s_attributes
{
    t_count count;
    int attr_count;
    char *so;
    char *we;
    char *no;
    char *ea;
    char *f;
    char *c;
}t_attributes;

typedef struct s_player
{
    int x;
    int y;
}t_player;

typedef struct s_game  
{
    t_attributes attr;
      t_player player;
    char **map;
    int map_x;
    int map_y;
    int height;
    int attr_line;
    int width;
} t_game;

void fix_player_pos(t_game *Game);
void	ft_put_error(char *string); 
int	ft_strncmp(const char	*s1, const char	*s2, size_t	n);
void	ft_check_argc_and_name(int argc, char *argv[]);
void check_file_exists(char *argv, int *fd);
void ft_print_map(t_game *Game);
void malloc_map(t_game *Game);
void get_lines(int fd, t_game *Game);
//void empty_map(t_game *Game);
void ft_get_map(char *argv, t_game *Game);
int is_pl_pos(char c);
void check_map_sym(t_game *Game);
int is_space(char c);
void check_map_sym(t_game *Game);
void check_player_count(int player_count);
void ft_check_map(t_game *Game);
//void free_map(char **map, int height);
char	**ft_split(char const *s, char c, int *size, long *i);
long	word_len(char const *s, char c, long i);
unsigned int is_delim(char c, char *delim);
char *my_strtok(char *str, char *delim);
void print_attributes(t_game *Game);
void pars_attributes(t_game *Game, int fd, int *map_start);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char	*s);
void init_attributes(t_game *Game);
int is_attribute(t_game *Game, char *line);
int inv_sym(char *line);

void check_borders(t_game *Game, int ind, int jind);
int is_valid_symbol(char c);

void free_attributes(t_game *Game);
int is_valid_symbol(char c);
void check_attr_count(t_game *Game);
void free_map(t_game *Game);


void			check_attr_identif(t_game *Game);

#endif