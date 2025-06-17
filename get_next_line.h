/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:50:28 by ssuopea           #+#    #+#             */
/*   Updated: 2025/06/15 15:04:16 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_stuff
{
	char	in[BUFFER_SIZE + 1];
	char	*out;
	size_t	join_count;
}	t_stuff;

char	*get_next_line(int fd);
char	*read_and_join(t_stuff *stuff, ssize_t *i, int *ready_to_go, int fd);

#endif
