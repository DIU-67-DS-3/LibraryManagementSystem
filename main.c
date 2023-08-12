/*Author: DIU-67-DS-3
        Member: S M Moshaddaque Hoshain
                        
*/

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

// Define the book structure
struct Book
{
    char title[100];
    char author[100];
    char department[100];
    char isbn[14];
    int is_available;
};

// Define the user structure for book borrowing
struct User
{
    char name[100];
    char contact[20];
};

// Function to add a book to the library
void addBook(struct Book library[], int *num_books)
{
    if (*num_books >= MAX_BOOKS)
    {
        printf("Library is full. Cannot add more books.\n");

        return;
    }

    printf("\n\t\t\t\tEnter book title: ");
    scanf(" %[^\n]", library[*num_books].title); // library[i]  == i = 0;

    printf("\t\t\t\tEnter book author: ");
    scanf(" %[^\n]", library[*num_books].author);

    printf("\t\t\t\tEnter book Department: ");
    scanf(" %[^\n]", library[*num_books].department);

    printf("\t\t\t\tEnter book ISBN: ");
    scanf(" %[^\n]", library[*num_books].isbn);

    library[*num_books].is_available = 1;
    (*num_books)++;
    // printf("\n\t\t\tBook added successfully!\n");
    printf("\n\t\t\t\t\033[1;32mBook added successfully!\033[0m\n");
}

// Function to search for a book by title or author
void searchBook(struct Book library[], int num_books, char query[])
{
    int found = 0;
    for (int i = 0; i < num_books; i++)
    {
        if (strstr(library[i].title, query) || strstr(library[i].author, query))
        {
            printf("\n\t\t\t\t\033[1;34mTitle: %s\033[0m\n\t\t\t\tAuthor: %s\n\t\t\t\tDepartment: %s\n\t\t\t\tISBN: %s\n\t\t\t\tAvailability: %s\n\n",
                   library[i].title, library[i].author, library[i].department, library[i].isbn, library[i].is_available ? "Available" : "Not Available");
            found = 1;
        }
    }
    if (!found)
    {
        printf("\n\t\t\t\t\033[1;31mBook not found!\033[0m\n");
    }
}

// Function to delete a book from the library by title
void deleteBook(struct Book library[], int *num_books, char title[])
{
    int found = 0;
    for (int i = 0; i < *num_books; i++)
    {
        if (strcmp(library[i].title, title) == 0)
        {
            // Move the last book in the array to the deleted position
            library[i] = library[*num_books - 1];
            (*num_books)--;
            found = 1;
            printf("\033[1;31m\n\t\t\t\t\"%s\" Book deleted successfully!\033[0m\n", title);
            break;
        }
    }

    if (!found)
    {
        printf("\033[1;31m\n\t\t\t\tBook \"%s\" not found!\033[0m\n", title);
    }
}

