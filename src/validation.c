#include "db.h"

// DROP CREATE DROP +
// INSERT +
// UPDATE +
// DELETE +
// SHOW (showing all db if * else db)

// SELECT (in feature)

static int	validate_create_done(char **querry) 
{
	if (ft_strcmp(querry[1],"TABLE") != 0 && ft_strcmp(querry[1],"DATABASE") != 0)
	{
		write(2,"INVALID ARGUMENT TO DELETE OR DROP\n",36);
		return (0);
	}
	if (querry[2] == NULL && ft_strcmp(querry[2],"*") == 0)
	{
		write(2,"INVALID DB OR TABLE NAME\n",26);
		return (0);
	}
	return (1);
}

static int validate_delete(char **querry) 
{
	if (ft_strcmp(querry[1],"FROM") != 0) {
		write(2,"INVALID STRUCTURE OF DELETE\n",29);
		return 0;
	}
	if (!querry[2]) {
		write(2,"NO TABLE NAME PROVIDED\n",24);
		return 0;
	}
	if (ft_strcmp(querry[3],"WHERE") != 0) {
		write(2,"INVALID STRUCTURE OF DELETE\n",29);
		return 0;
	}
	if (!querry[4]) {
		write(2,"NO CONDITION PROVIDED\n",22);
		return 0;
	}
}

static int validate_show(char **querry) 
{
	if (querry[1] == NULL)
	{
		write(2,"INVALID ARGUMENT TO SHOW\n",25);
		return (0);
	}
	if (querry[2] != NULL)
	{
		write(2,"INVALID ARGUMENT TO SHOW\n",25);
		return (0);
	}
	return (1);
}

static int validate_update(char **querry) 
{
	if (ft_strcmp(querry[1],"SET") != 0) {
		write(2,"INVALID STRUCTURE OF UPDATE\n",29);
		return 0;
	}
	if (!querry[2]) {
		write(2,"NO TABLE NAME PROVIDED\n",24);
		return 0;
	}
	if (ft_strcmp(querry[3],"WHERE") != 0) {
		write(2,"INVALID STRUCTURE OF UPDATE\n",29);
		return 0;
	}
	if (!querry[4]) {
		write(2,"NO CONDITION PROVIDED\n",22);
		return 0;
	}
	if (ft_strcmp(querry[5],"VALUES") != 0) {
		write(2,"INVALID STRUCTURE OF UPDATE\n",29);
		return 0;
	}
	if (!querry[6]) {
		write(2,"NO VALUES PROVIDED\n",20);
		return 0;
	}
}

static int	validate_insert(char **querry) {
	if (ft_strcmp(querry[1],"INTO") != 0) {
		write(2,"INVALID STRUCTURE OF INSERT\n",29);
		return 0;
	}
	if (!querry[2]) {
		write(2,"NO TABLE NAME PROVIDED\n",24);
		return 0;
	}
	if (ft_strcmp(querry[3],"VALUES") != 0) {
		write(2,"INVALID STRUCTURE OF INSERT\n",29);
		return 0;
	}
	if (!querry[4]) {
		write(2,"NO VALUES PROVIDED\n",20);
		return 0;
	}
	return 1;
}	

int	validation(char **querry) 
{
	print_mtx(querry);
	if (ft_strcmp(querry[0],"CREATE") == 0 || ft_strcmp(querry[0],"DROP") == 0)
		return (validate_create_done(querry));
	if (ft_strcmp(querry[0],"INSERT") == 0)
		return (validate_insert(querry));
	if (ft_strcmp(querry[0],"UPDATE") == 0)
		return (validate_update(querry));
	if (ft_strcmp(querry[0],"DELETE") == 0)
		return (validate_delete(querry));
	if (ft_strcmp(querry[0],"SHOW") == 0)
		return (validate_show(querry));
	write(2,"INVALID QUERRY\n",16);
	return (0);
}