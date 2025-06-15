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
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_bag
{
	char	block[BUFFER_SIZE];
	char	*out;
	size_t	blocks_joined;
}	t_bag;

char	*get_next_line(int fd);
char	*read_and_join(t_bag *bag, size_t *i, int *ready_to_go, int fd);

#endif
