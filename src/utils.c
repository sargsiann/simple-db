#include "db.h"

int mtx_len(char **mtx)
{
	int i;

	i = 0;
	while (mtx[i])
		i++;
	return (i);
}
