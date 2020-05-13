/*
	Author		: Carl Caldwell
	Date		: 03/02/2020
	FileName	: CaldwellC_PersonalProject
	Description	: This program plays the game of black jack. The player starts with $500 and can bet on each hand. $0 and your out. 
*/

#include <iostream>
#include "CardDeck.h"

using namespace std;

int main(int argc, char** argv) {

	int playerMoney = 500;
	bool playAgain = false;
	
	// Print the welcom screen
	cout << "-----------------------------------\n";
	cout << "------ Welcome to BlackJack! ------\n";
	cout << "-----------------------------------" << endl << "  by Carl Caldwell" << endl << endl;
	cout << "DIRECTIONS: \n";
	cout << "Try to get to 21 without going over. The computer hits if 16 or below.\n" << "If you AND the computer bust, no winners and money returned.\n\n";
	cout << "You have $500" << endl;
	
	// loop until the user runs out of money or quits. Loop exits by sentinal value stored in variable named "playAgain"
	do{
		
		// get the players bet for this hand. Loop intil valid amount. Also check to make sure the player has enough money and it's not a negative number, because that cheating.
		int playerBet;
		do{
			cout << "How much would you like to bet? [$0-$" << playerMoney<<"] $";
			cin >> playerBet;
			getchar();
			cout << endl;
		}while(playerBet > playerMoney || playerBet < 1);
		
		
		// the CardDeck class stores all cards in a normal card deck. It also keeps track of which cards are in play.
		CardDeck cards;
		// issue cards to both players
		cards.issueCards();
		
		// tell the player the computer cards and their cards.
		cout << "Computer Cards: [SecretCard] & " << cards.getComputerCard(0) << endl << endl;
		cout << "Your Cards: " << cards.getPlayerCard(0) << " & " << cards.getPlayerCard(1) << " with a score of " << cards.getPlayerScore() << endl;
		
		// prompt user if hit or stand
		cout << "\n\n--------------- Your Turn ---------------\n\n";
		int hitOrStand;
		cout << "Would you like to hit or stand? [0=hit, 1=stand] ";
		cin >> hitOrStand;
		getchar();
		
		// this loop will continue while the player wants to take a new card.
		while(hitOrStand == 0){
			// call the CardDeck class to issue another card to the player
			cards.issuePlayerHit();
			
			// show the user their cards and score
			cout << "Score: " << cards.getPlayerScore() << endl;
			
			// check if the new card busted their hand. If so, break from the loop because they cannot hit again.
			if(cards.getPlayerScore() > 21){
				cout << "BUSTED!! Your score is " << cards.getPlayerScore() << endl;
				cout << "Press [Enter] to continue ...";
				cin.get();
				break;
			}
			
			// re-prompt the user if they want another card. The loop will continue if they choose "0" again.
			cout << "Would you like to hit or stand? [0=hit, 1=stand] ";
			cin >> hitOrStand;
		}
		
		// the user has played their hand. The have chosen to stand or they have busted. Time for the computer's turn.
		cout << endl << "------------- Computer's Turn -------------" << endl << endl;
		
		// get/show computer cards to the player
		cout << "Computer Cards: " << cards.getComputerCard(0) << " & " << cards.getComputerCard(1) << " with a score of " << cards.getComputerScore() <<endl;
		
		// The computer stands if score is greater than 16 and not busted
		if(cards.getComputerScore() > 16 && cards.getComputerScore() < 22){
			cout << "Computer Stands!" << endl;
		};
			
		// The computer will continue hitting cards until it's hand is greater than 16
		while(cards.getComputerScore() <= 16){
			cards.issueComputerHit();
			
			// Display computer cards. Tell the user if the computer busted
			if(cards.getComputerScore() > 21){
				cout << "The computer Busted with a score of " << cards.getComputerScore() << endl;
			}else{
				cout << "The computer's score is " << cards.getComputerScore() << endl;
			};
			if(cards.getComputerScore() > 16 && cards.getComputerScore() < 22){
				cout << "Computer Stands!" << endl;
			};
			
		};
		cout << "Press [Enter] to continue ..." << endl;
		cin.get();
		
		// The player and the computer have both played their hands. We need to calculate the results.
		// If either player has an Ace card, it is calculated at 11. If the player's hand is >21, it will recalculate the score with an Ace value of 1
		cout << endl << "--------------- RESULTS ---------------" << endl << endl;
		cout << "You: " << cards.getPlayerScore() << " vs Computer: " << cards.getComputerScore() << endl;
		
		// Display the results to the user. Figure out who won and issue money.
		// if computer && user > 21 or computer==user 
		if((cards.getComputerScore() > 21 && cards.getPlayerScore() > 21) || cards.getComputerScore()==cards.getPlayerScore()){
			// Tell user that the game is a push
			cout << "No winner!" << endl << endl;
			// No money issued or subtracted
			
		}else if((cards.getComputerScore() > cards.getPlayerScore() && cards.getComputerScore() <= 21) || cards.getPlayerScore() > 21){
			// The computer has won the game
			// Insult the player
			cout << "The computer wins!!! lol" << endl;
			
			// Remove some $$$ from the user
			cout << "You lost $" << playerBet << "!!" << endl;
			playerMoney = playerMoney - playerBet;
			
		}else{
			// The player has won the hand
			cout << "You won $" << playerBet << "!" << endl;
			
			// Add money to the player's account
			playerMoney = playerMoney + playerBet;
		};
		
		// Tell the player how much money they have
		cout << "You now have $" << playerMoney << "." << endl << endl;
		
		// check if the player still has money. if so, prompt to play again
		if(playerMoney > 0){
			int playAgainAnswer;
			cout << "Would you like to play again? [1=yes, 0=no]: ";
			cin >> playAgain;
			if(playAgain == 1){
				playAgain = true;
			}
		}else{
			// The player is out of money
			// Issue insult
			cout << "You are broke!! You lose!!!";
			playAgain = false;
		};
		cout << "\n\n\n";
	}while(playAgain);
		
	cout << "Thanks for playing!!" << endl << "You ended up with $" << playerMoney;
	
	return 0;
}



