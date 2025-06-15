/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:57:45 by ssuopea           #+#    #+#             */
/*   Updated: 2025/06/14 17:50:18 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>

char	*let_go(t_bag *bag, int *ready_to_go)
{
	free(bag->out);
	*ready_to_go = 1;
	return (0);
}

char	*join(t_bag *bag, size_t *i, int *ready_to_go, size_t size)
{
	char	*new;
	size_t	eye;
	size_t	pen;

	eye = 0;
	pen = 0;
	new = malloc(BUFFER_SIZE * (bag->blocks_joined + 1) + 1);
	if (!new)
		return (let_go(bag, ready_to_go));
	if (bag->out[0])
	{
		while (bag->out[eye])
			new[pen++] = bag->out[eye++];
	}
	while (*i < size && bag->block[*i] != '\n')
		new[pen++] = bag->block[(*i)++];
	if (bag->block[*i] == '\n')
	{
		*ready_to_go = 1;
		new[pen++] = '\n';
		*i += 1;
	}
	new[pen] = 0;
	free(bag->out);
	return (new);
}

char	*read_and_join(t_bag *bag, size_t *i, int *ready_to_go, int fd)
{
	size_t	bytes_read;

	bytes_read = BUFFER_SIZE;
	if (*i == 0)
		bytes_read = read(fd, bag->block, BUFFER_SIZE);
	if (bytes_read == BUFFER_SIZE)
		bag->out = join(bag, i, ready_to_go, BUFFER_SIZE);
	else if (bytes_read <= 0)
		return (let_go(bag, ready_to_go));
	else
	{
		*ready_to_go = 1;
		bag->out = join(bag, i, ready_to_go, bytes_read);
	}
	bag->blocks_joined++;
	if (*i >= BUFFER_SIZE)
		*i = 0;
	return (bag->out);
}

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
	if (!i)
		i = 0;
	while (!ready_to_go)
		bag.out = read_and_join(&bag, &i, &ready_to_go, fd);
	return (bag.out);
}
