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
    DynamicList<Actor> combatList;  // List of combat actors
    string initiativeList;          // Stored initiative list
    const int MENU_LINE_SIZE = 35;  // Size of lines

public:

    /**************************************************************************
     * FUNCTION: Begin
     * ------------------------------------------------------------------------
     * Purpose : This function starts the program by calling the main menu
     *           module.
     * ------------------------------------------------------------------------
     * Receives:
     *     nothing
     * Returns:
     *     nothing
     *************************************************************************/
    void Begin()
    {
        MainMenu();
    }
        // --------------- Menu Output Methods -------------- //

    /**************************************************************************
     * FUNCTION: PrintMenu
     * ------------------------------------------------------------------------
     * Purpose : This function prints a complete menu by accepting input from
     *           other methods that contain 'menu options' intended to be
     *           printed using the "Dragon Menu" art asset. Once loaded, this
     *           function encases the 'menu options' into a 'menu shell' and
     *           prints the complete menu.
     *
     *           Used with:
     *                  Main Menu, Create Combat Encounter, and
     *                  Add Ally/Enemy to Combat.
     * ------------------------------------------------------------------------
     * Receives:
     *      menuBody : string
     * Returns:
     *      nothing
     *************************************************************************/
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

        cout << "        ,    |\\    /|     ,"            << endl
             << "       / \\    )\\__/(     / \\ "        << endl
             << "      /   \\  (_\\  /_)   /   \\ "       << endl
             << " ____/_____\\__\\@  @/___/_____\\ ___"   << endl
             << "|             |\\../|              |"    << endl
             << "|              \\VV/               |"    << endl
             <<            menuBody << endl
             << "|_________________________________|"     << endl
             << "  |    /\\ /      \\\\       \\ /\\   |" << endl
             << "  |  /   V        ))       V   \\ |"     << endl
             << "  |/     `       //        '    \\|"     << endl
             << "  `              V               '"      << endl;
    }

    /**************************************************************************
     * FUNCTION: LoadMainMenu
     * ------------------------------------------------------------------------
     * Purpose : This function loads menu-specific "Main Menu" options into a
     *           string to be returned and loaded into PrintMenu function.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      menuPrompt : string
     *************************************************************************/
    string LoadMainMenu()
    {

       /* |           Welcome to            |
          |   Verly's Initiative Tracker    |
          |                                 |
          |    C. Create Combat Encounter   |
          |    G. Fight!                    |
          |    R. Reset Combat              |
          |    Q. Quit                      |

         */

        ostringstream stream;
        string menuPrompt;

        stream << '|' << setw(21) << "Welcome to" << "            |"     << endl
               << '|' << setw(30) << "Verly's Initiative Tracker!" << "   |" << endl
               << "|" << setfill(' ') << setw(MENU_LINE_SIZE - 1) << '|' << endl
               << "|   <C> Create Combat Encounter   |" << endl
               << "|   <G> Fight!                    |" << endl
               << "|   <R> Reset Combat              |" << endl
               << "|   <Q> Quit                      |";

        menuPrompt = stream.str();
        return menuPrompt;
    }

    /**************************************************************************
     * FUNCTION: LoadEncounterCreationMenu
     * ------------------------------------------------------------------------
     * Purpose : This function loads menu-specific "Create Combat Encounter"
     *           options into a string to be returned and loaded into PrintMenu
     *           function.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      menuPrompt : string
     *************************************************************************/
    string LoadEncounterCreationMenu()
    {

        /*|     Create Combat Encounter     |
          |                                 |
          |    A. Load Party from File      |
          |    B. Add Ally/Enemy to Combat  |
          |    Q. Back                      |

         */

        ostringstream stream;
        string menuPrompt;

        stream << '|' << setw(25) << "Create Combat Menu" << "        |" << endl
               << '|' << setfill(' ') << setw(MENU_LINE_SIZE - 1) << '|' << endl
               << "|   <C> Load Party from File      |"                  << endl
               << "|   <A> Add Ally/Enemy to Combat  |"                  << endl
               << "|   <Q> Back to Main Menu         |";

        menuPrompt = stream.str();
        return menuPrompt;
    }

    /**************************************************************************
     * FUNCTION: LoadAddToCombatPrompt
     * ------------------------------------------------------------------------
     * Purpose : This function loads menu-specific "Add Ally/Enemy to Combat"
     *           options into a string to be returned and loaded into PrintMenu
     *           function.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      menuPrompt : string
     *************************************************************************/
    string LoadAddToCombatPrompt()
    {
                //  |   Enter Name:                   |

        const int LEFT_COL = 4;
        ostringstream stream;
        string menuPrompt;

        stream << left
               << setw(LEFT_COL) << '|'
               << setw(MENU_LINE_SIZE - LEFT_COL -1)
               << "Enter Name: " << '|'
               << right;

        menuPrompt = stream.str();
        return menuPrompt;
    }

    /**************************************************************************
     * FUNCTION: CreateScroll
     * ------------------------------------------------------------------------
     * Purpose : This function loads specific combat-related information
     *           designed for output using the "Scroll Border" Art Asset. It
     *           loads output into a string to be returned and printed in
     *           appropriate contexts.
     *
     *           Specifically, entering initiative scores, entering number of
     *           creatures of each type, and running the combat encounter.     *
     * ------------------------------------------------------------------------
     * Receives:
     *      menuBody   : const string
     * Returns:
     *      menuPrompt : string
     *************************************************************************/
    string CreateScroll(const string &menuBody)
    {
        ostringstream stream;
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

        stream << " ___________________________________"       << endl
             << " /  \\                                \\."    << endl
             << " |   |                                |."     << endl
             << " |   |   Name                   Init. |."     << endl
             << "  \\_ |                                |."    << endl
                                  << menuBody
             << "     |   _____________________________|___"   << endl
             << "     |  /                                /."  << endl
             << "     \\_/________________________________/."  << endl << endl;

        return stream.str();

    }

    /**************************************************************************
     * FUNCTION: CreateInitiativeList
     * ------------------------------------------------------------------------
     * Purpose : This function creates a standard (non-numbered) list of
     *           combat participants. It will contain their name and associated
     *           initiative value. It is intended to be loaded into
     *           "CreateScroll" to be printed at appropriate times listed
     *           in "CreateScroll" description.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      stream : ostreamstring -> string
     *************************************************************************/
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
            stream << "     |    " << setw(NAME_COL) << setfill(' ')
                   << combatList[index].GetName();
            stream << "  | ";
            // Init
            stream << right;
            stream << setw(3) << combatList[index].GetInitiative() << " |."
                   << endl;
            // Dashes
            stream << "     |    "
                   << setw(DASH_FILLER)<< setfill('-')
                   << " |." << endl;
        }

        return stream.str();
    }

    /**************************************************************************
     * FUNCTION: CreateNumberedList
     * ------------------------------------------------------------------------
     * Purpose : This function creates an alternate (numbered) list of combat
     *           participants. It will contain their name and associated
     *           initiative value. It is intended to be loaded into
     *           "CreateScroll" to be printed specifically when choosing which
     *           actor to remove during combat as a result of being 'killed'
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      stream : ostreamstring -> string
     *************************************************************************/
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
        const int DASH_FILLER = 31;
        ostringstream stream;

        for(int index = 0; index < combatList.Size(); index++)
        {
            // Name
            stream << left;
            stream << "     | " << setfill(' ') << right << setw(2) << index +1 << " "
                   << left << setw(NAME_COL)
                   << combatList[index].GetName();
            stream << "  | ";
            // Initiative
            stream << right;
            stream << setw(3) << combatList[index].GetInitiative() << " |."
                   << endl;
            // Line of Dashes
            stream << "     |   "  << setw(DASH_FILLER)<< setfill('-')
                   << "  |." << endl;

        }
        return stream.str();
    }

    /**************************************************************************
     * FUNCTION: UppercaseString
     * ------------------------------------------------------------------------
     * Purpose : This function converts a string to an uppercase version of
     *           itself. It is used in this case specifically to tell the user
     *           which actor is currently "active" i.e.
     *
     *           "IT'S JOHNNY'S TURN!"
     * ------------------------------------------------------------------------
     * Receives:
     *      input : string
     * Returns:
     *      input : string
     *************************************************************************/
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

    /**************************************************************************
     * FUNCTION: MainMenu
     * ------------------------------------------------------------------------
     * Purpose : This function handles all operations relating to the program's
     *           main menu. From here, user can choose to create a combat
     *           encounter, execute a combat encounter, or quit.
     *
     *           It will validate user input, pass it to the switch statement,
     *           and execute user's desired menu options.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
    void MainMenu()
    {
        enum MainMenuOptions
        {
            CREATE_ENCOUNTER = 'C',
            FIGHT = 'G', RESET = 'R',
            QUIT = 'Q'
        };

        const int inputArSize = 4;
        char inputAr [inputArSize] = {'C', 'G', 'R', 'Q'};
        string mainMenuOutput;
        bool invalidInput = true;
        bool inMainMenu = true;
        char mainMenuOption;
        const string PROMPT = "Choice: ";

        // Prepare Menu Prompt
        mainMenuOutput = LoadMainMenu();

        // Start Menu
        while(inMainMenu)
        {
            system("cls");
            invalidInput = true;

            while(invalidInput)
            {
                // Output
                PrintMenu(mainMenuOutput);

                // Input
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

            // Menu Switch
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

    /**************************************************************************
     * FUNCTION: EncounterCreationMenu
     * ------------------------------------------------------------------------
     * Purpose : This function handles all operations relating to the
     *           "Create Combat Encounter" menu. From here, User can add the
     *           default party to combat, add custom actors to combat via
     *           string input, or go back to the main menu.
     *
     *           It will validate user input, pass it to the switch statement,
     *           and execute user's desired menu options.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
    void EncounterCreationMenu()
    {
        enum EncounterMenuOptions{ ADD_PARTY = 'C', ADD_ACTOR = 'A', QUIT = 'Q' };
        const int inputArSize = 3;
        char inputAr [inputArSize] = {'C', 'A', 'Q'};
        string encounterMenuOutput;
        bool invalidInput;
        bool inEncounterMenu = true;
        char encounterMenuOption;
        bool partyAdded = false;
        const string PROMPT = "Choice: ";

        // Prepare Menu Prompt
        encounterMenuOutput = LoadEncounterCreationMenu();

        // Start
        while(inEncounterMenu)
        {
            system("cls");
            invalidInput = true;

            while(invalidInput)
            {
                // Output
                PrintMenu(encounterMenuOutput);
                // Input
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

            // Menu Switch
            switch(encounterMenuOption)
            {
                case ADD_PARTY: if(!partyAdded)
                                {
                                    AddPartyFromFile();
                                    if(combatList.Size() > 0)
                                    {
                                        cout << "Party Added!" << endl;
                                        partyAdded = true;
                                        system("pause");
                                    }
                                }
                                else
                                {
                                    cout << "Party already added from file." << endl;
                                    system("pause");
                                }

                        break;
                case ADD_ACTOR: AddActors();
                        break;
                case QUIT:      inEncounterMenu = false;
                        break;
            }
        }// END while(inEncounterMenu)
    }

    /**************************************************************************
     * FUNCTION: StartCombat
     * ------------------------------------------------------------------------
     * Purpose : This function represents the primary functionality of this
     *           program. After creating a combat encounter, user will select
     *           this option.
     *
     *           They can choose the following options:
     *              -'Continue' will cycle the initiative list to the
     *                next player
     *              -'Kill' will prompt the user to remove an actor from combat
     *              -'Quit' will exit combat, reset the combat list to empty,
     *              and place the user at the main menu.
     *
     *           It will validate user input, pass it to the switch statement,
     *           and execute user's desired menu options.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
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
        string scroll;

        // Start
        while(inBattle)
        {
            invalidInput = true;

            while(invalidInput)
            {
                system("cls");

                // Output
                initiativeList = CreateInitiativeList();
                scroll = CreateScroll(initiativeList);
                cout << scroll;
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

            // Menu Switch
            switch (battleInput)
            {
                case CONTINUE:  GetNextActor();
                            break;
                case KILL:      system("cls");
                                // Output
                                numberedList = CreateNumberedList();
                                scroll = CreateScroll(numberedList);
                                stream << scroll << "Kill who? (1-"
                                       << combatList.Size() << ") ";
                                killPrompt = stream.str();

                                // Input
                                ValidateIntInput(1, combatList.Size(), deadIndex, killPrompt);
                                KillActor(deadIndex - 1);

                                // Check to see if there are combatants left
                                if(combatList.Size() <= 0)
                                {
                                    inBattle = false;
                                }

                                // Clear prompt string
                                stream.str("");
                            break;
                case QUIT:      inBattle = false;
                                ResetCombat();
                            break;
            }
        }// END while(inBattle)
    }

        // --------------- COMBAT METHODS --------------- //

    /**************************************************************************
     * FUNCTION: ResetCombat
     * ------------------------------------------------------------------------
     * Purpose : This function will reinitialize the combatList to empty.
     *           It automatically executes after user exits combat, or can
     *           manually be activated from the main menu in case of user input
     *           error.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
    void ResetCombat() { combatList.InitializeList(); }

    /**************************************************************************
     * FUNCTION: AddPartyFromFile
     * ------------------------------------------------------------------------
     * Purpose : This function will read in the user's default party list from
     *           "partyDB.txt" and place them on the combatList. If this file
     *           does not exist, the program will not run. User can manually
     *           create their own database of default partymembers by correctly
     *           editing this file.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
    void AddPartyFromFile()
    {
        ifstream fin;
        string name;
        Actor temp;

        fin.open("partydb.txt");

        // Check file
        if(fin)
        {
            getline(fin, name);
        }
        else
        {
            cout << "Database file not found. Ensure text file is in same directory as .exe"
                 << endl;
            system("pause");
        }

        // Loop to Add Partymembers
        while(fin)
        {
            temp.SetName(name);
            combatList.Add(temp);
            getline(fin, name);
        }

        fin.close();
    }

    /**************************************************************************
     * FUNCTION: UppercaseFirstLetter
     * ------------------------------------------------------------------------
     * Purpose : This function will uppercase the first letter of a string
     *           In this specific case, it is used to standardize user input
     *           to appear more proper when outputting in initiative lists.
     *
     *          Example:
     *          skeleton warrior 1
     *          Skeleton Warrior 1
     *
     * ------------------------------------------------------------------------
     * Receives:
     *      name : string
     * Returns:
     *      nothing
     *************************************************************************/
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


    /**************************************************************************
     * FUNCTION: ValidateIntInput
     * ------------------------------------------------------------------------
     * Purpose : This function validates user's number input according to
     *           minumum and maximum acceptable limits. It accepts a prompt as
     *           a parameter to print in case of incorrect input. Can also be
     *           used to reprint menu options if menu is passed in combined
     *           with input prompt read into an ostringstream, concatanated,
     *           and converted to string.
     *
     *           Returns bool, but is intended to be used as a separate input
     *           and output module. Probably needs work.
     * ------------------------------------------------------------------------
     *  Receives:
     *      minLimit       : int
     *      maxLimit       : int
     *      numInput       : int
     *      prompt         : string
     *
     *  Returns:
     *      invalid        : bool
     **************************************************************************/
    bool ValidateIntInput(const int &minLimit, const int &maxLimit,
                          int &numInput, const string &prompt)
    {
        bool invalid = true;

        while (invalid)
        {
            system("cls");

            // Output
            cout << prompt;

            // Input
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

        return invalid;
    }

    /**************************************************************************
     * FUNCTION: AddActors
     * ------------------------------------------------------------------------
     * Purpose : This function accepts user input for allies or enemies to be
     *           added to combat encounter. It will take the 'type' of actor
     *           then prompt the user for how many of this 'type' to add.
     *
     *           Once the user selects the amount, the function will uppercase
     *           the first letter in every word, and assign a numeric value to
     *           each member of the same 'type.' If the user requests only one
     *           of a certain 'type,' then the numeric suffix will not be added
     *
     *           Example #1:
     *           type: city guard
     *           amount: 2
     *
     *           City Guard 1
     *           City Guard 2
     *
     *           Example #2:
     *           type: lich
     *           amount: 1
     *
     *           Lich
     *
     * ------------------------------------------------------------------------
     *  Receives:
     *      nothing
     *  Returns:
     *      nothing
     **************************************************************************/
    void AddActors()
    {
        string name;
        string finalName;
        string suffix;
        int actorCount = 0;
        bool invalidInput;
        bool addingActors;
        ostringstream intInputStream;
        ostringstream scrollStream;
        string scrollPrompt;
        string scroll;
        string intInputprompt;
        Actor temp;
        string list;

        addingActors = true;

        // Adding 'type' of actor
        while(addingActors)
        {
            invalidInput = true;

            while(invalidInput)
            {
                system("cls");

                // Output
                list = CreateInitiativeList();
                scroll = CreateScroll(list);
                cout << scroll;

                // Input
                cout << "Enter name of creature (input x to exit): ";
                getline(cin, name);

                // Check for string size >0
                invalidInput = name.size() <= 0;

                if(invalidInput)
                {
                    cout << "You didn't enter a name." << endl;
                    system("pause");
                }
                else // If string size <= 0
                {
                    UppercaseFirstLetter(name);
                }
            }

            // Check addingActors
            addingActors = name != "X";

            // Adding number of actors in group
            if(addingActors)
            {
                invalidInput = true;

                while(invalidInput)
                {
                    // Output
                    intInputStream << scroll << "Enter number of " << name << "s" << " to add: ";
                    intInputprompt = intInputStream.str();

                    // Input
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

    /**************************************************************************
     * FUNCTION: SortList
     * ------------------------------------------------------------------------
     * Purpose : This function uses a selection sort to order the combatList
     *           into descending order of 'initiative.' The reason for using
     *           selection sort is that this list will likely never be longer
     *           than 10-20 actors and does not require a more complex sorting
     *           algorithm.
     *
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
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

    /**************************************************************************
     * FUNCTION: PrepareCombat
     * ------------------------------------------------------------------------
     * Purpose : This function executes before StartCombat to ensure that all
     *           necessary preparation is set before combat begins. It prompts
     *           user to enter initiative scores for each actor and then calls
     *           SortList to order the list in descending initiative order. It
     *           then loads the basic initiativeList into a string, which is
     *           managed by the InitiativeTracker class to be used by various
     *           functions throughout combat.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
    void PrepareCombat()
    {
        int initiative = 0;
        bool invalidInput = true;
        ostringstream stream;
        string prompt;
        string initiativeList;
        string scroll;

        initiativeList = CreateInitiativeList();

        // User inputs initiative for all actors
        for(int index = 0; index < combatList.Size(); index++)
        {
            invalidInput = true;

            while(invalidInput)
            {
                // Clear
                system("cls");

                // Output
                initiativeList = CreateInitiativeList();
                scroll = CreateScroll(initiativeList);
                stream << scroll <<  "Input initiative for "
                       << combatList[index].GetName() << ": ";
                prompt = stream.str();
                // Input
                invalidInput = ValidateIntInput(0, 30, initiative, prompt);

                // Clear stream for next prompt
                stream.str("");
            } // END while(invalidInput)

            combatList[index].SetInitiative(initiative);
        }

        SortList();
        initiativeList = CreateInitiativeList();
    }

    /**************************************************************************
     * FUNCTION: ValidateCharInput
     * ------------------------------------------------------------------------
     * Purpose : This function validates character input. It is intended to be
     *           compared against uppercase commands/menu options. The function
     *           takes in an array of acceptable characters and the size of the
     *           array. It then uppercases the user's input and compares it
     *           against the array of acceptable characters.
     *
     *           It also takes in the input prompt, and can be used to print
     *           menus if combined with ostringstream and the menu prompt as
     *           well as input prompt are concatanated into a single string.
     *
     *           Returns true if invalid and intended to be used in an external
     *           looping structure. However, it can be used as a singular
     *           input/output module.
     *
     *           Probably needs work.
     * ------------------------------------------------------------------------
     * Receives:
     *      validAr   : char array
     *      arSize    : const int
     *      charInput : char
     *      prompt    : const string
     * Returns:
     *      invalidInput : bool
     *************************************************************************/
    bool ValidateCharInput(char validAr[], const int &arSize, char &charInput,
                           const string prompt)
    {
        bool invalidInput = true;
        int index = 0;

        // Output
        cout << prompt;

        // Input
        cin.get(charInput);
        cin.ignore(999, '\n');
        charInput = toupper(charInput);

        // Compare to valid array
        while(index < arSize && invalidInput)
        {
            invalidInput = charInput != validAr[index];
            index++;
        }

        return invalidInput;
    }



    /**************************************************************************
     * FUNCTION: KillActor
     * ------------------------------------------------------------------------
     * Purpose : This function will remove an actor from combat. It takes in
     *           'deadIndex,' which should be passed in as 'desired index - 1'
     *           if the options offered to user begin with 1 rather than 0.
     *
     *           Calls DynamicList's Remove() function to safely remove items
     *           from list.
     * ------------------------------------------------------------------------
     * Receives:
     *      deadIndex : const int
     * Returns:
     *      nothing
     *************************************************************************/
    void KillActor(const int &deadIndex)
    {
        combatList.Remove(combatList[deadIndex]);
    }

    /**************************************************************************
     * FUNCTION: GetNextActor
     * ------------------------------------------------------------------------
     * Purpose : This function allows user to cycle the initiative list once
     *           any actor's turn is complete. It will place the first [0]
     *           actor in the last position and move every other position up
     *           once in the order.
     * ------------------------------------------------------------------------
     * Receives:
     *      nothing
     * Returns:
     *      nothing
     *************************************************************************/
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

    /**************************************************************************
     * Art Assets:
     * ------------------------------------------------------------------------
     * Purpose : These assets were acquired in their original form from
     *           https://www.asciiart.eu/ and altered to fit the needs of this
     *           program.
     * ------------------------------------------------------------------------
     * Artist Credits:
     *
     * Dragon Menu:
     * No Artist Listed
     * Source: https://www.asciiart.eu/mythology/dragons
     *
     * Scroll Border:
     * No Artist listed
     * Source: https://www.asciiart.eu/art-and-design/borders
     *************************************************************************/

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
        |    A. Load Party from File      |
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
