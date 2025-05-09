#include "db.h"

void	cleanup(t_db **db, int to_exit) 
{
	if (!db) {
		if (to_exit)
			exit(0);
		return ;
	}

	if (!(*db)) {
		free(db);
		if (to_exit)
			exit(0);
		return ;
	}

	for (int i = 0; i < (*db)->size; i++) 
	{
		// FOR FREEING EXACT TABLE OF DB

		t_table *tmp_table = (*db)->tables[i];

		// FREEING NAME
		free(tmp_table->name);

		// IF WE HAVE NO DATAS IN THAT TABLE CONTINUEING
		if (!tmp_table->datas) {
			free(tmp_table);
			continue;
		}

		// FREEING DATAS
		for (int j = 0; j < tmp_table->size; j++) 
		{
			t_data *tmp_data = tmp_table->datas[j];
			
			// FREEING USERS MATRIX OF DATA
			// free_mtx(tmp_data->users);

			// FREEING POINTER TO THAT DATA
			free(tmp_data);
		}
		// FREEING DOUBLE POINTER TO DATA_VECTOR
		free(tmp_table->datas);

		// FREEING EXACT POINTER OF TABLE
		free(tmp_table);
	}

	// CLEANING DOUBLE POINTER TO TABLES
	if ((*db)->tables)
		free((*db)->tables);
	
	// AFTER CLEANING POINTER TO MAIN DB
	free((*db)->name);
	free(*db);

	// AFTER CLEANING DOUBLE POINTER OF DB
	free(db);

	if (to_exit)
		exit(0);
}

void	prompt(char **argv) 
{
	// INPUT GETTING FROM OUT GNL LIB
	char	*input = NULL;
	t_db	**db = malloc(sizeof(t_db *));

	*db = NULL;
	
	// IF WE HAVE AN DB SELECTED FOR WORKING IF NOT BY DEFAULT OUR DB IS NULL
	if (argv[1] != NULL) {
		get_db_info(db, argv[1]);
		cleanup(db,0);
	}
	/*while (1)
	{
		// GETTING OUR LINE
		write(1, "db > ", 5);

		input = get_next_line(0);
		if (ft_strcmp(input,"\n") == 0) {
			
			// IF WE PRESSED ENTER (NEWLINE)
			free(input);
			continue;
		}

		// PARSING THE LINE
		parser(input,db);
	}*/
}