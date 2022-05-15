#include "libft_standart.h"

t_bool				is_begin(const char *string, int i, char delimiter)
{
	if (i == 0 && string[i] != delimiter)
		return (true);
	if (i > 0 && string[i - 1] == delimiter && string[i] != delimiter)
		return (true);
	return (false);
}

t_bool 				is_end(const char *string, int i, char delimiter)
{
	if (i > 0 && string[i - 1] != delimiter && string[i] == delimiter)
		return (true);
	if (i > 0 && string[i - 1] != delimiter && string[i] == '\0')
		return (true);
	return (false);
}

void				allocate_data(char ***data, const char *string, char delimiter, t_bool save_delimiter)
{
	int 			i;
	int 			count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (save_delimiter && string[i] == delimiter)
			count++;
		else if (is_begin(string, i, delimiter))
			count++;
		i++;
	}
	*data = malloc(sizeof(char *) * (count + 1));
}

void 				split(char **data, const char *string, char delimiter, t_bool save_delimiter)
{
	int 			i[2];
	int 			data_i;

	data_i = 0;
	i[0] = 0;
	while (string[i[0]])
	{
		if (save_delimiter && string[i[0]] == delimiter)
			data[data_i++] = ft_strsub(string, i[0]++, 1);
		else if (!save_delimiter && string[i[0]] == delimiter)
			i[0]++;
		else if (is_begin(string, i[0], delimiter))
		{
			i[1] = i[0];
			while (!is_end(string, i[1], delimiter))
				i[1]++;
			data[data_i++] = ft_strsub(string, i[0], i[1] - i[0]);
			i[0] = i[1];
		}
	}
	data[data_i] = NULL;
}

char				**ft_str_tokenize(const char *string, char delimiter, t_bool save_delimiter)
{
	char			**data;

	allocate_data(&data, string, delimiter, save_delimiter);
	split(data, string, delimiter, save_delimiter);
	return (data);
}
