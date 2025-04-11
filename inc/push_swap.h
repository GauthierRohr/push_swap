/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:43:13 by grohr             #+#    #+#             */
/*   Updated: 2025/04/11 18:38:26 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_stacks
{
	int		*a;
	int		*b;
	int		a_size;
	int		b_size;
	char	*join_args;
}			t_stacks;

void		rotate(int *array, int size, char *direction, char *list);
void		swap(char *str, int *array, int size);
void		push(char *str, t_stacks *s);
void		sort_three_elements(t_stacks *s);
void		sort_four_elements(t_stacks *s);
void		sort_five_elements(t_stacks *s);
void		radix_sort(t_stacks *s);
void		just_parsing_my_args(t_stacks *s);
void		create_index(t_stacks *s);
void		init_stacks_size(int argc, char **argv, t_stacks *s);
void		free_exit_msg(t_stacks *s, char *msg);
void		cleanup_and_exit(char **tmp, t_stacks *s);
void		exit_sorted_duplicate(t_stacks *s, int i);
int			is_sorted(t_stacks *s);
long		ft_atol(const char *n, int *error);
int			ft_count_words(const char *str, char delimiter);
void		free_all(t_stacks *s);

#endif