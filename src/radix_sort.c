/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:09:23 by grohr             #+#    #+#             */
/*   Updated: 2025/04/11 14:04:13 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

// return (1) if sorted
// return (0) if not
int	is_sorted(t_stacks *s)
{
	int	i;

	i = 0;
	while (i < s->a_size - 1)
	{
		if (s->a[i] > s->a[i + 1])
			return (0);
		i++;
	}
	return (1);
}

static void	radix_sort_b(t_stacks *s, int b_size, int bit_size, int j)
{
	while (b_size-- && j <= bit_size && !is_sorted(s))
	{
		if (((s->b[0] >> j) & 1) == 0)
			rotate(s->b, s->b_size, "up", "b");
		else
			push("pa", s);
	}
	if (is_sorted(s))
		while (s->b_size != 0)
			push("pa", s);
}

// size max = biggest number cause of create_index
void	radix_sort(t_stacks *s)
{
	int	j;
	int	bit_size;
	int	size;

	bit_size = 0;
	size = s->a_size;
	while (size > 1 && ++bit_size)
		size /= 2;
	j = -1;
	while (++j <= bit_size)
	{
		size = s->a_size;
		while (size-- && !is_sorted(s))
		{
			if (((s->a[0] >> j) & 1) == 0)
				push("pb", s);
			else
				rotate(s->a, s->a_size, "up", "a");
		}
		radix_sort_b(s, s->b_size, bit_size, j + 1);
	}
	while (s->b_size != 0)
		push("pa", s);
}

/* void	radix_sort(t_stacks *s)
{
	int	max_num;
	int	max_bits;
	int	j;
	int	i;

	max_num = s->a_size - 1;
	max_bits = 0;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	j = -1;
	while (++j <= max_bits)
	{
		i = -1;
		while (++i < s->a_size && !is_sorted(s))
		{
			if (((s->a[0] >> j) & 1) == 0)
				push("pb", s);
			else
				rotate(s->a, s->a_size, "up", "a");
		}
		while (s->b_size != 0)
			push("pa", s);
	}
} */