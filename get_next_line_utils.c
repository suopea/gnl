/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:02:36 by ssuopea           #+#    #+#             */
/*   Updated: 2025/06/15 15:30:01 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*let_go(t_bag *bag, int *ready_to_go)
{
	free(bag->out);
	bag->out = NULL;
	*ready_to_go = 1;
	return (NULL);
}

static char	*join(t_bag *bag, ssize_t *i, int *ready_to_go)
{
	char	*new;
	ssize_t	pen;

	pen = 0;
	new = malloc(BUFFER_SIZE * (bag->join_count + 1) + 1);
	if (!new)
		return (let_go(bag, ready_to_go));
	while (bag->out[pen])
	{
		new[pen] = bag->out[pen];
		pen++;
	}
	while (bag->in[*i] != '\n' && bag->in[*i])
		new[pen++] = bag->in[(*i)++];
	if (bag->in[*i] == '\n' || (!bag->in[*i] && *i < BUFFER_SIZE))
		*ready_to_go = 1;
	if (bag->in[*i] == '\n')
	{
		new[pen++] = '\n';
		*i += 1;
	}
	new[pen] = 0;
	free(bag->out);
	return (new);
}

char	*what_to_do(t_bag *bag, ssize_t *i, int *ready_to_go, int fd)
{
	ssize_t	bytes_read;

	bytes_read = BUFFER_SIZE;
	if (*i == 0)
	{
		bytes_read = read(fd, bag->in, BUFFER_SIZE);
		if (bytes_read < 0 || (!bytes_read && !bag->join_count))
			return (let_go(bag, ready_to_go));
		bag->in[bytes_read] = 0;
	}
	bag->out = join(bag, i, ready_to_go);
	if (!bag->in[*i])
	{
		*i = 0;
		bag->join_count++;
	}
	return (bag->out);
}

// char	*read_and_join(t_bag *bag, size_t *i, int *ready_to_go, int fd)
// {
// 	ssize_t	bytes_read;
//
// 	bytes_read = BUFFER_SIZE;
// 	if (*i == 0)
// 		bytes_read = read(fd, bag->in, BUFFER_SIZE);
// 	if (bytes_read == BUFFER_SIZE)
// 		bag->out = join(bag, i, ready_to_go, BUFFER_SIZE);
// 	else if (bytes_read < 0 || (!bytes_read && !bag->join_count))
// 		return (let_go(bag, ready_to_go));
// 	else if (!bytes_read && bag->join_count)
// 	{
// 	*ready_to_go = 1;
// 	return (bag->out);
// 	}	
// 	else
// 	{
// 		*ready_to_go = 1;
// 		bag->in[bytes_read] = 0;
// 		bag->out = join(bag, i, ready_to_go, bytes_read);
// 		*i = 0;
// 	}
// 	if (*i >= BUFFER_SIZE)
// 	{
// 		*i = 0;
// 		bag->join_count++;
// 	}
// 	return (bag->out);
// }
