#include "db.h"

// CREATE DB, TABLE + 
// DROP DB, TABLE WHERE ID == +
// INSERT INTO TABLE (ID) VALUES VALUE,USER1,USER2 + 
// DELETE FROM TABLE WHERE ID == 
// UPDATE FROM TABLE WHERE ID == VALUES (VALUE, USERS)

void	create_database(t_db **db, char *name) {
	if ((*db) != NULL)
	{
		write(2, "YOU HAVE ALREADY DB\n",21);
		return ;
	}
	*db = malloc(sizeof(t_db));
	(*db)->size = 0;
	(*db)->capacity = 1024;
	(*db)->tables = NULL;
	(*db)->name = strdup(name);
}

void	create_table(t_db **db, char *name) 
{
	if (*db == NULL) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}
	int s = (*db)->size + 1;
	if (s > (*db)->capacity) {
		write(2, "DATABASE IS FULL\n", 18);
		return;
	}
	(*db)->size++;
	t_table **new_tables = malloc(sizeof(t_table *) * (*db)->size);
	t_table *new_table = malloc(sizeof(t_table));
	new_table->name = strdup(name);
	new_table->datas = NULL;
	new_table->size = 0;
	new_table->capacity = 1024;
	for (int i = 0; i < (*db)->size - 1; i++)
		new_tables[i] = (*db)->tables[i];
	new_tables[(*db)->size - 1] = new_table;
	free((*db)->tables);
	(*db)->tables = new_tables;
}

void	drop_db(t_db **db, char *name) 
{
	if (!*db && ft_strcmp((*db)->name,name) != 0) {
		write(2,"NO DB INVALID DB SELECTED\n",16);
		return ;
	}
	free((*db)->name);
	free_tables((*db));
	free((*db));
	*db = NULL;
}

void	drop_table(t_db **db, int id) 
{
	if (*db == NULL) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}
	if (id < 0 || id >= (*db)->size) {
		write(2, "TABLE ID OUT OF RANGE\n", 23);
		return;
	}

	t_table **new_tables = malloc(sizeof(t_table *) * ((*db)->size - 1));
	if (!new_tables)
		return;

	int j = 0;
	for (int i = 0; i < (*db)->size; i++) {
		if (i == id) {
			free((*db)->tables[i]->name);
			free((*db)->tables[i]);
			continue;
		}
		new_tables[j++] = (*db)->tables[i];
	}
	free((*db)->tables);
	(*db)->tables = new_tables;
	(*db)->size--;
}

void	insert_to_table(t_db **db, int id, char *v) 
{
	if (!*db)
	{
		write(2,"NO DB\n",6);
		return;
	}
	if (id < 0 || id >= (*db)->size) {
		write(2, "TABLE ID OUT OF RANGE\n", 23);
		return;
	}

	char **values = ft_split(v, ',');

	t_data *data = malloc(sizeof(t_data));
	data->value = atof(values[0]);
	data->users = values + 1;

	t_table *table = (*db)->tables[id];

	if (table->size >= table->capacity)
	{
		write(2, "TABLE IS FULL\n", 15);
		return;
	}

	t_data **new_datas = malloc(sizeof(t_data *) * (table->size + 1));
	for (int i = 0; i < table->size; i++)
		new_datas[i] = table->datas[i];
	new_datas[table->size] = data;

	free(table->datas);
	table->datas = new_datas;
	table->size++;
}

void	exec(char **querry, t_db **db) {
	if (ft_strcmp(querry[0],"CREATE") == 0) 
	{
		if (ft_strcmp(querry[1],"DATABASE") == 0)
			create_database(db, querry[2]);
		if (ft_strcmp(querry[1],"TABLE") == 0)
			create_table(db,querry[2]);
	}
	if (ft_strcmp(querry[0],"DROP") == 0) {
		if (ft_strcmp(querry[1],"DATABASE") == 0) 
			drop_db(db,querry[1]);
		if (ft_strcmp(querry[1],"TABLE") == 0)
			drop_table(db,atoi(querry[5]));
	}
	if (ft_strcmp(querry[0],"INSERT") == 0)
		insert_to_table(db,atoi(querry[2]),querry[4]);
	print_db(*db);
}