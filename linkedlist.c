// We now use makefile in ALL lab assignments
// Assignment in linked list
// Assignment: Create linked list using letters (distinctions between lowercase and uppercase letters) (int character)
// use makefile with macros: pattern rules
// update git and submit sourcecode, screenshots

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // This allows me to use 'isupper' and 'islower' to distinguish between uppercase and lowercase letters


struct node {
    char value; // This allows for letters instead of numbers
    struct node* next;
};


struct node* createnode(char value) {
    // This function creates a new node in the linked list, this could be used to insert nodes as well with some minor tweaks
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

int numberOfnodes(struct node* head) {
    // This function counts the number of nodes in the linked list
    int count = 0;
    struct node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}


struct node* generatelist(char* array, int size) {
    // This function generates a list from an array of letters input by the user (in the main function)
    struct node* head = NULL;
    struct node* temp = NULL;

    for (int i = 0; i < size; i++) {
        struct node* newnode = createnode(array[i]);
        if (head == NULL) {
            head = newnode;
            temp = head;
        } else {
            temp->next = newnode;
            temp = temp->next;
        }
    }
    return head;
}


void printlist(struct node* head) {
    // This function prints the linked list
    struct node* temp = head;
    while (temp != NULL) {
        if (isupper(temp->value)) {
            printf("%c (uppercase) -> ", temp->value);
        } else if (islower(temp->value)) {
            printf("%c (lowercase) -> ", temp->value);
        } else {
            printf("%c -> ", temp->value);
        }
        temp = temp->next;
    }
    printf("NULL\n");
}


void reverseprintlist(struct node* head) {
    // This function prints the list in reverse order
    if (head == NULL)
        return;
    reverseprintlist(head->next);
    if (isupper(head->value)) {
        printf("%c (uppercase) -> ", head->value);
    } else if (islower(head->value)) {
        printf("%c (lowercase) -> ", head->value);
    } else {
        printf("%c -> ", head->value);
    }
}


char getkey(struct node* head, int position) {
    // This function looks for the key at the position input by the user
    struct node* temp = head;
    int count = 0;
    while (temp != NULL) {
        if (count == position) {
            return temp->value;
        }
        count++;
        temp = temp->next;
    }
    return '\0'; 
}


int searchlist(struct node* head, char key) {
    // This function looks for a specific value in the list
    struct node* temp = head;
    int position = 0;
    while (temp != NULL) {
        if (temp->value == key) {
            return position;
        }
        position++;
        temp = temp->next;
    }
    return -1; // This returns -1 if the key is not found
}


void deletelist(struct node** head) {
    // This function deletes the linked list
    struct node* current = *head;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


int main() {
    char array[] = {'a', 'b', 'C', 'D', 'E', 'f', 'G'};
    int size = sizeof(array) / sizeof(array[0]);

    struct node* head = generatelist(array, size);

    printf("Linked list: ");
    printlist(head);

    printf("Number of nodes: %d\n", numberOfnodes(head));

    printf("Reverse print linked list: ");
    reverseprintlist(head);
    printf("NULL\n");

    char key = getkey(head, 2);
    printf("Key at position 2: %c\n", key);

    int position = searchlist(head, 'd');
    if (position != -1) {
        printf("'d' found at position: %d\n", position);
    } else {
        printf("'d' not found in the list\n");
    }

    deletelist(&head);
    printf("Linked list after deletion: ");
    printlist(head);

    return 0;
}

