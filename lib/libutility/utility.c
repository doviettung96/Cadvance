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

char** str_split(char* a_str, const char a_delim)
{
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	count += last_comma < (a_str + strlen(a_str) - 1);

	count++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx  = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}
