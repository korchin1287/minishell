#include "get_next_line.h"

int		get_next_line(char **line)
{
	char buf[2];
	int	ret;
	int	flag;
	char *tmp;

	flag = 1;
	if (!(*line))
	{
		*line = (char *)malloc(sizeof(char *) * 1);
		*line[0] = '\0';
	}
	while (flag == 1 && (ret = read(0, buf, 1)))
	{
		buf[ret] = '\0';
		if (buf[0] == '\n')
		{
			flag = 0;
			buf[0] = '\0';
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (ret);
}