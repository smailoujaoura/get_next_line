/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:26:20 by soujaour          #+#    #+#             */
/*   Updated: 2024/11/10 20:39:29 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*remove_line(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	j = i;
	while (buffer[i])
		i++;
	if (i - j == 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	new_buffer = malloc(i - j);
	if (!new_buffer)
		return (free(buffer), new_buffer = NULL);
	ft_strlcpy(new_buffer, &buffer[j + 1], i - j);
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

char	*read_into_buffer(int fd, char *buffer, int *read_size)
{
	char	*new;
	char	*tmp;

	while (*read_size)
	{
		if (ft_strchr(buffer, '\n'))
			break ;
		tmp = malloc(BUFFER_SIZE + 1);
		if (tmp == NULL)
			return (free(tmp), NULL);
		*read_size = read(fd, tmp, BUFFER_SIZE);
		if (*read_size == 0)
			return (free(tmp), tmp = NULL, buffer);
		tmp[*read_size] = '\0';
		new = ft_strjoin(buffer, tmp);
		free(tmp);
		tmp = NULL;
		free(buffer);
		buffer = new;
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

char	*extract_line(char *buffer)
{
	int		i;

	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	return (ft_substr(buffer, 0, i + 1));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_size;

	read_size = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(buffer), buffer = NULL);
	buffer = read_into_buffer(fd, buffer, &read_size);
	if (!buffer)
		return (buffer = NULL);
	line = extract_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL);
	buffer = remove_line(buffer);
	if (!buffer)
		return (free(buffer), buffer = NULL, line);
	if (ft_strlen(buffer) == 0)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}