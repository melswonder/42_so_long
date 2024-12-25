/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_new_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:39:19 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/25 17:52:14 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_new(t_map *m)
{
	m->map = 0;
	m->height = 0;
	m->width = 0;
	m->totalC = 0;
	m->countP = 0;
	m->countE = 0;
	m->start_x = 0;
	m->start_y = 0;

}
void put_error_map_delete(t_map *m)
{
	write(1, "Error\n", 6);
	if (m->map)
	{
		int i;
		
		i = 0;
		while (i < m->height)
		{
			free(m->map[i]);
			i++;
		}
		free(m->map);
	}
}
void gnl_new(t_read *sg)
{
	sg->line = NULL;
	sg->ret = 0;
	sg->len = 0;
	sg->new_line = NULL;
	sg->i = 0;
}

void gnl_delete(t_read *sg)
{
	sg->line = NULL;
	sg->ret = 0;
	sg->len = 0;
	sg->new_line = NULL;
	sg->i = 0;
}