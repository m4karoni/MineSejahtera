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

// clear screen function
void cls() {
  #ifdef __linux__
    system("clear");
  #elif _WIN32
    system("cls");
  #endif
}

void loading(string mode) {
  if (mode == "line") {
   for(int i = 0; i < 1; i++) {
    cout << "\b\\" << flush;
    sleep(1);
    cout << "\b|" << flush;
    sleep(1);
    cout << "\b/" << flush;
    sleep(1);
    cout << "\b-" << flush;
    sleep(1);
    cout << "\b " << flush;
    } 
  } else {
    for(int i = 0; i < 3; i++) {
      sleep(1);
      cout << "." << flush;
    }
  }
}

void optionMenu(string menu) {
  cout << "* " << menu << " *" << endl;
  for(int i = 0; i < menu.length() + 4; i++){
    cout << "=";
  }
  cout << endl;
}

void welcome() {
  optionMenu("Welcome to MineSejahtera program");
  cout << "1. Sign In" << endl;
  cout << "2. Sign Up" << endl;
  cout << "\nOption: ";
}

void promptUser(User person[],string ic, string name, string pw, int &rear, int choice) {
  cout << "IC Number (without spaces or \"-\"): ";
  getline(cin, person[rear].ic);
  if ((rear == 0 && choice == 2) || choice == 1) {
    cout << "Username: ";
  } else {
    cout << "Dependent's name: ";
  }
  getline(cin, person[rear].name);
  if (choice == 1 || choice == 2) {
    cout << "Password: ";
    getline(cin, person[rear].pw);
  }
  if (choice != 1) {
   rear++; 
  }
}

void promptLoc() {
  // ask user for location information
  cout << "Which Location are you Entering? : " <<endl;
}

