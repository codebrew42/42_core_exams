#include <stdlib.h>
#include <stdio.h>

typedef struct	s_solutions
{
	int	**solutions;
	int		count;
	int		size;
}	t_solutions;

void	save_solution(t_solutions *sol, int *column);

int		is_safe(int *column, int col, int row)
{
	int i = 0;
	while (i < row)
	{
		if (column[i] == col ||
		abs(column[i] - col) == abs(i - row))
			return (0);
		i++;
	}
	return (1);
}

void	solve(t_solutions *sol, int *column, int row)
{
	//normal return : all found
	if (row == sol->size)
	{
		save_solution(sol, column);
		return ;
	}

	//looping. think only suc
	int col = 0;
	while(col < sol->size)
	{
		if (is_safe(column, col, row)) //!
		{
			column[row] = col;
			solve(sol, column, row + 1);
		}
		col++;
	}
}

void	save_solution(t_solutions *sol, int *column)
{
	// Reallocate memory for a new solution
	sol->solutions = realloc(sol->solutions, sizeof(int *) * (sol->count + 1));
	sol->solutions[sol->count] = malloc(sizeof(int) * sol->size);
	
	// Copy current arrangement
	for (int i = 0; i < sol->size; i++)
		sol->solutions[sol->count][i] = column[i];
	
	sol->count++;
}

int	main(int ac, char **av)
{
	if(ac !=2 || !*av)
		return (1);

	//1. init
	t_solutions *sol = malloc(sizeof(t_solutions));
	if (!sol)
		return (1);
	sol->solutions = NULL;
	sol->size = atoi(av[1]);
	sol->count = 0;
	int	*column = calloc(sol->size, sizeof(int));
	if (!column)
		return (1);
	
	//2. solve
	solve(sol, column, 0);

	//3. print results
	printf("Found %d solutions\n", sol->count);
	
	//4. cleanup
	for (int i = 0; i < sol->count; i++)
		free(sol->solutions[i]);
	free(sol->solutions);
	free(column);
	free(sol);

	return (0);
}