// Function to display all books with sorting
void displayAllBooks(struct Book library[], int num_books, int sort_option)
{
    // Basic sorting algorithm (bubble sort) based on the chosen sorting criteria
    for (int i = 0; i < num_books - 1; i++)
    {
        for (int j = 0; j < num_books - i - 1; j++)
        {
            int compare_result = 0;
            switch (sort_option)
            {
            case 1: // Sort by book title
                compare_result = strcmp(library[j].title, library[j + 1].title);
                break;
            case 2: // Sort by author name
                compare_result = strcmp(library[j].author, library[j + 1].author);
                break;
            case 3: // Sort by ISBN number
                compare_result = strcmp(library[j].isbn, library[j + 1].isbn);
                break;
            default:
                printf("Invalid sort option. Please try again.\n");
            }

            if (compare_result > 0)
            {
                // Swap books
                struct Book temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }

    // Display sorted books
    for (int i = 0; i < num_books; i++)
    {

        printf("\n\t\t\t     \033[1;34m%d. Title: %s\033[0m\n\t\t\t\tAuthor: %s\n\t\t\t\tDepartment: %s\n\t\t\t\tISBN: %s\n\t\t\t\tAvailability: %s\n\n", i + 1,
               library[i].title, library[i].author, library[i].department, library[i].isbn, library[i].is_available ? "\033[1;32mAvailable\033[0m" : "\033[1;31mNot Available\033[0m");

        printf("\t\t\t___________________________________________\n");
    }
}

// Function to borrow a book from the library
void borrowBook(struct Book library[], int num_books, struct User users[], int *num_users)
{
    char query[100];
    printf("\n\t\t\t\tEnter search query: ");
    scanf(" %[^\n]", query);

    int found = 0;
    for (int i = 0; i < num_books; i++)
    {
        if (strstr(library[i].title, query) || strstr(library[i].author, query))
        {
            if (library[i].is_available)
            {
                printf("\t\t\t\tEnter your name: ");
                scanf(" %[^\n]", users[*num_users].name);
                printf("\t\t\t\tEnter your contact number: ");
                scanf(" %[^\n]", users[*num_users].contact);
                library[i].is_available = 0;
                found = 1;
                printf("\t\t\t\tBook \"%s\" borrowed successfully!\n", library[i].title);
                (*num_users)++;
            }
            else
            {
                printf("\t\t\t\t\033[1;31mBook \"%s\" is not available for borrowing.\033[0m\n", library[i].title);
            }
        }
    }

    if (!found)
    {
        printf("\n\t\t\t\t\033[1;31mBook not found.\033[0m\n");
    }
}

// Function to return a borrowed book to the library
void returnBook(struct Book library[], int num_books, struct User users[], int num_users)
{
    char query[100];
    printf("\n\t\t\t\tEnter book title to return: ");
    scanf(" %[^\n]", query);

    char name[100];
    printf("\t\t\t\tEnter your name: ");
    scanf(" %[^\n]", name);

    int found_book = 0;
    for (int i = 0; i < num_books; i++)
    {
        if (strstr(library[i].title, query) || strstr(library[i].author, name))
        {
            found_book = 1;
            if (!library[i].is_available)
            {
                int found_user = 0;
                for (int j = 0; j < num_users; j++)
                {
                    if (strstr(library[i].title, query) && strstr(users[i].name, name))
                    {
                        library[i].is_available = 1;
                        found_user = 1;
                        printf("\t\t\t\t\033[1;31mBook \"%s\" returned successfully!\033[0m\n", library[i].title);
                        break;
                    }
                }
                if (!found_user)
                {
                    printf("\t\t\t\t\033[1;31mNo user information found for this book.\033[0m\n");
                }
            }
            else
            {
                printf("\n\t\t\t\t\033[1;31mBook \"%s\" is not borrowed.\033[0m\n", library[i].title);
            }
            break; // Book found, no need to continue looping
        }
    }

    if (!found_book)
    {
        printf("\n\t\t\t\t\033[1;31mBook \"%s\" not found or not borrowed.\033[0m\n", query);
    }
}

// Function to save book records to a file
void saveBooksToFile(struct Book library[], int num_books)
{
    FILE *file = fopen("books.txt", "w");
    if (file == NULL)
    {
        printf("\t\t\t\tError opening file.\n");
        return;
    }
    for (int i = 0; i < num_books; i++)
    {
        fprintf(file, "%s;%s;%s;%s;%d\n", library[i].title, library[i].author, library[i].department, library[i].isbn, library[i].is_available);
    }

    fclose(file);
}

// Function to load book records from a file
int loadBooksFromFile(struct Book library[], int *num_books)
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("\t\t\t\tError opening file.\n");
        return 0;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^;];%[^;];%[^;];%[^;];%d\n", library[count].title, library[count].author, library[count].department, library[count].isbn, &library[count].is_available);
        count++;
    }

    fclose(file);
    *num_books = count;
    return 1;
}

