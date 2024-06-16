Write a C program to implement the following operations on Singly Linked List.
(i)	Polynomial Addition
(ii)	Polynomial Subtraction
(iii)	Polynomial Multiplication

Algorithm:
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

void insertNode(struct Node** head, int coeff, int exp);
void displayPolynomial(struct Node* head);
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2);
struct Node* subtractPolynomials(struct Node* poly1, struct Node* poly2);
struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2);
void addTerm(struct Node** head, int coeff, int exp);

int main() {
    struct Node *poly1 = NULL, *poly2 = NULL, *result = NULL;
    int choice, coeff, exp;

    printf("Enter the first polynomial:\n");
    while (1) {
        printf("Enter coefficient and exponent (enter -1 -1 to end): ");
        scanf("%d %d", &coeff, &exp);
        if (coeff == -1 && exp == -1) break;
        insertNode(&poly1, coeff, exp);
    }

    printf("Enter the second polynomial:\n");
    while (1) {
        printf("Enter coefficient and exponent (enter -1 -1 to end): ");
        scanf("%d %d", &coeff, &exp);
        if (coeff == -1 && exp == -1) break;
        insertNode(&poly2, coeff, exp);
    }

    while (1) {
        printf("\n1. Polynomial Addition\n");
        printf("2. Polynomial Subtraction\n");
        printf("3. Polynomial Multiplication\n");
        printf("4. Display Polynomials\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                result = addPolynomials(poly1, poly2);
                printf("Resultant Polynomial (Addition): ");
                displayPolynomial(result);
                break;
            case 2:
                result = subtractPolynomials(poly1, poly2);
                printf("Resultant Polynomial (Subtraction): ");
                displayPolynomial(result);
                break;
            case 3:
                result = multiplyPolynomials(poly1, poly2);
                printf("Resultant Polynomial (Multiplication): ");
                displayPolynomial(result);
                break;
            case 4:
                printf("First Polynomial: ");
                displayPolynomial(poly1);
                printf("Second Polynomial: ");
                displayPolynomial(poly2);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void insertNode(struct Node** head, int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    if (*head == NULL || (*head)->exp < exp) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL && temp->next->exp >= exp) {
            temp = temp->next;
        }
        if (temp->exp == exp) {
            temp->coeff += coeff;
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    while (head != NULL) {
        printf("%dx^%d", head->coeff, head->exp);
        head = head->next;
        if (head != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            insertNode(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            insertNode(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int sumCoeff = poly1->coeff + poly2->coeff;
            if (sumCoeff != 0) {
                insertNode(&result, sumCoeff, poly1->exp);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertNode(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertNode(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

struct Node* subtractPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            insertNode(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            insertNode(&result, -poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int diffCoeff = poly1->coeff - poly2->coeff;
            if (diffCoeff != 0) {
                insertNode(&result, diffCoeff, poly1->exp);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertNode(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertNode(&result, -poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

void addTerm(struct Node** head, int coeff, int exp) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL && temp->exp > exp) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL && temp->exp == exp) {
        temp->coeff += coeff;
        if (temp->coeff == 0) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            free(temp);
        }
    } else {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->coeff = coeff;
        newNode->exp = exp;
        newNode->next = temp;
        if (prev != NULL) {
            prev->next = newNode;
        } else {
            *head = newNode;
        }
    }
}

struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    if (poly1 == NULL || poly2 == NULL) {
        return NULL;
    }

    for (struct Node* p1 = poly1; p1 != NULL; p1 = p1->next) {
        for (struct Node* p2 = poly2; p2 != NULL; p2 = p2->next) {
            int coeff = p1->coeff * p2->coeff;
            int exp = p1->exp + p2->exp;
            addTerm(&result, coeff, exp);
        }
    }

    return result;
}


 
