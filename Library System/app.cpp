#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>
using namespace std;

#define MAX_BOOKS           100
#define MAX_USERS           50

struct book_t {
  int id;
  string name;
  int quantity;
};

struct user_t {
  int id;
  string name;
  int borrowed_books[MAX_BOOKS]; 
  int borrowed_count;
};

book_t Books_arr[MAX_BOOKS];
user_t Users_arr[MAX_USERS];

int book_count = 0;
int user_count = 0;

bool cmp_book_by_name(book_t &a, book_t &b) {
  return a.name < b.name;
}

bool cmp_book_by_id(book_t &a, book_t &b) {
  return a.id < b.id;
}

int menu(void);
void Add_book(void);
void Search_books_by_prefix(void);
void Print_who_borrowed_book_by_name(void);
void Print_library_by_id(void);
void Print_library_by_name(void);
void Add_user(void);
void User_borrow_book(void);
void User_return_book(void);
void Print_users(void);

int main() {
  while (true) {
    int choice = menu();

    switch (choice) {
    case 1:
      Add_book();
      break;
    case 2:
      Search_books_by_prefix();
      break;
    case 3:
      Print_who_borrowed_book_by_name();
      break;
    case 4:
      Print_library_by_id();
      break;
    case 5:
      Print_library_by_name();
      break;
    case 6:
      Add_user();
      break;
    case 7:
      User_borrow_book();
      break;
    case 8:
      User_return_book();
      break;
    case 9:
      Print_users();
      break;
    case 10:
      exit(0);
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}

int menu(void) {
  int choice;

  cout << "1) Add book\n";
  cout << "2) Search books by prefix\n";
  cout << "3) Print who borrowed book by name\n";
  cout << "4) Print library by id\n";
  cout << "5) Print library by name\n";
  cout << "6) Add user\n";
  cout << "7) User borrow book\n";
  cout << "8) User return book\n";
  cout << "9) Print users\n";
  cout << "10) Exit\n";
  cout << "Enter your choice [1 - 10]: ";
  cin >> choice;

  return choice;
}

void Add_book(void) {
  if(book_count >= MAX_BOOKS) {
    cout << "Library is full. Cannot add more books.\n";
    return;
  }

  book_t my_book;
  cout << "Enter Book [id] [name] [quantity]: ";
  cin >> my_book.id >> my_book.name >> my_book.quantity;
  Books_arr[book_count++] = my_book;
  cout << "Book added successfully.\n";
}

void Search_books_by_prefix(void) {
  string prefix;
  cout << "Enter book name prefix: ";
  cin >> prefix;

  bool found = false;
  for(int i = 0; i < book_count; ++i) {
    if (Books_arr[i].name.find(prefix) == 0) {
      cout << "Book ID: " << Books_arr[i].id << ", Name: " << Books_arr[i].name << ", Quantity: " << Books_arr[i].quantity << endl;
      found = true;
    }
  }

  if(!found) {
    cout << "No books found with the given prefix.\n";
  }
}

void Print_who_borrowed_book_by_name(void) {
  string book_name;
  cout << "Enter book name: ";
  cin >> book_name;

  bool book_found = false;
  for(int i = 0; i < book_count; ++i) {
    if(Books_arr[i].name == book_name) {
      book_found = true;
      cout << "Book ID: " << Books_arr[i].id << " is borrowed by:\n";
      for(int j = 0; j < user_count; ++j) {
        for(int k = 0; k < Users_arr[j].borrowed_count; ++k) {
          if(Users_arr[j].borrowed_books[k] == Books_arr[i].id) {
            cout << Users_arr[j].name << endl;
          }
        }
      }
      break;
    }
  }

  if(!book_found) {
    cout << "Book not found.\n";
  }
}

void Print_library_by_id(void) {
  sort(Books_arr, Books_arr + book_count, cmp_book_by_id);

  for(int i = 0; i < book_count; ++i) {
    cout << "Book ID: " << Books_arr[i].id << ", Name: " << Books_arr[i].name << ", Quantity: " << Books_arr[i].quantity << endl;
  }
}

void Print_library_by_name(void) {
  sort(Books_arr, Books_arr + book_count, cmp_book_by_name);

  for(int i = 0; i < book_count; ++i) {
    cout << "Book ID: " << Books_arr[i].id << ", Name: " << Books_arr[i].name << ", Quantity: " << Books_arr[i].quantity << endl;
  }
}

void Add_user(void) {
  if(user_count >= MAX_USERS) {
    cout << "Maximum number of users reached. Cannot add more users.\n";
    return;
  }

  user_t new_user;
  cout << "Enter User [id] [name]: ";
  cin >> new_user.id >> new_user.name;
  new_user.borrowed_count = 0;
  Users_arr[user_count++] = new_user;
  cout << "User added successfully.\n";
}

void User_borrow_book(void) {
  int user_id, book_id;
  cout << "Enter User ID and Book ID: ";
  cin >> user_id >> book_id;

  for(int i = 0; i < user_count; ++i) {
    if(Users_arr[i].id == user_id) {
      for(int j = 0; j < book_count; ++j) {
        if(Books_arr[j].id == book_id && Books_arr[j].quantity > 0) {
          Users_arr[i].borrowed_books[Users_arr[i].borrowed_count++] = book_id;
          Books_arr[j].quantity--;
          cout << "Book borrowed successfully.\n";
          return;
        }
      }
      cout << "Book not available.\n";
      return;
    }
  }

  cout << "User not found.\n";
}

void User_return_book(void) {
  int user_id, book_id;
  cout << "Enter User ID and Book ID: ";
  cin >> user_id >> book_id;

  for(int i = 0; i < user_count; ++i) {
    if(Users_arr[i].id == user_id) {
        for(int j = 0; j < Users_arr[i].borrowed_count; ++j) {
          if(Users_arr[i].borrowed_books[j] == book_id) {
            Users_arr[i].borrowed_books[j] = Users_arr[i].borrowed_books[--Users_arr[i].borrowed_count];
            for(int k = 0; k < book_count; ++k) {
              if(Books_arr[k].id == book_id) {
                Books_arr[k].quantity++;
                cout << "Book returned successfully.\n";
                return;
              }
            }
          }
        }
        cout << "Book not found in user's borrowed list.\n";
        return;
    }
  }

  cout << "User not found.\n";
}

void Print_users(void) {
  for(int i = 0; i < user_count; ++i) {
    cout << "User ID: " << Users_arr[i].id << ", Name: " << Users_arr[i].name << ", Borrowed books: ";
    for(int j = 0; j < Users_arr[i].borrowed_count; ++j) {
      cout << Users_arr[i].borrowed_books[j] << (j == Users_arr[i].borrowed_count - 1 ? "" : ", ");
    }
    cout << endl;
  }
}

