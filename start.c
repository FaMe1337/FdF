/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:29:29 by famendes          #+#    #+#             */
/*   Updated: 2024/08/23 18:49:39 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//check if map is .fdf ext
int	check_extension(t_data *data)
{
	int len;

	len = ft_strlen(data->map_path);
	if (len < 4)
		error("Wrong map extension", data);
	if (ft_strncmp(data->map_path + len - 4, ".fdf", 4) == 0)
		return(1);
	error("Wrong map extension", data);
}

//get number columns and rows
void	get_map_size(t_data *data)
{
	int		fd;
	char	*line;
	char	**tab;
	int x = 0;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		error("Invalid FD", data);
	line = get_next_line(fd);
	if (!line)
		error("No map present", data);
	tab = ft_split(line, ' ');
	while (tab[data->map_wcount] && *tab[data->map_wcount] != '\n')
		data->map_wcount++;
	while (tab[x])
		free(tab[x++]);
	free(tab);
	while (line)
	{
		free(line);
		data->map_hcount++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

//verify if map is square
void	check_map_is_square(t_data *data)
{
	int		fd;
	int		x;
	char	*line;
	char	**tab;
	int		x1;

	fd = open(data->map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		tab = ft_split(line, ' ');
		free(line);
		x = 0;
		while (tab[x] && *tab[x] != '\n')
			x++;
		x1 = 0;
		while (tab[x1])
			free(tab[x1++]);
		free(tab);
		if (x != data->map_wcount)
			error("Wrong map format", data);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

//copy map to data->map
void	copy_map(t_data *data)
{
	int		fd;
	char	*line;
	char	**tab;

	fd = open(data->map_path, O_RDONLY);
	data->map = malloc (data->map_hcount * sizeof(int *));
	if (!data->map)
		error("Failed Malloc creating matrix for map", data);
	while (data->y < data->map_hcount)
	{
		data->map[data->y] = malloc(data->map_wcount * sizeof(int));
		if (!data->map[data->y])
			error("Failed malloc while copying map", data);
		line = get_next_line(fd);
		tab = ft_split(line, ' ');
		free(line);
		data->x = 0;
		clean_and_copy(data, tab);
		data->y++;
		free(tab);
	}
}

void clean_and_copy(t_data *data, char **tab)
{
	int	x;

	x = 0;
	while (tab[x] && *tab[x] != '\n')
	{
		data->map[data->y][data->x] = ft_atoi(tab[data->x]);
		x++;
		data->x++;
	}
	x = 0;
	while (tab[x])
		free(tab[x++]);
}
