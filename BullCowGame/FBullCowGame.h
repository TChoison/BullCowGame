#pragma once
/*This is the game logic class
*/

#include <string>
using int32 = int;
using FString = std::string;

// all values initialized to 0
struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Wrong_Length,
	Not_Lower_Case,
	Not_Isogram,
};

class FBullCowGame
{
public:
	FBullCowGame(int);
	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 getHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus checkGuessValidity(FString) const;

	void Reset(int);
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 CurrentTry;
	int32 MaxTries;
	FString HiddenWord;
	bool bIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
