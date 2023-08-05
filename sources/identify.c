#include "../include/cub3D.h"


/*
1. Make sure F and C are there
2. Make sure NO, SO, WE, EA is there
3. After that, is the map
*/
// not going to next for some reason
int	*to_int(char *s)
{
	char	**split;
	int		*color;
	int		i;

	color = ft_calloc(4, sizeof(int));
	split = ft_split(s, ',');
	i = 0;
	while (split[i])
	{
		color[i] = ft_atoi(split[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			perror("Not a valid color");
			exit(1);
		}
		i++;
	}
	return (color);
}

int	check_main(t_main *main)
{
	if (main->n_path == NULL)
		return (1);
	if (main->s_path == NULL)
		return (1);
	if (main->w_path == NULL)
		return (1);
	if (main->e_path == NULL)
		return (1);
	if (main->f_color == NULL)
		return (1);
	if (main->c_color == NULL)
		return (1);
	if (main->n_path == NULL)
		return (1);
	return (0);
}

// add free and exit
t_omap	*identify(t_omap *omap_start, t_main *main)
{
	t_omap	*curr;
	int		i;
	t_omap	*ptr_map;

	i = 0;
	curr = omap_start;
	while (curr)
	{
		if (curr->row[0] == 'F')
		{
			if (main->f_color != NULL)
			{
				perror("incorrect number of identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row, "F ", 2) != 0)
			{
				perror("Incorrect identifier");
				exit(1);
			}
			main->f_color = to_int(curr->row + 2);
		}
		else if (curr->row[0] == 'C')
		{
			if (main->c_color != NULL)
			{
				perror("incorrect number of identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row, "C ", 2) != 0)
			{
				perror("Incorrect identifier");
				exit(1);
			}
			main->c_color = to_int(curr->row + 2);
		}
		else if (curr->row[0] == 'N')
		{
			if (main->n_path != NULL)
			{
				perror("incorrect number of identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row, "NO ", 3) != 0)
			{
				perror("Incorrect identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row + ft_strlen(curr->row) - 4, ".xpm", 4) != 0)
			{
				perror("Error\n require .xpm file");
				exit(1);
			}
			main->n_path = ft_calloc(ft_strlen(curr->row) - 2, sizeof(char));
			main->n_path = cub_strdup(curr->row + 3, main);
		}
		else if (curr->row[0] == 'S')
		{
			if (main->s_path != NULL)
			{
				perror("incorrect number of identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row, "SO ", 3) != 0)
			{
				perror("Incorrect identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row + ft_strlen(curr->row) - 4, ".xpm", 4) != 0)
			{
				perror("Error\n require .xpm file");
				exit(1);
			}
			main->s_path = ft_calloc(ft_strlen(curr->row) - 2, sizeof(char));
			main->s_path = cub_strdup(curr->row + 3, main);
		}
		else if (curr->row[0] == 'E')
		{
			if (main->e_path != NULL)
			{
				perror("incorrect number of identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row, "EA ", 3) != 0)
			{
				perror("Incorrect identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row + ft_strlen(curr->row) - 4, ".xpm", 4) != 0)
			{
				perror("Error\n require .xpm file");
				exit(1);
			}
			main->e_path = ft_calloc(ft_strlen(curr->row) - 2, sizeof(char));
			main->e_path = cub_strdup(curr->row + 3, main);
		}
		else if (curr->row[0] == 'W')
		{
			if (main->w_path != NULL)
			{
				perror("incorrect number of identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row, "WE ", 3) != 0)
			{
				perror("Incorrect identifier");
				exit(1);
			}
			if (ft_strncmp(curr->row + ft_strlen(curr->row) - 4, ".xpm", 4) != 0)
			{
				perror("Error\n require .xpm file");
				exit(1);
			}
			main->w_path = ft_calloc(ft_strlen(curr->row) - 2, sizeof(char));
			main->w_path = cub_strdup(curr->row + 3, main);
		}
		else if (ft_strchr(curr->row, '1') != NULL || ft_strchr(curr->row, '1') != NULL)
		{
			printf("%s\n%s\n%s\n%s\n", main->n_path, main->s_path, main->e_path, main->w_path);
			i = 0;
			while (main->f_color[i])
			{
				printf("%d\n%d\n", main->f_color[i], main->c_color[i]);
				i++;
			}
			if (check_main(main) == 1)
				return (NULL);
			ptr_map = curr;
			return (ptr_map);
		}
		curr = curr->next;
	}
	return (NULL);
}

