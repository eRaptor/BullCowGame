#pragma once

#include "FBullCowGame.h"

//to make more unreal friendly
#include <map>
#define TMap std::map 

using int32 = int;
//Getters
FBullCowGame::FBullCowGame(){Reset();} //Default constructor

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 3 }, {4, 5 }, {5, 6}, {6, 8} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	//Constants
	const FString HIDDEN_WORD = "planet";

	//Resets
	MyHiddenWord = HIDDEN_WORD; // Must be an Isogram 
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if guess isnt isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	//if guess isnt all lowercase 
	else if (!IsLowercase(Guess))
	{
		//TODO write function
		return EGuessStatus::Use_Lowercase_Please;
	}
	//if guess is wrong length
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	//otherwise
	else
	{
		return EGuessStatus::OK;
	}
}

//Recieves a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//Assuming same length as guess
	int32 WordLength = MyHiddenWord.length(); 

	//loop through all letters in hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against guess
		for (int32 GChar = 0; GChar< WordLength; GChar++)
		{
			//if letters match:
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				//if letters are in the same place
				if (MHWChar == GChar)
				{
					//increment bulls
					BullCowCount.Bulls++;
				}
				else
				{
					//Must be a cow
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))//if not a lowercase letter
		{
		return false;
		}
	}
	return true;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool > LetterSeen;
	for (auto Letter : Word)
	{
		// Handle mixed case
		Letter = tolower(Letter); 

		if (LetterSeen[Letter])
		{
			// do not have isogram at this stage
			return false; 
		}
		else
		{
			//add the letter to the map as seen
			LetterSeen[Letter] = true;
		}

	}
		return true; //for example in cases where /0 is entered
}
