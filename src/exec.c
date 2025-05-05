#include "db.h"

void	create_table(char **querry, t_db **db) {
	t_table *new_table = (t_table *)malloc(sizeof(t_table));
	new_table->name = strdup(querry[2]);
	new_table->capacity = 1024;
	new_table->size = 0;
	new_table->datas = NULL;

	if (*db == NULL)
	{
		write(2, "NO DATABASE SELECTED\n", 22);
		return ;
	}
	else
	{
		(*db)->size++;
		if ((*db)->size > (*db)->capacity)
		{
			write(2, "DB IS FULL\n", 12);
			return ;
		}
		t_table **new_tables = (t_table **)malloc(sizeof(t_table *) * ((*db)->size));
		for (int i = 0; i < (*db)->size - 1; i++)
			new_tables[i] = (*db)->tables[i];
		new_tables[(*db)->size - 1] = new_table;
		free_tables((*db));
		(*db)->tables = new_tables;
	}
}

void	create_database(char **querry, t_db **db) {
	t_db *new_db = (t_db *)malloc(sizeof(t_db));
	new_db->name = strdup(querry[2]);
	new_db->capacity = 1024;
	new_db->size = 0;
	new_db->tables = NULL;
	*db = new_db;
}



void	exec(char **querry, t_db **db) 
{
	if (ft_strcmp(querry[0], "CREATE") == 0)
	{
		if (ft_strcmp(querry[1], "TABLE") == 0)
			create_table(querry, db);
		if (ft_strcmp(querry[1], "DATABASE") == 0)
			create_database(querry, db);
		print_db(*db);
	}
	
}
