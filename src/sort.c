/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:09:11 by grohr             #+#    #+#             */
/*   Updated: 2025/04/10 16:25:05 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

// 2 operations max
void	sort_three_elements(t_stacks *s)
{
	if (s->a[0] > s->a[1])
		swap("sa", s->a, s->a_size);
	if (s->a[2] < s->a[0] || s->a[2] < s->a[1])
		rotate(s->a, s->a_size, "down", "a");
}

// 5 operations max
void	sort_four_elements(t_stacks *s)
{
	while (s->a[0] != 0)
		rotate(s->a, s->a_size, "up", "a");
	push("pb", s);
	sort_three_elements(s);
	push("pa", s);
}

// 7 operations max
void	sort_five_elements(t_stacks *s)
{
	while (s->b_size < 2)
	{
		if (s->a[0] == 0 || s->a[0] == 1)
			push("pb", s);
		else
			rotate(s->a, s->a_size, "up", "a");
	}
	if (s->b[0] == 0)
		swap("sb", s->b, s->b_size);
	sort_three_elements(s);
	push("pa", s);
	push("pa", s);
}

/*
void	sort_three_elements(t_stacks *s)
{
	if (s->a[2] != 2)
	{
		if (s->a[0] == 2)
			rotate(s->a, s->a_size, "up", "a");
		else
			rotate(s->a, s->a_size, "down", "a");
	}
	if (s->a[0] > s->a[1])
		swap("sa", s->a, s->a_size);
}

void	sort_four_to_five_elements(t_stacks *s)
{
	while (s->b_size <= 1)
	{
		if (s->a[0] == 0 || s->a[0] == 1)
			push("pb", s);
		else
			rotate(s->a, s->a_size, "up", "a");
	}
	if (s->b[0] == 0)
		swap("sb", s->b, s->b_size);
	if (s->a[2] != 4)
	{
		if (s->a[0] == 4)
			rotate(s->a, s->a_size, "up", "a");
		else
			rotate(s->a, s->a_size, "down", "a");
	}
	if (s->a[0] > s->a[1])
		swap("sa", s->a, s->a_size);
	push("pa", s);
	push("pa", s);
}
*/