/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mubulbul <mubulbul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:19:47 by mubulbul          #+#    #+#             */
/*   Updated: 2025/02/14 13:19:21 by mubulbul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strs(const char **str);

char	*ft_strdup(const char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_strdup_2d(const char **str)
{
	char	**ptr;
	int		str_count;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	str_count = count_strs(str);
	ptr = (char **)ft_calloc((str_count + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = ft_strdup(str[i]);
		if (ptr[i] == NULL)
		{
			clear_2d_pointer(ptr);
			return (NULL);
		}
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

static int	count_strs(const char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	clear_2d_pointer(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}
