#include "blackjack.h"
#include "blackjack.cpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

int main(){

    cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;

    BlackJackGame game;
    game.play();
    
    
     
    // The main loop of the game
    bool playAgain = true;
    char answer = 'y';
    while (playAgain)
    {
        
        // Check whether the player would like to play another round
        cout << "Would you like another round? (y/n): ";
        cin >> answer;
        cout << endl << endl;
        playAgain = (answer == 'y' ? true : false);
    }
    cout <<"Gave over!"; 
    return 0;
}























