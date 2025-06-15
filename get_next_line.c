/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:57:45 by ssuopea           #+#    #+#             */
/*   Updated: 2025/06/15 15:05:47 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_bag	bag;
	static size_t	i;
	int				ready_to_go;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bag.out = malloc(1);
	bag.out[0] = 0;
	ready_to_go = 0;
	bag.blocks_joined = 0;
	while (!ready_to_go)
		bag.out = read_and_join(&bag, &i, &ready_to_go, fd);
	return (bag.out);
}
