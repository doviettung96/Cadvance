#include "symboltab.h"
#include "string.h"
#include "menu.h"

Entry makePhone(void *name, void *phone);
int comparePhone(void *key1, void *key2);

void main()
{
	int choice;
	char sections[5][40] = {"Create new phonebook", "Drop phonebook", "Add new phone number", "Get phone number", "Exit"};
	char number[] = "01695742499";
	char name[] = "Ta Tuan Anh";
	char key[30];
	Entry *testEntry;
	SymbolTable book;

	do {
		choice = getMenu(sections, 5);
		switch (choice) {
		case 1:
			book  = createSymbolTable(makePhone, comparePhone);
			break;
		case 2:
			dropSymbolTable(&book);
			break;
			
		case 3:
			addEntry(name, &number, &book);
			printf("%s: %s\n", (char*)book.entries[0].key, (char *)book.entries[0].value);
			break;
		case 4:

			printf("Type in a name\n");
			while (getchar() != '\n');
			// printf("Eroor!\n");
			scanf("%s", key);
			// printf("Eroor!\n");
			testEntry = getEntry(key, book);
			printf("%s: %s\n", (char *)testEntry[0].key, (char *)testEntry[0].value);
			break;
		case 5: break;
		}
	} while (choice != 5);

}
Entry makePhone(void *name, void *phone)
{
	Entry res;
	res.key = strdup((char*)name);
	res.value = strdup((char*)phone);
	// memcpy(res.value, phone, sizeof(long));
	return res;
}

int comparePhone(void *key1, void *key2)
{
	return strcmp((char *)key1, (char *)key2);
}