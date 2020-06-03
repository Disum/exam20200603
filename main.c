#include <stdio.h>
#include "solve.h"
#define ERR_READ (-1)

int main(int argc, char **argv)
{
	int res;

	if( argc!=3 )
	{
		fprintf(stderr, "Usage: %s a b\n", argv[0]);
		return ERR_READ;
	}

	res = solve(argv[1], argv[2]);

	if( res<0 )
	{
		switch( res )
		{
			case SOLVE_ERR_OPEN:
				fprintf(stderr, "Can not open file!\n");
				break;
			case SOLVE_ERR_READ:
				fprintf(stderr, "Can not read!\n");
				break;
			default:
				fprintf(stderr, "Unknown error with code %d\n", res);
		}
	} else
		printf("solve(%s, %s) returned %d\n", argv[1], argv[2], res);

	return 0;
}
