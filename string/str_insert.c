/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_str_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:54 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/08 10:49:30 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_func/ft_func.h"
#include "string.h"

void	str_insert_char(t_str *str, char value, int index)
{
	int	count;

	count = str->count;
	if (str->capacity - 1 == str->count + 1)
		str_resize(str, str->capacity * 2);
	while (count > index)
	{
		str->content[count] = str->content[count - 1];
		count--;
	}
	str->content[index] = value;
	str->count++;
}

void	str_insert(t_str *str, char *value, int index)
{
	int	count;
	int	len;
	int	i;

	count = str->count;
	len = ft_strlen(value);
	if (str->capacity - 1 <= str->count + len)
	{
		while (str->capacity - 1 <= str->count + len)
			str->capacity *= 2;
		str_resize(str, str->capacity);
	}
	i = 0;
	while (count > index)
	{
		str->content[count - 1 + len] = str->content[count - 1];
		count--;
	}
	while (i < len)
	{
		str->content[index + i] = value[i];
		str->count++;
		i++;
	}
}

void	str_insert_len(t_str *str, char *value, int index, int s_len)
{
	int	count;
	int	len;
	int	i;

	count = str->count;
	len = ft_strlen(value);
	if (s_len < len)
		len = s_len;
	if (str->capacity - 1 <= str->count + len)
	{
		while (str->capacity - 1 <= str->count + len)
			str->capacity *= 2;
		str_resize(str, str->capacity);
	}
	i = -1;
	while (count > index)
	{
		str->content[count - 1 + len] = str->content[count - 1];
		count--;
	}
	while (++i < len)
	{
		str->content[index + i] = value[i];
		str->count++;
	}
}
