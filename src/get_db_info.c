#include "db.h"

static int	data_index = 0;
static int	table_index = 0;

void	init_db(t_db **db, char *input) 
{
	if (!input)
		return ;
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
		(*db)->size = atoi(input + 12);
		(*db)->tables = malloc(sizeof(t_table *) * (*db)->size);
	}
	else if (ft_strncmp(input,"TABLE_NAME:",11) == 0) {
		data_index = 0;
		(*db)->tables[table_index] = malloc(sizeof(t_table));
		(*db)->tables[table_index]->capacity = 1024;
		(*db)->tables[table_index]->size = 0;
		(*db)->tables[table_index]->name = ft_substr(strdup(input + 11),0,ft_strlen(input + 11) - 1,1);
		table_index++;
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
		if (!input)
			break;
		printf("%s",input);
		init_db(db,input);
		free(input);
	}
	print_db(*db);
	close(fd);
}