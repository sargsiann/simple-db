#include "db.h"

void	prompt(t_db *db) 
{
	char	*input = NULL;

	while (1)
	{
		write(1, "db > ", 5);
		input = get_next_line(0);
		parser(input, db);
	}
}