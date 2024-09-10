/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:29:29 by famendes          #+#    #+#             */
/*   Updated: 2024/09/04 14:08:40 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


//check if map is .fdf ext
void	check_extension(t_data *data)
{
	int len;

	len = ft_strlen(data->map_path);
	if (len < 4)
		error("Wrong map extension", data);
	if (ft_strncmp(data->map_path + len - 4, ".fdf", 4) == 0)
		return;
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
	int		y;
	char	*line;
	char	**tab;

	fd = open(data->map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		tab = ft_split(line, ' ');
		free(line);
		x = 0;
		while (tab[x] && *tab[x] != '\n')
			x++;
		y = 0;
		while (tab[y])
			free(tab[y++]);
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
	int		y;

	y = 0;
	fd = open(data->map_path, O_RDONLY);
	data->map = malloc (data->map_hcount * sizeof(int *));
	if (!data->map)
		error("Failed Malloc creating matrix for map", data);
	while (y < data->map_hcount)
	{
		data->map[y] = malloc(data->map_wcount * sizeof(int));
		if (!data->map[y])
			error("Failed malloc while copying map", data);
		line = get_next_line(fd);
		tab = ft_split(line, ' ');
		free(line);
		clean_and_copy(data, tab, y);
		y++;
		free(tab);
	}
}

void clean_and_copy(t_data *data, char **tab, int y)
{
	int	x;

	x = 0;
	while (tab[x] && *tab[x] != '\n')
	{
		data->map[y][x] = ft_atoi(tab[x]);
		x++;
	}
	x = 0;
	while (tab[x])
		free(tab[x++]);
}
