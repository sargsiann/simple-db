#ifndef DB_H
# define DB_H

// INCLUDES

#include "get_next_line.h"
#include <stdbool.h>


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


// ENUM FOR QUERRY TYPES 

typedef enum e_sql_query_type
{
    CREATE,
    SELECT,
    DELETE,
    UPDATE,
    INSERT,
	DROP
}   t_sql_query_type;


typedef struct s_select_squerry {
	char	*column;
	t_table	*table;
	char	*order_by;
	int		asc_or_desc;
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


#endif