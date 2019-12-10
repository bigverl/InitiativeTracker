#ifndef INITIATIVETRACKER_H
#define INITIATIVETRACKER_H

#include "Actor.h"
#include "DynamicList.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// This is menu printing and formatting stuff
#include <iomanip>
#include <sstream>

using namespace std;

class InitiativeTracker
{
private:
    DynamicList<Actor> combatList;
    string initiativeList;
    const int MENU_LINE_SIZE = 48;

public:
    //Methods

    // Program driver
    void Begin()
    {
        MainMenu();
    }


        // --------------- Menu Output Methods -------------- //

    // Put menu body into menu template and print
    void PrintMenu(const string menuBody)
    {
        /**********************************************
         *                                            *
         *                menuOptions                 *
         *                                            *
         **********************************************
        */

        // Store header
        cout   << setfill('*') << "*" << setw(MENU_LINE_SIZE +1) << "*" << endl
               << setfill(' ') << "*" << setw(MENU_LINE_SIZE +1) << "*" << endl
               << setfill(' ')
        // Store imported menu options
               << menuBody << endl
        // Store footer
               << setfill(' ') << "*" << setw(MENU_LINE_SIZE +1) << "*" << endl
               << setfill('*') << "*" << setw(MENU_LINE_SIZE +1) << "*"
               << endl << endl;
    }

    // Load main menu body into string to be output by PrintMenu
    string LoadMainMenu()
    {

        /*                Welcome to                  *
         *        Verly's Initiative Tracker!         *
         *                                            *
         *        <C> Create Combat Encounter         *
         *        <G> Fight!                          *
         *        <P> Clear Combat                    *
         *        <Q> Quit                            *

         */

        ostringstream stream;
        string menuPrompt;
        const int LEFT_COL = 6;

        // Welcome to Verly's Initiative Tracker!
        stream << '*' << CenterString("Welcome to", MENU_LINE_SIZE) << '*' << endl
               << '*' << CenterString("Verly's Initiative Tracker!", MENU_LINE_SIZE)
               << '*' << endl
               << setfill(' ') << '*' << setw(MENU_LINE_SIZE +1) << '*' << endl
        // Create Combat Encounter
               << left << setw(LEFT_COL) << '*'
               << setw(MENU_LINE_SIZE - LEFT_COL + 1)
               << "<C> Create Combat Encounter" << '*' << endl
        // Fight!
               << left << setw(LEFT_COL) << '*'
               << setw(MENU_LINE_SIZE - LEFT_COL + 1)
               << "<G> Fight!" << '*' << endl
        // Clear Combat
               << left << setw(LEFT_COL) << '*'
               << setw(MENU_LINE_SIZE - LEFT_COL + 1)
               << "<P> Reset Combat" << '*' << endl
        // Quit
               << setw(LEFT_COL) << '*'
               << setw(MENU_LINE_SIZE - LEFT_COL + 1)
               << "<Q> Quit" << '*'
               << right;
        menuPrompt = stream.str();
        return menuPrompt;
    }

    // Load 'Create Combat Encounter' body into string to be output by PrintMenu'
    string LoadEncounterCreationMenu()
    {

        /*          Create Combat Encounter           *
         *                                            *
         *        <C> Add Party to Combat             *
         *        <A> Add Ally/Enemy to Combat        *
         *        <Q> Back to Main Menu               *

         */

        ostringstream stream;
        string menuOptions;
        const int LEFT_COL = 6;

        // Welcome to Verly's Initiative Tracker!
        stream << '*' << CenterString("Create Combat Menu", MENU_LINE_SIZE)
               << '*' << endl
               << setfill(' ') << '*' << setw(MENU_LINE_SIZE +1) << '*' << endl
        // Add Party to Combat
               << left << setw(LEFT_COL) << '*'
               << setw(MENU_LINE_SIZE - LEFT_COL + 1)
               << "<C> Add Party to Combat" << '*' << endl
        // Add Ally/Enemy to Combat
               << left << setw(LEFT_COL) << '*'
               << setw(MENU_LINE_SIZE - LEFT_COL + 1)
               << "<A> Add Ally/Enemy to Combat" << '*' << endl
        // Quit
               << setw(LEFT_COL) << '*'
               << setw(MENU_LINE_SIZE - LEFT_COL + 1)
               << "<Q> Back to Main Menu" << '*'
               << right;
        menuOptions = stream.str();
        return menuOptions;
    }

