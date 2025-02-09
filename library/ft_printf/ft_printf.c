/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mubulbul <mubulbul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 08:46:36 by mubulbul          #+#    #+#             */
/*   Updated: 2024/11/09 15:35:23 by mubulbul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_format(char type, va_list args, int *count)
{
	char	c;

	if (type == 'c')
	{
		c = (char)va_arg(args, int);
		print_cs(&c, 'c', count);
	}
	else if (type == 's')
		print_cs(va_arg(args, char *), 's', count);
	else if (type == 'p')
		print_p(va_arg(args, void *), count);
	else if (type == 'd' || type == 'i')
		print_di(va_arg(args, int), count);
	else if (type == 'u')
		print_uxx(va_arg(args, unsigned int), "0123456789", count);
	else if (type == 'x')
		print_uxx(va_arg(args, unsigned int), "0123456789abcdef", count);
	else if (type == 'X')
		print_uxx(va_arg(args, unsigned int), "0123456789ABCDEF", count);
	else if (type == '%')
		ft_write("%", 1, count);
}

int	ft_printf(const char *print, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, print);
	while (print[i])
	{
		if (print[i] == '%')
		{
			i++;
			print_format(print[i], args, &count);
		}
		else
			ft_write(&print[i], 1, &count);
		i++;
	}
	va_end(args);
	return (count);
}
