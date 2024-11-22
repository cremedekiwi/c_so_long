/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:49:13 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/23 08:57:33 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// allocates memory for a 'temp' buffer
// total_size : existing content
// bytes_read : newly read bytes
// '\0' : + 1 for the null terminator
static char	*alloc_temp(char *content, size_t total_size, ssize_t bytes_read)
{
	char	*temp;

	temp = malloc(total_size + bytes_read + 1);
	if (temp == NULL)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		free(content);
		return (NULL);
	}
	return (temp);
}

// updates the pointer content to point to the new memory block 'temp'
static void	update_content(char **content, char *temp, size_t total_size)
{
	if (*content)
	{
		ft_memcpy(temp, *content, total_size);
		free(*content);
	}
	*content = temp;
}

// handles the allocation to content for new data read and appends to it.
// alloc_temp : allocates a new memory block large enough to hold old + new data
// update_content : updates the content pointer to this new memory block
// copies the new data from buffer at the end of the current content
// updates total_size to the new total size of the content
static char	*process_buffer(char *content, char *buffer, \
ssize_t bytes_read, size_t *total_size)
{
	char	*temp;

	temp = alloc_temp(content, *total_size, bytes_read);
	if (temp == NULL)
		return (NULL);
	update_content(&content, temp, *total_size);
	ft_memcpy(content + *total_size, buffer, bytes_read);
	*total_size += bytes_read;
	content[*total_size] = '\0';
	return (content);
}

// reads the contents of a file into a malloc
// bytes_read : read the data ; when there is no more to read (0) break
// each chunck of data is processed by process_buffer
// if reading successful, return the content
static char	*read_file(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*content;
	size_t	total_size;
	ssize_t	bytes_read;

	content = NULL;
	total_size = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		content = process_buffer(content, buffer, bytes_read, &total_size);
		if (content == NULL)
			return (NULL);
	}
	if (bytes_read == -1)
	{
		ft_putstr_fd("Error\nReading file\n", 2);
		free(content);
		return (NULL);
	}
	return (content);
}

// read the file (map.ber) and return the content
char	*read_map(char *file_path)
{
	int		fd;
	char	*content;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nOpening file\n", 2);
		return (NULL);
	}
	content = read_file(fd);
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error\nClosing file\n", 2);
		free(content);
		return (NULL);
	}
	return (content);
}
