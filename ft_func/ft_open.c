/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 05:52:58 by oel-bann          #+#    #+#             */
/*   Updated: 2025/05/11 17:54:50 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

int	ft_open(char *file_name, int flag, int perm)
{
	int	fd;

	if (!file_name)
		return (-1);
	fd = open(file_name, flag, perm);
	return (fd);
}
