#include "lem_in.h"
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
		while(ft_isalpha(line[i]) == 1 || ft_isdigit(line[i]) == 1)
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
	//print_lem(ant);
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
	printf("ants %d \n",ant1->ants);
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
	{
		res1[i] = NULL;
	}
	int kik =0;
	i=0;
	while(res1!=NULL && res1[i] != NULL)
	{
		printf("res_new[i] \n");
		while(kik < size)
		{
			printf(" [ %d ]",res1[i][kik]);
			kik++;
		}
		kik= 0;
		i++;
	}
	return(res1);
}

void free_ant(t_mas_ant **ant3)
{
	t_mas_ant *ant;
	int i;

	ant = *ant3;
	i = 0;
	while(i > ant->size + 3)
	{
		free(ant->variants[i]);
		free(ant->koordinats[i].name);
		i++;
	}
	free(ant->variants);
	free(ant->koordinats);
	free(ant);

}

t_mas_ant *memalloc_ant(t_mas_ant *ant3)
{
	t_mas_ant *ant_new;
	t_mas_ant *ant;
	int i;

	i = 0;
	ant = ant3;
	ant_new = malloc(sizeof(t_mas_ant));
	ant_new->variants = malloc ((ant->size + 2)  *sizeof(int*));
	ant_new->koordinats = malloc((ant->size + 2)  *sizeof(t_kor));
	while (i < ant->size + 2)
	{
		ant_new->variants[i] = malloc ((ant->size + 2)  *sizeof(int));
		ft_bzero(ant_new->variants[i],(ant->size + 2)  *sizeof(int));
		ant_new->koordinats[i].name = malloc(100);
		ft_bzero(ant_new->koordinats[i].name,100);
		ant_new->koordinats[i].num = 0;
		i++;
	}
	i = 0;
	ant_new->ants = ant->ants;
	ant_new->size = ant->size;
	if (ant->size > 2)
	{
		ft_memcpy(ant_new->koordinats,ant->koordinats,(ant->size - 1) * sizeof(t_kor));
		while(i < ant->size-1)
		{
			ft_memcpy(ant_new->koordinats[i].name,ant->koordinats[i].name,100);
			ant_new->koordinats[i].num = ant->koordinats[i].num;
			i++;
		}
	}
	if (ant->size > 2)
	free_ant(&ant);
	return(ant_new);
}

int main(int ac, char **av)
{
	char		*line;
	t_mas_ant	*ant;
	int *dextr;
	int **res;
	int i;
	int k;
	int size;

	i = 0;
	k = 0;

	ant = malloc(sizeof(t_mas_ant));
	ant->size = 2;
	ant->ants = 0;
	ant = memalloc_ant(ant);
	// memalloc_ant(&ant);
	i = 0;
	size = 1;
	while (get_next_line(0,&line) == 1)
	{
		printf("%s\n",line);
		if (ant->ants == 0)
		{
			while(ft_isdigit(line[i]) == 1)
			{
				k = line[i] - 48 + k*10;
				i++;
			}
			ant->ants = k;
			ant->size = 3;
			size = 3;
		}
		else
		{
			parse(&ant,line);
			if (size < ant->size)
			{
				size = ant->size;
				ant = memalloc_ant(ant);

			}
		}
		free(line);
		//print_lem(&ant);
	}
	i=0;
	//print_lem(&ant);
	dextr = solve(&ant);
	int kik =0;
	res = NULL;
	i = 0;
	//printf("\n");
	while (dextr != NULL)
	{
		res = join_res(dextr,i,res,ant->size);

		dextr = suurbale(&ant,dextr);
		i++;
	}

	res[i] = NULL;
	/*kik =0;
	i=0;
	while(res!=NULL && res[i] != NULL)
	{
		printf("res[i] \n");
		while(kik < ant->size)
		{
			printf(" [ %d ]",res[i][kik]);
			kik++;
		}
		kik= 0;
		i++;
	}*/
	if (i > 1)
		res = find_connect(res,i,ant->size - 1);
	/*i =0;
	kik =0;
	while(res!=NULL && res[i] != NULL)
	{
		printf("\n");
		while(kik < ant->size)
		{
			printf(" [ %d ]",res[i][kik]);
			kik++;
		}
		kik= 0;
		i++;
	}*/
	ants(res,&ant);
	return(0);
}
