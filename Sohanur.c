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
