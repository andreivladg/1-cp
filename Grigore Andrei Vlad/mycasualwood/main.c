#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TITLE 50
#define ACTORS 10
#define MAX 60
#define Max_length 100

typedef struct
{
    char *title;
    char **cast;
    int movieCount;
} Hollywood;

void initializeMovies(Hollywood *movie)
{
    movie->title=(char*)malloc(sizeof(char)*MAX_TITLE);
    movie->cast=(char**)malloc(sizeof(char*)*ACTORS);
    for(int i=0;i<ACTORS;i++)
    {
        movie->cast[i]=(char*)malloc(sizeof(char)*MAX);
    }
}

int isActorInMovie(char *actorName, Hollywood *movie, int count, int i)
{
    int ok=0;
    for(int j=0; j<movie[i].movieCount && ok==0; j++)
    {
        if(strcmp(actorName,movie[i].cast[j])==0)
            ok=1;
    }
    return ok;
}
void displayFriends(char *actorName, Hollywood *movie, int count)
{
    printf("The friends of %s are:\n",actorName);
    for(int i=0; i<count; i++)
    {
        if(isActorInMovie(actorName,movie,count,i)!=0)
        {
            for(int j=0; j<movie[i].movieCount; j++)
            {
                if(strcmp(movie[i].cast[j],actorName)!=0)
                {
                    printf("%s\n",movie[i].cast[j]);
                }
            }
        }
    }
}

void findMaxFriends(Hollywood *movie,int *maxFriends, char *maxName,char *actorName, int count)
{
    int nrOfFriends;
    for(int i=0; i<count; i++)
    {
        for(int j=0; j<movie[i].movieCount; j++)
        {
            strcpy(actorName,movie[i].cast[j]);
            nrOfFriends=0;
            for(int k=0; k<count; k++)
            {
                if(isActorInMovie(actorName,movie,count,k)!=0)
                {
                    nrOfFriends+=movie[k].movieCount-1;
                }
            }
            if(nrOfFriends>*maxFriends)
                    {
                        *maxFriends=nrOfFriends;
                        strcpy(maxName,actorName);
                    }
        }
    }
}

int main()
{
    FILE *f=fopen("movies.txt","r");
    Hollywood *movie=(Hollywood*)malloc(sizeof(Hollywood)*MAX);
    for(int i=0;i<MAX;i++)
    {
        initializeMovies(&movie[i]);
    }
    char *strbuf=(char*)malloc(sizeof(char)*Max_length);
    int count=0;
    while(fgets(strbuf,Max_length,f)!=NULL)
    {
        char *p;
        p=strtok(strbuf,",");
        strcpy(movie[count].title,p);
        puts(movie[count].title);
        movie[count].movieCount=0;
        p=strtok(NULL,",");
        while(p)
        {
            strcpy(movie[count].cast[movie[count].movieCount],p);
            puts(movie[count].cast[movie[count].movieCount]);
            movie[count].movieCount++;
            p=strtok(NULL,",");
        }
        count++;
    }
    char *actorName=(char*)malloc(sizeof(char)*MAX);
    gets(actorName);
    displayFriends(actorName,movie,count);
    char* maxName=(char*)malloc(sizeof(char)*MAX);
    int maxFriends=0;
    findMaxFriends(movie,&maxFriends,maxName,actorName,count);
    printf("\nMost popular actor is %s. He has %d friends\n",maxName,maxFriends);
    fclose(f);
    return 0;
}
