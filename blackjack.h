#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>

using namespace std;


//### CARD ####
class Card {
    public:
        enum rank{ACE=1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT, NINE, TEN, JACK=10, QUEEN=10, KING=10};
        enum type{CLUBS, DIAMONDS, HEARTS, SPADES};

        
        Card(rank r = ACE, type t = SPADES);

        int GetValue() const;

        char GetType() const;

        void displayCard();
    
    private:
        rank rk;
        type tp;
};

//### HAND ####
class Hand
{
    public:
        

      
        void Add(Card* pCard);
        void Clear();
        int GetTotal() const;
        void handDisplay();
        vector<Card*> getHand();


    protected: 
        vector<Card*> MyCards;
    
};


//### DECK ####
class Deck : public Hand
{
    public:
        
       
        void Populate();
        void Shuffle();
        void Deal(Hand& aHand);

};


//### ABSTRACTPLAYER ####
class AbstractPlayer : public Hand
{
    public:
       
        
        virtual bool IsDrawing() const = 0;  
        bool IsBusted() const;

};



//### HUMANPLAYER ####
class HumanPlayer :  public AbstractPlayer
{
    public:
        
       char setWantDraw(char answer);

        virtual bool IsDrawing() const;
        void announce(bool playerBusted, bool casinoBusted, int compTotal, int HumanTotal)  const;

    private: 
        char wantDraw;
};



//### COMPUTERPLAYER ####
class ComputerPlayer : public AbstractPlayer
{
    public:
     
       
        virtual bool IsDrawing() const;

        void DisplaycomputerHand();
};


//### BLACKJACKGAME ####
class BlackJackGame{

    public: 
        Hand chand;
        Hand phand;
        
       
        void  play();

    private: 
        Deck m_deck;
        ComputerPlayer m_casino;
        vector<HumanPlayer> m_Players;

};
 #endif