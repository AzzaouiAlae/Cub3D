/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:18 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 18:27:32 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

t_str	*ft_itoa(int num)
{
	long	n;
	t_str	*str;

	n = num;
	str = str_new();
	if (n < 0)
	{
		str_add_char(str, '-');
		n *= -1;
	}
	else if (!n)
		str_add_char(str, '0');
	while (n > 0)
	{
		if (str->content[0] == '-')
			str_insert_char(str, n % 10 + '0', 1);
		else
			str_insert_char(str, n % 10 + '0', 0);
		n /= 10;
	}
	return (str);
}

int	is_alpha(char ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

int	is_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}
