/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:42:24 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 21:19:04 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

int	is_sep(char *sep, char ch, char cur_sep)
{
	if (!ch)
		return (0);
	if (!cur_sep && ft_strchr(sep, ch))
		return (1);
	if (cur_sep && ch == cur_sep)
		return (1);
	return (0);
}

static int	count_words(const char *s, char *sep, char *special_sep)
{
	int		i;
	int		count;
	char	cur_sep;

	i = 0;
	count = 0;
	cur_sep = '\0';
	while (s[i])
	{
		while (is_sep(sep, s[i], cur_sep))
		{
			if (!cur_sep && ft_strchr(special_sep, s[i]))
				cur_sep = s[i];
			else if (cur_sep == s[i])
				cur_sep = '\0';
			i++;
		}
		if (s[i])
			count++;
		while (s[i] && !is_sep(sep, s[i], cur_sep))
			i++;
	}
	return (count);
}

static char	*create_word(char *s, char *sep, char *special_sep, int *j)
{
	int		i;
	char	*str;
	char	cur_sep;

	cur_sep = '\0';
	while (is_sep(sep, s[(*j)], cur_sep))
	{
		if (ft_strchr(special_sep, s[(*j)]))
			cur_sep = s[(*j)];
		(*j)++;
	}
	i = *j;
	while (s[i] && !is_sep(sep, s[i], cur_sep))
		i++;
	str = ft_substr(s, *j, i - *j);
	*j = i;
	return (str);
}

char	**ft_super_split(const char *s, char *sep, char *special_sep)
{
	int		words_len;
	char	**words;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	words_len = count_words(s, sep, special_sep);
	words = ft_calloc(words_len + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (i < words_len)
	{
		words[i] = create_word((char *)s, sep, special_sep, &j);
		j++;
		i++;
	}
	words[i] = 0;
	return (words);
}
