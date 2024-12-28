/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:22:08 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/28 14:29:16 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup(t_map *m, int **visited)
{
	for (int i = 0; i < m->height; i++)
	{
		free(visited[i]);
		free(m->map[i]);
	}
	free(visited);
	free(m->map);
}
