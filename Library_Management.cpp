#include <bits/stdc++.h>
using namespace std;

class Book{
    private:
        string name;
        string author;

    public:
        Book(string name, string author) : name(name), author(author) {}

        string getAuthor(){
            return author;
        }
        string getName(){
            return name;
        }
};

class Student{
    private:
        string rollNo;
        string name;

    public:
        Student(string rollNo, string name) : rollNo(rollNo), name(name) {}
        string getRollNo(){
            return rollNo;
        }
        string getName(){
            return name;
        }
};

class Library{
    private:
        int bookids = 0;
        map<pair<string,string>, Book*> books;
        map<pair<string,string>, int> booksAvailable;

        unordered_map<string, Student*> students;
        map<string,vector<pair<string,string>>> studentIssued;

    public:
        void addBook(string name, string author){
            pair<string,string> temp;
            temp.first = name;
            temp.second = author;
            if(booksAvailable.find(temp) == booksAvailable.end()){
                int id = bookids++;
                Book *book = new Book(name,author);
                books[temp] = book;
                booksAvailable[temp]++; 
            }

            else{
                booksAvailable[temp]++;
            }
        }

        bool removeBook(string name, string author){
            pair<string,string> temp;
            temp.first = name;
            temp.second = author;
            if(booksAvailable.find(temp) != booksAvailable.end()){
                booksAvailable.erase(temp);
                books.erase(temp);
                return 1;
            }
            return 0;
        }

        void displayBooks(){
            if(books.size() == 0){
                cout<<"\nSorry no books present in the library\n";
                return;
            }
            cout<<"\n";
            for(auto it: books){
                Book* book = it.second;
                cout<<"Name: "<<book->getName()<<"\n";
                cout<<"Author: "<<book->getAuthor()<<"\n";
                cout<<"---------"<<"\n";
            }
        }

        void displayAvailableBooks(){
            int booksaval = 0;
            cout<<"\n";
            for(auto it: books){
                if(booksAvailable[it.first] > 0){
                    Book* book = it.second;
                    cout<<"Name: "<<book->getName()<<"\n";
                    cout<<"Author: "<<book->getAuthor()<<"\n";
                    cout<<"---------"<<"\n";
                    booksaval++;
                }
            }
            if(booksaval == 0){
                cout<<"\nSorry, no books available at this moment\n";
            }
        }

        void addStudent(string rollno, string name){
            if(students.find(rollno) == students.end()){
                Student *student = new Student(rollno,name);
                students[rollno] = student;
            }
        }

        bool removeStudent(string rollno){
            if(students.find(rollno) != students.end()){
                students.erase(rollno);
                return 1;
            }
            return 0;
        }

        bool findStudent(string rollno){
            if(students.find(rollno) != students.end()){
                return 1;
            }
            return 0;
        }

        bool issueBook(string bookname, string author, string rollno){
            pair<string,string> temp;
            temp.first = bookname;
            temp.second = author;

            if(booksAvailable[temp] > 0){
                studentIssued[rollno].push_back(temp);
                booksAvailable[temp]--;
                return 1;
            }
            else{
                return 0;
            }
        }

