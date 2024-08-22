/*
*   Produced by Kyle Gibson
*   17 Aug 2024
*   SC210 - Project 3
*   Item-Tracking Application
*/

#include <iostream>
#include <iomanip> // formatting and setprecision for outputs
#include <fstream>  // Used to Load and Output from files within the workspace
#include <map>  // Used this to create a quick way of storing values for each Item

using namespace std;

void anyKey();
void printMenu(map <string, int>& itemTracker);
void cleanTerminal(); // Experiment to clean the output on the terminal

int main() {
    map<string, int> itemTracker;
    string fileToLoad = "ItemList.txt";
    ifstream loadFile(fileToLoad);

    string itemName;

    //  Loading all items to the map, initializing all items to 0
    if(loadFile.is_open()) {
        while (loadFile >> itemName) {
            itemTracker[itemName] ++;  // Adds 1 if item is in list more than once
        }
        loadFile.close();
    } else {
        cerr << "Cannot load " << fileToLoad << "!" << endl;
    }

    string starLine(80, '*');  // Used to make it look nice!
    
    // Title Screen
    cout << starLine << endl;
    cout << "*" << setw(50) << "Corner Grocer - Item list" << setw(29) << "*" << endl; 
    cout << starLine << endl;

    printMenu(itemTracker);
}

// Implemented this function because I would of had to type it over and over throughout program
void anyKey() {  // While I have used Any Key in the past, this only works with return in this way
    cout << setw(50) << "Press Return To Continue..." << endl;
    cin.ignore();
    cin.get();
}

void printMenu(map <string, int>& itemTracker) {
    bool userStatus = true;
    int width = 80;
    string line(width, '-');
    string starLine(width, '*');

    while (userStatus != false) {
        int userChoice = 0;
        const int nameWidth = 15;
        const int quantityWidth = 10;
        string searchItem;

        // Menu
        cout << line << endl;
        cout << setw(60) << "Please choose from the following options:" << endl;
        cout << line << endl;
        cout << "1): Search for Item" << endl;
        cout << "2): Item Frequency" << endl;
        cout << "3): Item Histogram" << endl;
        cout << "4): Quit" << endl;

        // Input Validation for Menu Selection Choice
        while (true) {
            cin >> userChoice;

            if(cin.fail()) {
                cin.clear();  // Clear Input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards Invalid Inputs
                cerr << "Error: Invalid Option. Please Choose an Option between 1 - 4." << endl;
            } else if (userChoice < 1 || userChoice > 4) {  // Checks for negative values or anything beyond 4
                cerr << "Error: Invalid Option. Please Choose an Option between 1 - 4." << endl;
            } else {
                break; // Breaks the loop
            }
        }
            // User Choices
            switch (userChoice) {
                case 1: {
                    // Search Option
                    cleanTerminal();

                    // Display current Items
                    cout << line << endl;
                    cout << setw(50) << "Current Items Avalable" << endl;
                    cout << line << endl;
                    const int itemsPerLine = 4; // Sets the column amount
                    int itemCount = 0;

                    for (const auto& item : itemTracker) {
                    cout << left << setw(nameWidth) << item.first << " | ";
                    itemCount ++;
                        if (itemCount % itemsPerLine == 0) { // Once itemCount = 4, Starts new row
                            cout << endl;
                        }
                    }
                    cout << endl << line << endl;

                    // Testing user input for errors like empty values
                    do {  
                        cout << "\nItem you are searching for: ";
                        cin.ignore();
                        getline(cin, searchItem);  

                        if (searchItem.empty()) {
                            cerr << "Error: No Value was Input. Please try again." << endl;
                        }
                    } while (searchItem.empty());  // Checks to see if no value was input (Input Validation)

                    auto searchForItem = itemTracker.find(searchItem);
                    if (searchForItem != itemTracker.end()) {
                        cout << "Item found: " << searchForItem->first << " - Quantity: " << searchForItem->second << endl;  
                    } else {
                        cout << "Item \"" << searchItem << "\" not found." << endl;
                    }

                    // Pause for User to Continue
                    cout << endl << line << endl;
                    anyKey();

                    break;
                }
                case 2: {
                    //  Test loaded file and map Use for Menu Option 2
                    cleanTerminal();
                    cout << line << endl;
                    cout << left << setw(nameWidth) << "Item" << setw(quantityWidth) << "Quantity" << endl;
                    cout << line << endl;
                    for (const auto& item : itemTracker) {
                        cout << left << setw(nameWidth) << item.first << setw(quantityWidth) << item.second << endl;
                    }

                    // Pause for User to Continue
                    cout << endl << line << endl;
                    anyKey();

                    break;
                }

                case 3: {
                    //  loaded file and map Use for Menu Option 3 - Histogram
                    cleanTerminal();
                    cout << line << endl;
                    cout << left << setw(nameWidth) << "Item" << setw(quantityWidth) << "Histogram" << endl;
                    cout << line << endl;
                    for (const auto& itemHistogram : itemTracker) {
                        int varWidth = itemHistogram.second;
                        string printStars(varWidth,'*');
                        cout << left << setw(nameWidth) << itemHistogram.first << setw(15) << printStars << endl;
                    } 
                    
                    // Pause for User to Continue
                    cout << endl << line << endl;
                    anyKey();
  
                    break;
                }

                case 4: {
                    cleanTerminal();
                    cout << "Exiting Program..." << endl;

                    //New doc creation
                    string fileToOutput = "frequency.dat";
                    ofstream outFile(fileToOutput); 
                        if (outFile.is_open()) {
                            for (const auto& item : itemTracker) {
                                outFile << item.first << " " << item.second << endl;
                            }
                            outFile.close(); 
                            cout << "Creating frequency.dat file..." << endl;
                        } else {
                            cerr << "Error! Unable to open file: " << fileToOutput << endl;
                        }
                    
                    // Cleaning up
                    itemTracker.clear();
                        if (itemTracker.empty()) {
                            cout << "Map Items have been cleared" << endl;
                        } else {
                            cout << "Could Not Clear Item Map!" << endl;
                        }
                    
                    cout << setw(35) << "Goodbye!" << endl;
                        
                    userStatus = false;  // End Program!!!

                    break;
                }
            
                default: {
                    cleanTerminal();
                    cout << starLine << endl;
                    cout << "Invalid Option! Please try again." << endl;
                    cout << starLine << endl;
                    anyKey();

                    break;
                }
            }
    }
}

// Used to clean up output for user. They don't need to scroll as much through the terminal window
void cleanTerminal() {
    #ifdef _WIN32
        system("cls");  // If Windows, Clears Terminal
    #else
        system("clear"); // If Unix, Linux, AppleOS, clears terminal
    #endif
}