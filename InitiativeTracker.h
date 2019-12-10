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
    const int MENU_LINE_SIZE = 35;

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
        /*
                    ,     \    /      ,
                   / \    )\__/(     / \
                  /   \  (_\  /_)   /   \
             ____/_____\__\@  @/___/_____\____
            |             |\../|              |
            |              \VV/               |
                        menuBody
            |_________________________________|
             |    /\ /      \\       \ /\    |
             |  /   V        ))       V   \  |
             |/     `       //        '     \|
 `                          V                '
        */

        // Store header
        cout << "        ,    |\\    /|     ,"         << endl
             << "       / \\    )\\__/(     / \\ "       << endl
             << "      /   \\  (_\\  /_)   /   \\ "      << endl
             << " ____/_____\\__\\@  @/___/_____\\ ___"  << endl
             << "|             |\\../|              |" << endl
             << "|              \\VV/               |" << endl
             <<            menuBody << endl
             << "|_________________________________|" << endl
             << "  |    /\\ /      \\\\       \\ /\\   |" << endl
             << "  |  /   V        ))       V   \\ |" << endl
             << "  |/     `       //        '    \\|" << endl
             << "  `              V               '" << endl;

    }

    // Load main menu body into string to be output by PrintMenu
    string LoadMainMenu()
    {

       /* |           Welcome to            |
          |   Verly's Initiative Tracker    |
          |                                 |
          |    C. Create Combat Encounter   |
          |    G. Fight!                    |
          |    P. Reset Combat              |
          |    Q. Quit                      |

         */

        ostringstream stream;
        string menuPrompt;

        stream << '|' << setw(21) << "Welcome to" << "            |" << endl
               << '|' << setw(30) << "Verly's Initiative Tracker!" << "   |" << endl
               << "|" << setfill(' ') << setw(MENU_LINE_SIZE - 1) << '|' << endl
               << "|   <C> Create Combat Encounter   |" << endl
               << "|   <G> Fight!                    |" << endl
               << "|   <P> Reset Combat              |" << endl
               << "|   <Q> Quit                      |";
        menuPrompt = stream.str();
        return menuPrompt;
    }

    // Load 'Create Combat Encounter' body into string to be output by PrintMenu'
    string LoadEncounterCreationMenu()
    {

        /*|     Create Combat Encounter     |
          |                                 |
          |    A. Add Party to Combat       |
          |    B. Add Ally/Enemy to Combat  |
          |    Q. Back                      |

         */

        ostringstream stream;
        string menuOptions;

        stream << '|' << setw(25) << "Create Combat Menu" << "        |" << endl
               << '|' << setfill(' ') << setw(MENU_LINE_SIZE - 1) << '|' << endl
               << "|   <C> Add Party to Combat       |" << endl
               << "|   <A> Add Ally/Enemy to Combat  |" << endl
               << "|   <Q> Back to Main Menu         |";

        menuOptions = stream.str();
        return menuOptions;
    }

    string LoadAddToCombatPrompt()
    {
        //  |   Enter Name:                   |

        const int LEFT_COL = 4;
        ostringstream stream;
        string prompt;

        // Quit
        stream << left
               << setw(LEFT_COL) << '|'
               << setw(MENU_LINE_SIZE - LEFT_COL -1)
               << "Enter Name: " << '|'
               << right;

        prompt = stream.str();
        return prompt;
    }

    // Output template used for conducting combat
    void PrintScroll(const string &menuBody)
    {
       /*
        __________________________________
       /  \                               \.
       |   |                               |.
       |   |   Name                  Init. |.
        \_ | _______________________|______|.
                     cout << menuBody;
        |   ____________________________|___
        |  /                               /.
        \_/_______________________________/.

        */

        cout << " __________________________________" << endl
             << " /  \\                               \\." << endl
             << " |   |                               |." << endl
             << " |   |   Name                  Init. |." << endl
             << "  \\_ |                               |." << endl
                            << menuBody
             << "     |   ____________________________|___" << endl
             << "     |  /                               /." << endl
             << "     \\_/_______________________________/." << endl << endl;

    }

    // Create un-numbered list to insert into battlescreen
    string CreateInitiativeList()
    {
        /*
         |   Skeleton Warrior 10  | 15   |.
         |   --------------------------- |.
         |   Jahan                | 12   |.
         |   --------------------------- |.
         |   Vampire              | 10   |.
         |   --------------------------- |.
         */
        const int NAME_COL = 20;
        const int DASH_FILLER = 30;
        ostringstream stream;

        for(int index = 0; index < combatList.Size(); index++)
        {
            // Name
            stream << left;
            stream << "     |   " << setw(NAME_COL) << setfill(' ') << combatList[index].GetName();
            stream << "  | ";
            // Init
            stream << right;
            stream << setw(3) << combatList[index].GetInitiative() << " |."
                   << endl;
            // Dashes
            stream << "     |   "  << setw(DASH_FILLER)<< setfill('-')
                   << " |." << endl;

        }

        return stream.str();
    }

    // Create numbered list of active combatants for user to choose who to 'kill'
    string CreateNumberedList()
    {

        /*
         | 1 Skeleton Warrior 10  | 15   |.
         |   --------------------------- |.
         | 2 Jahan                | 12   |.
         |   --------------------------- |.
         | 3 Vampire              | 10   |.
         |   --------------------------- |.
         */

        const int NAME_COL = 20;
        const int DASH_FILLER = 30;
        ostringstream stream;

        for(int index = 0; index < combatList.Size(); index++)
        {
            // Name
            stream << left;
            stream << "     | " << index +1 << " " << setw(NAME_COL) << setfill(' ') << combatList[index].GetName();
            stream << "  | ";
            // Init
            stream << right;
            stream << setw(3) << combatList[index].GetInitiative() << " |."
                   << endl;
            // Dashes
            stream << "     |   "  << setw(DASH_FILLER)<< setfill('-')
                   << " |." << endl;

        }
        return stream.str();
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
                                    cout << "Party already added from file." << endl;
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
        ostringstream intInputStream;
        ostringstream scrollStream;
        string scrollPrompt;
        string intInputprompt;
        Actor temp;
        string list;

        while(addingActors)
        {
            invalidInput = true;

            while(invalidInput)
            {
                system("cls");

                // Assign un-numbered list
                list = CreateInitiativeList();
                // Print Scroll
                PrintScroll(list);
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
                    // Store prompt
                    intInputStream << "Enter number of " << name << "s" << " to add: ";
                    intInputprompt = intInputStream.str();
                    // Get valid user input
                    invalidInput = ValidateIntInput(0, 30, actorCount, intInputprompt);
                    // Clear stream for next prompt
                    if(!invalidInput)
                    {
                        intInputStream.str("");
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
        string tempName;

        while(inBattle)
        {
            invalidInput = true;
            // Print menu and prompt
            while(invalidInput)
            {
                system("cls");
                // Output
                initiativeList = CreateInitiativeList();
                PrintScroll(initiativeList);
                tempName = UppercaseString(combatList[0].GetName());
                cout << tempName << "'S TURN!" << endl;

                // Input
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
                                // Output
                                numberedList = CreateNumberedList();
                                PrintScroll(numberedList);
                                stream << "Kill who? (1-" << combatList.Size() << ") ";
                                killPrompt = stream.str();
                                // Input
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
|   |                               |.
|   |  Name                  Init.  |.
 \_ |                               |.
    | 1 Skeleton Warrior 10  | 15   |.
    | ----------------------------- |.
    | 2 Jahan                | 12   |.
    | ----------------------------- |.
    | 3 Vampire              | 10   |.
    | ----------------------------- |.
    |                               |.
    |                               |.
    |                               |.
    |                               |.
    |                               |.
    |                               |.
    |   ____________________________|___
    |  /                               /.
    \_/_______________________________/.
*/
};

#endif // INITIATIVETRACKER_H
