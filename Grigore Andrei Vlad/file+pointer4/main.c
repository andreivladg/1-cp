#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100
#define CARS 16
#include  <string.h>
typedef struct
{
    char *brand;
    char *owner;
    char *color;
    char *number;
} garage;

void initializeGarage(garage * car)
{
    car->brand=(char*)malloc(sizeof(char)*MAX_LENGTH);
    car->owner=(char*)malloc(sizeof(char)*MAX_LENGTH);
    car->color=(char*)malloc(sizeof(char)*MAX_LENGTH);
    car->number=(char*)malloc(sizeof(char)*MAX_LENGTH);

}
void sortByOwnerName(garage *car,char *carColor,int count)
{
    garage *aux=(garage*)malloc(sizeof(garage)*MAX_LENGTH);
    for(int i=0;i<CARS;i++)
    {
    initializeGarage(&aux[i]);
    }
    for(int i=0; i<count; i++)
    {
        for(int j=i+1; j<count; j++)
        {
            if(strcmp(car[i].owner,car[j].owner)>0)
            {
               *aux=car[i];
               car[i]=car[j];
               car[j]=*aux;
            }
        }

    }
    for(int i=0;i<count;i++)
    {if(strstr(carColor,car[i].color)!=NULL)
    {
      printf("%s %s %s %s",car[i].brand,car[i].owner,car[i].color,car[i].number);
    }

    }
}

int main()
{
    FILE *f;
    f=fopen("garage.txt","r");
    garage *car=(garage*)malloc(sizeof(garage)*MAX_LENGTH);
    char *strbuf=(char*)malloc(sizeof(char)*MAX_LENGTH);
    for(int i=0; i<CARS; i++)
    {
        initializeGarage(&car[i]);
    }
    int count;
    while(fgets(strbuf,MAX_LENGTH,f)!=NULL)
    {
        sscanf(strbuf,"%s %s %s %s",car[count].brand,car[count].owner,car[count].color,car[count].number);
        puts(strbuf);
        strcpy(car[count].brand,strtok(strbuf," "));
        strcpy(car[count].owner,strtok(NULL," "));
        strcpy(car[count].color,strtok(NULL," "));
        strcpy(car[count].number,strtok(NULL," "));
        puts(car[count].brand);
        puts(car[count].owner);
        puts(car[count].color);
        puts(car[count].number);
        count++;
    }
    char *carColor=(char*)malloc(sizeof(char)*MAX_LENGTH);
    gets(carColor);
    sortByOwnerName(car,carColor,count);
    fclose(f);
    return 0;
}
