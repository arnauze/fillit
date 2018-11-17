/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:51:32 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/12 14:51:33 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fillit.h"

/*
**	Moves the tetrimino one to the right
*/

char			**new_tetri(void)
{
	char		**new;
	int			i;
	int			j;

	i = 0;
	new = ft_mapalloc(g_size, g_size);
	while (i < g_size)
	{
		j = 0;
		while (j < g_size)
		{
			new[i][j] = '.';
			j++;
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

int				check_if_ok(t_tetriminos **tetr, int x)
{
	int			i;
	int			j;

	i = -1;
	if (x == 1)
	{
		while ((*tetr)->piece[++i])
		{
			j = -1;
			while ((*tetr)->piece[i][++j])
				if ((*tetr)->piece[i][j] == '#' && j == g_size - 1)
					return (0);
		}
	}
	else
	{
		while ((*tetr)->piece[++i])
		{
			j = -1;
			while ((*tetr)->piece[i][++j])
				if ((*tetr)->piece[i][j] == '#' && i == g_size - 1)
					return (0);
		}
	}
	return (1);
}

int				move_right(t_tetriminos **tetr)
{
	int			i;
	int			j;
	char		**new_piece;

	new_piece = new_tetri();
	if (check_if_ok(tetr, 1) == 0)
		return (0);
	i = -1;
	while ((*tetr)->piece[++i])
	{
		j = -1;
		while ((*tetr)->piece[i][++j])
		{
			if ((*tetr)->piece[i][j] == '#')
			{
				new_piece[i][j + 1] = '#';
				(*tetr)->piece[i][j] = '.';
			}
		}
	}
	ft_mapdel((*tetr)->piece);
	(*tetr)->piece = new_piece;
	return (1);
}

/*
**	Moves the tetrimino one to the bottom
*/

int				move_down(t_tetriminos **tetr)
{
	int			i;
	int			j;
	int			min_offset;
	char		**new_piece;

	new_piece = new_tetri();
	if (check_if_ok(tetr, 0) == 0)
		return (0);
	min_offset = get_offset(tetr);
	i = -1;
	while ((*tetr)->piece[++i])
	{
		j = -1;
		while ((*tetr)->piece[i][++j])
		{
			if ((*tetr)->piece[i][j] == '#')
			{
				new_piece[i + 1][j - min_offset] = '#';
				(*tetr)->piece[i][j] = '.';
			}
		}
	}
	ft_mapdel((*tetr)->piece);
	(*tetr)->piece = new_piece;
	return (1);
}

int				move_tetrimino(t_tetriminos **tetr)
{
	if (move_right(tetr) == 0)
		if (move_down(tetr) == 0)
			return (0);
	return (1);
}
