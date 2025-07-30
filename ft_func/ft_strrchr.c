/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:28:53 by oel-bann          #+#    #+#             */
/*   Updated: 2025/05/03 22:34:31 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	lents;

	lents = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((char)c == '\0')
		return ((char *)&s[lents]);
	while (lents)
	{
		if (s[lents - 1] == (char)c)
			return ((char *)&s[lents - 1]);
		lents--;
	}
	return (NULL);
}
