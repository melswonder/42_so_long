/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:04:08 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/28 12:38:28 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_rectangle(t_map *m)
{
	int	x;
	int	y;

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
	int	x;
	int	y;
	
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->map[y][x] == 'P')
				m->countP++;
			else if (m->map[y][x] == 'C')
				m->totalC++;
			else if (m->map[y][x] == 'E')
				m->countE++;
			else if (m->map[y][x] != '0' && m->map[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	if (m->countP != 1 || m->totalC < 1 || m->countE < 1)
	{
		printf("p:%d,c:%d,e:%d\n",m->countP,m->totalC,m->countE);
		return (0);
	}
	return (1);
}
