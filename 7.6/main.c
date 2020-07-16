#include <stdio.h>

void main(int argc, char* argv[]) {
	if (argc == 3) {
		char* file1Name = argv[1];
		char* file2Name = argv[2];

		FILE* file1 = NULL;
		FILE* file2 = NULL;
		fopen_s(&file1, file1Name, "r");
		fopen_s(&file2, file2Name, "r");

		char file1LineBuffer[1024];
		char file2LineBuffer[1024];

		char* file1Result = NULL;
		char* file2Result = NULL;
		while ((file1Result=fgets(file1LineBuffer, 1024, file1)) && (file2Result=fgets(file2LineBuffer, 1024, file2)))
		{
			char* symbol1 = file1LineBuffer;
			char* symbol2 = file2LineBuffer;
			while (*symbol1 && *symbol2 && *symbol1 == *symbol2)
			{
				symbol1 = symbol1++;
				symbol2 = symbol2++;
			}

			if (*symbol1 != *symbol2) {
				printf("%s", file1LineBuffer);
				printf("%s", file2LineBuffer);
				exit(0);
			}
		}

		if (file1Result != file2Result) {
			printf("%s", file1LineBuffer);
			printf("%s", file2LineBuffer);
		}

		fclose(file1);
		fclose(file2);
	}
}