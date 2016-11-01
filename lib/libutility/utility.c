#include "utility.h"

//update: put myfflush after scanf %[^\n] for every case

int getMenu(char sections[][40], int maxsection) {
	char choice[30];
	printf("\n");
	for (int i = 0; i < maxsection; ++i)
		printf("%2d. %s\n", i + 1, sections[i]);
	printf("Your choice: ");
	scanf("%[^\n]", choice);
	myfflush();
	//as always, after a scanf [^\n] we must put a myfflush()
	printf("\n");
	return atoi(choice);
}

void dupChar(char c, int times)
{
	int i;
	for (i = 0; i < times; ++i)
		printf("%c", c);
}

void myfflush()
{
	while (getchar() != '\n');
}

void standardizeName(char *str) {
	char s[strlen(str) + 1];
	unsigned int i, z = 0, f = 1;
	while (str[z] == ' ')
		z++;
	for (i = z, z = 0 ; i < strlen(str) ; i++)
	{
		if (str[i] != ' ' && f == 1 && str[i] <= 'z' && str[i] >= 'a')
		{
			s[z] = str[i] - 'a' + 'A';
			f = 0;
			z++;
			i++;
		}
		if (str[i] != ' ' && f == 1 && str[i] <= 'Z' && str[i] >= 'A')
		{
			s[z] = str[i];
			f = 0;
			z++;
			i++;
		}
		if (str[i] != ' ')
		{
			s[z] = str[i];
			z++;
		}
		if (str[i] == ' ' && f == 0)
		{
			s[z] = str[i];
			f = 1;
			z++;
		}
		if (f == 1)
			while (str[i] == ' ' && str[i + 1] == ' ')
				i++;
	}

	if (s[z - 1] == ' ')
		z--;
	for (i = 0; i < z; ++i)
		str[i] = s[i];
	str[i] = '\0';
}