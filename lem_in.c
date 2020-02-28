#include "lem_in.h"
#include "limits.h"
#include <stdio.h>

void 	parse_line(t_mas_ant **ant,char *line, int num)
{
	int k;
	int i;
	t_mas_ant *ant_1;

	ant_1 = *ant;
	i = 0;
	k = 0;
	if (num > 1)
		ant_1->size = ant_1->size + 1;
	ant_1->koordinats[num].num = num;
	while(line[i]!= '\0')
	{
		while(line[i]!=' ')
		{
			ant_1->koordinats[num].name[i] = line[i];
			i++;
		}
		ant_1->koordinats[num].name[i] = '\0';
		while(line[i] == ' ')
			i++;
		while(ft_isdigit(line[i]) == 1)
		{
			k = line[i] - 48 + k*10;
			i++;
		}
		ant_1->koordinats[num].x = k;
		k = 0;
		while(line[i] == ' ')
			i++;
		while(ft_isdigit(line[i]) == 1)
		{
			k = line[i] - 48 + k*10;
			i++;
		}
		ant_1->koordinats[num].y = k;
		k = 0;
		while(line[i] != '\0')
			i++;
	}
}

void parse_line_svizi(t_mas_ant **ant,char *line)
{
	t_mas_ant *ant1;
	char *name1;
	char *name2;
	int num1;
	int num2;
	int i;
	int k;

	name1 = malloc(100);
	name2 = malloc(100);
	ant1 = *ant;
	i = 0;
	k = 0;
	while (line[i]!='\0')
	{
		while (line[i]!='-')
		{
			name1[i] = line[i];
			i++;
		}
		name1[i] = '\0';
		i++;
		while (line[i]!='\0')
		{
			name2[k] = line[i];
			i++;
			k++;
		}
		name2[k] = '\0';
	}
	i=0;
	num1 = 0;
	num2 = 0;
	while(i<ant1->size -1)
	{
		if(ft_strequ(ant1->koordinats[i].name,name1) == 1)
			num1 = i;
		if(ft_strequ(ant1->koordinats[i].name,name2) == 1)
			num2 = i;
		i++;
	}
	ant1->variants[num1][num2] = 1;
	ant1->variants[num2][num1] = 1;
}

int parse(t_mas_ant **ant,char *s)
{
	char		*line;
	t_mas_ant	*ant1;

	ant1 = *ant;
	if(s[0] == '#')
	{
		if (ft_strequ(s,"##start") == 1)
		{
			get_next_line(0,&line);
			printf("%s\n",line);
			parse_line(ant,line,1);
		}else
		{
			if (ft_strequ(s,"##end") == 1)
			{
				get_next_line(0,&line);
				printf("%s\n",line);
				parse_line(ant,line,0);
			}
		}
	}
	else
	{
		if (ft_strchr(s,'-') == NULL)
			parse_line(ant,s,ant1->size - 1);
		else
			parse_line_svizi(ant,s);

	}
	return(1);
}

void print_lem(t_mas_ant **ant)
{
	int i;
	int j;
	t_mas_ant *ant1;

	ant1 = *ant;
	i = 0;
	j = 0;
	printf("ants %ld \n",ant1->ants);
	printf("size %d \n",ant1->size);
	while(i < ant1->size - 1)
	{
		while(j < ant1->size - 1)
		{
			if (ant1->variants[i])
			printf("%d ",ant1->variants[i][j]);
			j++;
		}
		printf("\n");
		j=0;
		i++;
	}
}

int **join_res(int *dextr, int next, int **res, int size)
{
	int **res1;
	int i;

	i =0;
	res1 = malloc((next + 3) * sizeof(int*));
	while(i < next)
	{
		res1[i] = malloc(sizeof(int) * size);
		ft_memcpy(res1[i],res[i],sizeof(int) * size);
		i++;
	}
	if (dextr)
	{
		res1[i] = malloc(sizeof(int) * size);
		ft_memcpy(res1[i],dextr,sizeof(int) * size);
		i++;
		res1[i] = NULL;
	}
	else
		res1[i] = NULL;
	free_res(res,next);
	return(res1);
}

void free_ant(t_mas_ant **ant3)
{
	t_mas_ant *ant;
	int i;

	ant = *ant3;
	i = 0;
	while(i < ant->sizm)
	{
		free(ant->variants[i]);
		free(ant->koordinats[i].name);
		i++;
	}
	free(ant->variants);
	free(ant->koordinats);
	free(ant);

}

