/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_str_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:57 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 22:22:58 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_func/ft_func.h"
#include "string.h"

t_str	*str_new(void)
{
	t_str	*str;

	str = ft_calloc(1, sizeof(t_str));
	str->content = ft_calloc(16, sizeof(char));
	str->count = 0;
	str->capacity = 16;
	return (str);
}

t_str	*str_new_capacity(int capacity)
{
	t_str	*str;

	str = ft_calloc(1, sizeof(t_str));
	str->content = ft_calloc(capacity + 1, sizeof(char));
	str->count = 0;
	str->capacity = capacity + 1;
	return (str);
}

t_str	*str_new_substitute(char *s)
{
	t_str	*str;

	str = ft_calloc(1, sizeof(t_str));
	str->content = s;
	str->capacity = ft_strlen(s) + 1;
	str->count = str->capacity - 1;
	return (str);
}
