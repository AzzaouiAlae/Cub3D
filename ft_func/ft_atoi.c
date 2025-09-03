/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:12 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 22:23:13 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

int	is_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

int	is_valid_num(int num, long total)
{
	if (total > 0)
	{
		if (total < total * 10 + num)
			return (1);
		else
			return (0);
	}
	else if (total < 0)
	{
		if (total > total * 10 + num)
			return (1);
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str, int *error)
{
	int		i;
	long	total;
	int		first_time;
	int		num;

	i = 0;
	total = 0;
	first_time = 1;
	*error = 1;
	while (is_digit(str[i]) && (first_time || !(*error)) && total <= 255)
	{
		first_time = 0;
		*error = 0;
		num = (str[i] - '0');
		if (!is_valid_num(num, total))
			*error = 1;
		total = total * 10 + num;
		i++;
	}
	return ((int)total);
}
