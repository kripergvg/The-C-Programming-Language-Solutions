#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 255
#define MAX_WORDS_COUNT 1024
#define MAX_LINE_SYMBOLES MAX_WORDS_COUNT * MAXWORD
#define MAX_UNIQ_WORDS 100000
#define MAX_LINES 1024

void addToIntArray(struct INT_ARRAY* array, int lineNumber);
struct INT_ARRAY* createIntArray();
int parse_words(char* string, struct WORD* words[]);

struct WORD {
	char* text;
	int count;
};

struct WORD_LINES {
	struct WORD* word;
	struct INT_ARRAY* lines;
};

struct INT_ARRAY {
	int* nextElement;
	int* startElement;
};

struct WORD_LINES uniqWords[MAX_UNIQ_WORDS];
int uniqWordsCount = 0;

char buff[MAX_LINE_SYMBOLES];
struct WORD* words[MAX_WORDS_COUNT];

void main(int argc, char* argv[]) {
	char* pathToFile = argv[1];

	FILE* file;
	errno_t err = fopen_s(&file, pathToFile, "r");
	if (err != 0) {
		printf("Couldn't open the file\n");
		return 1;
	}


	int lineNumber = 1;
	while (fgets(buff, MAX_LINE_SYMBOLES, file)) {
		int wordsCount = parse_words(buff, words);

		for (int wordIndex = 0; wordIndex < wordsCount; wordIndex++)
		{
			struct WORD* word = words[wordIndex];
			char wordFound = 0;
			for (int uniqWordIndex = 0; uniqWordIndex < uniqWordsCount && !wordFound; uniqWordIndex++)
			{
				struct WORD_LINES wordLine = uniqWords[uniqWordIndex];
				if (strcmp(wordLine.word->text, word->text) == 0) {
					addToIntArray(wordLine.lines, lineNumber);
					wordFound = 1;
				}
			}

			if (!wordFound) {
				(uniqWords + uniqWordsCount)->word = word;
				(uniqWords + uniqWordsCount)->lines = createIntArray();
				addToIntArray((uniqWords + uniqWordsCount)->lines, lineNumber);
				uniqWordsCount++;

			}
		}
		lineNumber++;
	}

	for (int i = 0; i < uniqWordsCount; i++)
	{
		printf("word: %s lines: ", (uniqWords + i)->word->text);
		for (int* line = (uniqWords + i)->lines->startElement; line < (uniqWords + i)->lines->nextElement; line++)
		{
			printf("%d ", *line);
		}

		printf("\n");
	}

	int closeResult = fclose(file);
}

void addToIntArray(struct INT_ARRAY* array, int lineNumber) {
	for (int* i = array->startElement; i < array->nextElement; i++)
	{
		if (*i == lineNumber) {
			return;
		}
	}

	*(array->nextElement) = lineNumber;
	array->nextElement++;

}

struct INT_ARRAY* createIntArray() {
	int* array = malloc((sizeof(int)) * MAX_LINES);
	struct INT_ARRAY* wrapper = malloc(sizeof(struct INT_ARRAY));
	wrapper->nextElement = array;
	wrapper->startElement = array;
	return wrapper;
}

int parse_words(char* string, struct WORD* words[]) {
	int freeWordIndex = 0;
	char stringStarted = 0;
	char symbol;
	char possibleComment = 0;
	char wordStarted = 0;
	char wordSymbolIndex = 0;
	while (symbol = *string)
	{
		if (stringStarted) {
			if (symbol == '"') {
				stringStarted = 0;
			}
		}
		else if (symbol == '\\') {
			if (possibleComment) {
				return freeWordIndex;
			}
			else {
				possibleComment = 1;
			}
		}
		else {
			if (symbol != ' ' && symbol != '\n' && symbol != '\t') {
				if (!wordStarted) {
					struct WORD* word = malloc(sizeof(struct WORD));
					char* text = malloc(MAXWORD);
					word->text = text;
					words[freeWordIndex] = word;
					wordStarted = 1;
				}

				words[freeWordIndex]->text[wordSymbolIndex] = symbol;
				wordSymbolIndex++;
			}
			else {
				if (wordStarted) {
					words[freeWordIndex]->count = wordSymbolIndex;
					words[freeWordIndex]->text[wordSymbolIndex] = '\0';
					freeWordIndex++;
					wordStarted = 0;
					wordSymbolIndex = 0;
				}
			}

			possibleComment = 0;
		}

		string++;
	}

	return freeWordIndex;
}