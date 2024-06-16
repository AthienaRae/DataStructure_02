Write a C program to evaluate Arithmetic expression using stack. 

Algorithm:
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Stack structure
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Function to create a stack of given capacity.
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is empty when top is -1
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to add an item to stack. It increases top by 1
void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack. It decreases top by 1
int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1; // Underflow condition
}

// Function to return the top from stack without removing it
int peek(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return -1;
}

// Function to evaluate postfix expression
int evaluatePostfix(char* expression) {
    struct Stack* stack = createStack(strlen(expression));
    int i;

    // Scan all characters one by one
    for (i = 0; expression[i]; ++i) {
        // If the scanned character is an operand (number here), push it to the stack.
        if (isdigit(expression[i])) {
            push(stack, expression[i] - '0');
        } else {
            // If the scanned character is an operator, pop two elements from stack, apply the operator and push the result back.
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (expression[i]) {
                case '+':
                    push(stack, val2 + val1);
                    break;
                case '-':
                    push(stack, val2 - val1);
                    break;
                case '*':
                    push(stack, val2 * val1);
                    break;
                case '/':
                    push(stack, val2 / val1);
                    break;
            }
        }
    }
    return pop(stack);
}

int main() {
    char expression[100];
    printf("Enter a postfix expression: ");
    scanf("%s", expression);
    printf("Postfix evaluation: %d\n", evaluatePostfix(expression));
    return 0;
}
 
