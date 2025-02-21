#include "deck.h"




//initialize deck of card
void deck::initializeDeck(){
    _deck.clear();  
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 1; rank < 14; rank++) 
            _deck.push_back(card(suit, rank));
    }
    randomShuffle();
}




//constructor
deck::deck(){
    initializeDeck();
}



//assignment operator for deck of card
deck& deck::operator =(const deck& other){
    if (this == &other)
        return *this;

    _deck = other._deck;
    return *this;
}




//perform perfect shuffle on deck
void deck::perfectShuffle(){
    vector<card> shuffledDeck;
    int mid = _deck.size() / 2;

    for (int i = 0; i < mid; i++) {
        shuffledDeck.push_back(_deck[i]);
        shuffledDeck.push_back(_deck[mid + i]);
    }

    _deck = shuffledDeck;
}


//randomly shuffle all cards
void deck::randomShuffle(){
    vector<card> shuffledDeck;
    srand(time(0));

    for (int i = 0; i < _deck.size(); i++)
        shuffledDeck.push_back(_deck[rand()%_deck.size()]);

    _deck = shuffledDeck;
}


//print out all cards in the deck
void deck::printDeck() const{
    cout << "Printing the deck: \n";
    int ctr = 0;
    for(int i = 0; i < 52; i++){
        cout << _deck[i];
        ctr++;
        if(ctr >= 10){
            cout << endl;
            ctr = 0;
        }
    }
    cout << endl;
}


//compare two deck of cards, return true if same and false if not same
bool deck::cmpDeck(deck& other) const{
    for(int i = 0; i < 52; i++){
        if( !(_deck[i] == other.getDeck()[i]) )
            return false;
    }
    return true;
}