// Function to save user information to a file
void saveUsersToFile(struct User users[], int num_users)
{
    FILE *file = fopen("users.txt", "w");
    if (file == NULL)
    {
        printf("\t\t\t\tError opening file.\n");
        return;
    }

    for (int i = 0; i < num_users; i++)
    {
        fprintf(file, "%s;%s\n", users[i].name, users[i].contact);
    }

    fclose(file);
}

// Function to load user information from a file
int loadUsersFromFile(struct User users[], int *num_users)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("\t\t\t\tError opening file.\n");
        return 0;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^;];%[^\n]\n", users[count].name, users[count].contact);
        count++;
    }

    fclose(file);
    *num_users = count;
    return 1;
}
//========================================
//========================================

int main()
{
    struct Book library[MAX_BOOKS];
    int num_books = 0;

    struct User users[MAX_BOOKS];
    int num_users = 0;

    // Load book records from file
    if (!loadBooksFromFile(library, &num_books))
    {
        printf("\t\t\t\tFailed to load book records from file.\n");
    }

    // Load user information from file
    if (!loadUsersFromFile(users, &num_users))
    {
        printf("\n\t\t\t\t\033[1;31mFailed to load user information from file.\033[0m\n");
    }

    int choice;
    char query[100];
    char title[100];

    do
    {
        system("cls");
        printf("\t\t\t\t\033[1;36m================================\033[0m");
        printf("\n\t\t\t\t\033[1;33m|| Library Management System ||\033[0m\n");
        printf("\t\t\t\t\033[1;36m================================\033[0m\n\n");
        printf("\t\t\t\t1. Add Book\n");
        printf("\t\t\t\t2. Search Book\n");
        printf("\t\t\t\t3. Delete Book\n");
        printf("\t\t\t\t4. Display All Books\n");
        printf("\t\t\t\t5. Borrow Book\n");
        printf("\t\t\t\t6. returnBook\n");
        // printf("\t\t\t\t7. saveBooksToFile\n");
        printf("\t\t\t\t0. Exit\n");
        printf("\t\t\t\t\033[1;35m================================\033[0m\n\n");

        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            break;
        case 1:
            addBook(library, &num_books);

            saveBooksToFile(library, num_books);
            saveUsersToFile(users, num_users);
            break;
        case 2:
            printf("\n\t\t\t\tEnter search query(Title/Author): ");
            scanf(" %[^\n]", query);
            searchBook(library, num_books, query);

            saveBooksToFile(library, num_books);
            saveUsersToFile(users, num_users);
            break;
        case 3:
            printf("\n\t\t\t\tEnter the title of the book to delete: ");
            scanf(" %[^\n]", title);
            deleteBook(library, &num_books, title);

            saveBooksToFile(library, num_books);
            saveUsersToFile(users, num_users);
            break;
        case 4:
            printf("\n\t\033[1;32mSort Options:\033[0m\n");
            printf("\t1. By Book Title\n");
            printf("\t2. By Author Name\n");
            printf("\t3. By ISBN Number\n");
            printf("\tEnter your sort option: ");
            int sort_option;
            scanf("%d", &sort_option);
            if (sort_option >= 1 && sort_option <= 3)
            {
                displayAllBooks(library, num_books, sort_option);
            }
            else
            {
                printf("\n\t\t\t\t\033[1;31mInvalid sort option. Please try again.\033[0m\n");
            }

            saveBooksToFile(library, num_books);
            saveUsersToFile(users, num_users);
            break;
        case 5:
            borrowBook(library, num_books, users, &num_users);

            saveBooksToFile(library, num_books);
            saveUsersToFile(users, num_users);
            break;
        case 6:
            returnBook(library, num_books, users, num_users);

            saveBooksToFile(library, num_books);
            saveUsersToFile(users, num_users);
            break;
        default:
            printf("\t\t\t\tInvalid choice. Please try again.\n");
        }
        printf("\n\n\t\t\t\t\033[1;33mPress Any Key To Continue...\033[0m\n\n");
        getch();
    } while (choice != 0);

    return 0;
}
