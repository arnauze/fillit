/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:50:45 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/05 11:50:46 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fillit.h"

int					g_size;

/*
**	This function reads from the file and stores each tetrimino in a node of a linked list.
**	The function check_piece makes sure the tetrimino is valid while get_properties gets
**	the width and height of the tetrimino and move it to the top left corner.
*/

void				get_tetriminos(char *argv, t_tetriminos **head)
{
	int				fd;
	char			*str;
	t_tetriminos	*tetr;
	int				i;
	int				x;
	int				count;

	count = 0;
	str = NULL;
	x = 1;
	tetr = make_node(NULL, 'A');
	fd = open(argv, O_RDONLY);
	while (x > 0)
	{
		count++;
		i = 0;
		while (i < 4 && (x = get_next_line(fd, &str) > 0))
		{
			if (ft_strlen(str) != 4 || count > 26)
				ft_error("ERROR");
			tetr->piece[i++] = ft_strdup(str);
		}
		tetr->piece[i] = NULL;
		check_piece(tetr->piece);
		get_properties(&tetr);
		if (!(*head))
			*head = tetr;
		else
			add_node(head, tetr);
		tetr = make_node(NULL, '\0');
		x = get_next_line(fd, &str);
	}
	if (count == 1)
		ft_error("ERROR");
	close(fd);
}

void				print_grid(char **grid)
{
	int				i;

	i = -1;
	while (grid[++i])
		ft_putendl(grid[i]);
}

/*
**	This is the start of the function
*/

int					main(int argc, char **argv)
{
	t_tetriminos	*tetriminos;

	g_size = 4;
	tetriminos = NULL;
	if (argc == 2)
	{
		get_tetriminos(argv[1], &tetriminos);
		algorithm(tetriminos);
	}
	else
		ft_error("USAGE");
}
