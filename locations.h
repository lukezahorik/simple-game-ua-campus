#ifndef LOC_STRUCT
#define LOC_STRUCT
    
    typedef struct location
        {
        char *name;
        int visited;
        char *longer;
        char *shorter;
        char *north;
        char *south;
        char *east;
        char *west;
        char *logic;
        char *items;
        } Location;

#endif
#ifndef NODE_STRUCT
#define NODE_STRUCT

    typedef struct node
        {
        Location *place;
        struct node *next;
        } Node;

#endif
#ifndef ADV_STRUCT
#define ADV_STRUCT

    typedef struct adventurer
        {
        int score;
        int strength;
        char *items;
        } Adventurer;

#endif        
#ifndef NODE2_STRUCT
#define NODE2_STRUCT

    typedef struct node2
        {
        void *value;
        struct node *next;
        } Node2;

#endif  

//define logic (code stolen from project outline, may need more testing)
    typedef Location *(*Logic)(Location *,char *,char *);
        



/* Node prototypes */

Node *newNode(Location *value,Node *next);
Node *newEmptyNode(void);

/* List prototypes */

Node *newEmptyList(void);
void *head(Node *items);
Node *tail(Node *items);
void setHead(Node *items,void *s);
void setTail(Node *items,Node *newList);
Node *join(Location *s,Node *rest);
Node *arrayToList(void **items,int size);
void displayList(Node *items,void (*display)(void *));
void freeList(Node *items);
Location *locTail(Node *items);
