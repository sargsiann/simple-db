/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:39:58 by dasargsy          #+#    #+#             */
/*   Updated: 2025/05/04 21:06:04 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "db.h"

static size_t	count_size(char const *s, char c)
{
	size_t	size;
	size_t	i;
	int		flag;
	int		inbrackets;

	size = 0;
	i = 0;
	flag = 0;
	inbrackets = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == '('){
			size++;
			inbrackets = 1;
		}
		flag = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			if (!flag && inbrackets == 0)
			{
				flag = 1;
				size++;
			}
			i++;
		}
		if (s[i] == ')')
			inbrackets = 0;
		i++;
	}
	return (size);
}

static	void	free_splited(char **splitted)
{
	size_t	i;

	i = 0;
	while (splitted[i] != NULL)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

static void	fill_splited(char **splitted, char const *s, char c)
{
	size_t	i;
	size_t	lenght;
	size_t	sp_c;
	int	inbrackets;

	i = 0;
	lenght = 0;
	sp_c = 0;
	inbrackets = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == '(')
			inbrackets = 1;
		if (s[i] == ')')
			inbrackets = 0;
		lenght = 0;
		while (s[i] == c)
			i++;
		while (s[i])
		{
			if (s[i] == ')')
				inbrackets = 0;
			if (s[i] == c && inbrackets == 0)
				break ;
			i++;
			lenght++;
		}
		if (lenght > 0)
			splitted[sp_c++] = ft_substr((char *)s, i - lenght, lenght, 0);
		if (!splitted)
			free_splited(splitted);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**splitted;

	if (!s)
		return (NULL);
	size = count_size(s, c);
	if (!*s)
	{
		splitted = (char **)malloc(sizeof(char *) * (1));
		splitted[0] = NULL;
		return (splitted);
	}
	splitted = (char **)malloc(sizeof(char *) * (size + 1));
	if (!splitted)
	{
		free(splitted);
		return (NULL);
	}
	fill_splited(splitted, s, c);
	splitted[size] = NULL;
	if (!splitted)
		return (NULL);
	return (splitted);
}
