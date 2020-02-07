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
	while(i<ant1->size)
	{
		if(ft_strequ(ant1->koordinats[i].name,name1) == 1)
			num1 = ant1->koordinats[i].num;
		if(ft_strequ(ant1->koordinats[i].name,name2) == 1)
			num2 = ant1->koordinats[i].num;
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
			printf("| line %s\n",line);
			parse_line(ant,line,1);
		}else
		{
			if (ft_strequ(s,"##end") == 1)
			{
				get_next_line(0,&line);
				printf("| line %s\n",line);
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
	while(i < 11)
	{
		while(j < 11)
		{
			printf("%d ",ant1->variants[i][j]);
			j++;
		}
		printf("\n");
		j=0;
		i++;
	}
	i = 0;
	printf("\n");
	printf("ants %d\n",ant1->ants);
	printf("size %d\n",ant1->size);
	while (i < 11)
	{

		printf("name %s| num %d | coor x %d | coor y %d\n",ant1->koordinats[i].name,ant1->koordinats[i].num,ant1->koordinats[i].x,ant1->koordinats[i].y);
		i++;
	}


}

int main(int ac, char **av)
{
	char		*line;
	t_mas_ant	*ant;

	int i;
	int k;

	i = 0;
	k = 0;
	ant = malloc(sizeof(t_mas_ant));
	ant->names = malloc(20* sizeof(t_sootv));
	ant->variants = malloc (20 *sizeof(int*));
	ft_bzero(ant->variants,20 *sizeof(int*));
	ant->koordinats = malloc(20 *sizeof(t_kor));
	ant->size = 2;
	while(i < 11)
	{
		ant->koordinats[i].name = (char*)malloc(100);
		ant->names[i].name = (char*)malloc(100);
		ant->variants[i] = malloc(20 * sizeof(int));
		ft_bzero(ant->variants[i],20 *sizeof(int));
		i++;
	}
	i = 0;
	write(1,"f",1);
	while (get_next_line(0,&line) == 1)
	{
		printf("| line %s\n",line);
		if (ant->size == 2)
		{
			while(ft_isdigit(line[i]) == 1)
			{
				k = line[i] - 48 + k*10;
				i++;
			}
			ant->ants = k;
			ant->size = 3;
		}
		else
		{
			parse(&ant,line);
		}
		free(line);
	}
	print_lem(&ant);
	solve(&ant);
	return(0);
}
