#include <stdio.h>
void my_divmod(int x,int y,int *res1,int *res2)
{
	*res1 = x / y;
	*res2 = x % y;
}
int	main(void)
{
	int	x;
	int	y;
	int	res1;
	int	res2;

	x = 10;
	y = 3;
	my_divmod(x, y, &res1, &res2);
	printf("x / y = %d...%d\n", res1, res2);
}
