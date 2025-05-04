#include "db.h"

void	parser(char *input, t_db *db) 
{
	// DELETING \N FROM INPUT
	input = ft_substr(input, 0, ft_strlen(input) - 1,1);
	
	if (!input)
		return ;
	// SPLITTING INPUT
	char	**querry = ft_split(input, ' ');
	
	// VALIDATING INPUT
	validation(querry);
}