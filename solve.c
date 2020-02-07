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

int *solve(t_mas_ant **ant)
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
	minsum = ant1->size;
	while (kik != 1 && hod_now != -1 && j < ant1->size)
	{
		while(i != 0 && hod_now > -1)
		{
			while(j < ant1->size && (ant1->variants[i][j]!= 1 || new_connect(j,solve_now,hod_now) != 1))
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
				printf(" %d\n",j);
				kik = 0;
				printf("\n");
				while (kik < 9)
				{
					printf("| %d |",solve_now[kik] );
					kik++;
				}
				kik = 0;
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
		j = solve_now[hod_now] + 1;
		solve_now[hod_now] = 0;
		i = solve_now[hod_now - 1];
	}
	i = 0;
	printf("\n");
	while (i < 12)
	{
		printf("| %d |",solve[i] );
		i++;
	}
	return(solve);
}
