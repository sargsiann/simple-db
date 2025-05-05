#include "db.h"

// CREATE DB, TABLE + 
// DROP DB, TABLE WHERE ID == +
// INSERT INTO TABLE (ID) VALUES VALUE,USER1,USER2 + 
// DELETE FROM TABLE WHERE ID == +
// UPDATE FROM TABLE WHERE ID == VALUES (VALUE, USERS)
// SHOW (TABLE_ID) OR *(ALL)
// SAVE (NAME OF FILE)

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

void	show_table(t_db **db, char *arg)
{
	if (!*db) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}

	if (ft_strcmp(arg, "*") == 0) 
		print_db(*db);	
	else 
		print_table_data((*db)->tables[atoi(arg)]);
}

void	save_db_to_file(char *filename, t_db *db) 
{
	if (!db) {
		write(2, "NO DATABASE TO SAVE\n", 21);
		return;
	}

	FILE *file = fopen(filename, "w");
	if (!file) {
		perror("fopen");
		return;
	}

	fprintf(file, "DB_NAME:%s\n", db->name);
	fprintf(file, "TABLE_COUNT:%d\n", db->size);

	for (int i = 0; i < db->size; i++) {
		t_table *table = db->tables[i];
		fprintf(file, "TABLE_NAME:%s\n", table->name);
		fprintf(file, "DATA_COUNT:%d\n", table->size);

		for (int j = 0; j < table->size; j++) {
			t_data *data = table->datas[j];
			fprintf(file, "VALUE:%.2f", data->value);
			if (data->users) {
				for (int k = 0; data->users[k]; k++) {
					fprintf(file, ",%s", data->users[k]);
				}
			}
			fprintf(file, "\n");
		}
	}

	fclose(file);
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

void	delete_from_table(t_db **db, int table_id, int data_id)
{
	if (!*db) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}
	if (table_id < 0 || table_id >= (*db)->size) {
		write(2, "TABLE ID OUT OF RANGE\n", 23);
		return;
	}

	t_table *table = (*db)->tables[table_id];
	if (data_id < 0 || data_id >= table->size) {
		write(2, "DATA ID OUT OF RANGE\n", 22);
		return;
	}

	free(table->datas[data_id]);

	if (table->size == 1) {
		free(table->datas);
		table->datas = NULL;
		table->size = 0;
		return;
	}

	t_data **new_datas = malloc(sizeof(t_data *) * (table->size - 1));
	if (!new_datas)
		return;

	int j = 0;
	for (int i = 0; i < table->size; i++) {
		if (i == data_id)
			continue;
		new_datas[j++] = table->datas[i];
	}

	free(table->datas);
	table->datas = new_datas;
	table->size--;
}

void	update_in_table(t_db **db, int table_id, int data_id, char *v)
{
	if (!*db) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}
	if (table_id < 0 || table_id >= (*db)->size) {
		write(2, "TABLE ID OUT OF RANGE\n", 23);
		return;
	}

	t_table *table = (*db)->tables[table_id];
	if (data_id < 0 || data_id >= table->size) {
		write(2, "DATA ID OUT OF RANGE\n", 22);
		return;
	}

	char **values = ft_split(v, ',');
	if (!values)
		return;

	t_data *old_data = table->datas[data_id];
	free(old_data);

	t_data *new_data = malloc(sizeof(t_data));
	if (!new_data)
		return;

	new_data->value = atof(values[0]);
	new_data->users = values + 1;

	table->datas[data_id] = new_data;
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
	if (ft_strcmp(querry[0], "DELETE") == 0)
		delete_from_table(db, atoi(querry[2]), atoi(querry[6]));
	if (ft_strcmp(querry[0], "SET") == 0)
		update_in_table(db, atoi(querry[1]), atoi(querry[7]), querry[3]);
	if (ft_strcmp(querry[0],"SHOW") == 0)
		show_table(db,querry[1]);
	if (ft_strcmp(querry[0],"SAVE") == 0)
		save_db_to_file(querry[1],*db);
	print_db(*db);
}