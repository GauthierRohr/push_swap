/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:06:09 by grohr             #+#    #+#             */
/*   Updated: 2025/04/13 15:34:00 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	free_all(t_stacks *s)
{
	if (s != NULL)
	{
		free(s->a);
		free(s->b);
		free(s->join_args);
		free(s);
	}
}

// EXIT:
// Termine immédiatement l'exécution du programme.
// --> 0 terminaison réussie
// --> 1 (ou autre code non nul) : signaler une erreur.
// Nettoie les ressources allouées avant de fermer le programme,
// comme les buffers ou les fichiers ouverts.
void	free_exit_msg(t_stacks *s, char *msg)
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

void	cleanup_and_exit(char **tmp, t_stacks *s)
{
	int	k;

	k = 0;
	if (tmp)
	{
		while (tmp[k] != NULL)
			free(tmp[k++]);
		free(tmp);
	}
	free_exit_msg(s, "Error\n");
}

void	exit_sorted_duplicate(t_stacks *s, int i)
{
	int	j;

	if (i == 0)
	{
		i = 0;
		while (i < s->a_size)
		{
			j = i + 1;
			while (j < s->a_size)
			{
				if (s->a[i] == s->a[j])
					free_exit_msg(s, "Error\n");
				j++;
			}
			i++;
		}
	}
	if (is_sorted(s))
		free_exit_msg(s, NULL);
}
