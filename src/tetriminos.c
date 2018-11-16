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

void			get_tetri_size(t_tetriminos **tetr)
{
	int			i;
	int			j;
	int			h;
	int			w;
	int			max_w;

	max_w = 0;
	h = 0;
	i = 0;
	while ((*tetr)->piece[i])
	{
		j = 0;
		w = 0;
		if (ft_strchr((*tetr)->piece[i], '#'))
			h++;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#')
				w++;
			j++;
		}
		if (w > max_w)
			max_w = w;
		i++;
	}
	(*tetr)->height = h;
	(*tetr)->width = max_w;
}

/*
**	Move the tetriminos to the upper left corner
*/

void			prepare_tetriminos(t_tetriminos **tetr)
{
	int			i;
	int			j;

	i = 0;
	while ((*tetr)->piece[i])
	{
		j = 0;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#')
			{
				(*tetr)->piece[i - (*tetr)->dist_top][j - (*tetr)->dist_side] = '#';
				(*tetr)->piece[i][j] = '.';
			}
			j++;
		}
		i++;
	}
	get_tetri_size(tetr);
}

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

int				move_right(t_tetriminos **tetr)
{
	int			i;
	int			j;
	char		**new_piece;

	new_piece = new_tetri();
	i = 0;
	while ((*tetr)->piece[i])
	{
		j = 0;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#' && j == g_size - 1)
				return (0);
			j++;
		}
		i++;
	}
	i = 0;
	while ((*tetr)->piece[i])
	{
		j = 0;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#')
			{
				new_piece[i][j + 1] = '#';
				(*tetr)->piece[i][j] = '.';
			}
			j++;
		}
		i++;
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
	int			offset;
	int			min_offset;
	char		**new_piece;

	new_piece = new_tetri();
	i = 0;
	min_offset = 4;
	while ((*tetr)->piece[i])
	{
		j = 0;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#' && i == g_size - 1)
				return (0);
			j++;
		}
		i++;
	}
	i = 0;
	while ((*tetr)->piece[i])
	{
		j = 0;
		offset = 0;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#')
				break ;
			else
				offset++;
			j++;
		}
		if (offset < min_offset)
			min_offset = offset;
		i++;
	}
	i = 0;
	while ((*tetr)->piece[i])
	{
		j = 0;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#')
			{
				new_piece[i + 1][j - min_offset] = '#';
				(*tetr)->piece[i][j] = '.';
			}
			j++;
		}
		i++;
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
