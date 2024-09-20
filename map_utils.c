/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:18:27 by famendes          #+#    #+#             */
/*   Updated: 2024/09/19 22:13:57 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi_base(char *str, int base)
{
	int	result;
	int	i;

	i = 2;
	result = 0;
	while (str_is_valid(str[i]))
	{
		result *= base;
		if (str[i] >= '0' && str[i] <= '9')
			result += str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += str[i] + 10 - 'a';
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += str[i] + 10 - 'A';
		i++;
	}
	return (result);
}

int	str_is_valid(char c)
{
	int	i;
	char *str;

	str = "0123456789ABCDEFabcdef";
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

