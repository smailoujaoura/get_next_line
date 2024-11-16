/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:26:20 by soujaour          #+#    #+#             */
/*   Updated: 2024/11/10 20:44:29 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		return (free(buffer), buffer = NULL);
	new_buffer = malloc(i - j);
	if (!new_buffer)
		return (free(buffer), buffer = NULL);
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
			return (free(tmp), buffer = NULL);
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
	static char	*buffer[FD_MAX];
	char		*line;
	int			read_size;

	read_size = 1;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (free(buffer[fd]), buffer[fd] = NULL);
	buffer[fd] = read_into_buffer(fd, buffer[fd], &read_size);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), buffer[fd] = NULL);
	buffer[fd] = remove_line(buffer[fd]);
	if (!buffer[fd])
		return (free(buffer[fd]), buffer[fd] = NULL, line);
	if (ft_strlen(buffer[fd]) == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
