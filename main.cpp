#include <iostream>
#include <stdlib.h>

#ifdef __linux__
  #include <unistd.h>
#elif _WIN32
  #include <Windows.h>
#endif

using namespace std;

int const SIZE = 5;
const int EXAMPLE_SIZE = 5;

/* STRUCTURES */

// using queue array for User
struct User {
  string name, ic, pw;
};

// using stack with linked-list for history
struct Hist {
  string location;
  int yr, mth, day, hr, min, sec;
  Hist* prvHist;
} *top;

/* FUNCTIONS */

// clear screen function
void cls() {
  #ifdef __linux__
    system("clear");
  #elif _WIN32
    system("cls");
  #endif
}

// sleep function
void slp(double microseconds = 1) {
  #ifdef __linux__
    usleep(microseconds*1000000);
  #else
    sleep(microseconds);
  #endif
}

// loading icon
void loading(string mode = "") {
  /*
  This function is just to simulate a loading icon
  */
  if (mode == "line") {
   for(int i = 0; i <= 2; i++) {
    cout << "\b\\" << flush;
    slp(0.3);
    cout << "\b|" << flush;
    slp(0.3);
    cout << "\b/" << flush;
    slp(0.3);
    cout << "\b-" << flush;
    slp(0.3);
    }
    cout << "\b " << flush;
  } else {
    for(int i = 0; i < 3; i++) {;
      slp();
      cout << "." << flush;
    }
  }
}

// title format
void menu(string title) {
  /*

  This function generates a menu like interface for user
  e.g.

  * <your string for the title> *
  ===============================

  */
  cout << "* " << title << " *" << endl;
  for(int i = 0; i < title.length() + 4; i++){
    cout << "=";
  }
  cout << endl;
}

// welcome message
void welcome() {
  menu("Welcome to MineSejahtera program");
  cout << "1. Sign In" << endl;
  cout << "2. Sign Up" << endl;
  cout << "\nOption: ";
}

