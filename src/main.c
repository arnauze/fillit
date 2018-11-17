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
