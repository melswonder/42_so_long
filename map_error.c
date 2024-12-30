/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:38:27 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/30 15:39:05 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_error_map_delete(t_map *m)
{
	int	i;

	write(1, "Error\n", 6);
	if (m->map)
	{
		i = 0;
		while (i < m->height)
		{
			free(m->map[i]);
			i++;
		}
		free(m->map);
	}
}

void	visited_error_free(int **visited, int i)
{
	int	j;

	j = 0;
	write(1, "Error\n", 6);
	while (j < i)
	{
		free(visited[j]);
		j++;
	}
	free(visited);
}
