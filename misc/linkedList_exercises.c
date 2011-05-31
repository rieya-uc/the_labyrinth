#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Some notes on pointers, memory, and linked list construction */

typedef struct node {
    int data;
    struct node* next;
} node;


/* General unity functions */

//Creates a list containing 1,2,3. Not very useful. For testing.
node* BuildOneTwoThree() {

    node* head = malloc(sizeof(node));
    node* second = malloc(sizeof(node));
    node* third = malloc(sizeof(node));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    return head;
}

//Creates an empty list 
//Used to test tailPush1(...) below.
node* BuildNullEmpty() {
    node* head = NULL;
    return head;
}

void print(node* head) {
    while (head != NULL) {
        printf("%i ",head->data);
        head = head->next;
    }
    printf("\n");
}

int length(node* head) {
    node* current = head;
    
    int len = 0;
    while(current != NULL) {
        current = current->next;
        len++;
    }

    return len;
}

int push(node** headRef, int data) {
    node* new = malloc(sizeof(node));
    new->data = data;
    new->next = *headRef;
    *headRef = new;

    // node** head...
    // push(&head, data)
    // and in C++?
}

int isEmpty(node* head) {
    if (head == NULL)
        return 1;
    else
        return 0;
}
/******************** Exercises *******************/


//tail push using special case
void tailPush1(node** headRef, int data) {
    //use a tail pointer if pushing multiple times
    //node* tail;
    node* new = malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    if (*headRef == NULL) {
        *headRef = new;
        //tail = *headRef;
    }
    else {
        node* current = *headRef;
        //or use tail ptr so don't have to keep iterating
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

//Counts the number of times a given int occurs in a list.
int count(node* head, int toFind) {
    int c = 0;
    while (head != NULL) {
        if (head->data == toFind) {
            c++;
        }
        head = head->next;
    }

    return c;
}

//Returns the nth data value in a list
int getNth(node* head, int nth) {
    //check list is long enough
    assert(length(head) > nth);

    int i;   //gcc doesn't allow for-loop initialisation!
    for (i = 0; i < nth; ++i) {
        head = head->next;
    }

    return head->data;
}

//Deallocates a lists memory and sets head pointer to NULL
void deleteList(node** headRef) {
    //Go to end of list
    node* current = *headRef;
    node* next = current;
    while(next != NULL) {
        printf("deleting %i\n",current->data);
        next = current->next;
        free(current);
        current = next;
    }
    *headRef = NULL;
}

//Takes a non-empty list, deletes the head node, and returns head node's data
int pop(node** headRef){
    assert(!isEmpty(*headRef));
    
    node* temp = *headRef;
    int data = temp->data;
    *headRef = temp->next;
    free(temp);

    return data;
}

//Inserts new node at nth position
void insertNth(node** headRef, int index, int data) {
    if (*headRef == NULL) {
        push(headRef, data);
    }
    else {
        node* temp = *headRef;
        node* new = malloc(sizeof(node));
        new->data = data;

        int i;
        for(i = 0; i < index-1; ++i) {
            temp = temp->next;
        }
        new->next = temp->next;
        temp->next = new;
    }
}

//Takes a sorted list and inserts a new node in the correct position

//Checks list is sorted in ascending order
int isSorted(node* head){
    assert(head != NULL); // is an empty list sorted or not?

    int sorted = 1;
    int previous = head->data;

    while(head != NULL) {
        if (previous > head->data) {
            sorted = 0;
            break;
        }
        previous = head->data;
        head = head->next;
    }

    return sorted;
}
        


// Takes a sorted list and inserts new node in the correct position.
// Note: no checks to ensure list is sorted is made or list isn't empty.
void sortedInsert(node** headRef, node* new) {
    int data = new->data;
    node* upper = *headRef;
    node* lower = *headRef;

    if (*headRef == NULL || (*headRef)->data >= data) {
        new->next = *headRef;
        *headRef = new;
    }
    else {
        while (upper != NULL && upper->data < data) {
            lower = upper;
            upper = upper->next;
        }
        lower->next = new;
        new->next = upper;
    }
    
}

//Sorts a list using sortedInsert above
void insertSort(node** headRef) {
    node* result = NULL;
    int len = length(*headRef);
    int i;
    for (i = 0; i < len; ++i) {
        node* new = malloc(sizeof(node));
        new->data = pop(headRef);
        new->next = NULL;

        sortedInsert(&result, new);
        //print(result);
    }
    *headRef = result;

}

void insertSort2(node** headRef) {
    // Without all the freeing and allocating...
    node* result = NULL;
    node* n = *headRef;
    while(n != NULL) {
        *headRef = (*headRef)->next;
        sortedInsert(&result, n);
        n = *headRef;
        //print(result);
    }

    *headRef = result;
}


//Takes two lists and appends the second onto the first
//e.g. a = {1,2} b = {3,4} should give a = {1,2,3,4}
void append(node** aHeadRef, node* bHead) {
    node* tail = *aHeadRef;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = bHead;
}

//Given a list, split into two sublists - one for the front half and
//one for the back. If the number of elements is odd, add to front list.
void frontBackSplit(node* list, node** front, node** back){
    assert(list != NULL);

    node* temp = list;
    int len = length(list);

    if (len == 1 || len == 2) {
        *front = list;
        *back = NULL;
    }

    *front = list;  //Now front contains all of list
    int i;
    for(i = 0; i < (len-1)/2; ++i) { //-1 to correct for odd numbered lengths
        temp = temp->next;
    }
    
    *back = temp->next;    
    temp->next = NULL;

    //This solution screws up the original list.
    //But I checked the solutions pdf and so does the official answer.
}

//Not my solution, from the solutions pdf.
//I just copied it here 'cos it's a neat answer.
//Uses two pointers, moves one 2 nodes at a time, and the other
//one at a time. When the fast pointer is at the end of the list,
//the slow pointer is half-way through.
void frontBackSplit2(node* source, node** front, node** back) {
    node* fast;
    node* slow;
    if (source==NULL || source->next==NULL) {
        *front = source;
        *back = NULL;
    }
    else {
        slow = source;
        fast = source->next;

        //Advance 'fast' two nodes, and advance 'slow' one node
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow=slow->next;
                fast=fast->next;
            }
        }

        // 'slow is before the midepoint in the list, so split it in two
        // at that point.
        *front = source;
        *back = slow->next;
        slow->next = NULL;
    }
}

