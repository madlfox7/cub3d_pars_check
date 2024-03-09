#include "cub3d.h"
#include <string.h> //change strlen and strdup


void check_attr_count(t_game *Game)
{
  if (Game->attr.count.f_count != 1 || Game->attr.count.c_count != 1 )
    {
        ft_put_error("Error: ivalid count F || C \n");
        exit(EXIT_FAILURE);
    }
    if (!(Game->attr.count.no_count >= 1
     && Game->attr.count.so_count  >= 1 && Game->attr.count.we_count  >= 1 &&
            Game->attr.count.ea_count  >= 1))
            {
                ft_put_error("Error: ivalid count NO || SO || WE || EA \n");
                exit(EXIT_FAILURE);
            }
    
//    return (Game->attr.count.no_count >= 1
//      && Game->attr.count.so_count  >= 1 && Game->attr.count.we_count  >= 1 &&
//             Game->attr.count.ea_count  >= 1);
}



int is_attr(char *line)
{
  if (ft_strlen(line) < 2 && (line[0] != 'F' && line[0] != 'C')) 
        return 0;
    if ((ft_strncmp(line, "NO", ft_strlen(line)) == 0 )||
        ft_strncmp(line, "SO", ft_strlen(line)) == 0 ||
        ft_strncmp(line, "WE", ft_strlen(line)) == 0 ||
        ft_strncmp(line, "EA", ft_strlen(line)) == 0 ||
        ft_strncmp(line, "F", ft_strlen(line)) == 0 ||
        ft_strncmp(line, "C", ft_strlen(line)) == 0)
                return 1;
    return 0;
}


void init_attributes(t_game *Game)
{
    Game->attr_line = 0;
    Game->height = 1;
    Game->width = 0;
    Game->attr.count.no_count = 0;
    Game->attr.count.so_count = 0;
    Game->attr.count.we_count = 0;
    Game->attr.count.ea_count = 0;
    Game->attr.count.f_count = 0;
    Game->attr.count.c_count = 0;
    Game->attr.attr_count = 0;
    Game->attr.so = NULL;
    Game->attr.we = NULL;
    Game->attr.no = NULL;
    Game->attr.ea = NULL;
    Game->attr.f = NULL;
    Game->attr.c = NULL;
}

void pars_attributes(t_game *Game, int fd, int *map_start)
{
    char *line;

    while ((line = get_next_line(fd)))
    {   
        if (is_attribute(Game, line))
        {
            free(line);
            (*map_start)++;
        } 
        else
        {
            free(line);
            break;
        }
    }
    if (!line)
        {
            free(line); 
            ft_put_error("Error: Map is empty\n");
            exit(EXIT_FAILURE);
        }
}


void free_attributes(t_game *Game)
{
    free(Game->attr.so);
    free(Game->attr.we);
    free(Game->attr.no);
    free(Game->attr.ea);
    free(Game->attr.f);
    free(Game->attr.c);
}



char	*ft_strjoin_n(char *s1, char *s2)
{
    char *joined = ft_strjoin(s1, "\n");
    char *result = ft_strjoin(joined, s2);
  //  free(joined);
    return result;
}




void join_attribute_path(char **attribute, char *line, int *count)
{
    char *new_path;
    
    new_path = ft_strjoin_n(*attribute, line);
    *attribute = new_path;
    (*count)++;
}

void assign_path(t_game *Game, char *type, char *path)
{
    if (ft_strncmp(type, "NO", ft_strlen(type)) == 0)
        join_attribute_path(&Game->attr.no, path, &Game->attr.count.no_count);
    else if (ft_strncmp(type, "SO", ft_strlen(type)) == 0)
        join_attribute_path(&Game->attr.so, path, &Game->attr.count.so_count);
    else if (ft_strncmp(type, "WE", ft_strlen(type)) == 0)
        join_attribute_path(&Game->attr.we, path, &Game->attr.count.we_count);
    else if (ft_strncmp(type, "EA", ft_strlen(type)) == 0)
        join_attribute_path(&Game->attr.ea, path, &Game->attr.count.ea_count);
    else if (ft_strncmp(type, "F", ft_strlen(type)) == 0) 
    {
        Game->attr.f = strdup(path);
        Game->attr.count.f_count++;
    } 
    else if (ft_strncmp(type, "C", ft_strlen(type)) == 0)
    {
        Game->attr.c = strdup(path);
        Game->attr.count.c_count++;
    }
}




int is_attribute(t_game *Game, char *line)
{
    char *delim = " \t\n\v\f\r";
    char *token = my_strtok(line, delim);
   char *type = NULL;
    int word_count = 0;
    
    while (token)
    {
        if (word_count == 0)
        {
            if (is_attr(token)) //line starts from attr 
                type = token;
            else
                return 0; //stop attribute parsing, map found
        }
        if (word_count == 1)
            assign_path(Game, type, token); 
        else if (word_count > 1)
        {
            ft_put_error("Error: Invalid attribute: too many arguments for attr\n");
            exit(EXIT_FAILURE);
        }
        token = my_strtok(NULL, delim);
        word_count++;
    }
   if (word_count == 1)
   {
         printf("Error: Attribute identifier missing\n");
         exit(1);
   }
    return 1;
}

