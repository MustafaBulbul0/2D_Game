#include "./../so_long.h"

static char	**read_file(char *file_name, int row_num);
char	**map_man(char *file_name);
static char *n_line(char *line);

static char *n_line(char *line)  
{  
    char	*n_line;  
    size_t	size;  

    if (!line || (size = ft_strlen(line)) == 0 || line[size - 1] == '\n')  
        return line;  

    n_line = (char *)ft_calloc(size + 2, sizeof(char));  
    if (!n_line)  
    {  
        free(line);  
        exit(EXIT_FAILURE);  
    }  

    ft_strlcpy(n_line, line, size + 1);  
    n_line[size] = '\n';  
    n_line[size + 1] = '\0';  
    free(line);
    return n_line;  
}  

static char	**read_file(char *file_name, int row_num)  
{  
    char	**map;  
    char	*line;
    char    *tmp;
    int		i[2];  
    int		fd;  

    map = ft_calloc(row_num + 1, sizeof(char *));  
    if (!map)  
        exit(EXIT_FAILURE);  

    fd = open(file_name, O_RDONLY);  
    if (fd < 0)  
    {  
        clear_2d_pointer(map);  
        exit(EXIT_FAILURE);
    }  

    i[0] = -1;  
    i[1] = 0;  
    line = get_next_line(fd);  
    while (++i[0] < row_num)  
    {  
        if (line && line[0] != '\n')  
        {  
            line = n_line(line);  
            map[i[1]++] = line;  
        }  
        tmp = line;  
        line = get_next_line(fd);  
        free(tmp);
    }
    close(fd);  
    return (map);  
}

char	**map_man(char *file_name)  
{  
	char	**map;
    int		c_row;  

    c_row = count_row(file_name);  
	map = read_file(file_name, c_row);
    return (map);  
}  
