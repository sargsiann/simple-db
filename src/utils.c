#include "db.h"

int mtx_len(char **mtx)
{
	int i;

	i = 0;
	while (mtx[i])
		i++;
	return (i);
}

void	free_mtx(char **mtx)
{
	int i;

	i = 0;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}

void	free_datas(t_data **data) {
	int i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		free_mtx(data[i]->users);
		i++;
	}
	free(data);
}

void	free_table(t_table *table)
{
	int i;

	i = 0;
	if (table->datas != NULL)
		free_datas(table->datas);
	free(table->name);
	free(table);
}

void	free_tables(t_db *db)
{
	int i;

	i = 0;
	if (db->tables == NULL)
		return ;
	while (i < db->size)
	{
		free_table(db->tables[i]);
		i++;
	}
	free(db->tables);
}

void	free_db(t_db *db)
{
	free(db->name);
	free_tables(db);
	free(db);
}