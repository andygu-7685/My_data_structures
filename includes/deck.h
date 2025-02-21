#ifndef DECK_H
#define DECK_H

using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <cassert>




struct card{
    string suit;        // clubs, diamonds, hearts, spades
    int rank;           // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13

    //constructor
    card(int s, int r){
        switch(s){
            case 0:
                suit = "club";
            break;
            case 1:
                suit = "diamond";
            break;
            case 2:
                suit = "heart";
            break;
            case 3:
                suit = "spade";
            break;
            default:
                assert(false && "Invalid Initializer");
                break;
        }
        rank = r;
    }

    //compare two cards
    bool operator==(const card& other) const{
        return ((suit == other.suit) && (rank == other.rank));
    }

    //print card value
    friend ostream& operator<<(ostream& out, const card& c) {
        if(c.rank < 11){
            out << c.suit << ": " << c.rank << ", ";
        }
        else{
            switch(c.rank){
                case 11:
                    out << c.suit << ": J, ";
                break;
                case 12:
                    out << c.suit << ": Q, ";
                break;
                case 13:
                    out << c.suit << ": K, ";
                break;
                default:

                break;
            }
        }
        return out;
    }

};







class deck{
    public:

    deck();
    deck& operator =(const deck& other);
    void initializeDeck();
    void perfectShuffle();
    void randomShuffle();
    void printDeck() const;
    bool cmpDeck(deck& other) const;
    vector<card> getDeck(){ return _deck; }

    private:
    vector<card> _deck;

};



#endif