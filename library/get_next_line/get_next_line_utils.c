#include "get_next_line.h"

size_t	ft_strlen(const char *len)
{
	size_t	i;

	i = 0;
	if (!len)
		return (0);
	while (len[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
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

char	*ft_strndup(const char *str, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(n + 1);
	if (!ptr)
		return (NULL);
	while (i < n && str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_set_d(char **data)
{
	if (!data)
		return (1);
	if (*data == NULL)
	{
		*data = (char *) malloc(sizeof(char));
		if (*data)
			**data = '\0';
		else
			return (1);
	}
	return (0);
}

char	*ft_free(char *buf, char *adress)
{
	free(buf);
	free(adress);
	return (NULL);
}
