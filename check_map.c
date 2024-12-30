/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:04:08 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/30 20:31:22 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_rectangle(t_map *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->height)
	{
		if (ft_strlen(m->map[y]) != m->width)
			return (0);
		y++;
	}
	x = 0;
	while (x < m->width)
	{
		if (m->map[0][x] != '1' || m->map[m->height - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < m->height)
	{
		if (m->map[y][0] != '1' || m->map[y][m->width - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	check_collection(t_map *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->map[y][x] == 'P')
				m->count_p++;
			else if (m->map[y][x] == 'C')
				m->total_c++;
			else if (m->map[y][x] == 'E')
				m->count_e++;
			else if (m->map[y][x] != '0' && m->map[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	if (m->count_p != 1 || m->total_c < 1 || m->count_e < 1)
		return (0);
	return (1);
}

int	check_errors_find_p(t_map *m)
{
	int	y;
	int	x;

	if (!check_rectangle(m) || !check_collection(m))
		return (0);
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->map[y][x] == 'P')
			{
				m->start_y = y;
				m->start_x = x;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	is_valid(t_map *m, int x, int y, int **visited)
{
	if (x >= 0 && x < m->width && y >= 0 && y < m->height)
	{
		if (m->map[y][x] != '1' && visited[y][x] == 0)
			return (1);
	}
	return (0);
}

void	check_direction(int x, int y, int i, int coords[2])
{
	if (i == 0)
	{
		coords[0] = x;
		coords[1] = y + 1;
	}
	else if (i == 1)
	{
		coords[0] = x + 1;
		coords[1] = y;
	}
	else if (i == 2)
	{
		coords[0] = x;
		coords[1] = y - 1;
	}
	else
	{
		coords[0] = x - 1;
		coords[1] = y;
	}
}