    // Output template used for conducting combat
    void PrintScroll(const string &menuBody)
    {
        cout << menuBody;




        string tempName;

        tempName = UppercaseString(combatList[0].GetName());
        cout << tempName << "'S TURN!" << endl;
    }

    /*upperCase() *************************************
     *  This function takes a string input and converts all characters
     *  to uppercase for use in search function
     *
     *  Receives:
     *  input : string
     *
     *  Returns:
     *  nothing
     ******************************************************/
    string UppercaseString(string input)
    {
        unsigned int counter;

        for (counter = 0; counter < input.length(); counter++)
        {
            input[counter] = toupper(input[counter]);
        }

        return input;
    }

    /**************************************************************************
     * FUNCTION CenterString
     * ------------------------------------------------------------------------
     * Purpose : This function will center text a line of text
     * ------------------------------------------------------------------------
     * RECEIVES
     * Text and the size of the line
     *
     * RETURNS
     * stream : string
     **************************************************************************/
    string CenterString(string text, const int LINE_SIZE)
    {
        ostringstream stream;
        int length = text.length();
        int position = (int)((LINE_SIZE - length)/2);

        if(text.length() % 2 == 0)
        {
            for(int index = 0; index < position; index++)
            {
                stream << " ";
            }

            stream << text;

            for(int index = 0; index < position; index++)
            {
                stream << " ";
            }
        }
        else
        {
            for(int index = 0; index < position; index++)
            {
                stream << " ";
            }

            stream << text << " ";

            for(int index = 0; index < position; index++)
            {
                stream << " ";
            }
        }
        return stream.str();
    }

        // --------------- Menu Input Methods --------------- //

    // 'Main Menu' module
    void MainMenu()
    {
        enum MainMenuOptions{ CREATE_ENCOUNTER = 'C', FIGHT = 'G', RESET = 'P',
                              QUIT = 'Q' };
        const int inputArSize = 4;
        char inputAr [inputArSize] = {'C', 'G', 'P', 'Q'};
        string mainMenuOutput;
        bool invalidInput = true;
        bool inMainMenu = true;
        char mainMenuOption;
        const string PROMPT = "Choice: ";

        // Prepare menu prompt
        mainMenuOutput = LoadMainMenu();

        // Start menu
        while(inMainMenu)
        {
            system("cls");
            invalidInput = true;

            while(invalidInput)
            {
                PrintMenu(mainMenuOutput);
                invalidInput = ValidateCharInput(inputAr, inputArSize,
                                                mainMenuOption, PROMPT);
                if(invalidInput)
                {
                    cout << "Invalid Input. Please use letters listed in menu."
                         << endl;
                    system("pause");
                    system("cls");
                }
            }// END while(invalidInput)

            switch(mainMenuOption)
            {
                case CREATE_ENCOUNTER: EncounterCreationMenu();
                        break;
            case FIGHT: if(combatList.Size() > 0)
                        {
                            PrepareCombat();
                            StartCombat();
                        }
                        else
                        {
                            cout << "No combatants added." << endl;
                            system("pause");
                        }
                        break;
                case RESET: ResetCombat();
                        break;
                case QUIT:          inMainMenu = false;
                        break;
            }
        }// END while(inMainMenu)
    }

