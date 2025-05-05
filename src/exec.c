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
		// free_tables((*db));
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

void	drop_table(t_db **db, char *table_name) {
	int i = 0;
	while (i < (*db)->size)
	{
		if (strcmp((*db)->tables[i]->name, table_name) == 0)
		{
			free_table((*db)->tables[i]);
			for (int j = i; j < (*db)->size - 1; j++)
				(*db)->tables[j] = (*db)->tables[j + 1];
			(*db)->size--;
			return ;
		}
		i++;
	}
}

void	drop_database(t_db **db, char *db_name) {
	if (strcmp((*db)->name, db_name) == 0)
	{
		free_tables(*db);
		free((*db)->name);
		free(*db);
		*db = NULL;
	}
}


void	show_table(t_db **db, char *table_name) {
	int i = 0;
	if (*db == NULL)
	{
		write(2, "NO DATABASE SELECTED\n", 22);
		return ;
	}
	if (ft_strcmp(table_name, "*") == 0)
	{
		print_db(*db);
		return ;
	}
	while (i < (*db)->size)
	{
		if (strcmp((*db)->tables[i]->name, table_name) == 0)
		{
			print_table_data((*db)->tables[i]);
			return ;
		}
		i++;
	}
	write(2, "TABLE NOT FOUND\n", 16);
}

void	insert_data(t_db **db, char *table_name, char *data) {
	int i = 0;
	
	data = ft_substr(data, 1, ft_strlen(data) - 2, 0);

	data = ft_split(data, ',');
	t_data *new_data = (t_data *)malloc(sizeof(t_data));
	new_data->value = atof(data[0]);
	new_data->users = (char **)malloc(sizeof(char *) * (mtx_len(data) - 1));
	for (int j = 1; j < mtx_len(data); j++)
	{
		new_data->users[j - 1] = strdup(data[j]);
	}
	new_data->users[mtx_len(data) - 1] = NULL;

	while (i < (*db)->size)
	{
		if (ft_strcmp((*db)->tables[i]->name, table_name) == 0)
		{
			(*db)->tables[i]->size++;
			if ((*db)->tables[i]->size > (*db)->tables[i]->capacity)
			{
				write(2, "TABLE IS FULL\n", 14);
				return ;
			}
			t_table **new_table = (t_table **)malloc(sizeof(t_table *) * ((*db)->tables[i]->size + 1));
			for (int j = 0; j < (*db)->tables[i]->size; j++)
				new_table[j] = (*db)->tables[i]->datas[j];
			new_table[(*db)->tables[i]->size] = new_data;
			(*db)->tables[i]->datas = new_table;
			return ;
		}
		i++;
	}
}


void	exec(char **querry, t_db **db) 
{
	if (ft_strcmp(querry[0], "CREATE") == 0)
	{
		if (ft_strcmp(querry[1], "TABLE") == 0)
			create_table(querry, db);
		if (ft_strcmp(querry[1], "DATABASE") == 0)
			create_database(querry, db);
	}
	if (ft_strcmp(querry[0], "DROP") == 0)
	{
		if (ft_strcmp(querry[1], "TABLE") == 0)
			drop_table(db, querry[2]);
		if (ft_strcmp(querry[1], "DATABASE") == 0)
			drop_database(db, querry[2]);
	}
	if (ft_strcmp(querry[0], "INSERT") == 0)
	{
		insert_data(db, querry[2], querry[4]);
	}
	print_db(*db);
}
