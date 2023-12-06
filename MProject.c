#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data[10];
    struct node *pNext;
} Node;

int isEmpty(Node *head){
    return head == NULL;
}
//used chatgpt for help here(lines 15-17,22-24),implemented the code from there for my case
Node *addToEnd(Node *head, char str[]) {
    Node *node1=malloc(sizeof(Node));
    strncpy(node1->data,str,10);
    node1->pNext=NULL;
    if(head==NULL){
        head=node1;
    }
    else{
        Node *current=head;
        while(current->pNext!=NULL){
            current=current->pNext;
        }
        current->pNext=node1;
    }
    return head;
}
Node *addToBeginning(Node *head, char str[]){
    Node *pNew;
    pNew=(Node*)malloc(sizeof(Node));
    strcpy(pNew->data,str);
    pNew->pNext=NULL;
    if(head==NULL){
        head=pNew;
    }
    else{
        pNew->pNext=head;
        head=pNew;
    }
    return head;
}
//used help of chatgpt in line 49
int size(Node *head) {
    if (head == NULL) {
        return 0;
    } else {
        return 1 + size(head->pNext);
    }
}
//used help of chatgpt in line 55 for making the condition
Node *tail(Node *head) {
    Node *current = head;
    while (current != NULL && current->pNext != NULL) {
        current = current->pNext;
    }
    return current;
}
//used the help of chatgpt to complete and modify my code for this function in lines 65 and 67
Node *get_node(Node *head, int pos) {
    if (head == NULL || pos < 1) {
        return NULL;
    }
    Node *current = head;
    int count = 1;
    while (count < pos && current != NULL) {
        current = current->pNext;
        count++;
    }
    return current;
}

Node *deleteFirst(Node *head){
    Node *ptr;
    if(head!=NULL){
        ptr=head;
        head=head->pNext;
        free(ptr);
    }
    return head;
}
//used the help of chatgpt to fix and modify my code in this function.I did the lines 95-101.Chat gpt helped me with lines 85,91-94
Node *deleteLast(Node *head) {
    if (head == NULL || head->pNext == NULL) {
        free(head);
        return NULL;
    }
    Node *prev = NULL;
    Node *current = head;
    while (current->pNext != NULL) {
        prev = current;
        current = current->pNext;
    }
    free(current);
    if (prev != NULL) {
        prev->pNext = NULL;
        return head;
    } else {
        return NULL;
    }
}
//used the help of chatgpt to fix and modify my code in this function in lines 110-113
int find(Node *head, char *str) {
    int pos = 0;
    Node *current = head;

    while (current != NULL) {
        pos++;
        if (current->data==str) {
            return pos;
        }
        current = current->pNext;
    }

    return 0;
}
void print(Node *head) {
    printf("Printing...\n");
    Node *current = head;
    int position = 1;
    while (head != NULL) {
        printf("Node position %d: %s\n", position, head->data);
        head = head->pNext;
        position++;
    }
}
char *toString(Node *head){
    return 0;
}
//used chatgpt in lines 136-138 to reverse the list
Node* reverse(Node* head) {
    if (head == NULL || head->pNext == NULL) {
        return head;
    } else {
        Node* rest = reverse(head->pNext);
        head->pNext->pNext = head;
        head->pNext = NULL;
        return rest;
    }
}
int main(){
    FILE *filePointer;
    char lineBuffer[20];
    // Create an empty list
    Node *pFirst = NULL;
    // Testing if the list is empty
    printf("Is empty?: %d\n", isEmpty(pFirst));
    pFirst = addToBeginning(pFirst, "Kimi");
    // Reading the file and adding the elements
    filePointer = fopen("names.txt", "r");  
   if (filePointer == NULL) {
      printf("Unable to open file.\n");
      exit(1);}   
    while (fgets(lineBuffer, 20, filePointer)) {
        lineBuffer[strcspn(lineBuffer, "\n")] = '\0';
        pFirst = addToEnd(pFirst, lineBuffer);}   
    fclose(filePointer);
    // Testing if the list is empty again
    printf("Is empty?: %d\n", isEmpty(pFirst));
    // printing the list
    print(pFirst);
    // printing the size of the list
    printf("Size is: %d\n", size(pFirst));
    // Fetching the last not
    Node *nodePtr = tail(pFirst);
    printf("Last name: %s\n",nodePtr->data);
    // Fetching the 10th node
    nodePtr = get_node(pFirst, 10);
    printf("Name in position %d: %s\n", 10, nodePtr->data);
    // Fetching element outside the list 
    nodePtr = get_node(pFirst, 31);
    if (nodePtr == NULL){
        printf("Not found!\n");}
    // Delete the first element
    printf("Deleting first...\n");
    pFirst = deleteFirst(pFirst);
    // Add a new first
    printf("Adding \"Sirkka\" to the beginning...\n");
    pFirst = addToBeginning(pFirst, "Sirkka");
    // Remove the last
    printf("Deleting last...\n");
    pFirst = deleteLast(pFirst);
    // Print the modifed list
    print(pFirst);
    // test whether some names are present
    printf("The position of %s is: %d\n", "Teppo", find(pFirst, "Teppo"));
    printf("The position of %s is: %d\n", "Maija", find(pFirst, "Maija"));
    // reverse the list and print it
    printf("Reversing the list...\n");
    pFirst = reverse(pFirst);
    printf("%s\n", toString(pFirst));
	return 0;
}