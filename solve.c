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
	ants->ants = malloc((ant + 1) * sizeof(int));
	ants->room = malloc((ant + 1) * sizeof(int));
	ants->way = malloc((ant + 1) * sizeof(int));
	ft_bzero(ants->ants, (ant + 1) * sizeof(int));
	ft_bzero(ants->room, (ant + 1) * sizeof(int));
	ft_bzero(ants->way, (ant + 1) * sizeof(int));
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
	while(ant->room[i]!= 0)
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
	while(ant->room[i]!= 0)
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
	//printf("I %d max %d\n",i,max);
	//printf("ant->room %d\n",ants->room[i]);
	if (i == max || ants->room[i] == 0)
		return(1);
	else
		return(0);
}
void free_ant_h(t_ant *ant)
{
	free(ant->ants);
	free(ant->room);
	free(ant->way);

}
void	ants2(int **res, t_mas_ant **ant2,t_ant **ant3)
{
	t_mas_ant	*ant;
	t_ant		*ants;
	int i;

	ant = *ant2;
	ants = *ant3;
	i = 0;
	while(all_in_the_end(ants,ant->ants) != 1)
	{
		next_hod_for_ant(ant3,ant2,res);
		print_ants(ant3,ant2,res);
		printf("\n");
	}
	free_ant_h(ants);
}

