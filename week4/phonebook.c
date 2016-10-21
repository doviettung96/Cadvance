#include "jrb.h"
#include "jval.h"
// #include "dllist.h"
#include "fields.h"
#include "menu.h"
#include <string.h>
#include <stdlib.h>

#define MAXSECTION 5

typedef struct {
	long number;
	char name[30];
} person;

void getData(char fileName[], JRB *book, int size);

void main()
{
	JRB book;
	JRB ptr;
	JRB tobeDeleted;
	char key[30];
	char sections[MAXSECTION][40] = {"Create a phone book", "Insert a new entry", "Traverse", "Delete an entry", "Drop and exit"};
	int choice;
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:
			book = make_jrb();
			break;
		case 2:
			getData("input.txt", book, 3);
			// printf("Type in the name, number (name number): \n");
			// scanf(" % s % ld", name, &number);
			break;
		case 3:
			jrb_traverse(ptr, book) {
				printf(" %s % ld\n", jval_s(ptr->key), jval_l(ptr->val));
			}
			//how to use a define function
			break;
		case 4:
			while (getchar() != '\n');
			printf("Type in the name to be deleted: \n");
			scanf("%s", key);
			// printf("%s\n", key);
			tobeDeleted = jrb_find_str(book, key);
			//core dumpted
			printf("%s %ld\n", jval_s(tobeDeleted->key), jval_l(tobeDeleted->val));
			// jrb_free_tree(tobeDeleted);
			break;
		case MAXSECTION:
			jrb_free_tree(book);
			break;
		default: printf("Choice must be from 1 to % d\n", MAXSECTION);
			break;
		}
	} while (choice != MAXSECTION);
}

void getData(char fileName[], JRB *book, int size)
{
	FILE *fin;
	fin = fopen(fileName, "r");
	int i;
	person contact;
	for (i = 0; i < size; ++i)
	{
		fscanf(fin, "%s %ld\n", contact.name, &contact.number);
		jrb_insert_str(*book, strdup(contact.name), new_jval_l(contact.number));
	}
	printf("Input done!\n");
}