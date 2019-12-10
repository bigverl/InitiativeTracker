#include "InitiativeTracker.h"

int main()
{
    string name;
    InitiativeTracker it;

    it.Begin();
    // TESTING FOR ENTIRE PROGRAM

    /*

    // Test adding party from file
    it.AddPartyFromFile();

    // Add list to string
    string list = it.CreateInitiativeList();

    // Print string to test
    cout << list;

    //NOTE: READ IN FILE LOOP ITERATES ONE TOO MANY TIMES. SOMETHING ABOUT
    //      'END OF FILE' NOT SET UNTIL FIRST READ?


    // Add actors from sample
    for(int index = 0; index < 4; index++)
    {
        it.AddActors();
    }

    // Print to test
    list = it.CreateInitiativeList();

    cout << list;

    it.PrepareCombat();

        // THIS IS THE ENTIRE STARTCOMBAT MODULE. INCOMPLETE, THOUGH.

        // IT NEEDS TO BE ORGANIZED THO

    // Call StartCombat

    string numberedList;
    char battleOption;
    int deadIndex;
    bool inBattle = true;
    enum BattleOptions{CONTINUE = 'c', KILL = 'k', QUIT = 'q'};

    while(inBattle)
    {
        // Print menu and prompt
        cout << "Continue (c), Kill (k), Quit (q): " << endl;
        cin.get(battleOption);
        cin.ignore(999,'\n');

        switch (battleOption)
        {
            case CONTINUE:  it.GetNextActor();
                            list = it.CreateInitiativeList();
                            system("cls");
                            cout << list;
                        break;
            case KILL:      numberedList = it.CreateNumberedList();
                            system("cls");
                            cout << numberedList;
            // validate num input for range of people
            // REMEMBER THIS WILL BE IN A METHOD SO YOU CAN USE
            // COMBATLIST.SIZE() AS THE MAX
                            cout << "Kill who? (1-" << ") ";
                            cin >> deadIndex;
                            cin.ignore(999,'\n');
                            it.KillActor(deadIndex - 1);
                            system("cls");
                            list = it.CreateInitiativeList();
                            cout << list;
                        break;
            case QUIT:      inBattle = false;
                        break;
        }
    }// END while(inBattle)

    // END StartCombat

*/



    return 0;
}
