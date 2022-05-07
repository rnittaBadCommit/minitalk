#include <stdio.h>

char decoder(char *buf)
{
	int i;
	char ret;

	i = 0;
	ret = 0;
	while (i < 8)
	{
		ret = (ret<<1) + (buf[i] == 1);
		i++;
	}
	return (ret);
}

int main()
{
	char input[] = {0, 0, 0, 1, 0, 1, 1, 1};
	printf("%hd\n", decoder(input));
}
