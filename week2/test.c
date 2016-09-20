#include "generictab.h"
#include "string.h"

Entry makePhone(void *name, void *phone);
int comparePhone(void *key1, void *key2);

void main()
{
	char number[] = "01695742499";
	char name[] = "Ta Tuan Anh";
	SymbolTable book = createSymbolTable(makePhone, comparePhone);
	addEntry(name, &number, &book);
	printf("%s: %s\n", (char*)book.entries[0].key, (char *)book.entries[0].value);
	dropSymbolTable(&book);
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