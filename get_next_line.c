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
	static t_stuff	stuff;
	static ssize_t	eye;
	int				ready_to_go;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stuff.out = malloc(1);
	if (!stuff.out)
		return (NULL);
	stuff.out[0] = 0;
	stuff.join_count = 0;
	ready_to_go = 0;
	while (!ready_to_go)
		stuff.out = read_and_join(&stuff, &eye, &ready_to_go, fd);
	return (stuff.out);
}
