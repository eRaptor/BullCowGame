/*  This is the console executable that uses the Bull Cow Game Class.
	This acts as the view in a MVC pattern,
	and is responsible for all user interaction, 
	for game logic see FBullCowGame class.
*/

#pragma once 

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;

//prototypes outside of main
void PrintGameSummary();
void PrintIntro();
void PlayGame();

bool AskToPlayAgain();

FText GetValidGuess();
FBullCowGame BCGame;

int main()
{ 
	// Application Entry
	BCGame.Reset();
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain); 

	return 0; // Exit the game
}

void PrintIntro()
{
	// Game Intro
	std::cout << "J   J    " << std::endl;
	std::cout << " o o    o o " << std::endl;
	std::cout << "  -      -  " << std::endl;
	std::cout << "|  |     | |" << std::endl;
	std::cout << "Welcome To Bulls & Cows, A Fun Word Game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

//plays single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//Check here to see game win logic!!!
	//loop for the number of turns asking for guesses while the game is NOT Won and tries remain
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText PlayerGuess = GetValidGuess();

		// Submit valid guess to game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(PlayerGuess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE, YOU WON!!!\n";
	}
	else
	{
		std::cout << "Better luck next time :(\n";
	}
	return;
}

//Loop until user gives valid guess
FText GetValidGuess()
{
	FText PlayerGuess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do 
	{
		//Get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();

		// Get Input From Player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, PlayerGuess);

		//Checking if valid guess
		Status = BCGame.CheckGuessValidity(PlayerGuess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;

			case EGuessStatus::Not_Isogram:
				std::cout << "That word is not an Isogram.\n\n";
				break;

			case EGuessStatus::Use_Lowercase_Please:
				std::cout << "Use lowercase only.\n\n";
				break;
			
			default:
				//assuming guess is valid
				break;
		}
	}
	//Keep looping until we get get no errors
	while (Status != EGuessStatus::OK);
	return PlayerGuess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word??? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
