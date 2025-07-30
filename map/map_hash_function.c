/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_map_hash_function.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:32 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/08 10:45:48 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_func/ft_func.h"
#include "map.h"

int	map_hash_function(char *str)
{
	long	num;
	int		i;

	num = 1;
	i = 0;
	while (str && str[i])
	{
		num += str[i] + i + (i % ft_strlen(str));
		i++;
	}
	if (!i)
		return (num);
	if (str && str[i])
	{
		if (i)
			num *= str[i - 1];
		i = (i - 1) / 2;
		if (i >= 0 && i < ft_strlen(str))
			num *= str[i];
		num *= str[0];
	}
	return ((int)(num));
}