    // 'Create Combat Encounter' Menu Module
    void EncounterCreationMenu()
    {
        enum EncounterMenuOptions{ ADD_PARTY = 'C', ADD_ACTOR = 'A', QUIT = 'Q' };
        const int inputArSize = 3;
        char inputAr [inputArSize] = {'C', 'A', 'Q'};
        string encounterMenuOutput;
        bool invalidInput = true;
        bool inEncounterMenu = true;
        char encounterMenuOption;
        bool partyAdded = false;
        const string PROMPT = "Choice: ";

        // Prepare menu prompt
        encounterMenuOutput = LoadEncounterCreationMenu();

        // Start menu
        while(inEncounterMenu)
        {
            system("cls");
            invalidInput = true;

            while(invalidInput)
            {
                PrintMenu(encounterMenuOutput);
                invalidInput = ValidateCharInput(inputAr, inputArSize,
                                                encounterMenuOption, PROMPT);
                if(invalidInput)
                {
                    cout << "Invalid Input. Please use letters listed in menu."
                         << endl;
                    system("pause");
                    system("cls");
                }
            }// END while(invalidInput)

            switch(encounterMenuOption)
            {
                case ADD_PARTY: if(!partyAdded)
                                {
                                    AddPartyFromFile();
                                    cout << "Party Added!" << endl;
                                    partyAdded = true;
                                }
                                else
                                {
                                    cout << "Party already added from file.";
                                }
                                system("pause");
                        break;
                case ADD_ACTOR: AddActors();
                        break;
                case QUIT:      inEncounterMenu = false;
                        break;
            }
        }// END while(inEncounterMenu)
    }


    // This will reset the list back to empty state
    void ResetCombat()
    {
        combatList.InitializeList();
    }

        // --------------- COMBAT METHODS --------------- //

    // Add default party from text file
    void AddPartyFromFile()
    {
        ifstream fin;
        string name;
        Actor temp;

        fin.open("partydb.txt");

        // Loop to add
        if(fin)
        {
            getline(fin, name);
        }
        else
        {
            cout << "Database file not found. Ensure text file is in same directory as .exe";
            system("pause");
        }

        while(fin)
        {
            temp.SetName(name);
            combatList.Add(temp);
            getline(fin, name);
        }

        fin.close();
    }

    // Uppercases each letter in a sentence or name
    void UppercaseFirstLetter(string &name)
    {

        unsigned int index = 0;
        name[index] = toupper(name.at(index));
        for(int index = 0; index < name.length(); index++)
        {
            if(name.at(index) == ' ')
            {
                name[index + 1] = toupper(name.at(index+1));
            }
        }
    }


    /******************************************************************************
     * FUNCTION: ValidateIntInput
     * ----------------------------------------------------------------------------
     * Purpose : This function validates user's number input according to minumum
     *           and acceptable limits. It prints whichever menu and prompt passed
     *           in.
     * ----------------------------------------------------------------------------
     *  Receives:
     *      minLimit       : int
     *      maxLimit       : int
     *      numInput       : int
     *      prompt         : string
     *
     *  Returns:
     *      invalid        : int
     ******************************************************************************/
    bool ValidateIntInput(const int &minLimit, const int &maxLimit,
                          int &numInput, const string &prompt)
    {
        bool invalid;
        // Initialize invalid
        invalid = true;

        while (invalid)
        {
            // Print Prompt
            cout << prompt;

            // Input number
            while (!(cin >> numInput))
            {
                // Clear error
                cin.clear();
                cin.ignore(999, '\n');
                // Inform user of invalid attempt and re-prompt
                cout << "Invalid input. Please enter a number between "
                     << minLimit << " and " << maxLimit << "." << endl;
                system("pause");
                system("cls");

                // Print Prompt
                cout << prompt;
            } // while(!cin >> numInput)

            // Define valid
            invalid = numInput < minLimit || numInput > maxLimit;
            if (invalid)
            {
                cout << "Invalid input. Please enter a number between "
                     << minLimit << " and " << maxLimit << "." << endl;
                system("pause");
                system("cls");
            }
        } // while(invalid)

        // Clear Buffer
        cin.ignore(999, '\n');
        // Return valid input
        return invalid;
    }

