#include "db.h"

// WE GOT TWO STATIC VARIABLES TO NOT LOST VALUES AFTER FUNC CALL
static int	data_index = -1;
static int	table_index = -1;


void	init_db(t_db **db, char *input) 
{
	if (!input)
		return ;
	// DB_NAME LINE SAYS WE GOT DB ITS NAME 
	if (ft_strncmp(input,"DB_NAME:",8) == 0)
	{
		(*db) = malloc(sizeof(t_db));
		(*db)->name = ft_substr(strdup(input + 8),0,ft_strlen(input + 8) - 1,1);
		(*db)->tables = NULL;
		(*db)->capacity = 1024;
		(*db)->size = 0;
	}
	else if (ft_strncmp(input,"TABLE_COUNT:",12) == 0)
	{
		// INITING SIZE AND TABLES ARRAY BY TABLE COUNT
		(*db)->size = atoi(input + 12);
		(*db)->tables = malloc(sizeof(t_table *) * (*db)->size);
	}
	else if (ft_strncmp(input,"TABLE_NAME:",11) == 0) {
		// INCREMENTING TABLE_INDEX TO KNOW WHAT TABLE ARE WE IN FOR STORING DATAS EACH TIME WE HAVE TABLE NAME WE INCREMENT INDEX
		table_index++;
		// RESETING DATA INDEX BECAUSE EVERY TABLE STARTS FROM 0 INDEX
		data_index = -1;
		(*db)->tables[table_index] = malloc(sizeof(t_table));	
		(*db)->tables[table_index]->capacity = 1024;
		(*db)->tables[table_index]->size = 0;
		(*db)->tables[table_index]->name = ft_substr(strdup(input + 11),0,ft_strlen(input + 11) - 1,1);
	}
	else if (ft_strncmp(input,"DATA_COUNT:",11) == 0) {

		// GETTING DATA ARRAY FOR EXACT TABLE IN OUR TABLES ARRAY
		int	size = atoi(input + 11);
		(*db)->tables[table_index]->size = size;
		(*db)->tables[table_index]->datas = malloc(sizeof(t_data *) * size);
	}
	else if (ft_strncmp(input,"VALUE:",6) == 0) {

		// INITING VALUE FOR EXACT DATA OF EXACT TABLE AND INCREMENTING DATA INDEX
		t_data *d = malloc(sizeof(t_data));

		// PART OF CODE FOR RIGHT MEM MENEGMENT
		char **users = ft_split(input + 6,',');

		free_mtx(users);

		data_index++;
		(*db)->tables[table_index]->datas[data_index] = d;
	}
}

void	get_db_info(t_db **db, char *db_file) 
{
	// OPENING FILE
	int fd = open(db_file,O_RDONLY);
	char *input = NULL;


	if (fd < 0) {
		write(2,"INVALID DB TO READ FROM \n",26);
		exit(1);
	}

	// GOING THROUGH EACH LINE IN DB
	while (1)
	{
		input = get_next_line(fd);

		// IF WE GOT TO END BREAKING
		if (!input)
			break;

		// INITING DB BY EACH LINE IN FILE (SPECIFIED OUR FORMAT)
		init_db(db,input);

		// FREE IN EACH LINE 
		free(input);
	}
	close(fd);
}