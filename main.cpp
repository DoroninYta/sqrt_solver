#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPSILON = 1e-4;

enum nRoots {
	NO_ROOTS = 0,
	ONLY_ONE_ROOT,
	TWO_ROOTS,
	INF_ROOTS = 3,
	ERROR
};

int isEqual(double a, double b)									// сравнение чисел разных типов
{
	if (fabs(a - b) < EPSILON)
		return 1;
	else
		return 0;
}


int fn_which_chek_entered_characters_scanf(int n_Try_enter, double* a, double* b, double* c)			//функция безопастного ввода символов с клавиатуры
{
	int nCharacters = scanf_s("%lf %lf %lf", a, b, c);
	int nTry = 0;
	while (nTry < n_Try_enter && nCharacters != 3)
	{
		while (getchar() != '\n') { ; }										//отчистка буфера
		printf("error, please, try again, you have %d tryes to enter\n", n_Try_enter - nTry);
		nCharacters = scanf_s("%lf %lf %lf", a, b, c);
		nTry++;
	}
	if (nCharacters == 3)
		return 0;
	else
	{
		printf("there are too many incorrect inputs\n");
		return 5;
	}
}


double fn_line_solver(double a, double b)
{
	return (-b / a);
}

int fn_sq_solver(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL);
	assert(x2 != NULL);

	if (isEqual(a, 0) == 1)
	{

		if (isEqual(b, 0) == 1)
		{
			if (isEqual(c, 0) == 1)
				return (INF_ROOTS);

			else
				return(NO_ROOTS);
		}
		else							//b != 0
		{
			*x1 = fn_line_solver(b, c);
			return (ONLY_ONE_ROOT);
		}
	}
	else								// a, b, c != 0
	{
		double D = b * b - 4 * a * c;
		if (D - EPSILON > 0)
		{
			double z = sqrt(D);

			*x1 = (-b - z) / 2 / a;
			*x2 = (-b + z) / 2 / a;

			return (TWO_ROOTS);
		}
		else if (isEqual(D, 0) == 1)
		{
			*x1 = -b / 2 / a;

			return (ONLY_ONE_ROOT);
		}
		else		//D < 0
		{
			return (NO_ROOTS);
		}
	}
	return ERROR;

}

int PrintfResult(int nRoots)											// для вывода количества корней
{
	switch (nRoots) {		// z переделать
	case NO_ROOTS:
		printf("no roots\n");
		break;
	case ONLY_ONE_ROOT:
		printf(" only one root\n");
		break;
	case TWO_ROOTS:
		printf("two roots\n");
		break;
	case INF_ROOTS:
		printf("infinite roots\n");
		break;
	default:		//ERROR
		printf("something wrong %d\n", nRoots);
	}
	return 0;
}

int main()
{
	double a = 0;
	double b = 0;
	double c = 0;
	double x1 = 0;
	double x2 = 0;

	printf("print numbers a b c\n");
	int nTry_to_enter = 3;
	fn_which_chek_entered_characters_scanf(nTry_to_enter, &a, &b, &c);
	int nRoot = fn_sq_solver(a, b, c, &x1, &x2);
	PrintfResult(nRoot);
	return 0;
}