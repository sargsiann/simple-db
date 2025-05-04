#ifndef DB_H
# define DB_H

// INCLUDES

#include "get_next_line.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// THE DATA TYPE IN OUR DATABASE

typedef	struct s_data{
	float	value;
	char	**users;
}	t_data;

// TABLE IS VECTOR OF DATA ARRAY

typedef struct s_table {
	int		capacity;
	int		size;
	t_data *data;
}	t_table;

// DB STRUCT IS VECTOR OF TABLES

typedef struct s_db {
	int		capacity;
	int		size;
	t_table	*tables;
}	t_db;


// STRUCT FOR CREATE QUERRY

typedef struct s_create_querry {
	char 	*table_or_db;
	int		capacity;
}	t_create_querry;

typedef struct s_select_squerry {
	char	*column;
	t_table	*table;
	int		limit;
	char	*condition;
}	t_select_querry;

// INSERT QUERRY STRUCTURE

typedef struct s_insert_querry {
	t_table	*table;
	char	**users;
	float	value;
}	t_insert_querry;

// UPDATE AND DELETE QUERRY STRUCTURE

typedef struct s_update_delete_querry {
	t_table *table;
	int		to_delete;
	char	**values_to_set;
	char	*condition;
}	t_update_querry;

// FUNCTIONS

void	prompt(t_db *db);
char	**ft_split(char const *s, char c);
void	print_mtx(char **mtx);
void	parser(char *input, t_db *db);
int		validation(char **strs);
int		mtx_len(char **mtx);
int		ft_strcmp(const char *s1, const char *s2);



#endif