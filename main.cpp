#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int const SIZE = 5;

// structures
// using queue array for User
struct User {
  string name, ic, pw;
};

// using stack with linked-list for history
struct Hist {
  string location;
  int yr, mth, day, hr, min, sec;
  Hist* nxtHist;
} *top;

// functions
void cls() {
  system("clear");
}

void welcome() {
  cout << "Welcome to MineSejahtera program" << endl;
  cout << "================================" << endl;
  cout << "1. Sign In" << endl;
  cout << "2. Sign Up" << endl;
  cout << endl << "Option: ";
}

void promptUser(User person[],string ic, string name, string pw, int &rear, int choice) {
  cout << "person[" << rear << "]" << endl;
  cout << "IC Number (without spaces or \"-\"): ";
  cin >> person[rear].ic;
  cout << "person[" << rear << "].ic = " << person[rear].ic << endl; 
  if (rear == 0) {
    cout << "Username (no spaces allowed): ";
  } else {
    cout << "Dependent's name: ";
  }
  cin >> person[rear].name;
  cout << "person[" << rear << "].name = " << person[rear].name << endl;
  if (rear == 0) {
    cout << "Password: ";
    cin >> person[rear].pw;
    cout << "person[" << rear << "].pw = " << person[rear].pw << endl;
  }
  rear++;
}

// enqueuing dependents
void nQueue(User dependent[], string ic, string name, string pw, int &front, int &rear, int choice) {
  if(rear == SIZE - 1) {
    cout << "Maximum number of dependent reached!" << endl;
  } else if (front == -1 && rear == -1) {
    // register user
    front++;
    rear++;
    promptUser(dependent, ic, name, pw, rear, choice);
    cout << endl << "Registered successfully!" << endl;
    sleep(2);
  } else if (ic == dependent[0].ic && pw == dependent[0].pw) {
    cls();
    cout << "User already exists!" << endl;
    sleep(2);
  } 
  else {
    promptUser(dependent, ic, name, pw, rear, choice);
    cout << endl << "Dependent successfully added!" << endl;
    sleep(2);
  }
}

// dequeuing dependents
void dQueue(User dependent[], int front, int &rear) {
  if(front >= 0) {
    cout << "Removing dependent... ";
    for(int i = 0; i<= 2; i++) {
      sleep(1);
      cout << "\b\\" << flush;
      sleep(1);
      cout << "\b|" << flush;
      sleep(1);
      cout << "\b/" << flush;
      sleep(1);
      cout << "\b-" << flush;
    }
    for (int i = 0; i < rear; i++) {
      dependent[rear].ic = dependent[rear + 1].ic;
      dependent[rear].name = dependent[rear + 1].name;
    }
    rear--;
  } else {

  }
}

// display list of dependents
void dispQueue(User dependent[], int rear, int front) {
  if(front < 0) {
    cout << "No dependent available" << endl;
  } else {
    while (front >= 1 && front < rear) {
      cout << "Dependent #" << front + 1 << endl;
      cout << "IC Number: " << dependent[front].ic << endl;
      cout << "Name: " << dependent[front].name << "\n\n";
    }
  }
}

void addHistory(Hist*& front, Hist* history, Hist* rear) {
  history->nxtHist = NULL;

  
}

void delHistory() {

}

void dispHistory() {

}

// verify login
void logIn(User user[], string ic, string password) {
  if(ic == user[0].ic && password == user[0].pw) {
    cout << "Login succesful!" << endl;
    sleep(1);
    cls();
  } else {
    cout << "IC and password not matched!" << endl;
    cout << user[0].ic << endl;
    cout << user[0].pw << endl;
    sleep(1);
    // cls();
  }
}

//main
int main() {
  User dependent[SIZE];
  int choice = 0, front = -1, rear = -1;
  string icNum;
  string name;
  string password;
  bool login = false;

  do {
    cout << front << endl;
    cout << rear << endl;
    cout << dependent[0].ic << endl;
    cout << dependent[0].pw << endl;
    welcome();
    
    cin >> choice;
    
    cls();

    switch(choice) {
      case 1: {
        if (front == -1 && rear == -1) {
          cout << "No existing account" << endl;
          sleep(2);
          cls();
          break;
        } else {
          cout << "Sign In" << endl;
          cout << "=======" << endl;

          // function for passing ic and password into struct
          cout << "IC Number (without spaces and \"-\"): ";

          cin >> icNum;

          cout << "Password: ";
        
          cin >> password;

          // verify login
          logIn(dependent, icNum, password);
        }
        break;
      }
      
      case 2: {
        cout << "Sign Up" << endl;
        cout << "=======" << endl;

        // function for passing ic and password into struct
        nQueue(dependent, icNum, name, password, front, rear, choice);
        cls();
      }
      break;
      
      default: {
        cout << "Invalid option!" << endl;
        sleep(2);
        cls();
        break;
      }
    }
  } while (!login);


  return 0;
}