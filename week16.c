#include <stdio.h>

FILE *openFile(char *fileName, char *mode);
void closeFile(FILE *fptr);
char dictionary[80000][20];

void main()
{
	FILE *fptr;
	fptr = openFile("dict.txt", "r");
	int input = 1;
	int i = 0;
	if (fptr != NULL)
	{
		while (!feof(fptr))
		{
			fscanf(fptr, "%s", dictionary[i]);
			i++;
		}
		fclose(fptr);

		while (input != 0) {
			printf("Options: 1 = check spelling, 2 = find words, 0 = quit: \n");
			scanf("%d", &input);
			switch (input) 
			{
			case 1: 
				spellCheck();
				break;
			case 2: 
				findWord();
				break;
			case 0: 
				break;
			default: 
				printf("Thats not a valid Input\n");
				break;
			}
		}
	}
}

FILE * openFile(char *fileName, char *mode)
{
	FILE *fptr = fopen(fileName, mode);

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
	}

	return fptr;
}

void closeFile(FILE *fptr)
{
	fclose(fptr);
}

int spellCheck() 
{
	char word[20];
	printf("Enter a word to be checked: ");
	scanf("%s", word);
	for (int i = 0; i < 80000; i++) {
		if (strcmp(word, dictionary[i]) == 0) {
			printf("You have spelled this word correctly!\n");
			return 1;
		}
	}
	printf("You have not spelled this word correctly!\n");
}

int findWord()
{
	char bestFit[100];
	int matches = 0;
	int hMatch = 0;
	int i = 0, j = 0, lenght = 0;
	char temp[20];
	int tempCount = 0, wordCount = 0;

	puts("Enter letters you have: ");

	scanf("%s", temp);

	for (i = 0; i < 80000; i++)
	{
		matches = 0;
		lenght = strlen(dictionary[i]);

		for (j = 0; j < lenght; j++)
		{
			tempCount = 0;
			wordCount = 0;
			tempCount = countCharOccurence(temp, dictionary[i][j]);
			wordCount = countCharOccurence(dictionary[i], dictionary[i][j]);

			if ((tempCount > 0) && (tempCount == wordCount))
			{
				matches = matches + 1;
			}
			else
			{
				matches = 0;
				break;
			}
		}

		if (matches > hMatch)
		{
			strcpy(bestFit, dictionary[i]);
			hMatch = matches;
		}
	}

	printf("The best Fit for \"%s\" is \"%s\"  [%d]\n", temp, bestFit, hMatch);

	return matches;
}

int countCharOccurence(char *string, char c)
{
	int i = 0, count = 0, len = 0;
	len = strlen(string);
	for (i = 0; i < len; i++)
	{
		if (string[i] == c) count++;
	}
	return count;
}