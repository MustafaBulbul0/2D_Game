/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mubulbul <mubulbul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:33:59 by mustafa           #+#    #+#             */
/*   Updated: 2025/02/12 15:44:00 by mubulbul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*extract_line(char **last_address)
{
	char	*line;
	char	*temp;
	size_t	len;

	if (!*last_address || !**last_address)
	{
		free(*last_address);
		*last_address = NULL;
		return (NULL);
	}
	len = 0;
	while ((*last_address)[len] && (*last_address)[len] != '\n')
		len++;
	if ((*last_address)[len] == '\n')
		len++;
	line = ft_strndup(*last_address, len);
	temp = ft_strdup(*last_address + len);
	free(*last_address);
	if (temp && *temp == '\0')
	{
		free(temp);
		temp = NULL;
	}
	*last_address = temp;
	return (line);
}

static char	*read_and_store(int fd, char *last_address)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(last_address, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(buffer, last_address));
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(last_address, buffer);
		free(last_address);
		last_address = temp;
	}
	free(buffer);
	return (last_address);
}

char	*get_next_line(int fd)
{
	static char	*last_address = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || ft_set_d(&last_address))
		return (NULL);
	last_address = read_and_store(fd, last_address);
	if (!last_address)
		return (NULL);
	line = extract_line(&last_address);
	return (line);
}