        bool returnBook(string bookname, string author, string rollno){
            pair<string,string> temp;
            temp.first = bookname;
            temp.second = author;

            if(books.find(temp) == books.end() || students.find(rollno) == students.end()){
                return 0;
            }
            else{
                booksAvailable[temp]++;
                auto it = find(studentIssued[rollno].begin(), studentIssued[rollno].end(),
                   temp);
                   
                if (it != studentIssued[rollno].end()) {
                    studentIssued[rollno].erase(it);
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
};


int main(){
    Library library;

    cout<<"\n****************************************\n";
    cout<<"*                                      *\n";
    cout<<"*                                      *\n";
    cout<<"*     ----------------------------     *\n";
    cout<<"*      WELCOME TO IITJ Library         *\n";
    cout<<"*     ----------------------------     *\n";
    cout<<"*                                      *\n";
    cout<<"*                                      *\n";
    cout<<"*                                      *\n";
    cout<<"*       ------------------------       *\n";
    cout<<"*           STUDENT LIBRARY            *\n";
    cout<<"*       ------------------------       *\n";
    cout<<"*                                      *\n";
    cout<<"*                                      *\n";
    cout<<"*                                      *\n";
    cout<<"****************************************\n";


    while(true){
        cout<<"\n\nMain Menu\n";
        cout<<"For student portal press 0, for admin portal press 1 or press -1 to exit: ";
        int portal = 0;
        cin>>portal;

        if(portal > 1 || portal < -1){
            cout<<"Please enter a valid option\n";
            continue;
        }
        if(portal == -1){
            break;
        }

        if(portal == 0){
            while(true){
                cout<<"\nWelcome to the student portal here are the available options:\n";
                cout<<"0) Return to main menu\n";
                cout<<"1) Register youself\n";
                cout<<"2) Issue a book\n";
                cout<<"3) Return a book\n";
                cout<<"4) Check available books(some books might not be shown because of being issued)\n";
                cout<<"5) Check all books\n";
                cout<<"Please select an option to move forward: ";
                int choice = 0;
                cin>>choice;
                if(choice == 0){
                    break;
                }
                else if(choice == 1){
                    cout<<"Please enter your Roll No.: ";
                    string rollNo;
                    getline(cin >> ws, rollNo);

                    cout<<"Please enter your Name: ";
                    string name;
                    getline(cin >> ws, name);

                    library.addStudent(rollNo,name);
                    cout<<"Student added successfully";
                    continue;
                }
                else if(choice == 2){
                    cout<<"Please enter you Roll No.: ";
                    string rollNo;
                    getline(cin >> ws, rollNo);
                    int checkSt = library.findStudent(rollNo);
                    if(checkSt == 0){
                        cout<<"\nNo student found, Please register yourself";
                        continue;
                    }
                    else{
                        cout<<"Please enter the name of the Book you want to get: ";
                        string name;
                        getline(cin >> ws, name);

                        cout<<"Please enter the author of the book you want to get: ";
                        string author;
                        getline(cin >> ws, author);

                        int check = library.issueBook(name,author,rollNo);
                        if(check == 1){
                            cout<<"\nBook issue successfull";
                        }
                        else{
                            cout<<"\nNo such book was found";
                        }
                        continue;
                    }
                }
                else if(choice == 3){
                    cout<<"Please enter you Roll No.: ";
                    string rollNo;
                    getline(cin >> ws, rollNo);
                    int checkSt = library.findStudent(rollNo);
                    if(checkSt == 0){
                        cout<<"\nNo student found, Please register yourself";
                        continue;
                    }
                    else{
                        cout<<"Please enter the name of the Book you want to return: ";
                        string name;
                        getline(cin >> ws, name);

                        cout<<"Please enter the author of the book you want to return: ";
                        string author;
                        getline(cin >> ws, author);

                        int check = library.returnBook(name,author,rollNo);
                        if(check == 1){
                            cout<<"\nBook return was successfull";
                        }
                        else{
                            cout<<"\nBook return failed, please check roll no., name and author of book";
                        }
                        continue;
                    }
                }
                else if(choice == 4){
                    library.displayAvailableBooks();
                    continue;
                }
                else if(choice == 5){
                    library.displayBooks();
                    continue;
                }
                else{
                    cout<<"Please select a valid option: ";
                    continue;
                }
            }
            continue;
        }

        else{
            while(true){
                cout<<"\nWelcome to the admin portal here are the available options:\n";
                cout<<"0) Return to main menu\n";
                cout<<"1) Add a Book\n";
                cout<<"2) Remove a Book\n";
                cout<<"3) Add a Student\n";
                cout<<"4) Remove a Student\n";
                cout<<"Please select an option to move forward: ";
                int choice = 0;
                cin>>choice;
                if(choice == 0){
                    break;
                }
                else if(choice == 1){
                    cout<<"Please enter the name of the book: ";
                    string name;
                    getline(cin >> ws, name);

                    cout<<"Please enter the author of the book: ";
                    string author;
                    getline(cin >> ws, author);

                    library.addBook(name,author);
                    cout<<"\nBook added successfully";
                    continue;
                }
                else if(choice == 2){
                    cout<<"Please enter the name of the book: ";
                    string name;
                    getline(cin >> ws, name);

                    cout<<"Please enter the author of the book: ";
                    string author;
                    getline(cin >> ws, author);

                    int check = library.removeBook(name,author);

                    if(check == 1){
                        cout<<"\nBook removed successfully";
                    }
                    else{
                        cout<<"\nBook was not found in database";
                    }
                    continue;
                }
                else if(choice == 3){
                    cout<<"Please enter the Roll No. of the student: ";
                    string rollNo;
                    getline(cin >> ws, rollNo);

                    cout<<"Please enter the Name of the student: ";
                    string name;
                    getline(cin >> ws, name);

                    library.addStudent(rollNo,name);
                    cout<<"\nStudent added successfully";
                    continue;
                }
                else if(choice == 4){
                    cout<<"Please enter the Roll No. of the student: ";
                    string rollNo;
                    getline(cin >> ws, rollNo);

                    int check = library.removeStudent(rollNo);
                    if(check == 1){
                        cout<<"\nStudent removed successfully";
                    }
                    else{
                        cout<<"\nStudent was not found";
                    }
                    continue;
                }
                else{
                    cout<<"\nPlease select a valid option: ";
                    continue;
                }
            }
            continue;
        }
    }
    return 0;
}