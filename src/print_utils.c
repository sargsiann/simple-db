#include "db.h"

void	print_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		printf("%s\n", mtx[i]);
		i++;
	}
}

void	print_data(t_data *data, int index)
{
	printf("DATA %d\n", index);
	printf("%f\n", data->value);
	for (int i = 0; data->users[i]; i++) {
		printf("%s ",data->users[i]);
	}
	printf("\n\n");
}

void	print_datas(t_data **datas, int size)
{
	int	i;

	i = 0;
	if (datas == NULL || *datas == NULL)
	{
		return ;
	}
	printf("%s",BLUE);
	printf("------------------------\n");
	printf("%s",RESET);
	while (i < size)
	{
		print_data(datas[i], i);
		i++;
	}
	printf("%s",BLUE);
	printf("------------------------\n");
	printf("%s",RESET);
}


void	print_table_data(t_table *table, int index)
{	
	printf("%s",RED);
	printf("------------------------\n");
	printf("%s",RESET);
	printf("TABLE %d %s\n",index, table->name);
	printf("TABLE SIZE %d\n", table->size);
	print_datas(table->datas, table->size);
	printf("%s",RED);
	printf("------------------------\n");
	printf("%s",RESET);
}


void	print_db(t_db *db)
{
	int	i;

	i = 0;
	if (db == NULL)
	{
		printf("NO DB SELECTED\n");
		return ;
	}
	printf("%s",GREEN);
	printf("------------------------\n");
	printf("%s",RESET);
	printf("DB NAME %s\n", db->name);
	printf("DB SIZE %d\n", db->size);
	while (i < db->size && db->tables)
	{
		print_table_data(db->tables[i], i);
		i++;
	}
	printf("%s",GREEN);
	printf("------------------------\n");
	printf("%s",RESET);
}