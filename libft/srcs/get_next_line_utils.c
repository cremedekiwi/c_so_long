/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:49:36 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/15 17:27:59 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/get_next_line.h"

/* calculates the length of a string
1. if 'src' is NULL -> return '0'
2. while there is a character in the string 'src' we increment the count 'i'
3. we return the count 'i' */
size_t	ft_strlen_gnl(const char *src)
{
	size_t	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
		i++;
	return (i);
}

/* duplicates a string up to 'n' bytes
1. calculates the length of 'src'
2. if length of 'src' is greater than 'n' bytes, it sets len to n
3. allocates memory from 'dst' (the duplicate string)
4. if allocatioon fails -> we return 'NULL'
6. copies 'src' into 'dst' using 'ft_memcpy'
5. sets the last char of 'dst' at '\0'
6. return 'dst' */
char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*dst;

	len = ft_strlen_gnl(src);
	if (len > n)
		len = n;
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}
