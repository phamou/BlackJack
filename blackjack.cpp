#include "blackjack.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

//########### CARD IMPLEMENTATION #################
//constructor
Card::Card(rank r, type p) : rk(r), tp(p)
{
}

//getting the value of the card
int Card ::GetValue() const
{
    int value = rk;
    return value;
}
//getting the suit of the card
char Card::GetType() const
{
    //char TheType = tp;

    type suit = tp;
    char TheType;
    if(suit == CLUBS){
        TheType='C';
    }else if (suit == HEARTS){
        TheType= 'H';
    }else if (suit == DIAMONDS){
        TheType= 'D';
    }else if (suit == SPADES){
        TheType= 'S';
    }
    return TheType;
}

//combining both GetValue and GetType to display the card as wanted
void Card ::displayCard()
{

    cout << GetValue() << GetType() << endl;
}

//########### HAND IMPLEMENTATION #################

void Hand::Add(Card *pCard)
{
    MyCards.push_back(pCard);
}

//clearing the hand one by one
void Hand::Clear()
{
    vector<Card *>::iterator iter = MyCards.begin();
    for (iter = MyCards.begin(); iter != MyCards.end(); ++iter)
    {
        delete *iter;
        *iter = 0; //this is to get rid of the null pointers
    }

    MyCards.clear();
}

int Hand::GetTotal() const
{

    if (MyCards.empty())
        return 0;

    //Simply adding up all the values of the card using GetValue
    int total = 0;
    vector<Card *>::const_iterator iter;
    for (iter = MyCards.begin(); iter != MyCards.end(); ++iter)
        total += (*iter)->GetValue();

    //Check if hand contains an ace
    bool containsAce = false;
    for (iter = MyCards.begin(); iter != MyCards.end(); ++iter)
        if ((*iter)->GetValue() == Card::ACE)
            containsAce = true;

    //if it is possible to make ACE = 21, do so
    if (containsAce && total <= 11)
    {
        total += 10;
    }

    return total;
}

//helper method
vector<Card *> Hand ::getHand()
{
    return MyCards;
}

//helper method
void Hand ::handDisplay()
{
    vector<Card *>::iterator iter = MyCards.begin();

    for (iter = MyCards.begin(); iter != MyCards.end(); ++iter)
    {
        int val = (*iter)->GetValue();
        char theType = (*iter)->GetType();
        cout << val << theType << " ";
    }
}

//######### DECK IMPLEMENTATION ###########

void Deck::Populate()
{
    Clear();

    //create deck by going through each rank and suit
    for (int t = Card::CLUBS; t <= Card::SPADES; ++t)
    {
        for (int r = Card::ACE; r <= Card::KING; ++r)
        {
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::type>(t)));
        }
    }
}

void Deck::Shuffle()
{
    random_shuffle(MyCards.begin(), MyCards.end());
}

void Deck::Deal(Hand &aHand)
{ //Checking if the deck still has cards
    if (!MyCards.empty())
    {
        aHand.Add(MyCards.back());
        MyCards.pop_back();
    }
    else
    {
        cout << "Out of cards, Unable to deal.\n";
    }
}

//######### ABSTRACTPLAYER IMPLEMENTATION ##############
bool AbstractPlayer::IsBusted() const
{
    if (GetTotal() > 21)
        return true;

    return false;
}

//######## HUMANPLAYER IMPLEMENTATION #################

//Check if player wants to draw
bool HumanPlayer::IsDrawing() const
{
    if (wantDraw == 'y' || wantDraw == 'Y')
        return true;
    
    return false;
}

//helper method to determine if player wants to draw
char HumanPlayer ::setWantDraw(char response)
{
    wantDraw = response;
    return wantDraw;
}

//Check who wins
void HumanPlayer::announce(bool playerBusted, bool casinoBusted, int compTotal, int HumanTotal) const
{
    if (playerBusted)
        cout << "Player busts." << endl
             << "Casino wins." << endl
             << endl;
    else if(casinoBusted)
        cout<< "Casino busts" <<endl
            << "Player wins" << endl
            << endl;
    else if (HumanTotal > compTotal)
        cout << "Player wins." << endl
             << endl;
    else if (HumanTotal == compTotal)
        cout << "Push: No one wins." << endl
             << endl;
    else
        cout << "Casino wins." << endl
             << endl;
}

// ######### COMPUTERPLAYER IMPLEMENTATION ############

//If total below 16, keep drawing
bool ComputerPlayer::IsDrawing() const
{

    return (GetTotal() <= 16);
}

//helper method to show computer hand
void ComputerPlayer ::DisplaycomputerHand()
{
    vector<Card *>::const_iterator iter;
    for (iter = MyCards.begin(); iter != MyCards.end(); ++iter)
    {
        cout << "Your hand" << *iter;
    }
}

//######BLACKJACKGAME IMPLEMENTATION ##############
void BlackJackGame::play()
{
    //clear the hands of all players first because when we restart, we want the hands to be cleared
    phand.Clear();
    chand.Clear();
    srand(time(0));
    m_deck.Populate();
    m_deck.Shuffle();

    int csum = 0;
    int psum = 0;

    //dealing the initial cards
    m_deck.Deal(chand);
    cout << "Casino:";
    chand.handDisplay();
    csum = chand.GetTotal();
    cout << " [" << csum << "]" << endl;

    m_deck.Deal(phand);
    cout << "Player:";
    phand.handDisplay();
    psum = phand.GetTotal();
    cout << " [" << psum << "]" << endl;

    bool playerBusted = false;
    bool casinoBusted = false;

    //Player's turn
    HumanPlayer hm;
    cout << "Do you want to draw? (Y/N): ";
    char response;
    cin >> response;
    char ans = hm.setWantDraw(response);

    while (hm.IsDrawing())
    {
        //bool isBustedCheck1 = hm.IsBusted();

        if (!hm.IsBusted() && psum < 21 && (ans == 'y' || ans == 'Y'))
        {
            m_deck.Deal(phand);
            cout << "Player:";
            phand.handDisplay();
            psum = phand.GetTotal();
            cout << "[" << psum << "]" << endl;
            if(psum>21) {playerBusted = true; break;}
            if(psum==21) break;
            cout << "Do you want to draw? (Y/N): ";
            cin >> response;
            ans = hm.setWantDraw(response);
            //if player gets above 21, break the loop
        }
        else if (psum == 21)
        {
            break;
        }
        else if(psum>21)
        {
            playerBusted = true;
            break;
        }else{break;}
    }

    //Casino's turn
    while (m_casino.IsDrawing() && !playerBusted)
    {
        if (!m_casino.IsBusted())
        {
            m_deck.Deal(chand);
            cout << "Casino:";
            chand.handDisplay();
            csum = chand.GetTotal();
            cout << "[" << csum << "]" << endl;
            if(csum>21) {casinoBusted = true; break;}
            if(csum==21) break;
            if (csum > 16)break; //rule of having total above 16
        }
       
    }
    //announce winner if we get to that point
    hm.announce(playerBusted, casinoBusted, csum, psum);
}