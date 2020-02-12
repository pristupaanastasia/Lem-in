#include "lem_in.h"

int min_solve(t_mas_ant **ant)
{
	t_mas_ant *ant1;

	ant1 = *ant;
	int min = 0;
	int i = 1;
	int j =0;
	while (i != 0 && min < ant1->size + 1)
	{
		while(j < ant1->size && ant1->variants[i][j]!= 1)
		{
			j++;
		}
		if (j != ant1->size)
		{
			min = min + ant1->variants[i][j];
			i = j;
			j = 0;
		}
	}
	return(min);
}
int *lensolve(int **res)
{
	int i;
	int j;
	int *len;

	i = 0;
	while(res[i]!=0)
		i++;
	len = malloc((i+1) * sizeof(int));
	ft_bzero(len, (i+1) * sizeof(int));
	i = 0;
	j = 0;
	while(res[i]!=0)
	{
		len[i]++;
		while(res[i][j]!=0)
		{
			len[i]++;
			j++;
		}
		j=0;
		i++;
	}
	return(len);
}

int	max_hodd(int *len)
{
	int i;
	int max;

	i =0;
	max = len[i++];
	while(len[i]!=0)
	{
		if(len[i] > max)
			max = len[i];
		i++;
	}
	return(max);
}

int	min_hodd(int *len)
{
	int i;
	int min;

	i =0;
	min = len[i++];
	while(len[i]!=0)
	{
		if(len[i] < min)
			min = len[i];
		i++;
	}
	return(min);
}

t_ant *search_ants(int ant,int *len_solve)
{
	int i;
	t_ant *ants;

	ants = malloc(sizeof(t_ant));
	i =0;
	while(len_solve[i] != 0)
		i++;
	ants->ants = malloc((i + 2) * sizeof(int));
	ants->room = malloc((i + 2) * sizeof(int));
	ants->way = malloc((i + 2) * sizeof(int));
	ft_bzero(ants->ants, (i + 2) * sizeof(int));
	ft_bzero(ants->room, (i + 2) * sizeof(int));
	ft_bzero(ants->way, (i + 2) * sizeof(int));
	i =0;
	while(len_solve[i]!=0)
	{
		ants->ants[i] = ant/len_solve[i];
		i++;
	}
	return(ants);

}
void	print_ants(t_ant *ant,t_mas_ant **ant2,int **res)
{
	int i;

	i = 0;
	while(ant->room[i]!= 0)
	{
		if(ant->room[i] == -1)
		{
			printf("L%d- 0",i + 1);
			ant->room[i] = -2;
		}
		if(ant->room[i] > 0)
			printf("L%d- %d",i + 1,ant->room[i]);
		i++;
	}

}

int next_room(int room, int *rooms)
{
	int i;

	i = 0;
	while(rooms[i]!= 0 && rooms[i]!= room)
	{
		i++;
	}
	i++;
	if (rooms[i] == 0)
		return(-1);
	else
	{
		return(rooms[i]);
	}
	return(0);
}
void 	next_hod_for_ant(t_ant **ant3,t_mas_ant **ant2,int **res)
{
	int i;
	t_ant *ant;

	i = 0;
	ant = *ant3;
	while(ant->room[i]!= 0)
	{
		ant->room[i] = next_room(ant->room[i],res[ant->way[i]]);
		i++;
	}
}
int all_in_the_end(t_ant *ants)
{
	int i;

	i = 0;
	while(ants->room[i] < 0)
		i++;
	if (ants->room[i] == 0)
		return(1);
	else
		return(0);
}
void	ants2(int **res, t_mas_ant **ant2,t_ant **ant3)
{
	t_mas_ant	*ant;
	t_ant		*ants;
	int i;

	ant = *ant2;
	ants = *ant3;
	i = 0;
	while(all_in_the_end(ants) != 1)
	{
		next_hod_for_ant(ant3,ant2,res);
		if (all_in_the_end(ants) != 1)
			print_ants(ants,ant2,res);
		printf("\n");
	}
}
void	ants(int **res, t_mas_ant **ant2)
{
	t_mas_ant *ant1;
	int i;
	int j;
	int k = 0;
	int time;
	int	*len_solve;
	int ant;
	t_ant *ants;
	int max_hod;
	int min_hod;
	ant1 = *ant2;
	i = 0;
	ant = ant1->ants;
	printf("here!");
	len_solve = lensolve(res);
	max_hod = max_hodd(len_solve);
	min_hod = min_hodd(len_solve);
	time = min_hod * ant;
	if (min_hod > ant)
	{
		while(len_solve[i] > 0)
		{
			len_solve[i] = len_solve[i] - min_hod;
			i++;
		}
	}
	ants = search_ants(ant,len_solve);
	len_solve = lensolve(res);
	i= 0;
	j = 1;
	printf("\n");
	while(ant > 0)
	{
		if (j > 1)
		{
			next_hod_for_ant(&ants,ant2,res);
		}
		if(time > max_hod)
		{
			while(len_solve[i] != 0 && ant > 0)
			{
				ants->way[j - 1] = i;
				ants->room[j - 1] = res[i][0];
				j++;
				ant--;
				i++;
			}
			print_ants(ants,ant2,res);
			time = time - min_hod;
		}else
		{
			while(len_solve[i]!=0 && ant>0)
			{
				if(len_solve[i] < time)
				{
					ants->way[j - 1] = i;
					ants->room[j - 1] = res[i][0];
					j++;
					ant--;
				}
				i++;
			}
			if (i ==0)
			{
				printf("L%d- min",j);
				j++;
				ant--;
			}
			print_ants(ants,ant2,res);
			time = time - min_hod;
		}
		i =0;
		printf("\n");
		k++;
	}
	ants2(res,ant2,&ants);
}
int equality_solve(int *solve1,int *solve2,int max)
{
	int i;

	i = 0;
	while(i< max)
	{
		if (solve1[i] != solve2[i])
			return(0);
		i++;
	}
	return(1);
}

