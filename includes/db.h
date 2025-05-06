#ifndef DB_H
# define DB_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define RESET "\x1b[0m"
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
	char	*name;
	int		capacity;
	int		size;
	t_data **datas;
}	t_table;

// DB STRUCT IS VECTOR OF TABLES

typedef struct s_db {
	char	*name;
	int		capacity;
	int		size;
	t_table	**tables;
}	t_db;


// STRUCT FOR CREATE QUERRY

typedef struct s_create_querry {
	char 	*name;
	char 	*table_or_db;
	int		capacity;
}	t_create_querry;


// IN FUTURE

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

void	prompt(char **argv);
char	**ft_split(char const *s, char c);
void	print_mtx(char **mtx);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_db	*parser(char *input, t_db **db);
int		validation(char **strs);
int		mtx_len(char **mtx);
int		ft_strcmp(const char *s1, const char *s2);
void	free_mtx(char **mtx);
void	free_datas(t_data **data);
void	free_table(t_table *table);
void	free_tables(t_db *db);
void	create_table(t_db **db, char *name);
void	create_database(t_db **db, char *name);
void	exec(char **querry, t_db **db);
void	print_data(t_data *data, int index);
void	print_datas(t_data **datas);
void	print_table_data(t_table *table);
void	print_db(t_db *db);
void	get_db_info(t_db **db, char *db_file);

#endif