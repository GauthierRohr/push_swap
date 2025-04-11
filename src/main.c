/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:43:38 by grohr             #+#    #+#             */
/*   Updated: 2025/04/11 13:04:53 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

// convertit les char en long pour traiter les args
void	just_parsing_my_args(t_stacks *s)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = ft_split(s->join_args, ' ');
	i = 0;
	j = 0;
	while (tmp[i] != NULL && tmp[i][0] != '\0')
	{
		s->a[j++] = ft_atol(tmp[i++], s);
		free(tmp[i - 1]);
	}
	free(tmp);
}

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
			free_exit_msg(s, "Error\n");
		if (i != argc - 1)
		{
			result = ft_strjoin(temp, " ");
			free(temp);
			if (!result)
				free_exit_msg(s, "Error\n");
		}
		else
			result = temp;
	}
	s->join_args = result;
}

void	init_stacks_size(int ac, char **av, t_stacks *s)
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
		free_exit_msg(s, "Error\n");
	s->b = malloc(s->a_size * sizeof(*s->b));
	if (s->b == NULL)
		free_exit_msg(s, "Error\n");
}

// static --> empêche son utilisation depuis d'autres fichiers.
// (même si qqun inclut main.c ou tente de l'appeler depuis un autre fichier).
// --> réduit les risques de conflits de noms
static void	just_checking_my_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 2)
		free_exit_msg(NULL, "");
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!argv[i][0] || argv[i][0] == ' ')
			free_exit_msg(NULL, "Error\n");
		while (argv[i][j] != '\0')
		{
			if ((!(ft_isdigit(argv[i][j])) && (argv[i][j] != ' ')
					&& (argv[i][j] != '-' && argv[i][j] != '+'))
				|| ((argv[i][j] == '-' || argv[i][j] == '+') &&
				(argv[i][j + 1] == '\0' || argv[i][j + 1] == ' ')))
				free_exit_msg(NULL, "Error\n");
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
	init_stacks_size(argc, argv, s);
	join_args(argc, argv, s);
	just_parsing_my_args(s);
	exit_sorted_duplicate(s, 0);
	create_index(s);
	if (s->a_size == 2 && s->a[0] > s->a[1])
		swap("sa", s->a, s->a_size);
	else if (s->a_size == 3)
		sort_three_elements(s);
	else if (s->a_size == 4)
		sort_four_elements(s);
	else if (s->a_size == 5)
		sort_five_elements(s);
	else
		radix_sort(s);
	exit_sorted_duplicate(s, 1);
	free_all(s);
	return (0);
}
