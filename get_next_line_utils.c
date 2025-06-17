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

static char	*join(t_stuff *stuff, ssize_t *eye, int *ready_to_go);
static char	*let_go(t_stuff *stuff, int *ready_to_go);

char	*read_and_join(t_stuff *stuff, ssize_t *eye, int *ready_to_go, int fd)
{
	ssize_t	bytes_read;

	if (*eye == 0)
	{
		bytes_read = read(fd, stuff->in, BUFFER_SIZE);
		if (bytes_read < 0 || (!bytes_read && !stuff->join_count))
			return (let_go(stuff, ready_to_go));
		stuff->in[bytes_read] = 0;
	}
	stuff->out = join(stuff, eye, ready_to_go);
	if (!stuff->in[*eye])
	{
		*eye = 0;
		stuff->join_count++;
	}
	return (stuff->out);
}

static char	*join(t_stuff *stuff, ssize_t *eye, int *ready_to_go)
{
	char	*new;
	size_t	pen;

	pen = 0;
	new = malloc(BUFFER_SIZE * (stuff->join_count + 1) + 1);
	if (!new)
		return (let_go(stuff, ready_to_go));
	while (stuff->out[pen])
	{
		new[pen] = stuff->out[pen];
		pen++;
	}
	while (stuff->in[*eye] != '\n' && stuff->in[*eye])
		new[pen++] = stuff->in[(*eye)++];
	if (stuff->in[*eye] == '\n' || (!stuff->in[*eye] && *eye < BUFFER_SIZE))
		*ready_to_go = 1;
	if (stuff->in[*eye] == '\n')
	{
		new[pen++] = '\n';
		*eye += 1;
	}
	new[pen] = 0;
	free(stuff->out);
	return (new);
}

static char	*let_go(t_stuff *stuff, int *ready_to_go)
{
	free(stuff->out);
	stuff->out = NULL;
	*ready_to_go = 1;
	return (NULL);
}
