/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:28:50 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/16 15:28:50 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fillit.h"

/*
**	Creates an empty map of size SIZExSIZE
*/

t_map				*make_map(int size)
{
	t_map			*map;
	int				i;
	int				j;

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

void				del_map(t_map **map)
{
	ft_mapdel((*map)->grid);
	free(*map);
	*map = NULL;
}

void				clean_map(t_map **map, t_tetriminos *node)
{
	int				i;
	int				j;

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

void				print_grid(char **grid)
{
	int				i;

	i = -1;
	while (grid[++i])
		ft_putendl(grid[i]);
}
