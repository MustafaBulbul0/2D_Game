/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa <mustafa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:33:59 by mustafa           #+#    #+#             */
/*   Updated: 2025/02/11 23:34:02 by mustafa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	unsigned char	new_ch;

	if (!str)
		return (NULL);
	new_ch = (unsigned char)ch;
	while (*str)
	{
		if (*str == new_ch)
			return ((char *)str);
		str++;
	}
	if (new_ch == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*arr;
	size_t	i;
	size_t	arr_index;

	i = 0;
	arr_index = 0;
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = malloc(total_size);
	if (arr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		arr[arr_index++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		arr[arr_index++] = s2[i];
		i++;
	}
	arr[arr_index] = '\0';
	return (arr);
}

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
