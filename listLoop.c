#include <stdio.h>
#include <stdlib.h>
#include "ilist.h"
#include "listLoop.h"

/******** ListsLoops *********************/

int
getListIndex(Node *items,int index)
    {
    while (index > 0)
        {
        items = tail(items);
        --index;
        }
    return head(items);
    }

Node *
find(int value,Node *items)
    {
    while (items != 0 && head(items) != value)
        {
        items = tail(items);
        }
    return items;
    }

Node *
find2(int value,Node *items)
    {
    while (items != 0)
        {
        if (head(items) == value)
             {
             return items;
             }
        items = tail(items);
        }
    return 0;
    }

Node *
getPenultimateNode(Node *items)
    {
    Node *trailing = 0;
    Node *leading = items;
    while (tail(leading) != 0) //when to stop walking
        {
        trailing = leading;
        leading = tail(leading);
        }
    return trailing;
    }

Node *
getPenultimateNode2(Node *items)
    {
    Node *trailing = items;
    while (tail(tail(trailing)) != 0)
        {
        trailing = tail(trailing);
        }
    return trailing;
    }

void
insertInOrder(int value,Node *items)
    {
    Node *trailing = 0;
    Node *leading = items;
    while (head(leading) < value) //when to keep walking
        {
        trailing = leading;
        leading = tail(leading);
        }
    //insert new value in between trailing and leading
    Node *n = newNode(value,0);
    setTail(n,leading);
    setTail(trailing,n);
    }

int isEven(int x) { return x % 2 == 0; }

int
sumEvens(Node *items)
    {
    int total = 0;
    Node *spot = items;
    while (spot != 0)
        {
        int v = head(spot);
        if (v % 2 == 0)
            total += v;
        spot = tail(spot);
        }
    return total;
    }

Node *
extractEvens(Node *items)
    {
    Node *result = 0;
    Node *spot = items;
    while (spot != 0)
        {
        int v = head(spot);
        if (isEven(v))
            result = join(head(spot),result);
        spot = tail(spot);
        }
    return result;
    }
