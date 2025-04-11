/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3_to_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:09:11 by grohr             #+#    #+#             */
/*   Updated: 2025/04/11 13:34:46 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

//2 operations maximum
void	sort_three_elements(t_stacks *s)
{
	if (s->a[0] > s->a[1] && s->a[1] < s->a[2] && s->a[0] < s->a[2])
		swap("sa", s->a, s->a_size);
	else if (s->a[0] > s->a[1] && s->a[1] > s->a[2])
	{
		swap("sa", s->a, s->a_size);
		rotate(s->a, s->a_size, "down", "a");
	}
	else if (s->a[0] > s->a[2])
		rotate(s->a, s->a_size, "up", "a");
	else if (s->a[1] > s->a[2])
	{
		swap("sa", s->a, s->a_size);
		rotate(s->a, s->a_size, "up", "a");
	}
}

void	sort_four_elements(t_stacks *s)
{
	while (s->a[0] != 0)
		rotate(s->a, s->a_size, "up", "a");
	push("pb", s);
	sort_three_elements(s);
	push("pa", s);
}

void	sort_five_elements(t_stacks *s)
{
	while (s->b_size < 2)
	{
		if (s->a[0] == 0 || s->a[0] == 1)
			push("pb", s);
		else
			rotate(s->a, s->a_size, "up", "a");
	}
	sort_three_elements(s);
	if (s->b[0] < s->b[1])
		swap("sb", s->b, s->b_size);
	push("pa", s);
	push("pa", s);
}

/*

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