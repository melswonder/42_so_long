/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:45:04 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/28 14:33:24 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
// char	*strjoin_free(char const *s1, char const *s2,t_read *sg)
// {
// 	char	*dest;
// 	int		i;
// 	int		s1_size;

// 	i = 0;
// 	s1_size = ft_strlen(s1);
// 	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!dest)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (s2[i] != '\0')
// 	{
// 		dest[s1_size + i] = s2[i];
// 		i++;
// 	}
// 	dest[s1_size + i] = '\0';
// 	return (dest);
// }
