/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_new_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:39:19 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/30 21:28:17 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_new(t_map *m)
{
	m = (t_map *)malloc(sizeof(t_map));
	if(m == NULL)
	{
		free(m);
		return;
	}
	m->map = 0;
	m->height = 0;
	m->width = 0;
	m->total_c = 0;
	m->count_p = 0;
	m->count_e = 0;
	m->start_x = 0;
	m->start_y = 0;
}

void	gnl_new(t_read *sg)
{
	sg = (t_read *)malloc(sizeof(t_read));
	if(sg == NULL)
	{
		free(sg);
		return;
	}
	sg->line = NULL;
	sg->ret = 0;
	sg->len = 0;
	sg->new_line = NULL;
	sg->i = 0;
}

void	gnl_delete(t_read *sg)
{
	sg->line = NULL;
	sg->ret = 0;
	sg->len = 0;
	sg->new_line = NULL;
	sg->i = 0;
}

int	**initialize_visited(t_map *m)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(sizeof(int *) * m->height);
	if (!visited)
		return (write(1, "Error\n", 6), NULL);
	i = 0;
	while (i < m->height)
	{
		visited[i] = (int *)malloc(sizeof(int) * m->width);
		if (!visited[i])
		{
			visited_error_free(visited, i);
			return (NULL);
		}
		memset(visited[i], 0, sizeof(int) * m->width);
		i++;
	}
	return (visited);
}
