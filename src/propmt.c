#include "db.h"

void	prompt() 
{
	char	*input = NULL;
	t_db	*db = NULL;


	while (1)
	{
		write(1, "db > ", 5);
		input = get_next_line(0);
		if (ft_strcmp(input, "exit\n") == 0)
		{
			free(input);
			break ;
		}
		// FOR DB SAVEING TO FILE
		if (ft_strcmp(input, "save") == 0)
			;
		db = parser(input);
	}
}