/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:29:40 by secros            #+#    #+#             */
/*   Updated: 2025/02/07 10:58:44 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 10
# endif

# include <stdlib.h>
# include <unistd.h>

void	buff_cleaner(char *buff, size_t i);
int		is_new_line(char *str);
char	*ft_strappend(char *s1, char *s2);
char	*get_next_line(int fd);

#endif