    // Prompt user for name of group and number of actors. adds group to combatList
    void AddActors()
    {
        string name;
        string finalName;
        string suffix;
        int actorCount = 0;
        bool invalidInput = true;
        bool addingActors = true;
        ostringstream stream;
        string prompt;
        Actor temp;



        while(addingActors)
        {
            bool invalidInput = true;

            while(invalidInput)
            {
                system("cls");
                // User enters actor type
                cout << "Enter name of creature (input x to exit): ";
                getline(cin, name);

                invalidInput = name.size() <= 0;
                if(invalidInput)
                {
                    cout << "You didn't enter a name." << endl;
                    system("pause");
                }
                else
                {
                    UppercaseFirstLetter(name);
                }
            }
            addingActors = name != "X";

            if(addingActors)
            {
                invalidInput = true;
                // User enters number of actors in group
                while(invalidInput)
                {
                    system("cls");
                    // Store prompt
                    stream << "Enter number of " << name << "s" << " to add: ";
                    prompt = stream.str();
                    // Get valid user input
                    invalidInput = ValidateIntInput(0, 30, actorCount, prompt);
                    // Clear stream for next prompt
                    if(!invalidInput)
                    {
                        stream.str("");
                    }
                }// END while(invalidInput)

                if(actorCount > 0)
                {
                    // Add actors to combatList with numbered suffix
                    for(int index = 0; index < actorCount; index++)
                    {
                        if(actorCount == 1)
                        {
                            temp.SetName(name);
                            combatList.Add(temp);
                        }
                        else
                        {
                            finalName = name + ' ' + to_string(index + 1);
                            temp.SetName(finalName);
                            combatList.Add(temp);
                        }
                    }
                }
                else // actorCount < 1
                {
                    cout << "You didn't add any " << name << endl;
                    system("pause");
                }
            }// END if(name != "X")
        }// END while(addingActors)
    }

    // Create un-numbered list to insert into battlescreen
    string CreateInitiativeList()
    {
        const int LEFT_COL = 20;
        ostringstream stream;

        stream << left;

        stream << setw(LEFT_COL) << "Name:" << endl;

        for(int index = 0; index < combatList.Size(); index++)
        {
            stream << left;
            stream <<  "* " << setw(LEFT_COL) << combatList[index].GetName();
            stream << right;
            stream << setw(10) << combatList[index].GetInitiative() << endl;
        }

        return stream.str();

    }

    // Sort list before combat in descending order of initiative
    void SortList()
    {
        int index;
        int smallestIndex;
        int location;
        Actor temp;

        for (index = 0; index < combatList.Size() - 1; index++){
            //Step a
            smallestIndex = index;

            for (location = index + 1; location < combatList.Size(); location++){
                if (combatList[location].GetInitiative() > combatList[smallestIndex].GetInitiative())
                    smallestIndex = location;
            }
            //Step b

            temp = combatList[smallestIndex];
            combatList[smallestIndex] = combatList[index];
            combatList[index] = temp;
        }
    }

    void PrepareCombat()
    {
        int initiative = 0;
        bool invalidInput = true;
        ostringstream stream;
        string prompt;

        // User inputs initiative for all actors
        for(int index = 0; index < combatList.Size(); index++)
        {
            invalidInput = true;

            while(invalidInput)
            {
                system("cls");
                // Load correct prompt into stream
                stream << "Input initiative for " << combatList[index].GetName()
                     << ": ";
                prompt = stream.str();

                // Validate Input
                invalidInput = ValidateIntInput(0, 30, initiative, prompt);

                // Clear stream for next prompt
                stream.str("");
            } // END while(invalidInput)

            combatList[index].SetInitiative(initiative);
        }

        SortList();

        initiativeList = CreateInitiativeList();
    }

    // Menu Options are all Chars
    bool ValidateCharInput(char validAr[], const int &arSize, char &charInput,
                           const string prompt)
    {
        bool invalidInput = true;
        int index = 0;

        // Output prompt
        cout << prompt;
        // Get input
        cin.get(charInput);
        cin.ignore(999, '\n');
        charInput = toupper(charInput);

        // Validate input
        while(index < arSize && invalidInput)
        {
            invalidInput = charInput != validAr[index];
            index++;
        }

        return invalidInput;
    }

