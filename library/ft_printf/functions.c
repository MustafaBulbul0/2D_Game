/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mubulbul <mubulbul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 08:47:01 by mubulbul          #+#    #+#             */
/*   Updated: 2024/11/09 18:35:48 by mubulbul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write(const char *ptr, int a, int *count)
{
	write(1, ptr, a);
	*count += a;
}

void	print_cs(const char *str, char type, int *count)
{
	int	j;

	if (str == NULL && type == 's')
	{
		ft_write("(null)", 6, count);
		return ;
	}
	if (type == 's')
	{
		j = 0;
		while (str[j])
		{
			ft_write(&str[j], 1, count);
			j++;
		}
	}
	else if (type == 'c')
		ft_write(str, 1, count);
}

void	print_p(void *ptr, int *count)
{
	unsigned long long	address;
	char				*hexa;
	char				htoa[17];
	int					k;

	k = 0;
	hexa = "0123456789abcdef";
	if (!ptr)
	{
		ft_write("(nil)", 5, count);
		return ;
	}
	address = (unsigned long long)ptr;
	ft_write("0x", 2, count);
	while (address > 0)
	{
		htoa[k++] = hexa[address % 16];
		address /= 16;
	}
	while (k != 0)
	{
		ft_write(&htoa[k - 1], 1, count);
		k--;
	}
}

void	print_di(int num, int *count)
{
	unsigned int	n_num;
	char			a[10];
	int				j;

	j = 0;
	if (num == 0)
	{
		ft_write("0", 1, count);
		return ;
	}
	if (num < 0)
	{
		ft_write("-", 1, count);
		n_num = -num;
	}
	else
		n_num = num;
	while (n_num > 0)
	{
		a[j++] = (n_num % 10) + '0';
		n_num /= 10;
	}
	while (j > 0)
		ft_write(&a[--j], 1, count);
}

void	print_uxx(unsigned int num, const char *format, int *count)
{
	char	r_ptr[11];
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (format[i])
		i++;
	if (num == 0)
	{
		ft_write("0", 1, count);
		return ;
	}
	while (num > 0)
	{
		r_ptr[j++] = format[num % i];
		num /= i;
	}
	while (j > 0)
		ft_write(&r_ptr[--j], 1, count);
}
