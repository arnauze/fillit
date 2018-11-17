/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:30:01 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/16 15:30:01 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fillit.h"

void				get_tetri_size(t_tetriminos **tetr)
{
	int			i;
	int			j;
	int			h;
	int			w;

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
		if (w > (*tetr)->width)
			(*tetr)->width = w;
		i++;
	}
	(*tetr)->height = h;
}

/*
**	Move the tetriminos to the upper left corner
*/

void				prepare_tetriminos(t_tetriminos **tetr)
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
				(*tetr)->piece[i - (*tetr)->dist_top]
				[j - (*tetr)->dist_side] = '#';
				(*tetr)->piece[i][j] = '.';
			}
			j++;
		}
		i++;
	}
	get_tetri_size(tetr);
}

int					get_piece(t_tetriminos **tetr, int fd,
	char *str, int count)
{
	int				i;
	int				x;

	i = 0;
	while (i < 4 && (x = get_next_line(fd, &str) > 0))
	{
		if (ft_strlen(str) != 4 || count > 26)
			ft_error("ERROR");
		(*tetr)->piece[i++] = ft_strdup(str);
	}
	(*tetr)->piece[i] = NULL;
	check_piece((*tetr)->piece);
	get_properties(tetr);
	return (x);
}

/*
**	This function reads from the file and stores each
**	tetrimino in a node of a linked list.
**	The function check_piece makes sure the tetrimino
**	is valid while get_properties gets
**	the width and height of the tetrimino and move it
**	to the top left corner.
*/

void				get_tetriminos(char *argv, t_tetriminos **head)
{
	int				fd;
	char			*str;
	t_tetriminos	*tetr;
	int				x;
	int				count;

	count = 0;
	str = NULL;
	x = 1;
	fd = open(argv, O_RDONLY);
	while (x > 0)
	{
		tetr = make_node(NULL, 'A' + count);
		count++;
		x = get_piece(&tetr, fd, str, count);
		if (!(*head))
			(*head = tetr);
		else
			add_node(head, tetr);
		x = get_next_line(fd, &str);
	}
	if (count == 1)
		ft_error("ERROR");
	close(fd);
}

/*
**	Calculate distance from top left of the piece, calculate
**	the size of the tetromino and then move it in the top left corner.
*/

void				get_properties(t_tetriminos **tetr)
{
	int			i;
	int			j;
	int			min_width;

	i = 0;
	min_width = 4;
	while ((*tetr)->piece[i] && (!(ft_strchr((*tetr)->piece[i], '#'))))
		i++;
	(*tetr)->dist_top = i;
	i = 0;
	while ((*tetr)->piece[i])
	{
		j = 0;
		while ((*tetr)->piece[i][j])
		{
			if ((*tetr)->piece[i][j] == '#')
				break ;
			j++;
		}
		if (min_width > j)
			min_width = j;
		i++;
	}
	(*tetr)->dist_side = min_width;
	prepare_tetriminos(tetr);
}
