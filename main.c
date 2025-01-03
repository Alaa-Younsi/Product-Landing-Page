#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define ACCOUNTS_FILE "accounts.txt"

// Function prototypes
void registerUser();
int loginUser();
int checkCredentials(const char *username, const char *password);

int main() {
    int choice;

    while (1) {
        printf("\nMini Platform\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    printf("Login successful!\n");
                } else {
                    printf("Invalid username or password.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void registerUser() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    FILE *file;

    printf("\nRegister\n");
    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline

    file = fopen(ACCOUNTS_FILE, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("User registered successfully.\n");
}

int loginUser() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("\nLogin\n");
    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline

    return checkCredentials(username, password);
}

int checkCredentials(const char *username, const char *password) {
    char fileUsername[MAX_USERNAME];
    char filePassword[MAX_PASSWORD];
    FILE *file = fopen(ACCOUNTS_FILE, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
