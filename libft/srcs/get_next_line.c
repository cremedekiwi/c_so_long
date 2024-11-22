/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:39:59 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/15 17:27:22 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/get_next_line.h"

/* free the buffer
1. if '*buffer' is not NULL
	a. free the memory
	b. set the pointer to NULL */
static void	free_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

/* extract a line from a string '*buffer'
1. while '*buffer' is not NULL and '*buffer' is not '\n', we go forward
2. if '*buffer' is a newline :
	a. duplicates the string from the start to the newline
	b. duplicates the rest of the string after the newline
	c. if line or rest is not, free the buffer and return NULL
	d. frees 'buffer'
	e. assign the rest into 'buffer'
	f. if 'buffer' is empty, it frees the memory
3. if no new line, duplicates the entire string into 'line' then frees the memory
4. returns 'line' which contains the extracted line */
static char	*get_line(char **buffer)
{
	char	*line;
	char	*rest;
	int		i;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
	{
		line = ft_strndup(*buffer, i + 1);
		rest = ft_strdup(*buffer + i + 1);
		if (!line || !rest)
			return (free_buffer(buffer), NULL);
		free_buffer(buffer);
		*buffer = rest;
		if ((*buffer)[0] == '\0')
			free_buffer(buffer);
	}
	else
	{
		line = ft_strdup(*buffer);
		free_buffer(buffer);
	}
	return (line);
}

/* read data from a file and stores it in a buffer
* @brief
1. allocate memory for 'read_buffer' (+ 1 for '\0')
2. if malloc fails return -1
3. stock the number of bytes read
4. while there are bytes to read
	a. null terminate the buffer at the last position
	b. if 'buffer' is empty, duplicate 'read_buffer'
	c. if not empty, concatenate 'read_buffer' to 'buffer' and update 'buffer'
	d. if *buffer is NULL, free the read_buffer and return -1
	e. if a newline character is found, break the loop
	f. read the next chunk of bytes from the files
4. free the memory and return the number of bytes read
	a. if end of the file is 0
	b. if an error occured it will be -1 */
static int	read_file(int fd, char **buffer)
{
	char	*read_buffer;
	int		bytes_read;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (-1);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		if (!*buffer)
			*buffer = ft_strdup(read_buffer);
		else
			*buffer = ft_strjoin(*buffer, read_buffer);
		if (!*buffer)
			return (free(read_buffer), -1);
		if (ft_strchr(read_buffer, '\n'))
			break ;
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	}
	return (free(read_buffer), bytes_read);
}

/* get a line from a file descriptor
1. the static keyword means that buffer will retain value between function calls
2. if fd (neg) or BUFFER_SIZE (0 or less) values are incorrect -> return 'NULL'
3. stock the number of bytes read
4. if 'read_bytes' is -1 there was an error so free the buffer and return 'NULL'
5. if 'read_bytes' is 0 and "!buffer", it means end of file (nothing to read)
6. if no return NULL, return the extract line */
char	*get_next_line(int fd)
{
	static char	*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_file(fd, &buffer);
	if (bytes_read < 0)
		return (free_buffer(&buffer), NULL);
	if (bytes_read == 0 && !buffer)
		return (NULL);
	return (get_line(&buffer));
}
/*
#include <stdio.h>

void	print_get_next_line(int fd)
{
	char	*line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
}

int	main(void)
{
	int	fd;

	fd = open("txt/test.txt", O_RDONLY);
	printf("Reading from 'test.txt':\n");
	print_get_next_line(fd);
	close(fd);

	fd = open("txt/empty.txt", O_RDONLY);
	printf("\nReading from 'empty.txt':\n");
	print_get_next_line(fd);
	close(fd);

	fd = open("txt/newline.txt", O_RDONLY);
	printf("\nReading from 'newline.txt':\n");
	print_get_next_line(fd);
	close(fd);

	fd = open("txt/longline.txt", O_RDONLY);
	printf("\nReading from 'longline.txt':\n");
	print_get_next_line(fd);
	close(fd);

	return (0);
} */
