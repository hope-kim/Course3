/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Hope Kim
 * USC email: hopekim@usc.edu
 * Comments (you want us to know):
 * Plays the game twenty-one that allows a player to get
 *      as close to the number 21 as possible without
 *      going over but still being higher than the dealer
 * Also, I apologize because this is a lot of repetitive code,
 		but I could not really think of another way to do it.
 		I also have lines longer than 80 characters due to
 		indentation. I apologize in advance.
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] =
{"2","3","4","5","6","7",
    "8","9","10","J","Q","K","A"};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    /******** You complete ****************/

    // initializes each card to its index
    for (int i = 0; i < NUM_CARDS; i++)
    {
        cards[i] = i;
    }

    // shuffles the deck using Fisher-Yates / Durstenfeld shuffle algorithm
    for (int i = NUM_CARDS-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        int tempCardJ = cards[j];
        int tempCardI = cards[i];
        cards[j] = tempCardI;
        cards[i] = tempCardJ;
    }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
    /******** You complete ****************/

    // if the id is a heart
    if (id >= 0 && id <= 12)
    {
        char heartSuit = suit[0];

        // if statements that determine the type
        if (id >= 0 && id <= 8)
        {
            const char* heartType = type[id];
            cout << heartType << "-" << heartSuit;
        }
        else if (id == 9)
        {
            const char* heartType = type[id];
            cout << heartType << "-" << heartSuit;
        }
        else if (id == 10)
        {
            const char* heartType = type[id];
            cout << heartType << "-" << heartSuit;
        }
        else if (id == 11)
        {
            const char* heartType = type[id];
            cout << heartType << "-" << heartSuit;
        }
        else if (id == 12)
        {
            const char* heartType = type[id];
            cout << heartType << "-" << heartSuit;
        }
        
    }

    // if the id is a spade
    else if (id >= 13 && id <= 25)
    {
        char spadeSuit = suit[1];

        // if statements that determine the type
        if (id >= 13 && id <= 21)
        {
            const char* spadeType = type[id-13];
            cout << spadeType << "-" << spadeSuit;
        }
        else if (id == 22)
        {
            const char* spadeType = type[id-13];
            cout << spadeType << "-" << spadeSuit;
        }
        else if (id == 23)
        {
            const char* spadeType = type[id-13];
            cout << spadeType << "-" << spadeSuit;
        }
        else if (id == 24)
        {
            const char* spadeType = type[id-13];
            cout << spadeType << "-" << spadeSuit;
        }
        else if (id == 25)
        {
            const char* spadeType = type[id-13];
            cout << spadeType << "-" << spadeSuit;
        }
        
    }

    // if the id is a diamond
    else if (id >= 26 && id <= 38)
    {
        char diamondSuit = suit[2];

        // if statements that determine the type
        if (id >= 26 && id <= 34)
        {
            const char* diamondType = type[id-26];
            cout << diamondType << "-" << diamondSuit;
        }
        else if (id == 35)
        {
            const char* diamondType = type[id-26];
            cout << diamondType << "-" << diamondSuit;
        }
        else if (id == 36)
        {
            const char* diamondType = type[id-26];
            cout << diamondType << "-" << diamondSuit;
        }
        else if (id == 37)
        {
            const char* diamondType = type[id-26];
            cout << diamondType << "-" << diamondSuit;
        }
        else if (id == 38)
        {
            const char* diamondType = type[id-26];
            cout << diamondType << "-" << diamondSuit;
        }
    }

    // if the id is a club
    else if (id >= 39 && id <= 51)
    {
        char clubSuit = suit[3];

        // if statements that determine the type
        if (id >= 39 && id <= 47)
        {
            const char* clubType = type[id-39];
            cout << clubType << "-" << clubSuit;
        }
        else if (id == 48)
        {
            const char* clubType = type[id-39];
            cout << clubType << "-" << clubSuit;
        }
        else if (id == 49)
        {
            const char* clubType = type[id-39];
            cout << clubType << "-" << clubSuit;
        }
        else if (id == 50)
        {
            const char* clubType = type[id-39];
            cout << clubType << "-" << clubSuit;
        }
        else if (id == 51)
        {
            const char* clubType = type[id-39];
            cout << clubType << "-" << clubSuit;
        }
    }
    
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
    /******** You complete ****************/
    int cardValue = 0;

    // if statements that determine the card's value
    if ((id == 0 || id == 13) || (id == 26 || id == 39))
    {
        cardValue = 2;
    }
    else if ((id == 1 || id == 14) || (id == 27 || id == 40))
    {
        cardValue = 3;
    }
    else if ((id == 2 || id == 15) || (id == 28 || id == 41))
    {
        cardValue = 4;
    }
    else if ((id == 3 || id == 16) || (id == 29 || id == 42))
    {
        cardValue = 5;
    }
    else if ((id == 4 || id == 17) || (id == 30 || id == 43))
    {
        cardValue = 6;
    }
    else if ((id == 5 || id == 18) || (id == 31 || id == 44))
    {
        cardValue = 7;
    }
    else if ((id == 6 || id == 19) || (id == 32 || id == 45))
    {
        cardValue = 8;
    }
    else if ((id == 7 || id == 20) || (id == 33 || id == 46))
    {
        cardValue = 9;
    }
    else if ((id == 8 || id == 21) || (id == 34 || id == 47))
    {
        cardValue = 10;
    }
    else if ((id == 9 || id == 22) || (id == 35 || id == 48))
    {
        cardValue = 10;
    }
    else if ((id == 10 || id == 23) || (id == 36 || id == 49))
    {
        cardValue = 10;
    }
    else if ((id == 11 || id == 24) || (id == 37 || id == 50))
    {
        cardValue = 10;
    }
    else if ((id == 12 || id == 25) || (id == 38 || id == 51))
    {
        cardValue = 11;
    }
    return cardValue;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    /******** You complete ****************/

    // for loop to print out each hand
    for (int i = 0; i < numCards; i++)
    {
        printCard(hand[i]);
        cout << " ";
    }
    cout << endl;
    
}

