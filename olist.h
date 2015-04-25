typedef struct node
    {
    void *value;
    struct node *next;
    } Node;

/* Node prototypes */

Node *newNode(void *value,Node *next);
Node *newEmptyNode(void);

/* List prototypes */

Node *newEmptyList(void);
void *head(Node *items);
Node *tail(Node *items);
void setHead(Node *items,void *s);
void setTail(Node *items,Node *newList);
Node *join(void *s,Node *rest);
Node *arrayToList(void **items,int size);
void displayList(Node *items,void (*display)(void *));
void freeList(Node *items);
