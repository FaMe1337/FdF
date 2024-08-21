/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:29:29 by famendes          #+#    #+#             */
/*   Updated: 2024/08/21 19:08:59 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//check if map is .fdf ext
int	check_extension(t_data *data)
{
	int len;

	len = ft_strlen(data->map_path);
	if (len < 4)
	{
		error("Wrong map extension");
		exit(1);
	}	
	if (ft_strncmp(data->map_path + len - 4, ".fdf", 4) == 0)
		return(1);
	error("Wrong map extension");
	exit(1);
}

//get number columns and rows
void	get_map_size(t_data *data)
{
	int		fd;
	char	*line;
	char	**tab = NULL;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		error("Invalid FD");
	line = get_next_line(fd);
	printf("line: %s\n", line);
	if (!line)
		error("No map present");
	tab = ft_split(line, ' ');
	printf ("%c \n", tab[0][0]);
	printf ("%c \n", tab[0][1]);
	printf ("%c \n", tab[0][2]);
	printf ("%c \n", tab[0][3]);
	printf ("%c \n", tab[0][4]);
	while (tab[data->map_wcount])
		free(tab[data->map_wcount++]);
	data->map_wcount--;
	printf("wcount primeiro: %i\n", data->map_wcount);
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

	fd = open(data->map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		tab = ft_split(line, ' ');
		free(line);
		x = 0;
		while (tab[x])
			free(tab[x++]);
		printf("x valor in square map: %i\n", x);
		free(tab);	
		if (x < data->map_wcount || x > data->map_wcount)
			error("Wrong map format");
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
		error("Failed Malloc creating matrix for map");	
	while (data->y < data->map_hcount)
	{
		data->map[data->y] = malloc(data->map_wcount * sizeof(int));
		if (!data->map[data->y])
			error("Failed malloc while copying map");
		line = get_next_line(fd);
		tab = ft_split(line, ' ');
		free(line);
		data->x = 0;
		while (data->x < data->map_wcount)
		{
			data->map[data->y][data->x] = ft_atoi(tab[data->x]);
			free(tab[data->x++]);
		}
		data->y++;
		free(tab);
	}
}
