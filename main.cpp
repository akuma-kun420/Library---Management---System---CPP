#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Book
{
    public:
    int bookId;
    string title;
    string author;
    bool issued;
};

void addBook()
{
    Book b;
    
    ofstream file("books.txt", ios::app);
    
    cout << "Enter Book ID: ";
    cin >> b.bookId;
    cin.ignore();
    
    cout << "Enter Book Title: ";
    getline(cin, b.title);
    
    cout << "Enter Author Name: ";
    getline(cin, b.author);
    
    b.issued = false;
    
    file << b.bookId << "," << b.title << "," << b.author << "," << b.issued << endl;
    
    file.close();
    
    cout << "\nBook Added Successfully!\n";
}

void displayBooks()
{
    ifstream file("books.txt");
    
    string line;
    
    cout << "\n===== BOOK RECORDS =====\n";
    
    while(getline(file, line))
    {
        cout << line << endl;
    }
     file.close();
}

void searchByTitle()
{
    string searchTitle;
    
    cin.ignore();
    
    cout << "Enter Book title: ";
    getline(cin, searchTitle);
    
    ifstream file("books.txt");
    
    Book b;
    bool found = false;
    
    while(file >> b.bookId)
    {
        file.ignore();
        
        getline(file, b.title, ',');
        getline(file, b.author, ',');
        
        file >> b.issued;
        file.ignore();
        
        cout << "Reading Books: " << b.title << endl;
        
        if(b.title == searchTitle)
        {
            cout << "\nBook Found!\n";
            cout << "ID: " << b.bookId << endl;
            cout << "Author: " << b.author << endl;
            cout << "Status: " << (b.issued ? "Issued" : "Available") << endl;
            
            found = true;
            break;
        }
    }
    
    file.close();
    
    if(!found)
         cout << "Book Not Found!\n";
}

void searchByAuthor()
{
    string searchAuthor;
    
    cin.ignore();
    
    cout << "ENter Author Name: ";
    getline(cin, searchAuthor);
    
    ifstream file("books.txt");
    
    Book b;
    bool found = false;
    
    while(file >> b.bookId)
    {
        file.ignore();
        
        getline(file, b.title, ',');
        getline(file, b.author, ',');
        
        file >> b.issued;
        file.ignore();
        
        if(b.author == searchAuthor)
        {
            cout << "\nBook Found!\n";
            cout << "ID: " << b.bookId << endl;
            cout << "Title: " << b.title << endl;
            cout << "Status: " << (b.issued ? "Issued" : "Available") << endl;
            
            found = true;
        }
    }
    
    file.close();
    
    if(!found)
         cout << "No Books Found!\n";
}

void issueBook()
{
    int id;
    
    cout << "Enter Book ID to Issue: ";
    cin >> id;
    
    ifstream file("books.txt");
    ofstream temp("temp.txt");
    
    Book b;
    bool found = false;
    
    while(file >> b.bookId)
    {
        file.ignore();
        
        getline(file, b.title, ',');
        getline(file, b.author, ',');
        
        file >> b.issued;
        file.ignore();
        
        if(b.bookId == id)
        {
            if(!b.issued)
            {
                b.issued = true;
                cout << "Book Issued Successfully!\n";
            }
            else
            {
                cout << "Book Already Issued!\n";
            }
            
            found = true;
        }
        
        temp << b.bookId << "," << b.title << "," << b.author << "," << b.issued << endl;
    }
    
    file.close();
    temp.close();
    
    remove("books.txt");
    rename("temp.txt", "books.txt");
    
    if(!found)
         cout << "Book Not Found!\n";
}

void returnBook()
{
    int id;
    
    cout << "Enter Book Id  to Return: ";
    cin >> id;
    
    ifstream file("books.txt");
    ofstream temp("temp.txt");
    
    Book b;
    bool found = false;
    
    while(file >> b.bookId)
    {
        file.ignore();
        
        getline(file, b.title, ',');
        getline(file, b.author, ',');
        
        file >> b.issued;
        file.ignore();
        
        if(b.bookId == id)
        {
            if(b.issued)
            {
                b.issued = false;
                cout << "Book Returned Successfully!\n";
            }
            else
            {
                cout << "Book was Not Issued!\n";
            }
            
            found = true;
        }
        
        temp << b.bookId << "," << b.title << "," << b.author << "," << b.issued << endl;
    }
    
    file.close();
    temp.close();
    
    remove("books.txt");
    rename("temp.txt", "books.txt");
    
    if(!found)
         cout << "Book Not Found!\n";
}

int main()
{
    int choice;
    
    do
    {
        cout << "\n=====LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Dispaly Books\n";
        cout << "3. Search By Title\n";
        cout << "4. Search By Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        
        cin >> choice;
        
        switch(choice)
        {
            case 1:
            addBook();
            break;
            
            case 2:
            displayBooks();
            break;
            
            case 3:
            searchByTitle();
            break;
            
            case 4:
            searchByAuthor();
            break;
            
            case 5:
            issueBook();
            break;
            
            case 6:
            returnBook();
            break;
            
            case 7:
            cout << "EXiting...\n";
            break;
            
            default:
            cout << "Invalid choice!\n";
        }
    } while(choice != 7);
    
    return 0;
}
