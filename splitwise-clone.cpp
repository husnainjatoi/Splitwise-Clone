#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int maxusers = 100;
const int maxgroups = 100;
const int maxGroupMem = 100;
const int maxlength = 50;

char users[maxusers][maxlength];
char groups[maxgroups][maxlength];
int groupMembers[maxgroups][maxGroupMem];
int groupsize[maxgroups] = {0};
double balances[maxusers] = {0};

int totalusers = 0;
int totalgroups = 0;

int UserNum(const char *);
int GroupNum(const char *);
void savefile();
void loadfile();
void newuser();
void newgroup();
void newexpense();
void totalexpense();

int main() {
    loadfile();
    int choice;

    while (true) {
        cout << "Menu: \n";
        cout << "1. Add new user \n";
        cout << "2. Create new group \n";
        cout << "3. Add Expense \n";
        cout << "4. Show Balances \n";
        cout << "5. Exit \n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1: newuser(); 
                      break;
            case 2: newgroup(); 
                    break;
            case 3: newexpense(); 
                    break;
            case 4: totalexpense(); 
                    break;
            case 5:
                cout << "Thanks for using the program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid Choice! Please enter a valid option.\n";
        }
    }
    return 0;
}

int UserNum(const char *name) {
    for (int i = 0; i < totalusers; i++) {
        if (strcmp(users[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int GroupNum(const char *name) {
    for (int i = 0; i < totalgroups; i++) {
        if (strcmp(groups[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void savefile() {
    ofstream fileOut("splitwise.txt");
    if (!fileOut) {
        cout << "Error saving the data file!\n";
        return;
    }

    fileOut << totalusers << endl;
    for (int i = 0; i < totalusers; i++) {

        fileOut << users[i] << endl;  
        fileOut << balances[i] << endl; 
    }

    fileOut << totalgroups << endl;
    for (int i = 0; i < totalgroups; i++) {

        fileOut << groups[i] << endl;  
        fileOut << groupsize[i] << " ";

        for (int j = 0; j < groupsize[i]; j++) {
            fileOut << groupMembers[i][j] << " ";
        }

        fileOut << endl;
    }

    fileOut.close();
}


void loadfile() {
    ifstream fileIn("splitwise.txt");

    if (!fileIn) {
        cout << "File not found. Writing new file\n";
        return;
    }

    fileIn >> totalusers;
    fileIn.ignore(); 

    for (int i = 0; i < totalusers; i++) {

        fileIn.getline(users[i], maxlength);
        fileIn >> balances[i];
        fileIn.ignore(); 
    }

    fileIn >> totalgroups;
    fileIn.ignore(); 

    for (int i = 0; i < totalgroups; i++) {

        fileIn.getline(groups[i], maxlength);
        fileIn >> groupsize[i];
        
        for (int j = 0; j < groupsize[i]; j++) {
            fileIn >> groupMembers[i][j];
        }
        
        fileIn.ignore();
    }

    fileIn.close();
}


void newuser() {

    if (totalusers >= maxusers) {
        cout << "User limit reached, you cannot add more users.\n";
        return;
    }

    char uname[maxlength];
    cout << "Enter the username to add: ";
    cin.ignore();
    cin.getline(uname, maxlength);

    if (UserNum(uname) != -1) {
        cout << "User already exists.\n";
        return;
    }

    strcpy(users[totalusers], uname);
    balances[totalusers] = 0;
    totalusers++;

    savefile();
    cout << "User added successfully.\n";
}

void newgroup() {
    if (totalgroups >= maxgroups) {
        cout << "Group limit reached, you cannot create more groups.\n";
        return;
    }

    char gname[maxlength];
    cout << "Enter the group name: ";
    cin.ignore();  
    cin.getline(gname, maxlength);  

    if (GroupNum(gname) != -1) {
        cout << "Group already exists.\n";
        return;
    }

    int noMembers;
    cout << "Enter the number of members: ";
    cin >> noMembers;

    if (noMembers > maxGroupMem) {
        cout << "Group members limit exceeded.\n";
        return;
    }

    strcpy(groups[totalgroups], gname);
    groupsize[totalgroups] = noMembers;

    cin.ignore();  
    for (int i = 0; i < noMembers; i++) {

        char mname[maxlength];
        cout << "Enter name of member " << i + 1 << ": ";
        cin.getline(mname, maxlength);  

        int mIndex = UserNum(mname);
        if (mIndex == -1) {
            cout << "User does not exist. Add the user first.\n";
            return;
        
        }
        groupMembers[totalgroups][i] = mIndex;
    }

    totalgroups++;
    savefile();
    cout << "Group added successfully.\n";
}

void newexpense() {
    
    char payerName[maxlength], groupName[maxlength];
    double expense;
    cout << "Enter the payer name: ";
    cin.ignore();  
    cin.getline(payerName, maxlength);  

    int payerIdx = UserNum(payerName);
    if (payerIdx == -1) {
        cout << "Payer does not exist. Add the user first.\n";
        return;
    }

    cout << "Enter the amount: ";
    cin >> expense;

    cout << "Enter the group name: ";
    cin.ignore(); 
    cin.getline(groupName, maxlength);  

    int groupIdx = GroupNum(groupName);
    
    if (groupIdx == -1) {

        cout << "Group does not exist. Create the group to add expense.\n";
        return;
    }

    int noGroupMembers = groupsize[groupIdx];
    double share = expense / noGroupMembers;

    balances[payerIdx] += expense;

    for (int i = 0; i < noGroupMembers; i++) {
    
        int memberIdx = groupMembers[groupIdx][i];
        balances[memberIdx] -= share;
    }

    savefile();
    cout << "Expense added successfully. Select Option 4 to see the details.\n";
}


void totalexpense() {
    
    cout << "Summary of balances: \n";

    for (int i = 0; i < totalusers; i++) {

        cout << users[i] << ": " << balances[i] << endl;
    }

}