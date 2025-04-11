/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:43:58 by grohr             #+#    #+#             */
/*   Updated: 2025/04/11 20:29:23 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	ft_count_words(const char *str, char delimiter)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != delimiter && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*str == delimiter)
			in_word = 0;
		str++;
	}
	return (count);
}

static int	check_limits(long long res, long sign, const char *n, int *error)
{
	if (res > 2147483647 || (res * sign) < -2147483648 || ft_strlen(n) > 11)
	{
		*error = 1;
		return (1);
	}
	return (0);
}

// Return a status code instead of exiting --> avoid leaks
//
// return (*error = 1, 0);
// assignation of 1 to *error, then returns 0
long	ft_atol(const char *n, int *error)
{
	int			i;
	long		sign;
	long long	res;

	res = 0;
	sign = 1;
	i = 0;
	*error = 0;
	while (n[i] == ' ' || (n[i] >= '\t' && n[i] <= '\r'))
		i++;
	if ((n[i] == '+' || n[i] == '-'))
	{
		if (n[i] == '-')
			sign = -1;
		i++;
	}
	while (n[i])
	{
		if (check_limits(res, sign, n, error) || !(n[i] >= '0' && n[i] <= '9'))
			return (*error = 1, 0);
		res = res * 10 + (n[i++] - '0');
	}
	return ((int)(res * sign));
}

void	create_index(t_stacks *s)
{
	int	i;
	int	j;
	int	k;
	int	*new_a;

	new_a = malloc(s->a_size * sizeof * new_a);
	if (new_a == NULL)
		free_exit_msg(s, "Error\n");
	i = -1;
	while (++i < s->a_size)
	{
		k = 0;
		j = -1;
		while (++j < s->a_size)
		{
			if (s->a[i] > s->a[j])
				k++;
		}
		new_a[i] = k;
	}
	i = s->a_size;
	while (i--)
		s->a[i] = new_a[i];
	free(new_a);
}
