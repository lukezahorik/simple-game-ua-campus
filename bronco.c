#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "scanner.h"
#include "locations.h"
//#include "olist.h"

Location *getLoc(FILE*);
Location *findLocation(char*);
int legalUtterance(char*);
void printList(void*);
Logic findLogicFunction(char*);

Node *world = 0;

int main(int argc,char **argv)
    {
    FILE *fp;
    
    Location *loc;
    Node *temp = NULL;
    fp = fopen("locationList.txt", "r");
    loc = getLoc(fp);
    while(!feof(fp))
        {
        temp = join(loc,temp);
        loc = getLoc(fp);
        }
    world = temp;

    fclose(fp);  

//    printf("%s\n",world->place->name);
//    printf("%s\n",world->next->place->name);
//    printf("%s\n",world->next->next->place->name);
//    printf("%p\n",world->next->next->next);

//displays all locations, not needed
//displayList(world,printList);



//game core
    int victory = 0;
    int counter = 20;
    Location *location = head(world);
    printf("///////////////////////////////////////////////////////////////////\n");
    printf("To win the game, you must visit all of the locations on the map!\n");
    printf("Be careful though, as you only have 20 moves to visit all 15 spots!\n");
    printf("///////////////////////////////////////////////////////////////////\n");
    while(victory < 15 && counter != 0)
        {
        printf("You are currently at %s\n",location->name);
        printf("You have %d moves left\n",counter);
        if(location->visited == 0)
            {
            printf("%s\n",location->longer);
            victory++;
            }
        else if(location->visited == 1)
            {
            printf("%s\n",location->shorter);
            }
        //get a legal utterance
        //printf("This is the print statement right before I read something in\n");
        char *verb = readToken(stdin);
        char *noun = 0;
        if(legalUtterance(verb) == 1)
            {
            //good return
            }
        else if(legalUtterance(verb) == 2)
            {
            printf("What do you want to %s?\n",verb);
            char *nounInside = readToken(stdin);
            noun = nounInside;
            //insert an if loop checking to see if you can pick it up
            printf("You %s the %s.\n",verb,nounInside);
            }
        else if(legalUtterance(verb) == 3)
            {
            printf("Sorry mate, but I don't know what that command means!\n");
            }
        else if(legalUtterance(verb) == 4)
            {
            printf("%s\n",location->longer);
            }
        //and now for some blatant copying from the prompt
        char *logicName = location->logic;
        Logic f;
        f = findLogicFunction(logicName);
        location = f(location,verb,noun);
        counter = counter - 1;
        //find the logic function associated with current location
        //call the logic function, returning the location with the return value
        }
    if(counter > 0)
        {
        printf("////////////////////////////////////////////////////////\n");
        printf("Congratulations, you visited all of the places! You win!\n");
        printf("////////////////////////////////////////////////////////\n");
        }
    else if(counter <= 0)
        {
        printf("///////////////////////////////\n");
        printf("You ran out of moves, you lose!\n");
        printf("///////////////////////////////\n");
        }
    
    return 0;    
    }    

void printList(void *curr)
    {
    Node *current = (Node *)curr;
    printf("%s\n",current->place->name);
    printf("%d\n",current->place->visited);
    printf("%s\n",current->place->longer);
    printf("%s\n",current->place->shorter);
    printf("%s\n",current->place->north);
    printf("%s\n",current->place->south);
    printf("%s\n",current->place->east);
    printf("%s\n",current->place->west);
    printf("%s\n",current->place->logic);
    printf("%s\n",current->place->items);
    return;
    }

Location *getLoc(FILE *fp)
    {
    Location *loc;
    loc = malloc(sizeof(Location));

    loc->name = readToken(fp);
    if (feof(fp)) return 0;
    loc->visited = readInt(fp);
    loc->longer = readString(fp);
    loc->shorter = readString(fp);
    loc->north = readString(fp);
    loc->south = readString(fp);
    loc->east = readString(fp);
    loc->west = readString(fp);
    loc->logic = readToken(fp);
    loc->items = readToken(fp);
    return loc;
    }

Location *findLocation(char *name)
    {
    Node *spot = world;

    while(spot != 0)
        {
        if(strcmp((spot->place->name),name) == 0)
            {
            printf("%s\n",spot->place->name);
            return spot->place;
            }
        else if(spot != 0)
            {
            spot = tail(spot);
            }
        }
    return 0;    
    }

int legalUtterance(char *input)
    {
    if(strcmp(input,"north") == 0)
        {
        return 1;
        }
    else if(strcmp(input,"south") == 0)
        {
        return 1;
        }
    else if(strcmp(input,"east") == 0)
        {
        return 1;
        }
    else if(strcmp(input,"west") == 0)
        {
        return 1;
        }
    else if(strcmp(input,"look") == 0)
        {
        return 4;
        }
    else if(strcmp(input,"get") == 0)
        {
        return 2;
        }
    else if(strcmp(input,"drop") == 0)
        {
        return 2;
        }
    else
        {
        return 3;
        }
    }   

Location *basic_location_logic(Location *b,char *verb,char *noun)
    {
    Location *B = b;
    b->visited = 1;
    if(strcmp(verb,"north") == 0)
        {
        B = findLocation(b->north);
        }
    else if(strcmp(verb,"south") == 0)
        {
        B = findLocation(b->south);
        }
    else if(strcmp(verb,"east") == 0)
        {
        B = findLocation(b->east);
        }
    else if(strcmp(verb,"west") == 0)
        {
        B = findLocation(b->west);
        }
/*    else
        {
        printf("I can't do that mate.\n");
        }
*/  
    if(B == 0)
        {
        printf("I can't go there mate!\n");
        return b;
        }
    else
        {
        return B;
        }
    }

Logic findLogicFunction(char *logicName)
    {
    Location *(*g)(Location *,char *,char *);
    if(strcmp(logicName,"basic_location_logic") == 0)
        {
        g = basic_location_logic;
        }
    return g;    
    }    
