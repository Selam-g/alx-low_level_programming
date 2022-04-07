#include <stdlib.h>
#include <stdio.h>

int find_len(char *str);
char *create_xarray(int size);
char *iterate_zeroes(char *str);
void get_prod(char *prod, char *mult, int digit, int zeroes);
void add_nums(char *final_prod, char *next_prod, int next_len);

/**
 * find_len - Finds the length of a string.
 * @str: The string to be measured.
@@ -24,26 +30,26 @@ int find_len(char *str)
}

/**
 * create_array - Creates an array of chars and initializes it with
 *                a specific char. Adds a terminating null byte.
 * create_xarray - Creates an array of chars and initializes it with
 *                 the character 'x'. Adds a terminating null byte.
 * @size: The size of the array to be initialized.
 * @c: The specific char to initialize the array with.
 *
 * Return: If the function fails - exits with a status of 98.
 *         Otherwise - a pointer to the array.
 * Description: If there is insufficient space, the
 *              function exits with a status of 98.
 * Return: A pointer to the array.
 */
char *create_array(unsigned int size, char c)
char *create_xarray(int size)
{
	char *array;
	unsigned int index;
	int index;

	array = malloc(sizeof(char) * size);

	if (array == NULL)
		return (NULL);
		exit(98);

	for (index = 0; index < (size - 1); index++)
		array[index] = c;
		array[index] = 'x';

	array[index] = '\0';

@@ -66,11 +72,12 @@ char *iterate_zeroes(char *str)
}

/**
 * get_digit - Converts a character digit to a corresponding int.
 * get_digit - Converts a digit character to a corresponding int.
 * @c: The character to be converted.
 *
 * Return: If c is a non-digit - exits with a status of 98.
 *         Otherwise - Returns the converted int.
 * Description: If c is a non-digit, the function
 *              exits with a status of 98.
 * Return: The converted int.
 */
int get_digit(char c)
{
@@ -91,12 +98,16 @@ int get_digit(char c)
 * @mult: The string of numbers.
 * @digit: The single digit.
 * @zeroes: The necessary number of leading zeroes.
 *
 * Description: If mult contains a non-digit, the function
 *              exits with a status value of 98.
 */
void get_prod(char *prod, char *mult, int digit, int zeroes)
{
	int mult_len, num, tens = 0;

	mult_len = find_len(mult) - 1;
	mult += mult_len;

	while (*prod)
	{
@@ -112,15 +123,15 @@ void get_prod(char *prod, char *mult, int digit, int zeroes)
		prod--;
	}

	for (; mult_len >= 0; mult_len--, prod--)
	for (; mult_len >= 0; mult_len--, mult--, prod--)
	{
		if (*(mult + mult_len) < '0' || *(mult + mult_len) > '9')
		if (*mult < '0' || *mult > '9')
		{
			printf("Error\n");
			exit(98);
		}

		num = (*(mult + mult_len) - '0') * digit;
		num = (*mult - '0') * digit;
		num += tens;
		*prod = (num % 10) + '0';
		tens = num / 10;
@@ -134,8 +145,9 @@ void get_prod(char *prod, char *mult, int digit, int zeroes)
 * add_nums - Adds the numbers stored in two strings.
 * @final_prod: The buffer storing the running final product.
 * @next_prod: The next product to be added.
 * @next_len: The length of next_prod.
 */
void add_nums(char *final_prod, char *next_prod)
void add_nums(char *final_prod, char *next_prod, int next_len)
{
	int num, tens = 0;

@@ -145,20 +157,26 @@ void add_nums(char *final_prod, char *next_prod)
	while (*(next_prod + 1))
		next_prod++;

	for (; *final_prod != 'x'; final_prod--, next_prod--)
	for (; *final_prod != 'x'; final_prod--)
	{
		num = (*final_prod - '0') + (*next_prod - '0');
		num += tens;
		*final_prod = (num % 10) + '0';
		tens = num / 10;

		next_prod--;
		next_len--;
	}

	for (; *next_prod != 'x'; final_prod--, next_prod--)
	for (; next_len >= 0 && *next_prod != 'x'; next_len--)
	{
		num = (*next_prod - '0');
		num += tens;
		*final_prod = (num % 10) + '0';
		tens = num / 10;

		final_prod--;
		next_prod--;
	}

	if (tens)
@@ -170,8 +188,9 @@ void add_nums(char *final_prod, char *next_prod)
 * @argv: The number of arguments passed to the program.
 * @argc: An array of pointers to the arguments.
 *
 * Return: If the number of arguments is incorrect - exits with a status of 98.
 *         Otherwise - 0.
 * Description: If the number of arguments is incorrect or one number
 *              contains non-digits, the function exits with a status of 98.
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
@@ -195,14 +214,14 @@ int main(int argc, char *argv[])
	}

	size = find_len(argv[1]) + find_len(argv[2]);
	final_prod = create_array((size + 2), 'x');
	next_prod = create_array((size + 2), 'x');
	final_prod = create_xarray(size + 1);
	next_prod = create_xarray(size + 1);

	for (index = size - find_len(argv[1]) - 1; index >= 0; index--)
	for (index = find_len(argv[2]) - 1; index >= 0; index--)
	{
		digit = get_digit(*(argv[2] + index));
		get_prod(next_prod, argv[1], digit, zeroes++);
		add_nums(final_prod, next_prod);
		add_nums(final_prod, next_prod, size - 1);
	}
	for (index = 0; final_prod[index]; index++)
	{
		if (final_prod[index] != 'x')
			putchar(final_prod[index]);
	}
	putchar('\n');
	free(next_prod);
	free(final_prod);
	return (0);
}
