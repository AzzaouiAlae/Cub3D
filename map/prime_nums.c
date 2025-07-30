/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_nums.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:44 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 22:22:45 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	is_prime(int n)
{
	int	i;

	i = 2;
	while (i < n / 2)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	next_prime(int n)
{
	while (1)
	{
		if (is_prime(n))
			return (n);
		n++;
	}
	return (0);
}