t_mas_ant *memalloc_ant(t_mas_ant *ant3,int mem)
{
	t_mas_ant *ant_new;
	t_mas_ant *ant;
	int i;

	i = 0;
	ant = ant3;
	ant_new = malloc(sizeof(t_mas_ant));
	ant_new->variants = malloc ((mem)  *sizeof(int*));
	ant_new->koordinats = malloc((mem)  *sizeof(t_kor));
	while (i < mem)
	{
		ant_new->variants[i] = malloc ((mem)  *sizeof(int));
		ft_bzero(ant_new->variants[i],(mem)  *sizeof(int));
		ant_new->koordinats[i].name = ft_strnew(100);
		ant_new->koordinats[i].num = 0;
		ant_new->koordinats[i].level = -1;
		i++;
	}
	i = 0;
	ant_new->ants = ant->ants;
	ant_new->size = ant->size;
	if (mem > ant->sizm)
	{
		while(i < ant->sizm)
		{
			ft_memcpy(ant_new->koordinats[i].name,ant->koordinats[i].name,100);
			ant_new->koordinats[i].num = ant->koordinats[i].num;
			ant_new->koordinats[i].x = ant->koordinats[i].x;
			ant_new->koordinats[i].y = ant->koordinats[i].y;
			i++;
		}
	}
	if (mem > ant->sizm)
		free_ant(&ant);
	ant_new->sizm = mem;
	return(ant_new);
}
void free_res(int **res, int size)
{
	while(size-- >0)
		free(res[size]);
	free(res);
}
int 	check_valid(t_mas_ant *ant)
{
	char *line;
	int i;
	int j;
	int f;

	i = 100;
	j =0;
	f = 0;
	line = NULL;
	if (ant->ants == 0)
		return(1);
	while(i > 0)
	{
		if(get_next_line(0,&line) == 1)
		{
			free(line);
			return(1);
		}
		i--;
	}
	if (ant->koordinats[0].name[0] == '\0' || ant->koordinats[1].name[0] == '\0')
		return(1);
	i = 0;
	while(i < ant->size)
	{
		while(j < ant->size)
		{
			f = f + ant->variants[i][j];
			j++;
		}
		j=0;
		i++;
	}
	if (f == 0)
		return(1);
	return(0);
}

/*int check_ant(t_mas_ant *ant)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while(i < ant->size -1)
	{
		while(j < ant->size - 1)
		{
			if (ant->koordinats[i].x == ant->koordinats[j].x && ant->koordinats[i].y == ant->koordinats[j].y)
				return(1);
			if (ant->koordinats[i].name == ant->)
		}
	}
}*/

void del_level(t_mas_ant *ant)
{
	int i;
	int j;

	i = 1;
	j = 2;
	while (i < ant->size -1)
	{
		while (j < ant->size -1)
		{
			if (ant->variants[i][j] == 1 && ant->koordinats[i].level == ant->koordinats[j].level  && ant->koordinats[i].level > 1)
			{
				ant->variants[i][j] = 0;
				ant->variants[j][i] = 0;
				//printf("del %s  - %s",ant->koordinats[i].name,ant->koordinats[j].name);
			}
			j++;
		}
		j = 0;
		i++;
	}

}

void		find_level(t_mas_ant *ant)
{
	int i;
	int j;
	int k;

	i = 2;
	j = 0;
	k = 1;
	ant->koordinats[1].level = 0;
	while(i < ant->size -1)
	{
		if (ant->variants[1][i] == 1)
			ant->koordinats[i].level = 1;
		i++;
	}
	i = 2;
	while (k < ant->size -1)
	{
		while(i < ant->size - 1)
		{
			if (ant->koordinats[i].level == k)
			{
				j = 0;
				while(j < ant->size - 1)
				{
					if (ant->variants[i][j] == 1 && ant->koordinats[j].level < 1 && j != 1 && j!=0)
					{
						ant->koordinats[j].level = k + 1;
					}
					j++;
				}
			}
			i++;
		}
		k++;
		i = 0;
	}
	del_level(ant);
}
int main(int ac, char **av)
{
	char		*line;
	t_mas_ant	*ant;
	int *dextr;
	int **res;
	int i;
	int size;

	i = 0;

	ant = malloc(sizeof(t_mas_ant));
	ant->size = 2;
	ant->sizm = 1000;
	ant->ants = 0;
	size = 1000;
	ant = memalloc_ant(ant,size);
	while (get_next_line(0,&line) == 1)
	{
		printf("%s\n",line);
		if (ant->ants == 0)
		{
			while(ft_isdigit(line[i]) == 1 && ant->ants < INT16_MAX)
				ant->ants = line[i++] - 48 + ant->ants * 10;
			ant->size = 3;
			if (ant->ants == 0 || ant->ants >= INT16_MAX)
			{
				printf("error");
				return(0);
			}
		}
		else
		{
			parse(&ant,line);
			//if (check_ant(ant) == 1)
			//	return(0);
			if (size < ant->size + 3)
			{
				size = 2 * size;
				ant = memalloc_ant(ant,size);
			}
		}
		free(line);
	}
	if (check_valid(ant) == 1)
	{
		printf("error");
		return(0);
	}
	//print_lem(&ant);           39 
	if (ant->size > 1000)
		find_level(ant);
	dextr = solve(&ant);
	res = NULL;
	i = 0;
	//print_lem(&ant);
	while (dextr != NULL && i < 4 && i < ant->ants)
	{
		res = join_res(dextr,i,res,ant->size);
		dextr = suurbale(&ant,dextr);
		i++;
	}
	res[i] = NULL;
	/*i = 0;
	int kik = 0;
	//print_lem(&ant);
	while(res[i]!= NULL)
	{
		printf(" res %d\n",i);
		while(kik<ant->size -1)
		{
			printf(" %s ",ant->koordinats[res[i][kik]].name);
			kik++;
		}
		i++;
		kik =0;
		printf("\n");
	}*/
	if (i > 1)
		res = find_connect(res,i,ant->size - 1);
	/*i = 0;
	kik = 0;
	printf("POSLE\n");
	while(res[i]!= NULL)
	{
		printf(" res %d\n",i);
		while(kik<ant->size -1)
		{
			printf(" %s ",ant->koordinats[res[i][kik]].name);
			kik++;
		}
		i++;
		kik =0;
		printf("\n");
	}*/
	ants(res,&ant);
	free_ant(&ant);
	free_res(res,i);
	free(dextr);
	return(0);
}
