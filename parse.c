#include "cubed.h"

/*
1. Make sure F and C are there
2. Make sure NO, SO, WE, EA is there
3. After that, is the map 
*/

int main(void)
{
	int	fd;
	char	*str;
	int	str_len;
	int	*map_row;
	int	i;
	t_map	**map;
	t_map	*node;
	t_map	*cur;
	
	fd = open("map2.cub", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	str_len = ft_strlen(str);
	i = 0;
	//create linked list
	map = ft_calloc(sizeof(t_map *), 1);

	while (str)
	{
		//create array from string
		if (str[str_len - 1] == '\n')
			map_row = ft_calloc(sizeof(int), str_len - 1);
		else
			map_row = ft_calloc(sizeof(int), str_len);
		while (str[i] && str[i]!= '\n')
		{
			if (ft_isdigit(str[i]))
				map_row[i] = str[i] - '0';
			else if (str[i] == ' ')
				map_row[i] = -1;
			else
				map_row[i] = str[i];
			i++;
		}
		//add to the linked list
		node = ft_calloc(sizeof(t_map), 1);
		node->row_array = map_row;
		if (*map == NULL)
		{
			node->prev = NULL;
			node->next = NULL;
			*map = node;
			cur = node;
		}
		else 
		{
			node->prev = NULL;
			node->next = cur;
			cur->prev = node;
			cur = node;
		}
		//reset and get next line
		free(str);
		i = 0;
		str = get_next_line(fd);
	}
	print_map(map, str_len);
}