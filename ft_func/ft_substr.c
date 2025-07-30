/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:42:20 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/27 16:42:21 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

static int	memory_allocation(int *s_len, int len, char **str)
{
	if (*s_len > len)
	{
		*str = ft_calloc(len + 1, sizeof(char));
		*s_len = len;
	}
	else
		*str = ft_calloc(*s_len + 1, sizeof(char));
	return (1);
}

char	*ft_substr(const char *s, int start, int len)
{
	int		s_len;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (!len || !s[0])
		return (ft_strdup(""));
	i = ft_strlen(s) - start;
	if (i <= 0 || (start > ft_strlen(s) - 1))
		return (ft_strdup(""));
	s_len = i;
	i = 0;
	memory_allocation(&s_len, len, &str);
	while (i < s_len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
