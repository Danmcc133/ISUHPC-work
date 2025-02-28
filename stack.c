// Today's assignment: stack
// Develop a stack (be creative) (push, pop,...) (non-integer values)
// For all files, add documentation (guideline 7)
// makefile, put all functions in a single file
// Update git, submit source code and screenshots

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT 100 // This shows the "limit" of the stack to avoid stack overflow

typedef struct {
    // This defines the structure of a stack, including the types of elements, how many elements can be in the stack
    // As well as the "top" of the stack 
    char* items[LIMIT];
    int top;
} Stack;

Stack* createstack() {
    // This function creates a stack, the elements will have to be input later by the user
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int full(Stack* stack) {
    // This function lets you know if the stack is currently full to avoid stack overflow
    return stack->top == LIMIT - 1;
}

int empty(Stack* stack) {
    // This function lets you know if the stack is currently empty to avoid stack underflow
    return stack->top == -1;
}



void push(Stack* stack, char* word) {
    // This adds an element input by the user to the top of the stack
    // The inputs are the stack and the element you want to add to the stack
    if (full(stack)) {
        // This lets you know that the stack is full and a "pop" would have to occur before a push
        // It uses the earlier "full" function
        printf("Stack overflow\n"); // i.e. stack overflow
        return;
    }
    stack->items[++stack->top] = strdup(word);
}

char* pop(Stack* stack) {
    // This function "pops" the top element of the stack
    // The only input is the stack since the only element that can be removed is the top element
    if (empty(stack)) {
        // You can't remove an element if there are no elements
        printf("Stack underflow\n");
        return NULL;
    }
    return stack->items[stack->top--];
}


void display(Stack* stack) {
    // This function will print what is currently in the stack
    // The input is the stack itself, the output is each element of the stack printed if the stack isn't empty
    if (empty(stack)) {
        // If the stack is empty, the output will just be a message letting the user know
        printf("Stack is currently empty\n");
        return;
    }
    for (int i = 0; i <= stack->top; i++) {
        printf("%s\n", stack->items[i]);
    }
}



int main() {
    // The input for this function are the elements of the stack 
    // In this case they are the names of famous national parks for creativity
    Stack* stack = createstack();
    // The function will add three elements to the stack
    push(stack, "Yosemite");
    push(stack, "Yellowstone");
    push(stack, "Grand Canyon");
    //The function will then print the three elements currently in the stack
    printf("Stack elements:\n");
    display(stack);
    // Finally, the function will "pop" the top of the stack, let the user know which element was "popped" 
    // Then it will print the remaining elements of the stack
    printf("\nPopped element: %s\n", pop(stack));
    printf("Stack elements after pop:\n");
    display(stack);

    return 0;
}

