/*
	FileName		: CardDeck.h
	Author			: Carl Caldwell
	Date			: 04/10/2020
	Description		: This class keeps track of all the cards in the deck. The class has functions to issue initial cards, hits, and calculate scores.
*/
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

class CardDeck{
	private:
		// The cards and their values are stored in arrays. The index of the array will determin the card name and the value of it
		string cardName[52] = {"Ace Clubs", "2 Clubs", "3 Clubs", "4 Clubs", "5 Clubs", "6 Clubs", "7 Clubs", "8 Clubs", "9 Clubs", "10 Clubs", "Jack Clubs","Queen Clubs","King Clubs","Ace Spades", "2 Spades", "3 Spades", "4 Spades", "5 Spades", "6 Spades", "7 Spades", "8 Spades", "9 Spades", "10 Spades", "Jack Spades","Queen Spades","King Spades","Ace Hearts", "2 Hearts", "3 Hearts", "4 Hearts", "5 Hearts", "6 Hearts", "7 Hearts", "8 Hearts", "9 Hearts", "10 Hearts", "Jack Hearts","Queen Hearts","King Hearts","Ace Diamonds", "2 Diamonds", "3 Diamonds", "4 Diamonds", "5 Diamonds", "6 Diamonds", "7 Diamonds", "8 Diamonds", "9 Diamonds", "10 Diamonds", "Jack Diamonds","Queen Diamonds","King Diamonds"};
		int cardValue[52] = {1,2,3,4,5,6,7,8,9,10,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,10};
		
		// the hands for each player are stored as a vector. The int stored is the index in the above arrays
		vector<int> player;
		vector<int> computer;
		
		// this function will return an int. The int that is returned is the index of a card value. This function ensures that the card is not already in play
		int chooseAvailableCard(){
			
			// pick a random number 0-51. This int will be the index in the CardDeck arrays
			srand(time(NULL));
			int cardNum;
			bool cardAvailable;
			do{
				cardNum = rand()%52;
				
				// the card will start as being available. We need to make sure it isn't in either hand. if so, set cardAvailable=false and the loop will continue
				cardAvailable = true;
				for(int playerCard = 0 ; playerCard<player.size() ; playerCard++){
					if(player.at(playerCard) == cardNum){
						cardAvailable = false;
						break;
					}
				}
				for(int computerCard = 0 ; computerCard<computer.size() ; computerCard++){
					if(computer.at(computerCard) == cardNum){
						cardAvailable = false;
						break;
					}
				}
			}while(!cardAvailable);
			
			// if we got here, the card is available. return the card index to the calling f(x)
			return cardNum;	
		};
		
		// This function is private and called only by member functions. It accpets a vector of card indexes and returns an int of the score of the hand.
		// This function also checks if there is an Ace in the hand. If so, the card is counted as 11, unless the player busts. The Ace is then counted as 1
		int addScore(vector<int> hand){
			
			int aceCount = 0, score = 0;
			
			// loop through the hand and get the number of Aces
			for(int cardNum = 0 ; cardNum < hand.size() ; cardNum++){
				if(cardValue[hand.at(cardNum)] == 1){
					aceCount++;
				}
			}
			// add up points, ace == 11
			for(int cardNum = 0 ; cardNum < hand.size() ; cardNum++){
				if(cardValue[hand.at(cardNum)] == 1){
					score = score + 11;
				}else{
					score = score + cardValue[hand.at(cardNum)];
				};
			};
			
			// if ace and > 21, loop and subtract 10pts, because the Ace needs to be counted as 1 and not 11
			for(int x=0 ; x<aceCount ; x++){
				if(score <= 21){
					break;
				}else{
					score = score - 10;
				}
			}
			return score;
		};
		
	
	public:
		
		// Default constructor. No overload allowed
		CardDeck(){};
		
		// This function sets the initial cards for the player's and computer's hands. It will call the chooseAvailableCard() f(x) to ensure the card is not already in play.
		void issueCards(){
			// issue player hand
			player.push_back(chooseAvailableCard());
			player.push_back(chooseAvailableCard());
			
			// issue computer hand
			computer.push_back(chooseAvailableCard());
			computer.push_back(chooseAvailableCard());
			
			// the deed is done. Tell the calling f(x) to continue with the game
			return;
		};
		
		// This function calls the chooseAvilableCard() f(x) and adds another card to the player's hand. It also prints which card was selected.
		void issuePlayerHit(){
			int chosenCard = chooseAvailableCard();
			player.push_back(chosenCard);
			cout << "You drew a "<< cardName[chosenCard] << endl;
			return;
		};
		
		// This function calls the chooseAvilableCard() f(x) and adds another card to the computer's hand. It also prints which card was selected.
		void issueComputerHit(){
			int chosenCard = chooseAvailableCard();
			computer.push_back(chosenCard);
			cout << "The computer hit and drew a " << cardName[chosenCard] << endl;
			return;
		}
		
		// Adds up the score of the player via the addScore() f(x)
		int getPlayerScore(){
			return addScore(player);
		};
		
		// Adds up the score of the computer via the addScore() f(x)
		int getComputerScore(){
			return addScore(computer);
		};
		
		// This function accepts an int. This int the the index of the card in the player's hand. It looks up the CardDeck index and returns the name of the card.
		string getPlayerCard(int cardNum){
			return cardName[player.at(cardNum)];
		}
		
		// This function accepts an int. This int the the index of the card in the computer's hand. It looks up the CardDeck index and returns the name of the card.
		string getComputerCard(int cardNum){
			return cardName[computer.at(cardNum)];
		}
		
		
};

















