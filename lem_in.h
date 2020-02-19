
#ifndef LEM_IN_H
# define LEM_IN_H
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct		s_kor
{
	char	*name;
	int		num;
	int		x;
	int		y;
}					t_kor;

typedef struct		s_mas_ant
{
	int				ants;
	int				size;
	int				**variants;
	t_kor			*koordinats;
}					t_mas_ant;

typedef struct		s_ant
{
	int				*ants;
	int				*room;
	int				*way;
}					t_ant;

int		*solve(t_mas_ant **ant);
int		min_solve(t_mas_ant **ant);
void	parse_line(t_mas_ant **ant,char *line, int num);
void	parse_line_svizi(t_mas_ant **ant,char *line);
int		parse(t_mas_ant **ant,char *s);
void	print_lem(t_mas_ant **ant);
int		*suurbale(t_mas_ant **ant,int *dextr);
int	**find_connect(int **res, int max, int max1);
void	find_room(int *res1, int *res2, int max);
void	ants(int **res, t_mas_ant **ant2);
t_mas_ant *memalloc_ant(t_mas_ant *ant3);
#endif
