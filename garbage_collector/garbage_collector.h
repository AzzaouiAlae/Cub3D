/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:45:15 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/28 19:12:06 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_mem_list
{
	void				*mem;
	struct s_mem_list	*next;
}						t_mem_list;

t_mem_list				**ft_mem_list(void);
void					*ft_calloc_without_save(size_t n, size_t type_size);
void					*ft_calloc(size_t n, size_t type_size);
void					ft_exit(int num);
void					*current_working_mem(void *mem, int set_to_null);
void					ft_free_all(void);
void					find_to_free(void *mem);
void					ft_free(void *mem);
void					add_mem(t_mem_list *node);
void					save_mem(void *mem);
void					ft_bzero(void *mem, size_t size);

#endif