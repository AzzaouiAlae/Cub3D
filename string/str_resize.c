/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_str_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:00 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 22:23:02 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	str_resize(t_str *str, int capacity)
{
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	s = ft_calloc(sizeof(char), capacity);
	while (i < str->count)
	{
		s[i] = str->content[i];
		i++;
	}
	tmp = str->content;
	str->content = s;
	str->capacity = capacity;
	ft_free(tmp);
}
