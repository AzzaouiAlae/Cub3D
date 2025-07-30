/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:42:08 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/27 16:42:09 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

char	*ft_strldup(const char *s1, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	if (!len)
		return (NULL);
	s = (char *)ft_calloc(sizeof(char), (len + 1));
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;
	size_t	len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s = (char *)ft_calloc(sizeof(char), (len + 1));
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strdup_without_save_mem(const char *s1)
{
	int		i;
	char	*s;
	size_t	len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s = (char *)ft_calloc_without_save(sizeof(char), (len + 1));
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
