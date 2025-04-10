/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:06:09 by grohr             #+#    #+#             */
/*   Updated: 2025/04/11 14:50:51 by grohr            ###   ########.fr       */
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

// La fonction exit() termine immédiatement l'exécution d'un programme.
// Elle prend un argument entier, généralement :
// --> 0 pour indiquer une terminaison réussie
// --> 1 (ou autre code non nul) pour signaler une erreur.
// Elle nettoie les ressources allouées avant de fermer le programme,
// comme le nettoyage des buffers ou la fermeture des fichiers ouverts.
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

void	exit_sorted_duplicate(t_stacks *s, int i)
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
					free_exit_msg(s, "Error\n");
				j++;
			}
			i++;
		}
	}
	if (is_sorted(s))
		free_exit_msg(s, NULL);
}