// enqueuing dependents
void nQueue(User dependent[], string ic, string name, string pw, int &front, int &rear, int choice) {
  if(rear == SIZE - 1) {
    cout << "Maximum number of dependent reached!" << endl;
    cout << "\nPress any key to continue...";
    getchar();
  } else if (front == -1 && rear == -1) { 
    // register user
    front++;
    rear++;
    promptUser(dependent, ic, name, pw, rear, choice);
    loading("line");
    cout << endl << "Registered successfully!" << endl;
    front++;
    sleep(2);
  } else if (dependent[0].ic != "" && dependent[0].pw != "" && choice == 2) {
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

// display list of dependents
void dispQueue(User dependent[], int front, int rear) {
  cout << "\n**********************\n\n";
  if(front <= 1 && rear <= 1) {
    cout << "No dependent available\n\n";
  } else {
    cout << "Displaying dependents" << flush;
    loading("");
    sleep(1);
    cout << "\x1b[2K";
    while (front >= 1 && front < rear) {
      cout << "\rDependent #" << front << endl;
      cout << "IC Number: " << dependent[front].ic << endl;
      cout << "Name: " << dependent[front].name << "\n\n";
      sleep(1);
      front++;
    }
  }
}

// dequeuing dependents
void dQueue(User dependent[], int front, int &rear) {
  int remove = 0;
  if(front >= 1 && rear >= 2) {
    cout << "\nWhich dependent do you wish to remove?" << endl;
    dispQueue(dependent, front,rear);
    cout << "\nOption: ";
    cin >> remove;
    cin.ignore();
    cout << "*********************" << endl;
    cout << "\nRemoving Dependent #" << remove << endl;
    cout << "Removing dependent " << dependent[remove].name << flush; 
    loading("");
    sleep(1);
    cout << "\x1b[2K";
    cout << "\rRemoving IC number " << dependent[remove].ic << flush;
    loading("");
    sleep(1);
    cout << "\x1b[2K";
    cout << "\r\nDependent removed" << endl;
    sleep(2);
    for (int i = remove; i < rear; i++) {
      dependent[i].ic = dependent[i + 1].ic;
      dependent[i].name = dependent[i + 1].name;
    }
    rear--;
  } else {
    cls();
    cout << "No dependent to be removed" << endl;
    sleep(2);
  }
}

void addHistory(Hist*& front, Hist* history, Hist* rear) {
  /*Adding data from top*/
  history->nxtHist = NULL;
  /* Is this a function? because you cannot define a function in another function in C++
     Not exactly sure if C# can or not
  Hist * addRear(Hist *head, Hist* history)
  {
    Hist *guide = head;
    while(guide->nxtHist != NULL)
    {
      guide = guide->nxtHist;
    }
    guide->nxtHist = nHist;
  }
  */
}

void delHistory() {
  /*Deleting data from History*/
  /*
  Hist * deleteRear(Hist *head)
  {
    Car *rear = head;
    while(rear->nxtHist->nxtHist != NULL)
    {
      rear = rear->nxtHist;
      cout << "Deleting " << rear->nxtHist->Hist << endl << endl;
    }
    rear->nxtHist = NULL;
  }
  */
}

void dispHistory(Hist* head) {
  /* Displaying each variable*/
  Hist *nav = head;
  while(nav != NULL)
  {
    cout << "Location: " << nav->location <<endl;
    cout << "Year: " << nav->yr <<endl;
    cout << "Month: "<< nav->mth <<endl;
    cout << "Day: "  << nav->day <<endl;
    cout << "Time: " << nav->hr << " hr " 
                     << nav->min << " min " 
                     << nav->sec << " sec " <<endl;
    nav = nav->nxtHist;
  }

}

// verify login
bool login(User user[], string ic, string password) {
  if(ic == user[0].ic && password == user[0].pw) {
    loading("line");
    cout << "\nLogin succesful!" << endl;
    sleep(2);
    cls();
    return true;
  } else {
    loading("line");
    cout << "\nIC and password not matched!" << endl;
    sleep(2);
    cls();
    return false;
  }
}

//main
int main() {
  User dependent[SIZE];
  int choice = 0, front = -1, rear = -1;
  string icNum;
  string name;
  string password;
  bool logged = false;
  bool quit = false;
  
  do {
    while(!logged) {
      cls();
      welcome();
      cin >> choice;
      cin.ignore();
      cls();

      switch(choice) {
        case 1: {
          if (front == -1 && rear == -1) {
            cout << "No existing account" << endl;
            sleep(2);
            cls();
            break;
          } else {
            optionMenu("Sign In");
            // function for passing ic and password into struct
            cout << "IC Number (without spaces and \"-\"): ";
            getline(cin, icNum);
          
            cout << "Password: ";
            getline(cin, password);

            // verify login
            logged = login(dependent, icNum, password);
            }
          break;
        }
        case 2: {
          optionMenu("Sign Up");
          // function for passing ic and password into struct
          nQueue(dependent, icNum, name, password, front, rear, choice);
          cls();
          break;
        }
      
        default: {
          cout << "Invalid option!" << endl;
          sleep(2);
          cls();
          break;
        }
      }
    };

    int mainOption = 0;
    string welcomeMsg = "Welcome " + dependent[0].name + "!";
    
    cls();
    optionMenu(welcomeMsg);
    cout << "1. Locations" << endl;
    cout << "2. Dependents" << endl;
    cout << "3. Log out" << endl;
    cout << "4. Quit" << endl;
    cout << "\nOption: ";
    cin >> mainOption;
    cin.ignore();

    switch(mainOption) {
      case 1: {
        int locOption = 0;
        cls();
        optionMenu("Location");
        cout << "1. Check in" << endl;
        cout << "2. Check out" << endl;
        cout << "3. History" << endl;
        cout << "\n0. Back" << endl;
        cout << "Option: ";
        cin >> locOption;
        cin.ignore();

        switch(locOption) {
          case 1: {
            // check in
            break;
          }

          case 2: {
            // check out
            break;
          }

          case 3: {
            // display history
            break;
          }
        }
        break;
      }

      case 2: {
        int depOption = 0;
        cls();
        optionMenu("Dependent");
        cout << "1. Add Dependent" << endl;
        cout << "2. Remove Dependent" << endl;
        cout << "3. Display Dependents" << endl;
        cout << "\n0. Back" << endl;
        cout << "Option: ";
        cin >> depOption;
        cin.ignore();

        switch(depOption) {
          case 0: {
            break;
          }
          case 1: {
            // add dependent
            cout << endl;
            nQueue(dependent, icNum, name, password, front, rear, 0);
            break;
          }

          case 2: {
            // remove dependent
            dQueue(dependent, front, rear);
            break;
          }

          case 3: {
            // display dependent
            dispQueue(dependent, front, rear);
            cout << "Press any key to continue... ";
            getchar();
            break;
          }
        }
        break;
      }

      case 3:
        cout << "\nLogging out... ";
        loading("line");
        logged = false;
        break;

      case 4:
        cout << "\nQuitting" << flush;
        loading("");
        sleep(1);
        cout << "\n\n";
        quit = true;
        break;
    }
    
  } while(!quit);


  return 0;
}