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