/**
 * Should return the total score of the provided hand.
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    /******** You complete ****************/

    // variables to determine sum, number of aces, and if aces are present
    int sumScore = 0;
    int numAces = 0;
    bool acePresent = false;

    // for loop to sum the hand
    for (int i = 0; i < numCards; i++)
    {
        int cardScore = cardValue(hand[i]);
        
        // determines if there are aces
        if (cardScore == 11)
        {
            acePresent = true;
            numAces++;
        }
        sumScore += cardScore;
    }

    // if there are aces and need to be reduced to 1
    if (sumScore > 21 && acePresent)
    {
        int numDecrement = 10*numAces;
        sumScore -= numDecrement;
    }
    return sumScore;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, const char* argv[])
{
    //---------------------------------------
    // Do not change this code -- Begin
    //---------------------------------------
    if(argc < 2){
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    
    srand(seed);
    
    int cards[52];
    int dhand[9];
    int phand[9];
    //---------------------------------------
    // Do not change this code -- End
    //---------------------------------------
    
    /******** You complete ****************/
    
    
    // variable to determine if player wants to play again
    char playAgain = 'y';

    // while loop if player wants to keep playing
    while (playAgain == 'y')
    {
    	// shuffles cards
        shuffle(cards);

        // initializes the first round hands
        phand[0] = cards[0];
        dhand[0] = cards[1];
        phand[1] = cards[2];
        dhand[1] = cards[3];
        
        // variables to help determine the next hand
        int dealerNumCards = 2;
        int playerNumCards = 2;
        int nextCardIndex = 4;

        // first round output
        cout << "Dealer: ? ";
        printCard(dhand[1]);
        cout << endl;
        cout << "Player: ";
        printHand(phand, playerNumCards);
        
        // determines player's and dealer's scores
        int playerScore = getBestScore(phand, playerNumCards);
        int dealerScore = getBestScore(dhand, dealerNumCards);
        
        // first round: if player's score is more than 21, player loses
        if (playerScore > 21)
        {
            cout << "Player busts" << endl;
            cout << "Lose " << playerScore << " " << dealerScore << endl;
        }
        // first round: if player's score is 21, dealer automatically goes
        if (playerScore == 21)
        {
            // keep making dealer go until his score is at least 17
            if (dealerScore <= 16)
            {
                while (dealerScore <= 16)
                {
                	// makes dealer's new hand
                    dhand[dealerNumCards] = cards[nextCardIndex];
                    nextCardIndex++;
                    dealerNumCards++;

                    // makes dealer's new score
                    dealerScore = getBestScore(dhand, dealerNumCards);
                }
            }
            
            // if dealer's score is at least 17 but less than 21, player wins
            if (dealerScore >= 17 && dealerScore < 21)
            {
                cout << "Dealer: ";
                printHand(dhand, dealerNumCards);
                cout << "Win " << playerScore << " " << dealerScore << endl;
            }
            
            // if dealer's score is over 21, player wins
            if (dealerScore > 21)
            {
                cout << "Dealer: ";
                printHand(dhand, dealerNumCards);
                cout << "Dealer busts" << endl;
                cout << "Win " << playerScore << " " << dealerScore << endl;
            }
            
            // if dealer's score is 21, they tie
            if (dealerScore == 21)
            {
            	cout << "Dealer: ";
                printHand(dhand, dealerNumCards);
                cout << "Tie " << playerScore << " " << dealerScore << endl;
            }
            
        }
        
        // first round: if player's score is less than 21
        if (playerScore < 21)
        {
            
            // continue asking if player wants to hit or stand until game ends
            while (playerScore < 21)
            {
            	// variables and output for hit or stand
                char hitOrStay = '\0';
                cout << "Type \"h\" to hit and \"s\" to stay:" << endl;
                cout << "> ";
                cin >> hitOrStay;

                // if player wants to hit
                if (hitOrStay == 'h')
                {
                    
                    // keep asking if player wants to hit or stay until they stand
                    while (hitOrStay == 'h')
                    {
                    	// makes player's new hand
                        phand[playerNumCards] = cards[nextCardIndex];
                        nextCardIndex++;
                        playerNumCards++;
                        cout << "Player: ";
                        printHand(phand, playerNumCards);

                        // makes player's new score
                        playerScore = getBestScore(phand, playerNumCards);
                        
                        // if player's new score is 21
                        if (playerScore == 21)
                        {
                            // keep making dealer go until his score is at least 17
                            if (dealerScore <= 16)
                            {
                                while (dealerScore <= 16)
                                {
                                	// makes dealer's new hand
                                    dhand[dealerNumCards] = cards[nextCardIndex];
                                    nextCardIndex++;
                                    dealerNumCards++;

                                    // makes dealer's new score
                                    dealerScore = getBestScore(dhand, dealerNumCards);
                                }
                            }
                            
                            // once dealer's score is at least 17 but less than 21, player wins
                            if (dealerScore >= 17 && dealerScore < 21)
                            {
                                cout << "Dealer: ";
                                printHand(dhand, dealerNumCards);
                                cout << "Win " << playerScore << " " << dealerScore << endl;
                                break;
                            }

                            // if dealer's score is over 21, player wins
                            if (dealerScore > 21)
                            {
                            	cout << "Dealer: ";
                            	printHand(dhand, dealerNumCards);
                                cout << "Dealer busts " << endl;
                                cout << "Win " << playerScore << " " << dealerScore << endl;
                                break;
                            }
                            
                            // if dealer's score is 21, they tie
                            if (dealerScore == 21)
                            {
                            	cout << "Dealer: ";
                				printHand(dhand, dealerNumCards);
                                cout << "Tie " << playerScore << " " << dealerScore << endl;
                                break;
                            }

                        // if player's new score is over 21, player loses
                        }
                        if (playerScore > 21)
                        {
                            cout << "Player busts" << endl;
                            cout << "Lose " << playerScore << " " << dealerScore << endl;
                      
                            break;
                        }
                        
                        // if player's new score is still less than 21, ask them to hit or stand
                        if (playerScore < 21)
                        {
	                        cout << "Type \"h\" to hit and \"s\" to stay:" << endl;
	                        cout << "> ";
	                        cin >> hitOrStay;
                    	}
                        
                    }
                }
                
                // if they want to stand
                if (hitOrStay == 's')
                {
                    // if player's score is 21
                    if (playerScore == 21)
                    {
                        // keep making the dealer go until his score is at least 17
                        if (dealerScore <= 16)
                        {
                            while (dealerScore <= 16)
                            {
                            	// makes dealer's new hand
                                dhand[dealerNumCards] = cards[nextCardIndex];
                                nextCardIndex++;
                                dealerNumCards++;

                                // makes dealer's new score
                                dealerScore = getBestScore(dhand, dealerNumCards);
                            }
                        }
                        
                        // once dealer's score is at least 17 but less than 21, player wins
                        if (dealerScore >= 17 && dealerScore < 21)
                        {
                            cout << "Dealer: ";
                            printHand(dhand, dealerNumCards);
                            cout << "Win " << playerScore << " " << dealerScore << endl;
                      
                            break;
                        }

                        // if dealer's score is over 21, player wins
                        if (dealerScore > 21)
                        {
                        	cout << "Dealer: ";
                            printHand(dhand, dealerNumCards);
                            cout << "Dealer busts " << endl;
                            cout << "Win " << playerScore << " " << dealerScore << endl;
                            break;
                        }
                        
                        // if dealer's score is 21, they tie
                        if (dealerScore == 21)
                        {
                        	cout << "Dealer: ";
               				printHand(dhand, dealerNumCards);
                            cout << "Tie " << playerScore << " " << dealerScore << endl;
                            break;
                        }
                        
                    }
                    
                    // if player's score is still under 21
                    if (playerScore < 21)
                    {
                        
                        if (dealerScore <= 16)
                        {
                            // keep making the dealer go until his score is at least 17
                            while (dealerScore <= 16)
                            {
                            	// makes dealer's new hand
                                dhand[dealerNumCards] = cards[nextCardIndex];
                                nextCardIndex++;
                                dealerNumCards++;

                                // makes dealer's new score
                                dealerScore = getBestScore(dhand, dealerNumCards);
                            }
                        }
                        
                        // if dealer's score is at least 17 but less than 21
                        if (dealerScore >= 17 && dealerScore < 21)
                        {
                            // if there is a tie
                            if (playerScore == dealerScore)
                            {
                                cout << "Dealer: ";
                                printHand(dhand, dealerNumCards);
                                cout << "Tie " << playerScore << " " << dealerScore << endl;
                                break;
                            }

                            // if player loses
                            else if (playerScore < dealerScore)
                            {
                                cout << "Dealer: ";
                                printHand(dhand, dealerNumCards);
                                cout << "Lose " << playerScore << " " << dealerScore << endl;
                                break;
                            }
                            else if (playerScore > dealerScore)
                            {
                                cout << "Dealer: ";
                                printHand(dhand, dealerNumCards);
                                cout << "Win " << playerScore << " " << dealerScore << endl;
                                break;
                            }
                            
                        }
                        
                        // if dealer's score is over 21, player wins
                        if (dealerScore > 21)
                        {
                            cout << "Dealer: ";
                            printHand(dhand, dealerNumCards);
                            cout << "Dealer busts" << endl;
                            cout << "Win " << playerScore << " " << dealerScore << endl;
                            break;
                        }
                        
                        
                    }
                    
                    // if player's score is 21, dealer automatically goes
                    if (playerScore == 21)
                    {
                        // keep making dealer go until his score is at least 17
                        if (dealerScore <= 16)
                        {
                            while (dealerScore <= 16)
                            {
                            	// makes dealer's new hand
                                dhand[dealerNumCards] = cards[nextCardIndex];
                                nextCardIndex++;
                                dealerNumCards++;
                                dealerScore = getBestScore(dhand, dealerNumCards);
                            }
                        }
                        
                        // once dealer's score is at least 17 but less than 21, player wins
                        if (dealerScore >= 17 && dealerScore < 21)
                        {
                            cout << "Dealer: ";
                            printHand(dhand, dealerNumCards);
                            cout << "Win " << playerScore << " " << dealerScore << endl;
                      
                            break;
                        }

                        // if dealer's score is over 21, player wins
                        if (dealerScore > 21)
                        {
                        	cout << "Dealer: ";
                			printHand(dhand, dealerNumCards);
                			cout << "Dealer busts" << endl;
                            cout << "Win " << playerScore << " " << dealerScore << endl;
                            break;
                        }
                        
                        // if dealer's score is 21, they tie
                        if (dealerScore == 21)
                        {
                        	cout << "Dealer: ";
                			printHand(dhand, dealerNumCards);
                            cout << "Tie " << playerScore << " " << dealerScore << endl;
                            break;
                        }
                    }
                    
                    // if player's score is over 21, player loses
                    if (playerScore > 21)
                    {
                        cout << "Player busts" << endl;
                        cout << "Lose " << playerScore << " " << dealerScore << endl;
                        break;
                    }
                } 
            }
        }

        // asks the player if they want to play again
        cout << endl;
        cout << "Play again? (y/n)" << endl;
        cout << "> ";
        cin >> playAgain;
    }
    return 0;
}