    // Combat Module
    void StartCombat()
    {
        string numberedList;
        char battleInput;
        int deadIndex;
        bool inBattle = true;
        enum BattleOptions{CONTINUE = 'C', KILL = 'K', QUIT = 'Q'};
        const int inputArSize = 3;
        char inputAr [inputArSize] = {'C', 'K', 'Q'};
        const string OPTION_PROMPT = "Next Actor (C), Kill (K), Quit (Q): ";
        ostringstream stream;
        string killPrompt;
        bool invalidInput;

        while(inBattle)
        {
            invalidInput = true;
            // Print menu and prompt
            while(invalidInput)
            {
                system("cls");
                initiativeList = CreateInitiativeList();
                PrintScroll(initiativeList);
                invalidInput = ValidateCharInput(inputAr, inputArSize,
                                                 battleInput, OPTION_PROMPT);
                if(invalidInput)
                {
                    cout << "Invalid Input. Please use letters listed in menu."
                         << endl;
                    system("pause");
                    system("cls");
                }
            }// END while(invalidInput)

            switch (battleInput)
            {
                case CONTINUE:  GetNextActor();
                            break;
                case KILL:      system("cls");
                                numberedList = CreateNumberedList();
                                PrintScroll(numberedList);
                                stream << "Kill who? (1-" << combatList.Size() << ") ";
                                killPrompt = stream.str();
                                ValidateIntInput(1, combatList.Size(), deadIndex, killPrompt);
                                KillActor(deadIndex - 1);
                                // Clear prompt string
                                stream.str("");
                            break;
                case QUIT:      inBattle = false;
                                ResetCombat();
                            break;
            }
        }// END while(inBattle)
    }

    // Create numbered list of active combatants for user to choose who to 'kill'
    string CreateNumberedList()
    {
        const int LEFT_COL = 20;
        ostringstream stream;

        stream << left;

        stream << setw(LEFT_COL) << "Name:" << endl;

        for(int index = 0; index < combatList.Size(); index++)
        {
            stream << left;
            stream <<  "* [" << index + 1 << ']' << setw(LEFT_COL) << combatList[index].GetName();
            stream << right;
            stream << setw(10) << combatList[index].GetInitiative() << endl;
        }

        return stream.str();

    }

    // Allow user to remove an actor from combat
    void KillActor(const int &deadIndex)
    {
        combatList.Remove(combatList[deadIndex]);
    }

    // Cycles list to put 'on deck' player on top, and top player on bottom

    void GetNextActor()
    {
        int index = 0;
        Actor temp = combatList[0];
        for (index = 0; index < combatList.Size() - 1; index++)
        {
            combatList[index] = combatList[index + 1];
        }
            combatList[index] = temp;
    }

/* Main Menu
        ,     \    /      ,
       / \    )\__/(     / \
      /   \  (_\  /_)   /   \
 ____/_____\__\@  @/___/_____\____
|             |\../|              |
|              \VV/               |
|           Welcome to            |
|   Verly's Initiative Tracker    |
|                                 |
|    C. Create Combat Encounter   |
|    G. Fight!                    |
|    P. Reset Combat              |
|    Q. Quit                      |
|_________________________________|
 |    /\ /      \\       \ /\    |
 |  /   V        ))       V   \  |
 |/     `       //        '     \|
 `              V                '
*/

/* Create Combat Menu
        ,     \    /      ,
       / \    )\__/(     / \
      /   \  (_\  /_)   /   \
 ____/_____\__\@  @/___/_____\____
|             |\../|              |
|              \VV/               |
|     Create Combat Encounter     |
|                                 |
|    A. Add Party to Combat       |
|    B. Add Ally/Enemy to Combat  |
|    Q. Back                      |
|_________________________________|
 |    /\ /      \\       \ /\    |
 |  /   V        ))       V   \  |
 |/     `       //        '     \|
 `              V                '
*/

/* Add Ally/Enemy
        ,     \    /      ,
       / \    )\__/(     / \
      /   \  (_\  /_)   /   \
 ____/_____\__\@  @/___/_____\____
|             |\../|              |
|              \VV/               |
|   Enter Name:                   |
|_________________________________|
 |    /\ /      \\       \ /\    |
 |  /   V        ))       V   \  |
 |/     `       //        '     \|
 `              V                '
*/



/* Battle Screen
 __________________________________
/  \                               \.
|   |                              |.
|   |  Name                  Init. |.
 \_ |  _____________________|______|.
    |  Skeleton Warrior 10  | 15   |.
    |  --------------------------- |.
    |  Jahan                | 12   |.
    |  --------------------------- |.
    |  Vampire              | 10   |.
    |  --------------------------- |.
    |                              |.
    |                              |.
    |                              |.
    |                              |.
    |                              |.
    |                              |.
    |   ___________________________|___
    |  /                               /.
    \_/______________________________ /.
*/
};

#endif // INITIATIVETRACKER_H
