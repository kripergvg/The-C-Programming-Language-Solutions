struct nlist* install(char* name, char* defn);
struct nlist* lookup(char* s);

void undef(char* name);

struct nlist {
	struct nlist* next;
	struct nlist* prev;
	char* name;
	char* defn;
};


#ifdef HASHSET_IMPLEMETATION

#include <stdio.h>
#include <string.h>

#define HASHSIZE 101

static struct nlist* hashtab[HASHSIZE];

unsigned int hash(char* s) {
	unsigned int hashval;

	for (hashval = 0; *s != '\0'; s++)
	{
		hashval = *s + 31 * hashval;
	}

	return hashval % HASHSIZE;
}

struct nlist* lookup(char* s) {
	struct nlist* np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
	{
		if (strcmp(s, np->name) == 0)
			return np;
	}

	return NULL;
}

struct nlist* install(char* name, char* defn) {
	struct nlist* np;
	unsigned int hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist*) malloc(sizeof(*np));
		if (np == NULL || (np->name = _strdup(name)) == NULL) {
			return NULL;
		}

		np->prev = NULL;

		hashval = hash(name);
		struct nlist* next = hashtab[hashval];
		np->next = next;
		if (next != NULL) {
			next->prev = np;
		}

		hashtab[hashval] = np;
	}
	else {
		free((void*)np->defn);
	}

	np->defn = _strdup(defn);
}

void undef(char* name) {
	struct nlist* removeElement = lookup(name);
	if (removeElement != NULL) {
		if (removeElement->prev != NULL) {
			removeElement->prev->next = removeElement->next;
		}
		else {
			hashtab[hash(name)] = removeElement->next;
		}

		free(removeElement->name);
		free(removeElement->defn);
		free(removeElement);
	}
}
#endif