/*The Game logic (No view code or direct user interaction)
The game is a simple guess the word game based on mastermind
*/

#pragma once
#include <string>

//To make syntax Unreal friendly
using int32 = int;
using FString = std::string;


//two ints, initialised to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//Enumerator, Error Codes
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Use_Lowercase_Please
};

class FBullCowGame
{
public:
	FBullCowGame();// Constructor

	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	FBullCowCount SubmitValidGuess(FString);

private:
	// See constructor
	int32 MyCurrentTry;

	FString MyHiddenWord;

	bool bGameIsWon;
	bool IsLowercase(FString) const;
	bool IsIsogram(FString) const;
};
