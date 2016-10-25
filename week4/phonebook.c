#include <libfdr/jrb.h>
#include <utility.h>
#include <string.h>
#include <stdlib.h>

#define MAXSECTION 6

typedef struct {
	long number;
	char name[30];
} person;

void getData(char fileName[], JRB book);

void main()
{
	JRB book;
	JRB ptr;
	JRB tobeDeleted;
	JRB tobeModified;
	char key[30];
	long number;
	char sections[MAXSECTION][40] = {"Create a phone book", "Insert a new entry", "Traverse", "Delete an entry", "Modify a number", "Drop and exit"};
	int choice;
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:
			book = make_jrb();
			break;
		case 2:
			getData("input.txt", book);
			// printf("Type in the name, number (name number): \n");
			// scanf(" % s % ld", name, &number);
			break;
		case 3:
			jrb_traverse(ptr, book) {
				printf(" %-30s %-15ld\n", jval_s(ptr->key), jval_l(ptr->val));
			}
			//how to use a define function
			break;
		case 4:
			myfflush();
			printf("Type in the name to be deleted: \n");
			scanf("%s", key);
			tobeDeleted = jrb_find_str(book, key);
			if (tobeDeleted == NULL)
			{
				printf("Can't find!!\n");
				exit(1);
			}
			jrb_delete_node(tobeDeleted);
			break;
		case 5:
			myfflush();
			printf("Type in the name to be modified: \n");
			scanf("%s", key);
			tobeModified = jrb_find_str(book, key);
			if (tobeModified == NULL)
			{
				printf("Can't find!!\n");
				exit(1);
			}

			printf("Type in the new name new phone number: \n");
			scanf("%s %ld", key, &number);
			jrb_delete_node(tobeModified);
			jrb_insert_str(book, strdup(key), new_jval_l(number));
			printf("Updated\n");
			break;
		case MAXSECTION:
			jrb_free_tree(book);
			break;
		default: printf("Choice must be from 1 to % d\n", MAXSECTION);
			break;
		}
	} while (choice != MAXSECTION);
}

void getData(char fileName[], JRB book)
{
	FILE *fin;
	int i;
	person contact;
	JRB ptr;

	if ((fin = fopen(fileName, "r")) == NULL)
	{
		printf("Can't open file %s\n", fileName);
		exit(1);
	}
	while (!feof(fin))
	{
		fscanf(fin, "%[^\n]\n%ld\n", contact.name, &contact.number);
		standardizeName(contact.name);
		ptr = jrb_find_str(book, contact.name);
		if (ptr == NULL)
			jrb_insert_str(book, strdup(contact.name), new_jval_l(contact.number));
		else
			printf("Already a node in the tree\n");
	}
	fclose(fin);
	printf("Input done!\n");
}