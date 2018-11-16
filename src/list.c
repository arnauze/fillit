/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:37:23 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/05 12:37:24 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fillit.h"

int						g_size;

/*
**	This file is a basic list handler file.
*/

t_tetriminos			*make_node(t_tetriminos *next, char letter)
{
	t_tetriminos		*new;

	if (!(new = (t_tetriminos *)malloc(sizeof(t_tetriminos))))
		return (NULL);
	new->piece = ft_mapalloc(g_size, g_size);
	new->letter = letter;
	new->next = next;
	new->width = 0;
	new->height = 0;
	return (new);
}

int						add_node(t_tetriminos **head, t_tetriminos *new_node)
{
	t_tetriminos		*current;

	current = *head;
	if (!head || !*head || !new_node)
		return (-1);
	while (current->next)
		current = current->next;
	new_node->letter = current->letter + 1;
	current->next = new_node;
	return (1);
}

void					erase_list(t_tetriminos **head)
{
	t_tetriminos		*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_mapdel(tmp->piece);
		free(tmp);
		tmp = NULL;
	}
	head = NULL;
}

void					del_node(t_tetriminos **node)
{
	ft_mapdel((*node)->piece);
	free(*node);
	*node = NULL;
}
