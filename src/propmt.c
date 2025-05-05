#include "db.h"

void	prompt() 
{
	char	*input = NULL;
	t_db	**db = malloc(sizeof(t_db *));


	while (1)
	{
		write(1, "db > ", 5);
		input = get_next_line(0);
		if (ft_strcmp(input, "exit\n") == 0)
		{
			free(input);
			break ;
		}
		if (ft_strcmp(input,"\n") == 0) {
			free(input);
			continue;
		}
		// FOR DB SAVEING TO FILE
		if (ft_strcmp(input, "save") == 0)
			;
		parser(input,db);
	}
}