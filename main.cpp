#include <iostream>
#include <iomanip>
#include "C:\Users\agu4\Documents\CS8 Projects\09_p2_delete_repeats-andygu-7685\includes\deck.h"

using namespace std;

int main(int argv, char** argc) {
    
    deck d1;
    deck d2 = d1;

    //initialize deck of card
    //------------------------------------------------------------------
    cout << "\n-----------------------------------------------------------------------\n";
    cout << "randomly initalized deck of card: \n\n";
    d1.printDeck();
    //------------------------------------------------------------------

    //perfect shuffle
    //------------------------------------------------------------------
    cout << "\n-----------------------------------------------------------------------\n";
    cout << "perform perfect shuffle on d1: \n\n";
    d1.perfectShuffle();
    d1.printDeck();
    //------------------------------------------------------------------
    
    //compare deck of card
    //------------------------------------------------------------------
    cout << "\n-----------------------------------------------------------------------\n";
    cout << "comapre shuffled deck(d1) with initial deck(d2): \n\n";
    (d2.cmpDeck(d1)) ? cout << "true, d1 == d2\n" : cout << "false, d1 != d2\n";
    //------------------------------------------------------------------

    //shuffle until shuffled deck is same as initial deck
    //------------------------------------------------------------------
    cout << "\n-----------------------------------------------------------------------\n";
    cout << "shuffle until shuffled deck(d1) is same as initial deck(d2): \n\n";
    int shuffleCtr = 1;
    while(true){
        d1.perfectShuffle();
        d1.printDeck();
        (d2.cmpDeck(d1)) ? cout << "\ntrue, d1 == d2\n\n" : cout << "\nfalse, d1 != d2\n\n";
        shuffleCtr++;
        if(d2.cmpDeck(d1))
            break;
    }
    cout << "\ntotal shuffle to return to inital deck (including first shuffle): " << shuffleCtr << endl;
    //------------------------------------------------------------------


    return 0;
}
