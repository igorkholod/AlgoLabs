#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGHT 255 //max length for one string

void fileprint(FILE* file_to_print);
void CopyFrom4String(FILE* FromHere, FILE* ToHere);
int LastWordCount(FILE* file_to_count);

int main()
{
    FILE* from; //file to read
    FILE* to; //file to write
    
    if ((from = fopen("from.txt", "r")) == NULL) //opening file from
    {
       perror("Can't open a file from");
       exit(0);
    }
    
    if ((to = fopen("to.txt", "w")) == NULL) //opening file to
    {
       perror("Can't open a file to");
       exit(0);
    }
    //printing a file "from"
    printf("1st file:\n");
    fileprint(from);
    
    printf("\nCopying strings after 3rd from 1st file to 2nd...\n");
    //copying strings after 3rd from "from" to "to"
    rewind(to);
    rewind(from);
    CopyFrom4String(from, to);
    
    fclose(from); //closing "from"
    
    //printing a file "to"
    fclose(to);
    to = fopen("to.txt", "r");
    printf("2nd file:\n");
    fileprint(to);
    
    printf("\nCounting amount of characters of the last word of a 2nd file...\n");
    fclose(to);
    to = fopen("to.txt", "r"); 
    printf("Last word of a 2nd file has %i characters.\n", LastWordCount(to));
    
    fclose(to);
    
    return 0;
}

void fileprint(FILE* file_to_print)
{
    char buff[MAXLENGHT];
    while (fgets(buff, MAXLENGHT, file_to_print))
        printf("%s", buff);
}
void CopyFrom4String(FILE* FromHere, FILE* ToHere)
{
    char buff[MAXLENGHT];
    for (int i = 1; fgets(buff, MAXLENGHT, FromHere) != NULL; i++)
        if (i <= 3)
            continue;
        else
            fputs(buff, ToHere);
}
int LastWordCount(FILE* file_to_count)
{
    char buff[MAXLENGHT];
    //getting the last string of the file
    while (1)
        if (fgets(buff, MAXLENGHT, file_to_count) == NULL)
            break;
    char* word = strtok(buff, " ");
    char lastword[MAXLENGHT];
    
    //getting the last word of the last string
    while (word != NULL)
    {
        strcpy(lastword, word);
        word = strtok(NULL, " ");
    }
    
    //counting the number of charecters in the last word
    int count = 0;
    for (int i = 0; i < strlen(lastword); i++)
        if ((lastword[i] != '\0') && (lastword[i] != '\n'))
            count++;
    
    return count;
}
