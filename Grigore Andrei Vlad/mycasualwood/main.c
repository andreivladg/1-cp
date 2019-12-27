#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 7

typedef struct
{
    char *movie;
    char *name;
} actors;
void initializeActor(actors *a)
{
    a->movie=(char*)malloc(sizeof(char)*100);
    a->name=(char*)malloc(sizeof(char)*100);
}


void readMovies(char *strbuf)
{
    FILE *f=fopen("movies.txt","r");
    char *p=(char*)malloc(sizeof(char)*100);
    while(fgets(strbuf,100,f)!=NULL)
    {
        p=strtok(strbuf,",");
        puts(p);
    }
    fclose(f);

}
void printFriends(actors *a,char *actor,int *friends)
{
    FILE *f=fopen("movies.txt","r");
    int i=0,j;
    char *p=(char*)malloc(sizeof(char*)*100);
    char *strbuf=(char*)malloc(sizeof(char*)*100);
    while(fgets(strbuf,100,f)!=NULL)
    {
        char *movie=strtok(strbuf,",");
        p=strtok(NULL,",");
        while(p!=NULL)
        {
            if(i==0)
            {
                initializeActor(&a[i]);
                strcpy(a[i].movie,movie);
                strcpy(a[i].name,p);
                i++;
            }
        }
        for(i=0; i<MAX; i++)
        {
            if(strcmp(a[i].name,actor)==0)
            {
                friends[i]=0;
                for(j=0; j<MAX; j++)
                {
                    if(strstr(a[i].movie,a[j].movie)!=NULL&&i!=j)
                    {
                        printf("\n%s",a[j].name);
                        friends[i]++;
                    }
                }
            }
            printf("\n%d",friends[i]);

        }






    }
    fclose(f);

}
int main()
{

    actors *a=(actors*)malloc(sizeof(actors)*100);
    char *strbuf=(char*)malloc(sizeof(char)*100);
    char*actor=(char*)malloc(sizeof(char)*100);
    int *friends=(int*)malloc(sizeof(int)*30);
    readMovies(strbuf);
    printf("Enter name of the actor:");
    gets(actor);
    printFriends(a,actor,friends);



    return 0;
}
