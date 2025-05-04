#include "db.h"

void	create_table(char **querry, t_db *db) {
	
	if (!db) {
		write(2, "NO DB SELECTED\n", 16);
		return ;
	}
	db->size++;
	if (db->size > db->capacity)
		write(2, "DB FULL\n", 8);

	t_table *table = (t_table *)malloc(sizeof(t_table));
	table->capacity = 1024;
	table->size = 0;

	t_table **new_tables = (t_table **)malloc(sizeof(t_table *) * db->capacity);
	for (int i = 0; i < db->size - 1; i++)
		new_tables[i] = db->tables[i];
	new_tables[db->size - 1] = table;
	db->tables = new_tables;
}

void	create_database(char **querry, t_db **db) {
	t_db *new_db = (t_db *)malloc(sizeof(t_db));
	new_db->capacity = 1024;
	new_db->size = 0;
	new_db->tables = NULL;
	*db = new_db;
}



void	exec(char **querry, t_db *db) 
{
	if (ft_strcmp(querry[0], "CREATE") == 0)
	{
		if (ft_strcmp(querry[1], "TABLE") == 0)
			create_table(querry, db);
		else if (ft_strcmp(querry[1], "DATABASE") == 0)
			create_database(querry, &db);
	}
	
}