int len_solve_len(int *len)
{
	int i;

	i = 0;
	while(len[i]!=0)
		i++;
	return(i);
}
int arifmet(int *lem)
{
	int i;
	int sum;

	sum = 0;
	while(lem[i]!=0)
	{
		sum =sum+ lem[i];
		i++;
	}
	return(sum);
}
int opr_len(int len, int *mas)
{
	int i;
	int t;
	i = 0;
	t = 0;
	while (mas[i] != 0)
	{
		if(len > mas[i])
			t = len - mas[i] + t;
		i++;
	}
	return(t);
}
void	ants(int **res, t_mas_ant **ant2)
{
	t_mas_ant *ant1;
	int i;
	int j;
	int	*len_solve;
	int ant;
	t_ant *ants;
	int min_hod;
	int len;
	int arifm;

	ant1 = *ant2;
	ant = ant1->ants;
	len_solve = lensolve(res);
	min_hod = min_hodd(len_solve);
	ants = search_ants(ant,len_solve,ant1->size);
	len_solve = lensolve(res);
	i = 0;
	j = 1;
	len = len_solve_len(len_solve);
	arifm = arifmet(len_solve);
	printf("\n");
	while(ant> 0 )
	{
		if (j > 1)
			next_hod_for_ant(&ants,ant2,res);
		while(len_solve[i]!=0 && ant>0)
		{
			if(ant > opr_len(len_solve[i],len_solve))
			{
				ants->room[j - 1] = res[i][0] == 0 ? -1 : res[i][0];
				ants->way[j - 1] = i;
				j++;
				ant--;
			}
			i++;
		}
		print_ants(&ants,ant2,res);
		printf("\n");
		i =0;
	}
	free(len_solve);
	ants2(res,ant2,&ants);
}
int equality_solve(int *solve1,int *solve2)
{
	int i;

	i = 0;
	while(solve2[i]!=0)
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
/*void swap_res(int *res1, int *res2, int i, int j)
{
	int k;
	int y;
	int x;
	int *buf;
	int max;

	k = 0;
	y = j;
	max = buf_len(res2);//тут хуйня
	buf = malloc(max * sizeof(int));
	int kik = 0;
	printf(" \nres1 do\n");
	while(res1[kik]!=0)
	{
		printf(" %d ",res1[kik]);
		kik++;
	}
	kik = 0;
	printf(" \nres2 do\n");
	while(res2[kik]!=0)
	{
		printf(" %d ",res2[kik]);
		kik++;
	}
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
	kik = 0;
	printf(" \nres1 posle\n");
	while(res1[kik]!=0)
	{
		printf(" %d ",res1[kik]);
		kik++;
	}
	kik = 0;
	printf(" \nres2 posle\n");
	while(res2[kik]!=0)
	{
		printf(" %d ",res2[kik]);
		kik++;
	}
	printf(" \n\n");
}
*/
int find_res_room(int *res,int room)
{
	int i;

	i = 0;
	while(res[i]!=0)
	{
		if (res[i] == room)
			return(1);
		i++;
	}
	return(0);
}

void swap_res(int *res1, int *res2)
{
	int x;
	int x1;
	int y;
	int y1;
	int *buf;
	int max;

	x = 0;
	y = 0;
	max = buf_len(res1);
	buf = malloc(max * sizeof(int));
	while(res1[x]!=0 && find_res_room(res2,res1[x]) == 0)
		x++;
	x1 = x;
	while(res1[x]!=0 && find_res_room(res2,res1[x]) == 1)
		x++;
	while(res1[x]!=0)
	{
		buf[y] = res1[x];
		y++;
		x++;
	}
	buf[y] = 0;
	x = 0;
	while(res2[x]!=0 && find_res_room(res1,res2[x]) == 0)
		x++;
	y1 = x;
	while(res2[x]!=0 && find_res_room(res1,res2[x]) == 1)
		x++;
	while(res2[x-1]!=0)
	{
		res1[x1] = res2[x-1];
		x1++;
		x++;
	}
	while(res1[x1]!=0)
	{
		res1[x1] =0;
		x1++;
	}
	x = 0;
	while(buf[x]!=0)
	{
		res2[y1+1] = buf[x];
		x++;
		y1++;
	}
	while(res2[y1+1]!=0)
	{
		res2[y1+1] = 0;
		y1++;
	}
}
void find_room(int *res1, int *res2, int max)
{
	int i;
	int j;


	i = 0;
	j =0;
	while(res1[i] != 0 )
	{
		while( res2[j] != 0 )
		{
			if (i > 0 && i > j && res1[i] != 0 && res2[j] != 0 &&
			res1[i] == res2[j] && res1[i - 1] == res2[j + 1])
			{
				swap_res(res1,res2);
			}
			if (j > 0 && j >= i &&res1[i] != 0 && res2[j] != 0 &&
			res1[i] == res2[j] && res2[j - 1] == res1[i + 1])
			{
				swap_res(res2,res1);
			}
			j++;
		}
		j=0;
		i++;
	}
}

int **delet_res(int t, int **res,int max)
{
	int i;

	i = t;
	while(res[i]!=0)
	{
		if (res[i + 1] != 0)
			ft_memcpy(res[i],res[i+1],sizeof(int) * (max));
		else
		{
			res[i] = 0;
		}
		i++;
	}
	return(res);
}

int find_repeat(int *res1,int *res2)
{
	int i;
	int j;
	int check;
	int j1;

	i = 0;
	j = 0;
	j1 = 0;
	check = 0;
	while(res1[i]!=0)
	{
		while(res2[j]!=0)
		{
			if(res1[i] == res2[j] && res1[i]!= 0 && res2[j]!=0)
			{
				check = 1;
			}			
			j++;
		}
		j1 = j;
		j = 0;
		i++;
	}
	if (check == 1)
	{
		if (j1 > i)
			return(2);
		else
		{
			return(1);
		}
		
	}
	return(-1);

}

void check_room_repeat(int **res,int max)
{
	int i;
	int j;

	i = 0;
	j = 1;
	//printf("FFFF\n");
	while(res[i] != NULL)
	{
		while(res[j] != NULL)
		{
			if (i != j && find_repeat(res[i],res[j]) >= 0)
			{
				if (find_repeat(res[i],res[j]) == 1)
					res = delet_res(i,res,max);
				else
				{
					res = delet_res(j,res,max);
				}	
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
				find_room(res[i],res[j],max1);//написать функцию которая чекает на одинаковые комнаты и удаляет эти пути
			j++;
		}
		j=0;
		i++;
	}
	check_room_repeat(res,max1);//написать функцию которая чекает на одинаковые комнаты и удаляет эти пути
	return(res);
}

int end_empty(int **var,int max)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(var[0][j] < 1 && j < max)
		j++;
	if (j == max)
		return(0);
	else
	{
		return(1);
	}
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
	free(dextr);
	if (end_empty(var,ant1->size - 1)!= 0)
		solve1= solve(ant);
	else
	{
		return(NULL);
	}
	if (solve1[0] == 0)
	{
		free(solve1);
		return(NULL);
	}
	//print_lem(ant);
	return(solve1);
}



int		*mal_mas(int size)
{
	int *mas;

	mas = malloc(6 * sizeof(int));
	mas[0] = 1;//i
	mas[1] = 0;//j
	mas[2] = 0;//sum
	mas[3] = size;//minsum
	mas[4] = 0;//hod_now
	mas[5] = 0;//check
	return(mas);
}

void	solve1(int *mas, int *solve, int *solve_now, t_mas_ant *ant1)
{
	solve_now[mas[4]] = mas[0];
//	if ((mas[3] != ant1->size - 1 && equality_solve(solve_now,solve) == 1 )|| mas[0] != 0)
//		mas[5] = 1;
//	else
//	{
		if (mas[4] < mas[3] && mas[0] == 0)
		{
			mas[3] = mas[4];
			ft_memcpy(solve,solve_now,(ant1->size) *sizeof(int));
			/*printf("MINSUM %d HOD %d\n",mas[3],mas[4]);
			int i;
			i=0;
			while(solve_now[i]!=0)
			{
				printf(" %d ",solve_now[i]);
				i++;
			}
			printf("\n");*/
		}
		if (mas[4] > 0)
		{

			mas[4]--;
			mas[1] = solve_now[--mas[4]] + 1;
			solve_now[mas[4]] = 0;
			mas[2]--;
			mas[0] = mas[4] > 0 ? solve_now[mas[4] - 1] : 1;
		}
//	}
}

void	solve2(int *mas, int *solve, int *solve_now)
{
	//printf("solve \n");
	//while(solve_now[kik]!=0)
	//{
	//	printf(" %d ",solve_now[kik]);
	//	kik++;
	//}
	//printf("\n hod_now %d\n",mas[4]);
	if (mas[4] > 0 )//&& mas[4] < mas[3])
	{
		mas[4]--;
		mas[1] = solve_now[mas[4]] + 1;
		solve_now[mas[4]] = 0;
		mas[2]--;
		mas[0] = mas[4] > 0 ? solve_now[mas[4] - 1] : 1;
	//printf("solve posle i %d j %d\n",mas[0],mas[1]);
	//while(solve_now[kik]!=0)
	//{
	//	printf(" %d ",solve_now[kik]);
	//	kik++;
	//}
//	printf("\n hod_now %d\n",mas[4]);
	}
	else
	{
		mas[4] = -1;
		mas[0] = 1;
	}
}
void	solve3(int *mas, int *solve_now)
{
	mas[2]++;
	solve_now[mas[4]++] = mas[1];
	mas[0] = mas[1];
	mas[1] = 0;
}
int		*solve(t_mas_ant **ant)
{
	int *mas;
	int *solve;
	int *solve_now;
	t_mas_ant *ant1;

	ant1 = *ant;
	//printf("SOLVEEEEE\n");
	solve = malloc((ant1->size) *sizeof(int));
	solve_now = malloc((ant1->size)*sizeof(int));
	mas = mal_mas(ant1->size - 1);
	ft_bzero(solve,(ant1->size) *sizeof(int));
	ft_bzero(solve_now,(ant1->size) *sizeof(int));
	while (mas[5] != 1 && mas[4] != -1 && 
	mas[0] < ant1->size - 1 )//&& mas[4] < mas[3])
	{
		while(mas[0] != 0 && mas[4] > -1 && mas[4] < mas[3] )
		{
			//print_lem(ant);
			//printf("\nJ %d\n",mas[1]);
			//printf("\n +%d+\n",ant1->variants[mas[0]][mas[1]]);
			//printf("|I %d |hod_now %d|",mas[0],mas[4]);
			while(mas[1] < (ant1->size - 1) && (ant1->variants[mas[0]][mas[1]] < 1 ||
			new_connect(mas[1],solve_now,mas[4]) != 1))
				mas[1]++;
			//printf("\nJ %d\n",mas[1]);
			if (mas[1] < (ant1->size - 1) && mas[0] < ant1->size - 1 &&
			new_connect(mas[1],solve_now,mas[4]) == 1 && mas[4] < mas[3])
				solve3(mas,solve_now);
			else
				solve2(mas,solve,solve_now);
		}
		if (mas[4] > -1)
		{
			solve1(mas,solve,solve_now,ant1);
		}
	}
	printf("CHECK %d HOD NOW %d J %d  I %d MINSUM %d\n",mas[5],mas[4],mas[1],mas[0],mas[3]);
	free(solve_now);
	free(mas);
	return(solve);
}
/*int *bell_ford(t_mas_ant **ant)
{

	int i;
	int j;
	t_mas_ant *ant1;
	int *bell;
	int h;

	i = 0;
	j = 0;
	h = 0;
	ant1 = *ant;
	bell = malloc(sizeof(int) * ant1->size);
	while(i < ant1->variants - 1)
	{
		bell[i] = ant1->size;
		i++;
	}
	bell[1] = 0;
	i = 1;
	while (i < ant1->size - 1)
	{
		while (j < ant1->size - 1)
		{
			if ( )
		}
	}
}

int		find_to_level(t_mas_ant *ant,int i,int *solve)
{
	int j;
	int hod;

	j = 0;
	hod = 1;
	solve[0] = j;
	while(i < ant->size -1 && i !=0)
	{
		while(j < ant->size - 1 && (ant->variants[i][j] < 1 || new_connect(j,solve,hod) != 1 || ant->koordinats[j].level < hod))
			j++;
		if (ant->koordinats[j].level == hod)
		{

		}
	}
}
int		*solve_max(t_mas_ant *ant)
{
	int i;
	int j;
	int sum;
	int minsum;
	int *solve_now;
	int *solve;

	i = 1;
	j = 2;
	sum = 0;
	solve_now = malloc((ant1->size)*sizeof(int));
	ft_bzero(solve_now,(ant1->size) *sizeof(int));
	minsum = ant->size;
	while(i < ant->size -1)
	{
		while(j < ant->size - 1)
		{
			if (ant->variants[i][j] == 1 && ant->koordinats[j].level == 2)
			sum = find_to_level(ant,j,solve_now);
			if (sum < minsum)
			{
				solve = solve_now;
				solve_now = malloc((ant1->size)*sizeof(int));
				minsum = sum;
			}
			ft_bzero(solve_now,(ant1->size) *sizeof(int));
		}
	}

}
*/