// press any key to continue...
void enter2Ctn() {
  slp(0.5);
  cout << "Press enter key to continue... " << flush;
  #ifdef __linux__
    getchar();
  #elif _WIN32
    #include <conio.h>
    _getch();
  #endif
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

// enqueuing dependents (including user)
void nQueue(User dependent[], string ic, string name, string pw, int &front, int &rear, int choice) {
  if(rear == SIZE - 1) {
    cout << "Maximum number of dependent reached!" << endl;
    enter2Ctn();
  } else if (front == -1 && rear == -1) { 
    // register user
    front++;
    rear++;
    promptUser(dependent, ic, name, pw, rear, choice);
    loading("line");
    cout << endl << "Registered successfully!" << endl;
    front++;
    slp(2);
  } else if (dependent[0].ic != "" && dependent[0].pw != "" && choice == 2) {
    cls();
    cout << "User already exists!" << endl;
    slp(2);
  } 
  else {
    promptUser(dependent, ic, name, pw, rear, choice);
    cout << endl << "Dependent successfully added!" << endl;
    slp(2);
  }
}

// display list of dependents
void dispQueue(User dependent[], int front, int rear) {
  cout << "\n*********************\n\n";
  if(front <= 1 && rear <= 1) {
    cout << "No dependent available\n\n";
  } else {
    cout << "Displaying dependents" << flush;
    loading();
    slp();
    cout << "\x1b[2K";
    while (front >= 1 && front < rear) {
      cout << "\rDependent #" << front << endl;
      cout << "IC Number: " << dependent[front].ic << endl;
      cout << "Name: " << dependent[front].name << "\n\n";
      slp(0.5);
      front++;
    }
  }
}

// dequeuing dependents
void dQueue(User dependent[], int front, int &rear, int option) {
  int edit = 0;
  int editOption = 0;

  if(front >= 1 && rear >= 2) {
    if (option == 2) {
      cout << "\nWhich dependent do you wish to edit?" << endl;    
    }  else if(option == 3) {
      cout << "\nWhich dependent do you wish to remove?" << endl;
    }

    if (option != 1) {
      dispQueue(dependent, front,rear);
      cout << "\nOption: ";
      cin >> edit;
      cin.ignore();
    }
    
    if (edit == 2 || option == 1) {
      cout << "*********************" << endl;
      if(edit == 2) {
        cout << "\nEditing Dependent #" << edit << endl;
      } else {
        cout << "\nEditing Profile" << endl;
      }
      cout << "\n1. Name" << endl;
      cout << "2. IC number" << endl;
      cout << "\n0. Back" << endl;
      cout << "Option: ";
      cin >> editOption;
      cin.ignore();
      
      switch(editOption) {
        case 0:
        break;
        case 1:
        cout << "New name: ";
        if (edit == 2) {
          getline(cin, dependent[edit].name);
        } else {
          getline(cin, dependent[0].name);
        }
        break;

        case 2:
        cout << "New IC: ";
        if (edit == 2) {
          getline(cin, dependent[edit].ic);
        } else {
          getline(cin, dependent[0].ic);
        }
        break;

        default:
        cout << "Invalid option!" << endl;
        enter2Ctn();
      }
      cout << endl;
      loading("line");
      cout << "Edit successful!" << endl;
      slp();
      
    } else if(edit == 3) {
      cout << "*********************" << endl;
      cout << "\nRemoving Dependent #" << edit << endl;
      cout << "Removing dependent " << dependent[edit].name << flush; 
      loading();
      slp(0.5);
      cout << "\x1b[2K";
      cout << "\rRemoving IC number " << dependent[edit].ic << flush;
      loading();
      slp(0.5);
      cout << "\x1b[2K";
      cout << "\r\nDependent removed" << endl;
      slp(0.5);
      for (int i = edit; i < rear; i++) {
        dependent[i].ic = dependent[i + 1].ic;
        dependent[i].name = dependent[i + 1].name;
        }
      rear--;
      }

  } else if (option == 1) {
    cls();
    cout << "Editing Profile" << endl;
    cout << "*********************" << endl;
    cout << "\n1. Name" << endl;
    cout << "2. IC number" << endl;
    cout << "\n0. Back" << endl;
    cout << "\nOption: ";
    cin >> editOption;
    cin.ignore();
      
    switch(editOption) {
      case 0: 
        break;
      case 1: {
        cout << "\nNew name: ";
        getline(cin, dependent[0].name);
        break;
      }

      case 2: {
        cout << "\nNew IC: ";
        getline(cin, dependent[0].ic);
        break;
      }

      default: {
        cout << "Invalid option!" << endl;
        enter2Ctn();
      }
    }
    cout << endl;
    if(editOption != 0) {
      loading("line");
      cout << "\x1b[2K";
      cout << "\rEdit successful!" << endl;
      slp();
    }
    
  } else { 
    cls();
      if (option == 2) {
        cout << "No dependent to be edited\n\n";
        enter2Ctn();
      }
      else if (option == 3) {
        cout << "No dependent to be removed\n\n";
        enter2Ctn();
      }
  }
}

Hist* addHistory(Hist* hist, string location, int yr, int mth, int day, int hr, int min, int sec) {
  // Create new node temp and allocate memory
  Hist* temp;

  temp->location = location;
  temp->yr = yr;
  temp->mth = mth; 
  temp->day = day;
  temp->hr = hr;
  temp->min = min;
  temp->sec = sec;

  temp->prvHist = hist;

  hist = temp;

  top = temp;

  return hist;
}
/*
void delHistory(Hist *top) {
  Deleting data from History
    Hist *rear = top;
    while(rear->nxtHist->nxtHist != NULL)
    {
      rear = rear->nxtHist;
      cout << "----- Deleting -----" << rear->nxtHist << endl << endl;
    }
    rear->nxtHist = NULL;

}*/

Hist* delHistory(Hist* history) //If verify worked bool (Can remain unused to act as void)
{
  /*Deleting data from History*/

    if (top == NULL)
    {
      cout << "\n-------There is no existing History for user.-------" << endl;
      exit(1); //Failed
    }
    else
    {
        // Top assign into temp
        history = history->prvHist;
 
        // Assign second Hist to top
        top = history;
 
        // Destroy connection between
        // first and second
 
        // Release memory of top Hist

        return history; //Success
    }
}
/*
void dispHistory() {
   Displaying each variable
  Hist *nav = top;
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

}*/
void dispHistory(Hist* hist) {

    Hist* temp; //To avoid changing the original, use temp

    temp = hist; //Mark temp as the original so it contains all the info
 
    // Check for stack underflow
    if (temp == NULL)
    {
      cout << "\nNo History to Display";
      enter2Ctn();
    }
    else
    {
      
        while (temp != NULL)
        {
 
          // Print Hist data
 
  //string location; Reference!!!
  //int yr, mth, day, hr, min, sec;

          cout << "Location : " + temp->location << endl;
          cout << "Year:" << temp->yr << endl;
          cout << "Month: "<< temp->mth << endl;
          cout << "Day: "<< temp->day << endl;
          cout << "Time: "<< temp->hr << ":";
          cout << temp->min << ":";
          cout << temp->sec << endl;


          // Assign temp link to nxtHist
        }
    }
}


// verify login
bool login(User user[], string ic, string password) {
  if(ic == user[0].ic && password == user[0].pw) {
    loading("line");
    cout << "\nLogin successful!" << endl;
    slp(1);
    cls();
    return true;
  } else {
    loading("line");
    cout << "\nIC and password not matched!" << endl;
    slp();
    cls();
    return false;
  }
}

//main
int main() {
  User dependent[SIZE];
  Hist* history;
  int choice = 0, front = -1, rear = -1;
  string icNum;
  string name;
  string password;
  bool logged = false;
  bool quit = false;

  const int EXAMPLE_SIZE = 5;

  //Create example Locations that can be added
              string exampleLocations[EXAMPLE_SIZE] = {
                  "Ali'House", "Mamak Store", "TomTom's", "Abali", "Rock'n Stone" 
              };
  
  do {
    while(!logged) {
      cls();
      welcome();
      cin >> choice;
      cin.clear();
      cin.ignore();
      cls();

      switch(choice) {
        case 1: {
          if (front == -1 && rear == -1) {
            cout << "No existing account" << endl;
            slp();
            cls();
            break;
          } else {
            menu("Sign In");
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
          menu("Sign Up");
          // function for passing ic and password into struct
          nQueue(dependent, icNum, name, password, front, rear, choice);
          cls();
          break;
        }
      
        default: {
          cout << "Invalid option!" << endl;
          cls();
          break;
        }
      }
    };

    int mainOption = 0;
    string welcomeMsg = "Welcome " + dependent[0].name + "!";
    
    cls();
    menu(welcomeMsg);
    cout << "1. Locations" << endl;
    cout << "2. Dependents" << endl;
    cout << "3. Profile" << endl;
    cout << "4. Log out" << endl;
    cout << "5. Quit" << endl;
    cout << "\nOption: ";
    cin >> mainOption;
    cin.clear();
    cin.ignore();

    switch(mainOption) {
      case 1: {
        int locOption = 0;
        cls();
        menu("Location");
        cout << "1. Check in" << endl;
        cout << "2. Check out" << endl;
        cout << "3. History" << endl;
        cout << "\n0. Back" << endl;
        cout << "Option: ";
        cin >> locOption;
        cin.clear();
        cin.ignore();

        switch(locOption) {
          case 0: {
            // back
            break;
          }

          case 1: {
            int currentLocation = rand() % (EXAMPLE_SIZE - 1);
            time_t now = time(0);
            tm *ltm = localtime(&now);
            addHistory(history, exampleLocations[currentLocation], 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, 8 + ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

            cout << "Check in successful!" << endl;
            cout << "Location : " << history->location << endl;
            cout << "Year:" << 1900 + history->yr << endl;
            cout << "Month: "<< 1 + history->mth << endl;
            cout << "Day: "<< history->day << endl;
            cout << "Time: "<< 8 + history->hr << ":";
            cout << history->min << ":";
            cout << history->sec << "\n\n";
            enter2Ctn();
            // check in
            break;
          }

          case 2: {
            // check out
            history = delHistory(history);
            break;
          }

          case 3: {
            // display history
            dispHistory(history);
            enter2Ctn();
            break;
          }
        }
        break;
      }

      case 2: {
        int depOption = 0;
        cls();
        menu("Dependent");
        cout << "1. Add Dependent" << endl;
        cout << "2. Edit Dependent" << endl;
        cout << "3. Remove Dependent" << endl;
        cout << "4. Display Dependents" << endl;
        cout << "\n0. Back" << endl;
        cout << "Option: ";
        cin >> depOption;
        cin.clear();
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
            // edit dependent
            dQueue(dependent, front, rear, depOption);
            break;
          }

          case 3: {
            // remove dependent
            dQueue(dependent, front, rear, depOption);
            break;
          }

          case 4: {
            // display dependent
            dispQueue(dependent, front, rear);
            enter2Ctn();
            break;
          }

          default: {
            cout << "\nInvalid option!" << endl;
            enter2Ctn();
          }
        }
        break;
      }

      case 3: {
        int profOption = 0;
        cls();
        menu("Profile");
        cout << "Name: " << dependent[0].name << endl;
        cout << "IC Number: " << dependent[0].ic << endl << endl;
        dispQueue(dependent, front, rear);
        cout << "*********************" << endl;
        cout << "\n1. Edit profile" << endl;
        cout << "\n0. Back" << endl;
        cout << "Option: ";
        cin >> profOption;
        cin.clear();
        cin.ignore();
        switch(profOption) {
          case 0:
            break;
          case 1: {
            dQueue(dependent, front, rear, profOption);
            break;
          }
          default: {
            cout << "\nInvalid option!" << endl;
            slp(0.5);
            break;
          }
        }
        break;
      }

      case 4: {
        cout << "\nLogging out... ";
        loading("line");
        logged = false;
        break;
      }

      case 5: {
        cout << "\nQuitting" << flush;
        loading();
        cout << "\n\n";
        quit = true;
        break;
      }

      default: {
        cout << "\nInvalid option!" << endl;
        slp(0.5);
      }
    }
    
  } while(!quit);

  return 0;
}