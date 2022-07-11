#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int x;

	x = (int)malloc(sizeof(int));
	x = 5;
	free(x);
	printf("%d", x);
	return (0);
}
