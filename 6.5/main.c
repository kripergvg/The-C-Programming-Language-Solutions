#define HASHSET_IMPLEMETATION

#include "hashset.h";
#include <stdio.h>


void main() {
	install("test", "1");
	install("test1", "2");
	install("test2", "3");

	printf("%s\n", lookup("test")->defn);
	printf("%s\n", lookup("test1")->defn);
	printf("%s\n", lookup("test2")->defn);

	undef("test");
	struct nlist* element1 = lookup("test");
}