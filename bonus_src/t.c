#include "../include/pipex.h"

int main()
{
	int ac = 4;
	int fd[ac][2];
	int i =0;

	while (i < ac)
	{
		ft_memset(fd[i], 0, sizeof(fd[i]) / 4);
		i++;
	}
	fd[ac] = INT_MIN;
	for(i=0; fd[i] != INT_MIN; i++)
	{
		
	}
}

/*

nbrofcmds = 4
nbrofpipes = 3
nbrofports = 6

int *pipeline = alloc(sizeof(int) * 6)
for (int i = 0; i < nbrofports; i += 2)
	pipe(pipeline[i]);

*/
