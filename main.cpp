#include <iostream>
#include <string>
#include <fstream>
#include <limits>  
using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    string title;
    string author;
    int year;
};

Book library[MAX_BOOKS];
int bookCount = 0;

int GetValidChoice() {
    int choice;
    while (true) {
        cout << "Choose: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input! Please enter a number (1-8).\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

bool IsValidYear(int year) {
    return year >= 0 && year <= 2026;  
}


void AddBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        cout << " Library is full!\n";
        return;
    }

    cout << "Enter book title: ";
    getline(cin, library[bookCount].title);

    if (library[bookCount].title.empty()) {
        cout << " Title cannot be empty. Please try again.\n";
        return;
    }

    cout << "Enter book author: ";
    getline(cin, library[bookCount].author);

    if (library[bookCount].author.empty()) {
        cout << " Author cannot be empty. Please try again.\n";
        return;
    }

    cout << "Enter publication year: ";
    cin >> library[bookCount].year;

    if (cin.fail() || !IsValidYear(library[bookCount].year)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << " Invalid year! Please enter a valid year (0-2026).\n";
        return;
    }

    cin.ignore();  

    bookCount++;

    cout << " Book added successfully!\n";
}

void ViewBooks()
{
    if (bookCount == 0)
    {
        cout << " No books found.\n";
        return;
    }

    cout << "\n===== Book List (" << bookCount << " books) =====\n";

    for (int i = 0; i < bookCount; i++)
    {
        cout << "\n Book #" << i + 1 << endl;
        cout << "   Title : " << library[i].title << endl;
        cout << "   Author: " << library[i].author << endl;
        cout << "   Year  : " << library[i].year << endl;
    }
}

void SearchBook()
{
    if (bookCount == 0)
    {
        cout << " No books found.\n";
        return;
    }

    string searchTitle;
    cout << "Enter book title to search: ";
    getline(cin, searchTitle);

    if (searchTitle.empty()) {
        cout << " Search title cannot be empty.\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < bookCount; i++)
    {
        string titleLower = library[i].title;
        string searchLower = searchTitle;

        for (char& c : titleLower) c = tolower(c);
        for (char& c : searchLower) c = tolower(c);

        if (titleLower == searchLower)
        {
            cout << "\n Book found:\n";
            cout << "   Title : " << library[i].title << endl;
            cout << "   Author: " << library[i].author << endl;
            cout << "   Year  : " << library[i].year << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << " Book not found.\n";
    }
}

void DeleteBook()
{
    if (bookCount == 0)
    {
        cout << " No books found.\n";
        return;
    }

    string deleteTitle;
    cout << "Enter book title to delete: ";
    getline(cin, deleteTitle);

    if (deleteTitle.empty()) {
        cout << " Title cannot be empty.\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < bookCount; i++)
    {
        string titleLower = library[i].title;
        string deleteLower = deleteTitle;

        for (char& c : titleLower) c = tolower(c);
        for (char& c : deleteLower) c = tolower(c);

        if (titleLower == deleteLower)
        {
            char confirm;
            cout << "Are you sure you want to delete '" << library[i].title << "'? (y/n): ";
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirm != 'y' && confirm != 'Y') {
                cout << " Deletion cancelled.\n";
                return;
            }

            for (int j = i; j < bookCount - 1; j++)
            {
                library[j] = library[j + 1];
            }
            bookCount--;
            found = true;
            cout << " Book deleted successfully!\n";
            break;
        }
    }
    if (!found)
    {
        cout << " Book not found.\n";
    }
}

void EditBook()
{
    if (bookCount == 0)
    {
        cout << " No books found.\n";
        return;
    }

    string editTitle;
    cout << "Enter book title to edit: ";
    getline(cin, editTitle);

    if (editTitle.empty()) {
        cout << " Title cannot be empty.\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < bookCount; i++)
    {
        string titleLower = library[i].title;
        string editLower = editTitle;

        for (char& c : titleLower) c = tolower(c);
        for (char& c : editLower) c = tolower(c);

        if (titleLower == editLower)
        {
            cout << " Editing book: " << library[i].title << endl;

            cout << "Enter new title (press Enter to keep current): ";
            string newTitle;
            getline(cin, newTitle);
            if (!newTitle.empty()) {
                library[i].title = newTitle;
            }

            cout << "Enter new author (press Enter to keep current): ";
            string newAuthor;
            getline(cin, newAuthor);
            if (!newAuthor.empty()) {
                library[i].author = newAuthor;
            }

            cout << "Enter new publication year (0 to keep current): ";
            int newYear;
            cin >> newYear;

            if (cin.fail() || newYear < 0 || newYear > 2026) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Invalid year! Keeping current year: " << library[i].year << endl;
            }
            else if (newYear > 0) {
                library[i].year = newYear;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            found = true;
            cout << " Book updated successfully!\n";
            break;
        }
    }
    if (!found)
    {
        cout << " Book not found.\n";
    }
}

void LoadBooks()
{
    ifstream inFile("library.txt");
    if (!inFile)
    {
        cout << " No saved books found.\n";
        return;
    }

    bookCount = 0;
    while (inFile && bookCount < MAX_BOOKS)
    {
        getline(inFile, library[bookCount].title);
        getline(inFile, library[bookCount].author);
        inFile >> library[bookCount].year;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
        bookCount++;
    }
    inFile.close();
    cout << bookCount << " books loaded successfully!\n";
}

void SaveBooks()
{
    ofstream outFile("library.txt");
    if (!outFile)
    {
        cout << " Error saving books.\n";
        return;
    }

    for (int i = 0; i < bookCount; i++)
    {
        outFile << library[i].title << endl;
        outFile << library[i].author << endl;
        outFile << library[i].year << endl;
    }
    outFile.close();
    cout << bookCount << " books saved successfully!\n";
}


int main()
{
    cout << "\n Welcome to Library Management System 📚\n";
    cout << "==========================================\n";

     
    LoadBooks();

    while (true)
    {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Edit Book\n";
        cout << "6. Load Books\n";
        cout << "7. Save Books\n";
        cout << "8. Exit\n";
        cout << "------------------------------------\n";
        cout << " Total books: " << bookCount << "/" << MAX_BOOKS << endl;

        int choice = GetValidChoice();    

        switch (choice)
        {
        case 1:
            AddBook();
            break;

        case 2:
            ViewBooks();
            break;

        case 3:
            SearchBook();
            break;

        case 4:
            DeleteBook();
            break;

        case 5:
            EditBook();
            break;

        case 6:
            LoadBooks();
            break;

        case 7:
            SaveBooks();
            break;

        case 8:
            if (bookCount > 0) {
                char confirm;
                cout << " You have: " << bookCount << " books. Save before exit? (y/n): ";
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (confirm == 'y' || confirm == 'Y') {
                    SaveBooks();
                }
            }
            cout << " Exiting the program. Goodbye!\n";
            return 0;

        default:
            cout << " Invalid choice. Please enter a number between 1 and 8.\n";
        }
    }

    return 0;
}
