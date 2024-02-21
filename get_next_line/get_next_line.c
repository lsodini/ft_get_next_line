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
	if (!temp)
		return (NULL);
	free(str1);
	return (temp);
}

char	*ft_sep_str(char **testo)
{
	if (!testo || !*testo)
		return (NULL);
	char	*buffer;
	char	*temp;
	char	*ret;
	int		i
	int		j

	i = 0;
	j = 0;
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
	if (!buffer)
		return (NULL);
	if (j != -1)
		ret = ft_substr(*testo, i, j);
	if (ret == NULL && j != -1)
	{
		free (buffer);
		return (NULL);
	}
	free(*testo);
	*testo = ret;
	return (buffer);
}

char	*ft_get_line(int fd, char *testo)
{
	if (!testo)
		return (NULL);
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && !*testo))
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
	static char		*testo = NULL;
	char			*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, 0, 0) < 0)
	{
		free(testo);
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
	if (!buffer)
		return (NULL);
	return (buffer);
}

int main() {
    int fd = ("prova1.txt", O_RDONLY); 
	//con fd = 0 legge da stdin
    if (fd < 0) {
        perror("Errore nell'apertura del file");
        return 1;
    }

    char *str;
    int i = 0;
    while ((str = get_next_line(fd)) != NULL) {
        printf("Linea letta: (riga %i): %s\n", i++, str);
        free(str);
    }

    close(fd);
    return 0;
}