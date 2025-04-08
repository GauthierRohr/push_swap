/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:43:38 by grohr             #+#    #+#             */
/*   Updated: 2025/04/08 18:17:16 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static void	join_args(int argc, char **argv, t_stacks *s)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (++i < argc)
	{
		temp = ft_strjoin(result, argv[i]);
		free(result);
		if (!temp)
			free_excit_msg(s, "Error\n");
		if (i != argc - 1)
		{
			result = ft_strjoin(temp, " ");
			free(temp);
			if (!result)
				free_excit_msg(s, "Error\n");
		}
		else
			result = temp;
	}
	s->join_args = result;
}

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

void	free_excit_msg(t_stacks *s, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (s != NULL)
	{
		free(s->a);
		free(s->b);
		free(s->join_args);
		free(s);
	}
	exit(1);
}

static void	just_checking_my_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 2)
		free_excit_msg(NULL, "");
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!argv[i][0] || argv[i][0] == ' ')
			free_excit_msg(NULL, "Error\n");
		while (argv[i][j] != '\0')
		{
			if ((!(ft_isdigit(argv[i][j])) && (argv[i][j] != ' ')
					&& (argv[i][j] != '-' && argv[i][j] != '+'))
				|| ((argv[i][j] == '-' || argv[i][j] == '+') &&
				(argv[i][j + 1] == '\0' || argv[i][j + 1] == ' ')))
				free_excit_msg(NULL, "Error\n");
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_stacks	*s;

	just_checking_my_args(argc, argv);
	s = malloc(sizeof(*s));
	if (s == NULL)
		exit(1);
	init_stacks(argc, argv, s);
	join_args(argc, argv, s);
	parse_numbers(s);
	exit_if_sorted_or_has_duplicate(s, 0);
	create_index(s);
	if (s->a_size == 2 && s->a[0] > s->a[1])
		swap("sa", s->a, s->a_size);
	else if (s->a_size == 3)
		sort_three_elements(s);
	else if (s->a_size >= 4 && s->a_size <= 5)
		sort_four_to_five_elements(s);
	else
		radix_sort(s);
	exit_if_sorted_or_has_duplicate(s, 1);
	free_excit_msg(s, "Error\n");
	return (0);
}
