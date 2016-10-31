#include <stdio.h>
#include <string.h>

void main()
{
	int MAX = 10;
	char temp[100];
	char name[100];
	FILE *f = fopen("input.graph", "r");
	while (1)
	{
		fgets(temp, 100, f);
		if (strcmp(temp, "[STATIONS]\n") == 0)
			break;
	}
	for(int i = 0; i < MAX - 1; ++i)
	{
		fscanf(f, "S%*d=%[^\n]\n", name);
		printf("%s\n", name);
	}

	while (1)
	{
		fgets(temp, 100, f);
		if (strcmp(temp, "[LINES]\n") == 0)
			break;
	}
	while(!feof(f))
	{
		fscanf(f, "M%*d=%[^\n]\n", name);
		printf("%s\n", name);	
	}
	fclose(f);
}