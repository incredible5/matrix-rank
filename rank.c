#include<stdio.h>
int row, col, i, j, mat_rank, mataug_rank;
int mat[80][80], matrix[80][80];

void display(int row, int col)
{
	for(int x = 0; x < row; x++)
	{
		for(int y = 0; y < col; y++)
		{
			printf("%.1d\t",matrix[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

void interchange(int row_pos, int row, int col)
{
	int temp;
	for(int col_pos = 0; col_pos < col; col_pos++)
	{
		temp = matrix[row_pos][col_pos];
		matrix[row_pos][col_pos] = matrix[row_pos + 1][col_pos];
		matrix[row_pos + 1][col_pos] = temp;
	}
}

void echelon( int row, int col)
{
	int god = 0;
	while(god < (row - 1))
	{
		i = god;
		while(i < row)
		{
			if(matrix[0][0] == 0 && i != row - 1)
			{
				interchange(0, row, col);
			}
			i++;
			double mult = 0;
			for(j = 0; j < col; j++)
			{
				if(matrix[i][j] != 0 && matrix[god][j] != 0)
				{
					mult = matrix[i][j] / matrix[god][j];
					break;
				}
			}
			for(j = 0; j < col; j++)
			{
				matrix[i][j] -= (int)mult * matrix[god][j];
			}
		}
		god++;	
	}
}

int rank(int row, int col)
{
	int i ,j , rank = 0, flag = 0;
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			if(matrix[i][j] != 0)
			flag = 1;
		}
		if(flag == 1)
		{
			rank++;
			flag = 0;
		}
	}
	return rank;
}


int main()
{
	int god;

	printf("Enter the number of equations: ");
	scanf("%d", &row);
	printf("Enter the number of coefficients in the equations: ");
	scanf("%d",&col);

	for(i = 0; i < row; i++)
	{
		printf("Enter the coefficients of equation number %d:\n", i + 1);
		for(j = 0; j < col; j++)
			scanf("%d", &mat[i][j]);
	}
	for(i = 0;i < row; i++)
		for(j = 0; j < col - 1; j++)
			matrix[i][j] = mat[i][j];
	echelon(row, col - 1);
	mat_rank = rank(row, col - 1);
	printf("Rank of the coefficient matrix is: %d\n", mat_rank);

	for(i = 0;i < row; i++)
		for(j = 0; j < col; j++)
			matrix[i][j] = mat[i][j];

	echelon(row, col);
	mataug_rank = rank(row, col);
	printf("Rank of the augmented matrix is: %d\n", mataug_rank);

	if(mat_rank < mataug_rank)
		printf("The system of equations is inconsistent i.e., no solution exists\n");
	else if(mat_rank == mataug_rank)
	{
		if(mat_rank == row)
			printf("The system of equations has a unique solution\n");
		else if(mat_rank < row)
			printf("The system of equations has inifinitely many solutions\n");
		else
			printf("Some error occured in calculation\n");
	}
	else
		printf("Some error occured in calculation\n");

	return 0;
}