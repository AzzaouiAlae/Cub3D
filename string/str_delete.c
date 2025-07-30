/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_str_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:51 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/08 10:46:55 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	str_delete_char(t_str *str, int index)
{
	if (!str || index > str->count - 1)
		return ;
	while (index < str->count - 1)
	{
		str->content[index] = str->content[index + 1];
		index++;
	}
	if (index == str->count - 1)
		str->content[index] = 0;
	str->count--;
}

void	str_delete_len(t_str *str, int index, int len)
{
	int	ln;

	if (index > str->count - 1 || index < 0 || len < 0 || !str)
		return ;
	ln = (str->count - 1) - (index + len);
	if (ln < 0)
		ln = str->count - index;
	if (ln < len)
		len = ln;
	while (str->count > index)
	{
		str->content[index] = str->content[index + len];
		index++;
	}
	str->count -= len;
}

void	str_clear(t_str *str)
{
	int	i;

	i = 0;
	while (str->count > i)
	{
		str->content[i] = '\0';
		i++;
	}
	str->count = 0;
}
