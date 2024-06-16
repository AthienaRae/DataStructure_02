Write a C program to implement the following operations on Doubly Linked List.
(i)	Insertion
(ii)	Deletion
(iii)	Search
(iv)	Display

Algorithm:

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head = NULL;

void insertAtEnd(int data);
void deleteFromEnd();
struct node* search(int data);
void displayList();

int main() {
    int choice, data;

    while (1) {
        printf("\n1. Insert at End\n");
        printf("2. Delete from End\n");
        printf("3. Search\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 2:
                deleteFromEnd();
                break;
            case 3:
                printf("Enter data to search: ");
                scanf("%d", &data);
                struct node* found = search(data);


                if (found) {
                    printf("Element %d found.\n", data);
                } else {
                    printf("Element %d not found.\n", data);
                }
                break;
            case 4:
                displayList();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void insertAtEnd(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Unable to allocate memory.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
    } else {
        struct node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    displayList();
}

void deleteFromEnd() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        head = NULL;
    }
    free(temp);
    displayList();

}

struct node* search(int data) {
    struct node *temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void displayList() {
    struct node *temp;
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Data in the list:\n");
    temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


 
