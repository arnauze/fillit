/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:53:00 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/05 11:53:00 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fillit.h"

/*
**	Returns the number of links a coordinate has. One link is when '#' is next to another '#'
*/

int				get_links(char **grid, int i, int j)
{
	int			n;

	n = 0;
	if (j < 3 && grid[i][j + 1] == '#')
		n++;
	if (j > 0 && grid[i][j - 1] == '#')
		n++;
	if (i < 3 && grid[i + 1][j] == '#')
		n++;
	if (i > 0 && grid[i - 1][j] == '#')
		n++;
	return (n);
}

/*
**	This function checks for errors. If the tetromino has a different char than '#' or '.',
**	if it has 4 '#' and if there is 6 or 8 links (a valid tetromino will always have 6 or 8 links)
*/

void			check_piece(char **grid)
{
	int			i;
	int			j;
	int			links;
	int			count;

	i = 0;
	count = 0;
	links = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] != '.' && grid[i][j] != '#')
				ft_error("ERROR");
			else if (grid[i][j] == '#')
			{
				links += get_links(grid, i, j);
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 4 || (links != 6 && links != 8))
		ft_error("ERROR");
}

/*
**	Get height and width of the current tetrimino
*/

void			get_properties(t_tetriminos **tetr)
{
	int			i;
	int			j;
	int			min_width;

	i = 0;
	min_width = 4;
	while ((*tetr)->piece[i])
	{
		if (ft_strchr((*tetr)->piece[i], '#'))
			break ;
		i++;
	}
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

/*
**	Function we call whenever we want to output and error message and exit the function.
*/

void			ft_error(char *str)
{
	if (ft_strcmp("USAGE", str) == 0)
	{
		ft_putstr_fd("usage: ./fillit file_name\n", 2);
		exit(-1);
	}
	else if (ft_strcmp("ERROR", str) == 0)
	{
		ft_putstr_fd("error\n", 2);
		exit(-1);
	}
}
