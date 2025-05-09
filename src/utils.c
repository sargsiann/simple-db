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

void	free_datas(t_data **data, int size) {
	int i;

	i = 0;
	while (i < size)
	{
		free_mtx(data[i]->users);
		free(data[i]);
		i++;
	}
	free(data);
}

void	free_table(t_table *table)
{
	if (table->datas != NULL)
		free_datas(table->datas, table->size);
	free(table->name);
	free(table);
}

void	free_tables(t_db *db)
{
	if (db->tables == NULL)
		return ;
	int i = 0;
	while (i < db->size)
	{
		free_table(db->tables[i]);
		i++;
	}
	free(db->tables);
}