//Takes a list sorted in increasing order and deletes duplicate nodes.
//Ideally the list should only be traversed once.
void removeDuplicates(node** list){
    if (length(*list) < 2) {
        return;
    }
    node* left = *list;
    node* right = left->next;
    while(right != NULL) {
        if (left->data == right->data) {
            left->next = right->next;
            free(right);
            right = left->next;
        }
        else {
            left = left->next;
            right = right->next;
        }
    }
}

// Takes two lists, removes the front node from the second list,
// and pushes it onto the front of the first list.
void moveNode(node** aRef, node** bRef) {
    assert(*bRef != NULL);

    node* temp = *bRef;
    *bRef = temp->next;
    temp->next = *aRef;
    *aRef = temp;
}

// Takes one list and divides up its nodes to make two smaller lists.
// The sublists should be made from alternating elements in the 
// original list.
void alternatingSplit(node* source, node** aRef, node** bRef) {
    int len = length(source);
    int i;
    for(i = 0; i < len/2; ++i) {
        moveNode(aRef, &source);
        moveNode(bRef, &source);
    }
    // For lists with an odd number of elements
    if (source != NULL) {
        moveNode(aRef, &source);
    }

    //Destroys source list
}

// Takes two lists, and merges together, taking nodes alternately from
// each list. If one of the lists run out, all the nodes should be taken
// from the other list.
// {1,2,3} + {7, 13,1} should return {1,7,2,13,3,1}
node* shuffleMerge(node* a, node* b) {
    node dummy;
    node* tail = &dummy;
    dummy.next = NULL;

    while(a != NULL || b != NULL) {
        if (a != NULL) {
            tail->next = a;
            tail = a;
            a = tail->next;
        }
        if (b != NULL) {
            tail->next = b;
            tail = b;
            b = tail->next;
        }
    }

    return dummy.next;

}

