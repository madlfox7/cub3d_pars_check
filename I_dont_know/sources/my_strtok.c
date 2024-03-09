#include "cub3d.h"
# include <string.h>



char	*ft_strpbrk(const char *s, const char *charset)
{
	int		i;

	if (!s || !charset)
		return (0);
	while (*s)
	{
		i = -1;
		while (charset[++i])
			if (*s == charset[i])
				return ((char *)s);
		s++;
	}
	return (0);
}

int		check_char(char c, const char *charset)
{
	int		i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!check_char(s[i], accept))
			return (i);
		i++;
	}
	return (i);
}


char *my_strtok(char *s, char *delim)
{
    static char *olds;
    char *token;

    if (s == NULL)
        s = olds;
    s += ft_strspn(s, delim);
    if (*s == '\0')
    {
        olds = s;
        return (NULL);
    }
    token = s;
    s = ft_strpbrk(token, delim);
    if (s == NULL)
        olds = strchr(token, '\0');
    else
    {
        *s = '\0';
        olds = s + 1;
    }
    return (token);
}

