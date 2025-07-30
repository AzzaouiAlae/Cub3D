/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:36:37 by oel-bann          #+#    #+#             */
/*   Updated: 2025/05/08 11:40:46 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

void	ft_putstr_fd(int fd, char *s, int len)
{
	if (!s || fd < 0)
		return ;
	if (!len)
		len = ft_strlen(s);
	write(fd, s, len);
}
