#include <stdio.h>
#include <stdlib.h>

//Structure HUMAN
typedef struct
{
    unsigned int number;
    char firstname[25];
    char lastname[25];
    char middlename[25];
    char home_adress[25];
    char phone_number[15];
    unsigned int age;
} HUMAN;

void input_data(HUMAN* hum); //function to write data into a structure
void output_data(HUMAN hum); //to show data from a structure
void delete_age(HUMAN* hum_from, HUMAN* hum_to, int fromsize, unsigned int age);//to delete human with specified age
void add_human(HUMAN* hum_from, HUMAN* hum_to, int fromsize, unsigned int num, HUMAN add);//to add human after number

int main()
{
    FILE *fin; 
    HUMAN a;
    HUMAN b;
    HUMAN array[5];
    HUMAN add;
    char A;
    //int count = 0;
    //opening a file for writing
    if ((fin = fopen("data.txt", "rb")) == NULL)
    {
        if ((fin = fopen("data.txt", "wb")) == NULL)
        {
            perror("Can't open a file");
            exit(0);
        }   
        //writting info about each human
        for (int i = 0; i < 5; i++)
        {
            printf("Write info about human %i:\n", i + 1);
            input_data(&a);
        
            fwrite(&a, sizeof(a), 1, fin);
            fclose(fin);
            fin = fopen("data.txt", "ab");
        }
    }
    else
    {
        printf("File already exists. Do you want to rewrite it? (y, n)");
        A = getchar();
        if ((A == 'y') || A == 'Y')
        {
            fclose(fin);
            if ((fin = fopen("data.txt", "wb")) == NULL)
            {
                perror("Can't open a file");
                exit(0);
            }
            //writting info about each human
            for (int i = 0; i < 5; i++)
            {
                    printf("Write info about human %i:\n", i + 1);
                    input_data(&a);
        
                    fwrite(&a, sizeof(a), 1, fin);
            }
        }
        else if ((A == 'n') || (A == 'N'))
        {
            int l = 0;
            printf("Data that already exists in file:\n");
            while (!feof(fin))
            {
                fread(&a, sizeof(HUMAN), 1, fin);
                if (feof(fin))
                    break;
                printf("Info about human %i:\n", l + 1);
                output_data(a);
                l++;
            }
            
            if (l == 0)
                printf("FILE IS EMPTY!\n");
            
            fclose(fin);
            fin = fopen("data.txt", "ab");
            
            printf("More data:\n");
            for ( ; l < 5; l++)
            {
                printf("Write info about human %i:\n", l + 1);
                input_data(&b);
        
                fwrite(&b, sizeof(b), 1, fin);
            }
        }
    }   
    
    
    fclose(fin); //closing a file
            
    unsigned int del_age; 
    unsigned int add_num; 
    
    if ((fin = fopen("data.txt", "rb")) == NULL) //opening a file for reading
    {
       perror("Can't open a file");
       exit(0);
    }
    
    //reading info about humans from file
    int delc = 0;
    for (int i = 0; i < 5; i++)
        fread(&array[i], sizeof(HUMAN), 1, fin);
        
    fclose(fin);
    
    printf("\nYour data:\n\n"); //printing data from a file
    for (int i = 0; i < 5; i++)
    {
        printf("Info about human %i:\n", i + 1);
        output_data(array[i]);
    }

    printf("Age to be deleted: "); 
    scanf("%i", &del_age);
    
    for (int i = 0; i < 5; i++) //counting humans that will be deleted
        if (array[i].age == del_age)
            delc++;
    
    int size = 5 - delc;
    HUMAN array_newd[size];
    HUMAN array_newa[size + 1];

    delete_age(array, array_newd, 5, del_age); //deleting humans
    
    printf("\n\nInfo after deleting:\n");
    if (size == 0)
        printf("EMPTY LIST!\n");
    for (int i = 0; i < size; i++)
    {
        printf("Info about human %i:\n", i + 1);
        output_data(array_newd[i]);
        array_newd[i].number = i + 1;
    }
    
    printf("Number, after which you want to add new human: "); 
    scanf("%i", &add_num); 
         
    printf("Info about human you want to add:\n"); 
    input_data(&add);
    
    add_human(array_newd, array_newa, size, add_num, add); //adding human
        
    if ((fin = fopen("data.txt", "wb")) == NULL) //opening file for writing
    {
       perror("Can't open a file");
       exit(0);
    }
    
    //writing a final info to a file
    for (int i = 0; i < size + 1; i++)
        fwrite(&array_newa[i], sizeof(add), 1, fin);
        
    fclose(fin);
    
    //printing an info
    printf("\nFinal info:\n");
    for (int i = 0; i < size + 1; i++)
    {
        printf("Info about human %i:\n", i + 1);
        output_data(array_newa[i]);
    }
    
    return 0;
}
        
void input_data(HUMAN* hum)
{
    printf("First name: ");
    scanf("%s", hum->firstname);
    printf("Last name: ");
    scanf("%s", hum->lastname);
    printf("Middle name: ");
    scanf("%s", hum->middlename);
    printf("Home adress: ");
    scanf("%s", hum->home_adress);
    printf("Phone number: ");
    scanf("%s", hum->phone_number);
    printf("Age: ");
    scanf("%i", &hum->age);
}

void output_data(HUMAN hum)
{
    printf("First name: %s\n", hum.firstname);
    printf("Last name: %s\n", hum.lastname);
    printf("Middle name: %s\n", hum.middlename);
    printf("Home adress: %s\n", hum.home_adress);
    printf("Phone number: %s\n", hum.phone_number);
    printf("Age: %i\n\n", hum.age);
}

void delete_age(HUMAN* hum_from, HUMAN* hum_to, int fromsize, unsigned int age)
{
    for (int i = 0, k = 0; i < fromsize; i++)
        if (hum_from[i].age != age)
            hum_to[k++] = hum_from[i];
}

void add_human(HUMAN* hum_from, HUMAN* hum_to, int fromsize, unsigned int num, HUMAN add)
{
    if (fromsize == 0)
        hum_to[0] = add;
    else
        for (int i = 0, k = 0; i < fromsize; i++)
        {
            hum_to[k++] = hum_from[i];
            if (hum_from[i].number == num)
                hum_to[k++] = add;
        }
}    
