#include "db.h"

t_db	*parser(char *input) 
{
	// DELETING \N FROM INPUT
	input = ft_substr(input, 0, ft_strlen(input) - 1,1);
	
	if (!input)
		return ;
	
		// SPLITTING INPUT
	char	**querry = ft_split(input, ' ');
	
	// VALIDATING INPUT
	if (validation(querry) == 0)
	{
		free(input);
		free_mtx(querry);
		return ;
	}
	
	// GETTING STRUCT TO EXECUTE
	exec(querry);



	// FREEING MEMORY
	free(input);
	free_mtx(querry);
}