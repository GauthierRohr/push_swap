/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:43:47 by grohr             #+#    #+#             */
/*   Updated: 2025/04/11 13:33:16 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	swap(char *str, int *array, int size)
{
	int	tmp;

	if (size < 2)
		return ;
	tmp = array[0];
	array[0] = array[1];
	array[1] = tmp;
	if (str)
		ft_putendl_fd(str, 1);
}

void	push(char *str, t_stacks *s)
{
	int	tmp;

	if (ft_strncmp(str, "pa", 3) == 0 && s->b_size > 0)
	{
		tmp = s->b[0];
		ft_memmove(s->a + 1, s->a, sizeof(int) * s->a_size);
		s->a[0] = tmp;
		s->b_size--;
		ft_memmove(s->b, s->b + 1, sizeof(int) * s->b_size);
		s->a_size++;
		ft_putendl_fd(str, 1);
	}
	else if (ft_strncmp(str, "pb", 3) == 0 && s->a_size > 0)
	{
		tmp = s->a[0];
		ft_memmove(s->b + 1, s->b, sizeof(int) * s->b_size);
		s->b[0] = tmp;
		s->a_size--;
		ft_memmove(s->a, s->a + 1, sizeof(int) * s->a_size);
		s->b_size++;
		ft_putendl_fd(str, 1);
	}
}

void	rotate(int *array, int size, char *direction, char *list)
{
	int	tmp;

	if (size < 1)
		return ;
	if (ft_strncmp(direction, "up", 5) == 0)
	{
		tmp = array[0];
		ft_memmove(array, array + 1, sizeof(int) * (size - 1));
		array[size - 1] = tmp;
		write(1, "r", 1);
	}
	else if (ft_strncmp(direction, "down", 5) == 0)
	{
		tmp = array[size - 1];
		ft_memmove(array + 1, array, sizeof(int) * (size - 1));
		array[0] = tmp;
		write(1, "rr", 2);
	}
	ft_putendl_fd(list, 1);
}