// Compact recursive solution from pdf. Works, but doesn't return
// the list in the order specified above.
node* shuffleMerge2(node* a, node* b) {    
    node* result;
    node* recur;
    if (a==NULL) return(b);          // see if either list is empty
        else if (b==NULL) return(a);
    else {
        // it turns out to be convenient to do the recursive call first --
        // otherwise a->next and b->next need temporary storage.
        recur = shuffleMerge(a->next, b->next);
        result = a;       // one node from a
        a->next = b;      // one from b
        b->next = recur;  // then the rest
        return(result);
    }
}

// Takes two lists which are sorted in increasing order, and merges
// into one list of increasing order. Ideally, should make only one
// pass through each list.
node* sortedMerge(node* a, node* b) {
    node dummy;
    node* result = &dummy;
    dummy.next = NULL;
    while (a != NULL && b != NULL) {
        node* temp = NULL;
        if (a->data < b->data) {
            moveNode(&temp,&a);
        }
        else {
            moveNode(&temp,&b);
        }
        result->next = temp;
        result = temp;
    }

    if (a != NULL) {
        result->next = a;
    }
    if (b != NULL) {
        result->next = b;
    }

    return dummy.next;

    // Now try writing a recursive sortedmerge
}

// A recursive merge sort using frontBackSplit() and SortedMerge().
void mergeSort(node** headRef) {
    node* a = NULL;
    node* b = NULL;

    frontBackSplit(*headRef, &a, &b);
        
    if (length(a) > 1) {
        mergeSort(&a);
    }
    if (length(b) > 1) {
        mergeSort(&b);
    }
    *headRef = sortedMerge(a,b);
}

// Given two lists sorted in increasing order, returns a new list
// representing the intersection of the two lists. The original two lists
// are not modified.
node* sortedIntersect(node* a, node* b) {
    // Assuming the lists are sets? Neither the question or solution
    // mentions it.
    node dummy;
    node* result = &dummy;
    dummy.next = NULL;

    while(a != NULL && b != NULL) {
        if (a->data == b->data) {
            if (a->data != result->data) {
                push(&(result->next),a->data);
                result = result->next;
            }
            a = a->next;
            b = b->next;
        }
        else if (a->data < b->data) {
            a = a->next;
        }
        else {
            b = b->next;
        }
    }

    return (dummy.next);
}

// Reverses a list by rearranging all the .next pointers and
// the head pointer.
void reverse(node** headRef) {
    node* result = NULL;
    while(*headRef != NULL) {
        moveNode(&result, headRef);
    }
   *headRef = result;
}

// A recursive solution to Reverse, making a single pass through the list.
void recursiveReverse(node** headRef) {
    node* temp = (*headRef)->next;
    if (temp->next != NULL) {
        recursiveReverse(&temp);
        temp->next = *headRef;
        (*headRef)->next = NULL;
    }
    else {
        temp->next = *headRef;
        (*headRef)->next = NULL;
        *headRef = temp;
    }



}


/******************** Some Notes ********************/

/* This doesn't work, as the "new head" is a copy,
 * and it gets deleted at the end of the function.
 *
 * Note: This and the correct push(), push to the *start*
 * of the list. Faster than pushing to tail end, 
 * finding NULL.
 */
void wrongPush(struct node* head, int newData) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = newData;
    newNode->next = head;
    head = newNode;

    //if you can't see why this doesn't work, try drawing it!
}

/* Doesn't work for an empty list, otherwise fine.
 * Options: Use a "dummy" node when the list is empty.
 *          Create a special case + (use a tail pointer or find list end)
 *          Use local references.
 */

void wrongTailPush(struct node** headRef, int newData) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = newData;
    newNode->next = NULL;
    struct node* tail = *headRef;
    while(tail->next != NULL) {
        tail = tail->next;
     }

    tail->next = newNode;

    //and what happens when it's an empty list?
}

int main() {
    node* a = NULL;
    push(&a, 11);
    push(&a, 7);
    //push(&a, 1);
    push(&a,1);
    push(&a, 12);
    push(&a, 8);
    push(&a, 6);
    push(&a, 2);
    mergeSort(&a);
    print(a);
    recursiveReverse(&a);
    print(a);

       

}


