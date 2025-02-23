/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:46:03 by secros            #+#    #+#             */
/*   Updated: 2025/02/07 10:59:14 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*build_line(char *str, char *buff)
{
	char	*end;
	char	*fs;
	size_t	i;

	i = 0;
	end = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!end)
	{
		free(str);
		return (NULL);
	}
	while (buff[i] && buff[i] != '\n')
	{
		end[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		end[i++] = '\n';
	end[i] = '\0';
	fs = ft_strappend(str, end);
	free(end);
	buff_cleaner(buff, i);
	if (!fs)
		return (NULL);
	return (fs);
}

static char	*read_file(int fd, char *buff)
{
	ssize_t		size;
	size_t		i;
	char		*str;

	i = 0;
	str = NULL;
	size = 1;
	while (size > 0 && !is_new_line(buff))
	{
		str = ft_strappend(str, buff);
		if (!str)
			return (NULL);
		size = read(fd, buff, BUFFER_SIZE);
		if (size < 0 && str)
			free(str);
		if (size < 0)
			return (buff_cleaner(buff, BUFFER_SIZE), NULL);
		buff[size] = '\0';
	}
	if (size > 0)
		str = build_line(str, buff);
	else
		while (buff[i])
			buff[i++] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buff[MAX_FD][BUFFER_SIZE + 1];
	char		*str;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_file(fd, buff[fd]);
	if (!str)
		return (NULL);
	if (!*str)
	{
		free(str);
		return (NULL);
	}
	return (str);
}
/* 
#include <fcntl.h>
int main ()
{
	int fd = open("test.txt", O_RDONLY);
	int	fd2 = open("test2.txt", O_RDONLY);
	int	i = 0;
	char *str;

	str = get_next_line(fd);
	while(str)
	{
		printf("Ligne %d: %s", i, str);
		free(str);
		str = get_next_line(fd2);
		printf("Ligne %d: %s", i, str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	printf("%s",str);
} */
