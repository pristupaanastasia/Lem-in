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

t_ant *search_ants(int ant,int *len_solve,int max)
{
	int i;
	t_ant *ants;

	ants = malloc(sizeof(t_ant));
	i =0;
	ants->ants = malloc((max) * sizeof(int));
	ants->room = malloc((max) * sizeof(int));
	ants->way = malloc((max) * sizeof(int));
	ft_bzero(ants->ants, (max) * sizeof(int));
	ft_bzero(ants->room, (max) * sizeof(int));
	ft_bzero(ants->way, (max) * sizeof(int));
	return(ants);

}
void	print_ants(t_ant **ant1,t_mas_ant **ant2,int **res)
{
	int i;
	t_ant *ant;
	t_mas_ant *ant3;

	i = 0;
	ant = *ant1;
	ant3 = *ant2;
	while(i < ant3->size -1 && ant->room[i]!= 0)
	{
		if(ant->room[i] == -1)
		{
			printf("L%d-%s ",i + 1,ant3->koordinats[0].name);
			ant->room[i] = -2;
		}
		if(ant->room[i] > 0)
			printf("L%d-%s ",i + 1,ant3->koordinats[ant->room[i]].name);
		i++;
	}

}

int next_room(int room, int *rooms,int max)
{
	int i;

	i = 0;
	while(i < max -1 && room && rooms[i]!= 0 && rooms[i]!= room)
	{
		i++;
	}
	i++;
	if (i >= max-1 ||rooms[i] == 0)
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
	while(i < (*ant2)->size - 1 && ant->room[i]!= 0)
	{
		if (ant->room[i] > 0)
			ant->room[i] = next_room(ant->room[i],res[ant->way[i]],(*ant2)->size);
		i++;
	}
}
int all_in_the_end(t_ant *ants,int max)
{
	int i;

	i = 0;
	while(i < max && ants->room[i] < 0)
		i++;
	if (i == max || ants->room[i] == 0)
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
	while(all_in_the_end(ants,ant->size - 1) != 1)
	{
		next_hod_for_ant(ant3,ant2,res);
		print_ants(ant3,ant2,res);
		printf("\n");
	}
}
void	ants(int **res, t_mas_ant **ant2)
{
	t_mas_ant *ant1;
	int i;
	int j;
	int time;
	int	*len_solve;
	int ant;
	t_ant *ants;
	int min_hod;

	ant1 = *ant2;
	ant = ant1->ants;
	len_solve = lensolve(res);
	min_hod = min_hodd(len_solve);
	time = min_hod * ant;
	ants = search_ants(ant,len_solve,ant1->size);
	len_solve = lensolve(res);
	i = 0;
	j = 1;
	printf("\n");
	while(ant > 0 && j < ant1->size - 1)
	{
		if (j > 1)
			next_hod_for_ant(&ants,ant2,res);
		while(len_solve[i]!=0 && ant>0)
		{
			if(len_solve[i] <= time)
			{
				ants->room[j - 1] = res[i][0] == 0 ? -1 : res[i][0];
				ants->way[j++ - 1] = i;
				ant--;
			}
			i++;
		}
		print_ants(&ants,ant2,res);
		time = time - min_hod;
		i =0;
		printf("\n");
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

int	buf_len(int *res)
{
	int i;

	i = 1;
	while(res[i]!= 0)
		i++;
	return(i);
}
void rewrite_res(int *res,int i,int j)
{
	int hod;

	if (i > j)
	{
		hod = i-j;
		while (res[i]!=0)
		{
			res[j] = res[i];
			i++;
			j++;
		}
		while(hod > -1)
		{
			res[j] = 0;
			j++;
			hod--;
		}

	}
	else
	{
		hod = j-i;
		while (res[j]!=0)
		{
			res[i] = res[j];
			i++;
			j++;
		}
		while (hod > -1)
		{
			res[i] = 0;
			i++;
			hod--;
		}
	}

}
void check_res(int *res1)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while(res1[i]!=0)
	{
		while(res1[j] !=0)
		{
			if (i!=j)
			{
				if(res1[i] == res1[j])
					rewrite_res(res1,i,j);
			}
			j++;
		}
		j=0;
		i++;
	}
}
void swap_res(int *res1, int *res2, int i, int j)
{
	int k;
	int y;
	int x;
	int *buf;
	int max;

	k = 0;
	y = j;
	max = buf_len(res2);
	buf = malloc(max * sizeof(int));
	ft_bzero(buf,max * sizeof(int));
	while(j + 1 < max && res2[j + 1]!= 0)
		buf[k++] = res2[j++ + 1];
	x = i;
	j = y;
	while(i < max)
		res2[j++] = res1[i++];
	i = x;
	k = 0;
	while (i < max)
		res1[i++ - 1] = buf[k++];
	check_res(res1);
	check_res(res2);
}

void find_room(int *res1, int *res2, int max)
{
	int i;
	int j;


	i = 0;
	j =0;
	/*int kik =0;
	printf("res1 \n");
	while(kik < max)
	{
			printf("[ %d ]",res1[kik]);
			kik++;
	}
	kik= 0;
	printf("res2 \n");
	while(kik < max)
	{
			printf("[ %d ]",res2[kik]);
			kik++;
	}
	i++;*/
	while(res1[i] != 0 )
	{
		while( res2[j] != 0 )
		{
			if (i > 0 && i > j && res1[i] != 0 && res2[j] != 0 && res1[i] == res2[j] && res1[i - 1] == res2[j + 1])
			{
				swap_res(res1,res2,i,j);
			}
			if (j > 0 && res1[i] != 0 && res2[j] != 0 && res1[i] == res2[j] && res2[j - 1] == res1[i + 1])
			{
				swap_res(res2,res1,j,i);
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
	int *solve1;
	t_mas_ant *ant1;
	int i;
	int j;
	ant1 = *ant;
	var = ant1->variants;

	i = 1;
	j = 0;
	while (dextr[j] <ant1->size -1 && j < ant1->size - 1 && dextr[j] != 0)
	{
		var[i][dextr[j]] = -1;
		i = dextr[j];
		j++;
	}
	var[i][dextr[j]] = -1;
	solve1= solve(ant);
	if (solve1[0] == 0)
		return(NULL);
	return(solve1);
}

int		*solve(t_mas_ant **ant)
{
	int *solve;
	int *solve_now;
	int i;
	int j;
	int sum;
	int minsum;
	int hod_now;
	int check;
	t_mas_ant *ant1;

	ant1 = *ant;
	sum = 0;
	solve = malloc((ant1->size +2) *sizeof(int));
	solve_now = malloc((ant1->size + 2)*sizeof(int));
	i = 1;
	j = 0;
	check = 0;
	hod_now = 0;
	ft_bzero(solve,(ant1->size + 2) *sizeof(int));
	ft_bzero(solve_now,(ant1->size + 2) *sizeof(int));
	minsum = ant1->size - 1;
	while (check != 1 && hod_now != -1 && j < ant1->size - 1 && i < ant1->size - 1)
	{
		while(i != 0 && hod_now > -1)
		{
			while(j < (ant1->size - 1) && (ant1->variants[i][j] < 1 || new_connect(j,solve_now,hod_now) != 1))
				j++;
			if (j < (ant1->size - 1) && i < ant1->size - 1 && new_connect(j,solve_now,hod_now) == 1 && hod_now < minsum)
			{
				sum = sum + 1;
				solve_now[hod_now++] = j;
				i = j;
				j = 0;
			}else
			{
				if (hod_now > 0)
				{
					j = solve_now[--hod_now] + 1;
					solve_now[hod_now] = 0;
					sum--;
					i = hod_now > 0 ? solve_now[hod_now - 1] : 1;
				}
				else
				{
					hod_now--;
					i = 1;
				}

			}
		}
		if (hod_now > -1)
		{
			solve_now[hod_now] = i;
			if ((minsum != ant1->size && equality_solve(solve_now,solve,hod_now) == 1 )|| i != 0)
				check = 1;
			if (sum < minsum && i == 0)
			{
				minsum = sum;
				ft_memcpy(solve,solve_now,(ant1->size) *sizeof(int));
			}
			sum--;
			if (hod_now > 0)
			{
				j = solve_now[--hod_now] + 1;
				solve_now[hod_now] = 0;
				if (hod_now > 0)
				i = solve_now[hod_now - 1];
			}
		}
	}
	/*i = 0;
	while(i < ant1->size - 1)
	{
		printf("-%d-",solve[i]);
		i++;
	}
	printf("\n");*/
	free(solve_now);
	return(solve);
}
