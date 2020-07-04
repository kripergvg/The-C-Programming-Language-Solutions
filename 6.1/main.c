#include<stdio.h>
#include <ctype.h>
#include <string.h>

struct Node {
	char* word;
	struct Node* leftNode;
	struct Node* rightNode;
	int occurience;
};

int getword(char*, int);
struct Node* AlocateNode(char* word);
void rememberWord(char* word, struct Node* node);

char words[1000][100];
char(*word)[100] = words;


void main() {
	struct Node* root = NULL;

	while (getword(word, 1000)!= EOF)
	{
		if (root == NULL) {
			root = AlocateNode(word);
		}
		else {
			rememberWord(word, root);
		}

		word++;
	}

	return 0;
}

struct Node nodesStorage[1000];
struct Node* freeNode = nodesStorage;

struct Node* AlocateNode(char* word) {
	struct Node* usedNode = freeNode;
	usedNode->word = word;
	usedNode->leftNode = NULL;
	usedNode->rightNode = NULL;
	usedNode->occurience = 1;
	freeNode++;
	return usedNode;
}

void rememberWord(char* word, struct Node* node) {
	int compareResult = strcmp(node->word, word);
	if (compareResult == 0) {
		node->occurience++;
	}
	else if (compareResult > 0) {
		if (node->leftNode == NULL) {
			node->leftNode = AlocateNode(word);
		}
		else {
			rememberWord(word, node->leftNode);
		}
	}
	else {
		if (node->rightNode == NULL) {
			node->rightNode = AlocateNode(word);
		}
		else {
			rememberWord(word, node->rightNode);
		}
	}
}


int getword(char* word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char* w = word;
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}