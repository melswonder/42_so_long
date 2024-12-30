/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:22:08 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/30 15:42:24 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup(t_map *m, int **visited)
{
	int	i;

	i = 0;
	while (i < m->height)
	{
		free(visited[i]);
		free(m->map[i]);
		i++;
	}
	free(visited);
	free(m->map);
}
