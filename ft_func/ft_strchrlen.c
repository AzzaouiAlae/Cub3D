/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:24 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 22:23:25 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

size_t	ft_strchrlen(const char *s, char ch)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != ch)
		i++;
	return (i);
}

size_t	ft_strlen_delimiter(const char *s, char *sep)
{
	size_t	i;

	i = 0;
	while (s && s[i] && !ft_strchr(sep, s[i]))
		i++;
	return (i);
}
