/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algortihm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:37:00 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/06 13:37:01 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fillit.h"

/*
**	Creates an empty map of size SIZExSIZE
*/

t_map		*make_map(int size)
{
	t_map	*map;
	int		i;
	int		j;

	i = 0;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->grid = ft_mapalloc(size, size);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			map->grid[i][j] = '.';
			j++;
		}
		i++;
	}
	map->grid[i] = NULL;
	map->size = size;
	return (map);
}

void		del_map(t_map **map)
{
	ft_mapdel((*map)->grid);
	free(*map);
	*map = NULL;
}

/*
**	That is the function that solves the puzzle. We create a map 4x4 and try to fill it with the tetriminos
**	in the fill_grid function. If we can fit all the pieces in the map, we display the map, free the memory
**	and then exit. If we can't fit all the pieces, we erase the map, and recursively call the algortihm, which
**	will try again but with a larger map.
*/

void		algorithm(t_tetriminos *head)
{
	t_map	*map;

	map = make_map(g_size);
	if (fill_grid(map, head) == 0)
	{
		del_map(&map);
		g_size++;
		algorithm(head);
	}
	else
	{
		print_grid(map->grid);
		del_map(&map);
		erase_list(&head);
	}
}

void		clean_map(t_map **map, t_tetriminos *node)
{
	int		i;
	int		j;

	i = 0;
	while ((*map)->grid[i])
	{
		j = 0;
		while ((*map)->grid[i][j])
		{
			if ((*map)->grid[i][j] == node->letter)
				(*map)->grid[i][j] = '.';
			j++;
		}
		i++;
	}
}

/*
**	For each position in the map, we try to put the current tetrimino. If it fits somewhere, we recursively
**	call the function with the next tetromino. If there's no tetromino, it means we reached the end of the
**	list and that all the tetrominos should be in the map. If we reach the end of the function, it means
**	that we can't fit the tetrominos in the actual map. It then returns 0 and will try again with a larger map.
*/

int			fill_grid(t_map *map, t_tetriminos *node)
{
	int		x;

	x = 1;
	if (!node)
		return (1);
	while (x == 1)
	{
		if (try_piece(map, node) == 1)
		{
			if (fill_grid(map, node->next) == 1)
				return (1);
		}
		clean_map(&map, node);
		x = move_tetrimino(&node);
	}
	get_properties(&node);
	return (0);
}

/*
**	In this function first we make sure we can fit the entire tetromino in the map at the current location.
**	If we can't the function will return 0 and we will try again at the next coordinate. If we can we call
**	put_piece, which is going to add the tetromino on the map.
*/

int			try_piece(t_map *map, t_tetriminos *node)
{
	int		i;
	int		j;

	i = 0;
	while (node->piece[i])
	{
		j = 0;
		while (node->piece[i][j])
		{
			if (node->piece[i][j] == '#' && map->grid[i][j] != '.')
				return (0);
			j++;
		}
		i++;
	}
	put_piece(map, node);
	return (1);
}

/*
**	Puts the tetromino on the map.
*/

void		put_piece(t_map *map, t_tetriminos *node)
{
	int		i;
	int		j;

	i = 0;
	while (node->piece[i])
	{
		j = 0;
		while (node->piece[i][j])
		{
			if (node->piece[i][j] == '#' && map->grid[i][j] == '.')
				map->grid[i][j] = node->letter;
			j++;
		}
		i++;
	}
}
