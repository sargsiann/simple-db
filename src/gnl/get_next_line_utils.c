/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:58:35 by dasargsy          #+#    #+#             */
/*   Updated: 2024/03/15 13:40:26 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	s_zero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*ft_calloc(size_t count, size_t n)
{
	void	*memory;

	if (count && n && count > (UINT_MAX / n))
		return (NULL);
	memory = malloc(count * n);
	if (!memory)
		return (NULL);
	s_zero(memory, count * n);
	return (memory);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int f)
{
	char	*a;
	size_t	i;

	i = 0;
	if (!s || len == 0)
		return (NULL);
	if (start > ft_strlen(s))
	{
		a = (char *)ft_calloc(1, 1);
		return (a);
	}
	if (len > ft_strlen(s) - start)
		a = (char *)ft_calloc(1, ft_strlen(s) - start + 1);
	else
		a = (char *)ft_calloc(1, (len + 1) * sizeof(char));
	if (!a)
		return (NULL);
	while (i < len && s[i + start])
	{
		a[i] = s[i + start];
		i++;
	}
	if (f)
		free(s);
	return (a);
}

char	*ft_strjoin(char *s1, char *s2, int f, int f2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	joined = (char *)ft_calloc(1, ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	if (f)
		free(s1);
	if (f2)
		free(s2);
	return (joined);
}
