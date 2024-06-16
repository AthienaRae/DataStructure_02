Write a C program to implement the following operations on Singly Linked List.
(i)	Insert a node in the beginning of a list.
(ii)	Insert a node after P
(iii)	Insert a node at the end of a list
(iv)	Find an element in a list
(v)	FindNext
(vi)	FindPrevious
(vii)	isLast
(viii)	isEmpty
(ix)	Delete a node in the beginning of a list.
(x)	Delete a node after P
(xi)	Delete a node at the end of a list
(xii)	Delete the List

Algorithm:

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void insertAtBeginning(int data);
void insertAfter(int data, int position);
void insertAtEnd(int data);
struct node* findElement(int data);
struct node* findNext(int data);
struct node* findPrevious(int data);
int isLast(struct node *n);
int isEmpty();
void deleteFromBeginning();
void deleteAfter(int position);
void deleteFromEnd();
void deleteList();
void displayList();

struct node *head = NULL;




int main() {
    int choice, data, position;

    while (1) {
        printf("\n1. Insert at Beginning\n");
        printf("2. Insert After Position\n");
        printf("3. Insert at End\n");
        printf("4. Find Element\n");
        printf("5. Find Next\n");
        printf("6. Find Previous\n");
        printf("7. Is Last\n");
        printf("8. Is Empty\n");
        printf("9. Delete from Beginning\n");
        printf("10. Delete After Position\n");
        printf("11. Delete from End\n");
        printf("12. Delete List\n");
        printf("13. Display List\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
            case 2:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position after which to insert: ");
                scanf("%d", &position);
                insertAfter(data, position);
                break;
            case 3:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 4:
                printf("Enter data to find: ");
                scanf("%d", &data);
                struct node* found = findElement(data);
                if (found) {
                    printf("Element %d found.\n", data);
                } else {
                    printf("Element %d not found.\n", data);
                }
                break;
            case 5:
                printf("Enter data to find next: ");
                scanf("%d", &data);
                struct node* next = findNext(data);
                if (next) {
                    printf("Next element is %d.\n", next->data);
                } else {
                    printf("No next element found.\n");
                }

                break;
            case 6:
                printf("Enter data to find previous: ");
                scanf("%d", &data);
                struct node* prev = findPrevious(data);
                if (prev) {
                    printf("Previous element is %d.\n", prev->data);
                } else {
                    printf("No previous element found.\n");
                }
                break;
            case 7:
                printf("Enter data to check if it's the last element: ");
                scanf("%d", &data);
                struct node* element = findElement(data);
                if (element && isLast(element)) {
                    printf("Element %d is the last element.\n", data);
                } else {
                    printf("Element %d is not the last element.\n", data);
                }
                break;
            case 8:
                if (isEmpty()) {
                    printf("List is empty.\n");
                } else {
                    printf("List is not empty.\n");
                }
                break;
            case 9:
                deleteFromBeginning();
                break;
            case 10:
                printf("Enter position after which to delete: ");
                scanf("%d", &position);
                deleteAfter(position);
                break;
            case 11:
                deleteFromEnd();
                break;
            case 12:
                deleteList();
                break;
            case 13:
                displayList();
                break;
            case 14:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}


void insertAtBeginning(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Unable to allocate memory.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    displayList();
}

void insertAfter(int data, int position) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Unable to allocate memory.\n");
        exit(0);
    }
    newNode->data = data;

    struct node *temp = head;
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position does not exist.\n");
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    displayList();
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
        head = newNode;
    } else {
        struct node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    displayList();
}

struct node* findElement(int data) {
    struct node *temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct node* findNext(int data) {
    struct node *temp = findElement(data);
    if (temp != NULL && temp->next != NULL) {
        return temp->next;
    }
    return NULL;
}

struct node* findPrevious(int data) {
    if (head == NULL || head->data == data) {
        return NULL;
    }
    struct node *temp = head;
    while (temp->next != NULL && temp->next->data != data) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        return NULL;
    }
    return temp;
}

int isLast(struct node *n) {
    return n != NULL && n->next == NULL;
}

int isEmpty() {
    return head == NULL;
}

void deleteFromBeginning() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct node *temp = head;
    head = head->next;
    free(temp);
    displayList();
}

void deleteAfter(int position) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }


    struct node *temp = head;
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position does not exist or no element to delete.\n");
        return;
    }

    struct node *toDelete = temp->next;
    temp->next = temp->next->next;
    free(toDelete);
    displayList();
}

void deleteFromEnd() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
    } else {
        struct node *temp = head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    }
    displayList();
}

void deleteList() {
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("List deleted.\n");
}

void displayList() {
    struct node *temp = head;
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Data in the list:\n");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
 
