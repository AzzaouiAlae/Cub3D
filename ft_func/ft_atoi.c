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
	int		sign;
	int		num;

	i = 0;
	total = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (is_digit(str[i]))
	{
		num = (str[i] - '0') * sign;
		if (!is_valid_num(num, total))
			*error = 1;
		total = total * 10 + num;
		i++;
	}
	return ((int)total);
}