int new_connect(int j,int *solve, int max)
{
	int i;

	i = 0;
	while (i < max)
	{
		if (j == solve[i] || j == 1)
			return(0);
		i++;
	}
	return(1);
}

void find_room(int *res1, int *res2, int max)
{
	int i;
	int j;
	int k;
	int x;
	int y;

	int *buf;
	i = 0;
	j =0;
	k = 0;
	buf = malloc(max * sizeof(int));
	ft_bzero(buf,max * sizeof(int));
	while(i < max && res1[i] != 0 )
	{
		while(j < max && res2[j] != 0 )
		{
			if (i > 0 && res1[i] != 0 && res2[j] != 0 && res1[i] == res2[j] && res1[i - 1] == res2[j + 1])
			{

				y = j;
				while(j + 1 < max && res2[j + 1]!= 0)
				{
					buf[k] = res2[j + 1];
					k++;
					j++;
				}
				x = i;
				j = y;
				while(i < max)
				{
					res2[j] = res1[i];
					j++;
					i++;
				}
				i = x;
				k = 0;
				while (i < max)
				{
					res1[i - 1] = buf[k];
					i++;
					k++;
				}
				i = x;
				j = y;
				k = 0;
			}
			if (j > 0 && res1[i] != 0 && res2[j] != 0 && res1[i] == res2[j] && res2[j - 1] == res1[i + 1])
			{
				y = j;
				x = i;
				while(i + 1 < max && res1[i + 1]!= 0)
				{
					buf[k] = res1[i + 1];
					k++;
					i++;
				}
				i = x;
				while(j < max)
				{
					res1[i] = res2[j];
					j++;
					i++;
				}
				j = y;
				k = 0;
				while (j < max)
				{
					res2[j - 1] = buf[k];
					j++;
					k++;
				}
				i = x;
				j = y;
				k = 0;
			}
			j++;
		}
		j=0;
		i++;
	}
}

int	**find_connect(int **res, int max, int max1)
{
	int i;
	int j;
	int kik;

	i = 0;
	j = 1;
	while (i < max)
	{
		while(j < max)
		{
			if (i != j)
				find_room(res[i],res[j],max1);
			j++;
		}
		j=0;
		i++;
	}
	return(res);
}
int *suurbale(t_mas_ant **ant,int *dextr)
{
	int **var;
	t_mas_ant *ant1;
	int i;
	int j;
	ant1 = *ant;
	var = ant1->variants;

	i = 1;
	j = 0;
	while (dextr[j] != 0)
	{
		var[i][dextr[j]] = -1;
		i = dextr[j];
		j++;
	}
	var[i][dextr[j]] = -1;
	printf("\n");
	print_lem(ant);
	return(solve(ant));
}

int		*solve(t_mas_ant **ant)
{
	int *solve;
	int *solve_now;
	int i;
	int j;
	int sum;
	int minsum;
	int next;
	int hod_now;
	int kik;
	t_mas_ant *ant1;

	i = 0;
	j = 0;
	ant1 = *ant;
	sum = 0;
	solve = malloc(12 *sizeof(int));
	solve_now = malloc(12 *sizeof(int));
	next = 0;
	i = 1;
	j = 0;
	kik = 0;
	hod_now = 0;
	ft_bzero(solve,12 *sizeof(int));
	ft_bzero(solve_now,12 *sizeof(int));
	minsum = ant1->size;
	while (kik != 1 && hod_now != -1 && j < ant1->size)
	{
		while(i != 0 && hod_now > -1)
		{
			while(j < ant1->size && (ant1->variants[i][j] < 1 || new_connect(j,solve_now,hod_now) != 1))
			{
				j++;
			}
			if (j < ant1->size  && new_connect(j,solve_now,hod_now) == 1 && hod_now < minsum)
			{
				sum = sum + ant1->variants[i][j];
				solve_now[hod_now] = j;
				i = j;
				j = 0;
				hod_now++;
			}
			else
			{

				hod_now--;
				j = solve_now[hod_now] + 1;
				solve_now[hod_now] = 0;
				sum = sum - 1;
				if (hod_now > 0)
					i = solve_now[hod_now - 1];
				else
					i = 1;
			}
		}
		solve_now[hod_now] = i;
		if ((minsum != ant1->size && equality_solve(solve_now,solve,hod_now) == 1 )|| i != 0)
			kik = 1;

		if (sum < minsum && i == 0)
		{
			minsum = sum;
			if(solve[0] == 0)
			{
				ft_memcpy(solve,solve_now,12 *sizeof(int));
			}
			else
			{
				ft_bzero(solve,12 *sizeof(int));
				ft_memcpy(solve,solve_now,12 *sizeof(int));
			}
		}
		hod_now--;
		sum--;
		j = solve_now[hod_now] + 1;
		solve_now[hod_now] = 0;
		i = solve_now[hod_now - 1];
	}
	if (solve[0] == 0)
		return NULL;
	i = 0;
	printf("\n");
	while (i < 11)
	{
		printf("| %d |",solve[i] );
		i++;
	}
	return(solve);
}
