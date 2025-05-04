#include "db.h"

void	print_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		printf("%s\n", mtx[i]);
		i++;
	}
}

