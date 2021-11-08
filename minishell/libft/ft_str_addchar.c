#include "libft.h"

char	*ft_str_addchar(char *tmp, char buffer)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(tmp);
	res = malloc(sizeof(char) * (len + 2));
	while (len > 0)
	{
		res[i] = tmp[i];
		i++;
		len--;
	}
	res[i] = buffer;
	i++;
	res[i] = '\0';
	if (tmp)
		free(tmp);
	return (res);
}
