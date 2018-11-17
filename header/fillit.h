/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:25:39 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/05 11:25:43 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "../libft/libft.h"

typedef	struct				s_tetriminos
{
	char					**piece;
	char					letter;
	int						width;
	int						height;
	int						dist_side;
	int						dist_top;
	struct s_tetriminos		*next;
}							t_tetriminos;

typedef	struct				s_map
{
	char					**grid;
	int						size;
}							t_map;

int							g_size;

t_map						*make_map(int size);
void						del_map(t_map **map);
void						clean_map(t_map **map, t_tetriminos *node);
void						print_grid(char **grid);
void						algorithm(t_tetriminos *head);
int							fill_grid(t_map *map, t_tetriminos *node);
int							try_piece(t_map *map, t_tetriminos *node);
void						put_piece(t_map *map, t_tetriminos *node);
int							get_links(char **grid, int i, int j);
void						get_properties(t_tetriminos **tetr);
void						get_tetriminos(char *argv, t_tetriminos **head);
void						get_tetri_size(t_tetriminos **tetr);
void						prepare_tetriminos(t_tetriminos **tetr);
void						ft_error(char *str);
void						check_piece(char **grid);
t_tetriminos				*make_node(t_tetriminos *next, char letter);
int							add_node(t_tetriminos **head,
										t_tetriminos *new_node);
void						erase_list(t_tetriminos **head);
int							get_piece(t_tetriminos **tetr, int fd,
										char *str, int count);
void						del_node(t_tetriminos **node);
char						**new_tetri(void);
int							move_right(t_tetriminos **tetr);
int							move_down(t_tetriminos **tetr);
int							move_tetrimino(t_tetriminos **tetr);
int							get_offset(t_tetriminos **tetr);

#endif
