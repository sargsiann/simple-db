#include "db.h"

// DROP CREATE DROP +
// INSERT +
// UPDATE +
// DELETE +
// SHOW (showing all db if * else db) + 


// SELECT (in feature)

static int	validate_create_done(char **querry) 
{
	// WE DO NOT CREATING OR DROPING TABLE AND DATABASE ITS INVALID
	if (ft_strcmp(querry[1],"TABLE") != 0 && ft_strcmp(querry[1],"DATABASE") != 0)
	{
		write(2,"INVALID ARGUMENT TO DELETE OR DROP\n",36);
		return (0);
	}
	// CHECKING FOR ID OF DB OR TABLE
	if (querry[2] == NULL && ft_strcmp(querry[2],"*") == 0)
	{
		write(2,"INVALID DB OR TABLE ID\n",24);
		return (0);
	}
	return (1);
}

// CHECKING DELETE
static int validate_delete(char **querry) 
{
	// CHECKING DELETING DATA FROM TABLE ID
	if (ft_strcmp(querry[1],"FROM") != 0) {
		write(2,"INVALID STRUCTURE OF DELETE\n",29);
		return 0;
	}
	if (!querry[2]) {
		write(2,"NO TABLE ID PROVIDED\n",22);
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
	return 1;
}

static int validate_show(char **querry) 
{
	// SHOWING VALIDATION IF HAVE NOTING TO SHOW OR HAVE MORE THAN TO SHOW
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

// VALIDATING UPDATE QUERRY (STARTS WITH SET)
static int validate_update(char **querry) 
{
	// NO TABLE ID
	if (!querry[1]) {
		write(2,"NO TABLE NAME PROVIDED\n",24);
		return 0;
	}
	// NO VALUES WHAT TO SET
	if (ft_strcmp(querry[2],"VALUES") != 0) {
		write(2,"INVALID STRUCTURE OF UPDATE\n",29);
		return 0;
	}
	if (!querry[3]) {
		write(2,"NO VALUES PROVIDED\n",20);
		return 0;
	}
	// NO CONDITION WHERE TO SET
	if (ft_strcmp(querry[4],"WHERE") != 0) {
		write(2,"INVALID STRUCTURE OF UPDATE\n",29);
		return 0;
	}
	if (!querry[5]) {
		write(2,"NO CONDITON PROVIDED\n",22);
		return 0;
	}
	return 1;
}

// VALIDATION FOR INSERTING DATA TO TABLE
static int	validate_insert(char **querry) {
	// NO TABLE TO INSERT
	if (ft_strcmp(querry[1],"INTO") != 0) {
		write(2,"INVALID STRUCTURE OF INSERT\n",29);
		return 0;
	}
	if (!querry[2]) {
		write(2,"NO TABLE NAME PROVIDED\n",24);
		return 0;
	}
	// NO VALUES
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

// MAIN VALIDATION FUNCTION
int	validation(char **querry) 
{
	// CHECKING WHAT QUERRY DO WE HAVE
	if (ft_strcmp(querry[0],"CREATE") == 0 || ft_strcmp(querry[0],"DROP") == 0)
		return (validate_create_done(querry));
	if (ft_strcmp(querry[0],"INSERT") == 0)
		return (validate_insert(querry));
	if (ft_strcmp(querry[0],"SET") == 0)
		return (validate_update(querry));
	if (ft_strcmp(querry[0],"DELETE") == 0)
		return (validate_delete(querry));
	if (ft_strcmp(querry[0],"SHOW") == 0)
		return (validate_show(querry));
	if (ft_strcmp(querry[0],"SAVE") == 0)
		return 1;
	
	// WE HAVE INVALID QUERRY NAME AT THIS TIME (IN FUTURE WILL BE MORE ))
	write(2,"INVALID QUERRY\n",16);
	return (0);
}