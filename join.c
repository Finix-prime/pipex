#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s3 = malloc(sizeof(char) * (i + j + 1));
	if (!s3)
		return (0);
	while (*s1)
	{
		*s3 = *s1;
		s3++;
		s1++;
	}
	while (*s2)
	{
		*s3 = *s2;
		s3++;
		s2++;
	}
	*s3 = '\0';
	return (s3 - i - j);
}

int main()
{
	char	*s;

	s = ft_strjoin("note", "/");
	s = ft_strjoin(s, "x/x");
	printf("%s\n",s);
	free(s);
	return (0);
}
