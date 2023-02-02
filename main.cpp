#include<iostream>
using namespace std;
/*Create the variables, “playerOne”, ”playerTwo”, “randomNumber”, “playerGuess”, and “currentPlayer”
Ask the first person their name and store that into the variable “playerOne”
Ask the second person their name and store that into variable “playerTwo”
Generate a random number between 1 and 100 and store that into the variable “randomNumber”
Tell the players to flip a coin.
Prompt the player who won and store it into “currentPlayer”
Start a loop for player turns
In the loop, prompt the current player for their guess and store it to “playerGuess”
Compare the variable “playerGuess” to “randomNumber”
If the “playerGuess” is incorrect
If “playerGuess” is less than “randomNumber”, prompt the player “Your guess is too low”
If “playerGuess” is greater than “randomNumber”, prompt the player “Your guess is too high”
If the “playerGuess” is equal to “randomNumber”
Print “end the game”
Switch to the next player by updating the “currentPlayer” and repeat steps 8-11
*/
int main()
{

	std::string namePlayer1;
	std::string namePlayer2;
	int playerGuess = 0;

	srand(time(0));
	int currentPlayer = rand() % 2;
	char gameState;
	gameState = 'y';
	int players = 0;

	cout << "How many players are playing" << endl << "1 or 2" << endl;
	cin >> players;
	if (players == 2) {
		cout << "Please Enter Player 1's name" << endl;
		cin >> namePlayer1;
		cout << "Please Enter Player 2's name" << endl;
		cin >> namePlayer2;
	}
	else {
		cout << "Please Enter Player 1's Name" << endl;
		cin >> namePlayer1;
	}
	while (gameState == 'y' && players == 1) { //This is the gamestate for single player. A computer will make a guess on behalf of player 2
		srand(time(0));
		int cGuess;
		int randomNumber = rand() % 100 + 1;
		//cout << randomNumber << endl;
		do {
			switch (currentPlayer) {
			case 0: {
				cout << namePlayer1 << " Enter your guess" << endl << endl;
				cin >> playerGuess;

				break;
				}
			case 1:
			{
				cout << "The computer makes a guess of";
				cGuess = rand() % 100 + 1;
				cout << " " << cGuess << endl;
				playerGuess = cGuess;
				break;
			}
			default: {
				break;
			}
			}
			if (playerGuess == randomNumber){
				switch (currentPlayer) {
				case 0: {
					cout << namePlayer1 << " has won the game" << endl;
					break;
				}
				case 1: {
					cout << "The Computer has won the game";
					break;
				}
				default: {
					break;
				}
				}
			}
			else if (playerGuess < randomNumber) {
				cout << "The number is too low" << endl << endl;
			}
			else if (playerGuess> randomNumber) {
				cout << "The number is too high" << endl << endl;
			}
			currentPlayer = 1 - currentPlayer;
		} while (playerGuess != randomNumber);
		cout << "Would you like to play again? Press 'y or 'n'" << endl;
		cin >> gameState; //Sets the game to loop
	}

	while (gameState == 'y' && players == 2) //This is the 2 player version of the game where a player
	{
		srand(time(0));
		int randomNumber = std::rand() % 100 + 1;
		//cout << "Answer is: " << randomNumber << std::endl;
		do
		{
			switch (currentPlayer)
			{
			case 0:
				cout << namePlayer1 << " enter in your guess" << std::endl << endl;
				break;

			case 1:
				std::cout << namePlayer2 << " enter in your guess" << std::endl << endl;
				break;


			default:
				break;
			}
			std::cin >> playerGuess;
			if (playerGuess == randomNumber)
			{
				switch (currentPlayer)
				{
				case 0:
				{
					std::cout << namePlayer1 << " you won this game!" << std::endl;
					break;
				}
				case 1:
				{
					std::cout << namePlayer2 << " you won this game!" << std::endl;
					break;
				}
				default: {
					break;
				}
				}
			}

			else if (playerGuess < randomNumber)
			{
				std::cout << "Too low!" << std::endl;
			}
			else if (playerGuess > randomNumber)
			{
				std::cout << "Too high!" << std::endl;
			}


		 currentPlayer = 1 - currentPlayer;
	}
			 while (playerGuess != randomNumber);
			std::cout << "Would you like to play again?" << std::endl << "Press 'y' or 'n'" << std::endl;
			std::cin >> gameState; //Sets the game to replay or not
		}

	}