/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:43:58 by grohr             #+#    #+#             */
/*   Updated: 2025/04/02 19:43:34 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	exit_if_sorted_or_has_duplicate(t_stacks *s, int i)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		while (i < s->a_size)
		{
			j = i + 1;
			while (j < s->a_size)
			{
				if (s->a[i] == s->a[j])
					free_excit_msg(s, "Error\n");
				j++;
			}
			i++;
		}
	}
	if (is_array_sorted(s))
		free_excit_msg(s, NULL);
}
// convertit les char en long pour traiter les args
void	parse_numbers(t_stacks *s)
{
	char	**tmp;
	int		i;
	int		z;

	tmp = ft_split(s->join_args, ' ');
	i = 0;
	z = 0;
	while (tmp[i] != NULL && tmp[i][0] != '\0')
	{
		s->a[z++] = ft_atol(tmp[i++], s);
		free(tmp[i - 1]);
	}
	free(tmp);
}

void	init_stacks(int ac, char **av, t_stacks *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	s->a_size = 0;
	s->b_size = 0;
	while (--ac)
	{
	    words = ft_count_words(av[i + 1], ' ');
	    if (words > 0)
	        s->a_size += words;
	    i++;
	}
	s->a = malloc(s->a_size * sizeof(*s->a));
	if (s->a == NULL)
		free_excit_msg(s, "Error\n");
	s->b = malloc(s->a_size * sizeof(*s->b));
	if (s->b == NULL)
		free_excit_msg(s, "Error\n");
}

void	create_index(t_stacks *s)
{
	int		i;
	int		j;
	int		k;
	int		*new_a;

	new_a = malloc(s->a_size * sizeof * new_a);
	if (new_a == NULL)
		free_excit_msg(s, "Error\n");
	i = -1;
	while (++i < s->a_size)
	{
		k = 0;
		j = -1;
		while (++j < s->a_size)
			if (s->a[i] > s->a[j])
				k++;
		new_a[i] = k;
	}
	i = s->a_size;
	while (i--)
		s->a[i] = new_a[i];
	free(new_a);
}

int	ft_atol(const char *n, t_stacks *s)
{
	int			i;
	long		sign;
	long long	res;

	res = 0;
	sign = 1;
	i = 0;
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
		if (res > 2147483647 || (res * sign) < -2147483648 || ft_strlen(n) > 11)
			free_excit_msg(s, "Error\n");
		if (!(n[i] >= '0' && n[i] <= '9'))
			free_excit_msg(s, "Error\n");
		res = res * 10 + (n[i++] - '0');
	}
	return ((int)(res * sign));
}
