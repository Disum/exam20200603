#include <stdio.h>
#include <string.h>
#include "solve.h"
#define MAX_LEN 1024

int solve(char *a, char *b)
{
	FILE *in, *out;
	int i, j, count = 0, open_comment = 0;
	char buff[MAX_LEN], res[2*MAX_LEN + 1];

	if( !(in = fopen(a, "r")) )
		return SOLVE_ERR_OPEN;
	if( !(out = fopen(b, "w")) )
	{
		fclose(in);
		return SOLVE_ERR_OPEN;
	}

	while( fgets(buff, MAX_LEN, in) )
	{
		i = 0;
		j = 0;
		if( open_comment )
		{
			for( ; buff[i]!='\0'; i++ )
			{
				res[j] = buff[i];
				j++;
				if( buff[i - 1]=='*' && buff[i]=='/' )
				{
					open_comment = 0;
					i++;
					break;
				}
			}
		}
		for( ; buff[i]!='\0'; i++ )
		{
			if( buff[i]=='/' )
			{
				if( buff[i + 1]=='/' )
				{
					strcpy(res + j, buff + i);
					j += strlen(buff + i);
					break;
				} else if( buff[i + 1]=='*' )
				{
					open_comment = 1;
					res[j] = buff[i];
					j++;
					i++;
					res[j] = buff[i];
					j++;
					i++;
					if( buff[i]!='\0' )
					{
						res[j] = buff[i];
						j++;
						i++;
					} else
						break;
					for( ; buff[i]!='\0'; i++ )
					{
						res[j] = buff[i];
						j++;
						if( buff[i - 1]=='*' && buff[i]=='/' )
						{
							open_comment = 0;
							break;
						}
					}
					if( buff[i]=='\0' )
						break;
				} else
				{
					count++;
					if( j==0 || res[j - 1]!=' ' )
					{
						res[j] = ' ';
						j++;
					}
					res[j] = buff[i];
					j++;
					if( buff[i + 1]!=' ' )
					{
						res[j] = ' ';
						j++;
					}
				}
			} else if( buff[i]=='+' || buff[i]=='-' || buff[i]=='*' )
			{
				count++;
				if( j==0 || res[j - 1]!=' ' )
				{
					res[j] = ' ';
					j++;
				}
				res[j] = buff[i];
				j++;
				if( buff[i + 1]!=' ' )
				{
					res[j] = ' ';
					j++;
				}
			} else
			{
				res[j] = buff[i];
				j++;
			}
		}
		res[j] = '\0';
		fprintf(out, "%s", res);
	}

	fclose(out);

	if( !feof(in) )
	{
		fclose(in);
		return SOLVE_ERR_READ;
	}

	fclose(in);
	return count;
}
