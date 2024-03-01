/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsodini <marvin@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:37:59 by lsodini           #+#    #+#             */
/*   Updated: 2024/02/16 17:37:59 by lsodini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_freejoin(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

char	*ft_sep_str(char **testo)
{
	char	*buffer;
	char	*temp;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = *testo;
	ret = NULL;
	buffer = NULL;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
		j = -1;
	i++;
	while (j != -1 && temp[i + j])
		j++;
	buffer = ft_substr(*testo, 0, i);
	if (j != -1)
		ret = ft_substr(*testo, i, j);
	free(temp);
	*testo = ret;
	return (buffer);
}

char	*ft_get_line(int fd, char *testo)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && ft_strlen(testo) == 0))
		{
			free(testo);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		testo = ft_freejoin(testo, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (testo);
}

char	*get_next_line(int fd)
{
	static char		*testo;
	char			*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	if (!testo)
		testo = ft_calloc(1, 1);
	if (!testo)
		return (NULL);
	testo = ft_get_line(fd, testo);
	if (!testo)
		return (NULL);
	buffer = ft_sep_str(&testo);
	return (buffer);
}
/*int	main()
{
	char	*str;
	int		i;
	int		fd;
	i = 1;
	fd = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("File %i: (riga %i) :%s", 1, i++, str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close (fd);
	return (0);
}*/
/*
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int     fd;
    char    *line;

    fd = open("prova1.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    if (line == NULL)
    {
        perror("get_next_line");
        close(fd);
        return (1);
    }

    close(fd);
    return (0);
}*/
