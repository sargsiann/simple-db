#include "db.h"

void	parser(char *input, t_db **db) 
{
	// DELETING \N FROM INPUT
	input = ft_substr(input, 0, ft_strlen(input) - 1,0);
	
	// CHECKING EXIT COMMAND

	if (ft_strcmp(input,"EXIT") == 0)
	{
		free(input);
		if (db != NULL)
			cleanup(db,1);
	}

	// SPLITTING INPUT
	char	**querry = ft_split(input, ' ');
	
	// VALIDATING INPUT
	if (validation(querry) == 0)
	{
		free(input);
		free_mtx(querry);
		return ;
	}
	
	exec(querry, db);
	
	// FREEING MEMORY
	free(input);
	free_mtx(querry);
}