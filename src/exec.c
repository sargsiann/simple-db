#include "db.h"

// CREATE DB, TABLE + 
// DROP DB, TABLE WHERE ID == +
// INSERT INTO TABLE (ID) VALUES VALUE,USER1,USER2 + 
// DELETE FROM TABLE WHERE ID == +
// UPDATE FROM TABLE WHERE ID == VALUES (VALUE, USERS)
// SHOW (TABLE_ID) OR *(ALL) + 
// SAVE (NAME OF FILE) + 

// CREATING DB

void	create_database(t_db **db, char *name) {
	// IF WE HAVE DB SELECTED WE CANT CREATE ANOTHER ONE
	if ((*db) != NULL)
	{
		write(2, "YOU HAVE ALREADY DB\n",21);
		return ;
	}
	*db = malloc(sizeof(t_db));
	(*db)->size = 0;
	(*db)->capacity = 1024;
	(*db)->tables = NULL;
	// DUPING NAME FROM QUERRY
	(*db)->name = strdup(name);
}

void	show_table(t_db **db, char *arg)
{
	if (!db || !*db) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}

	if (ft_strcmp(arg, "*") == 0) 
		print_db(*db);	
	else 
		print_table_data((*db)->tables[atoi(arg)],atoi(arg));
}

void	save_db_to_file(char *filename, t_db *db) 
{
	if (!db) {
		write(2, "NO DATABASE TO SAVE\n", 21);
		return;
	}

	if (!db->tables || db->size == 0) {
		write(2, "NO TABLES TO SAVE\n", 18);
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
		if (!table) continue;

		fprintf(file, "TABLE_NAME:%s\n", table->name);
		fprintf(file, "DATA_COUNT:%d\n", table->size);

		if (!table->datas || table->size == 0)
			continue;

		for (int j = 0; j < table->size; j++) {
			t_data *data = table->datas[j];
			if (!data) continue;

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

// CREATING TABLE FOR DB
void	create_table(t_db **db, char *name) 
{
	// IF WE DONT HAVE DB CANT CREATE TABLE
	if (db == NULL || *db == NULL) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}

	// IF WE HAVE MORE TABLES THEN CAPACITY
	int s = (*db)->size + 1;
	if (s > (*db)->capacity) {
		write(2, "DATABASE IS FULL\n", 18);
		return;
	}
	(*db)->size++;

	// CREATING NEW ARRAY FOR TABLES BY ONE SIZE BIGGER AND NEW TABLE
	t_table **new_tables = malloc(sizeof(t_table *) * (*db)->size);
	t_table *new_table = malloc(sizeof(t_table));
	new_table->name = strdup(name);
	new_table->datas = NULL;
	new_table->size = 0;
	new_table->capacity = 1024;

	// PUTTING FROM OLD DB TO THIS LAST TABLE IS NEW CREATED
	for (int i = 0; i < (*db)->size - 1; i++)
		new_tables[i] = (*db)->tables[i];
	new_tables[(*db)->size - 1] = new_table;

	// FREEING POINTER 
	free((*db)->tables);
	(*db)->tables = new_tables;
}

void	drop_db(t_db **db, char *name) 
{
	// IF WE HAVE NOT DB CANT DROP
	if (!*db && ft_strcmp((*db)->name,name) != 0) {
		write(2,"NO DB INVALID DB SELECTED\n",16);
		return ;
	}
	// ELSE DROPING 
	cleanup(db,0);
}

void	drop_table(t_db **db, int id) 
{
	// SO DOING FOR TABLE
	if (*db == NULL) {
		write(2, "NO DATABASE SELECTED\n", 22);
		return;
	}
	if (id < 0 || id >= (*db)->size) {
		write(2, "TABLE ID OUT OF RANGE\n", 23);
		return;
	}

	// CREATING NEW ARRAY BY ONE SIZE LOWER
	if ((*db)->size - 1 < 0) {
		free_tables((*db));
		return ;
	}
	t_table **new_tables = malloc(sizeof(t_table *) * ((*db)->size - 1));
	if (!new_tables)
		return;

	
	int j = 0;
	for (int i = 0; i < (*db)->size; i++) {
		// WHEN WE GOT TO THAT EXACT ID WE SKIP
		if (i == id) {
			free_table((*db)->tables[i]);
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
	// INSERTING
	if (!*db)
	{
		write(2,"NO DB\n",6);
		return;
	}
	if (id < 0 || id >= (*db)->size) {
		write(2, "TABLE ID OUT OF RANGE\n", 23);
		return;
	}


	t_data *data = malloc(sizeof(t_data));
	data->value = atof(v);

	// GOING TO USERS PART AND GETTING USERS
	int i = 0;
	for (;v[i] && v[i] != ',';i++)
			;
	data->users = ft_split(v + i + 1,',');


	t_table *table = (*db)->tables[id];

	if (table->size >= table->capacity)
	{
		write(2, "TABLE IS FULL\n", 15);
		return;
	}

	// creating NEW ARRAY FOR DATAS BY ONE SIZE BIGGER
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


	// IF OUR SIZE IS ONE JUST PUTTING NULL TO IT
	if (table->size == 1) {
		free_datas(table->datas, table->size);
		table->datas = NULL;
		table->size = 0;
		return;
	}

	free_mtx(table->datas[data_id]->users);
	free(table->datas[data_id]);

	// ELSE CREATING NEW DATAS BY ONE SIZE LOWER
	t_data **new_datas = malloc(sizeof(t_data *) * (table->size - 1));
	if (!new_datas)
		return;

		// DOING SAME THING
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


	t_data *data = table->datas[data_id];
	int i = 0;
	for (;v[i] && v[i] != ',';i++)
				;
	data->value = atof(v);
	free_mtx(data->users);
	data->users = ft_split(v + i + 1,',');
}

// AFTER VALIDATION IT COMES TO EXECUTION

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
}