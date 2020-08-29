#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame(int wordLength) { Reset(wordLength); }
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int, int> WordLengthToMaxTries{ {3,5}, {4,6}, {5,6}, {6,10} };
	return WordLengthToMaxTries[HiddenWord.length()];
}

void FBullCowGame::Reset(int wordLength)
{
	TMap<int, FString> HiddenWordMap{ {3,"cat"}, {4,"nice"}, {5,"great"}, {6,"should"} };
	const FString HIDDEN_WORD = HiddenWordMap[wordLength];
	constexpr int32 MAX_TRIES = 3;

	HiddenWord = HIDDEN_WORD;
	MaxTries = MAX_TRIES;
	CurrentTry = 1;
	bIsWon = false;
	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString Guess) const
{
	if (Guess.length() != getHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowerCase(Guess))	// if the guess isn't all lower case
	{
		return EGuessStatus::Not_Lower_Case;
	}
	else if (!IsIsogram(Guess)) // if the guess isn't all isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BCCount;
	int32 WordLength = FBullCowGame::getHiddenWordLength();

/*	// loop and check each letter if they match in iterator way
	for (int32 i = 0; i < HiddenWord.length(); i++)
	{
		if (HiddenWord[i] == Guess[i])
		{
			Bulls++;
		}
		else 
		{
			for (FString::iterator it = Guess.begin(); it != Guess.end(); it++)
			{
				if (*it == HiddenWord[i])
				{
					Cows++;
				}
			}
		}
	}
*/

	// loop as the course
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (HiddenWord[HWChar] == Guess[GChar])
			{
				if (HWChar == GChar) 
				{
					BCCount.bulls++; 
				}
				else
				{
					BCCount.cows++;
				}
			}
		}
	}
	if (BCCount.bulls == WordLength) { bIsWon = true; }

	return BCCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (!LetterSeen[Letter])
		{
			LetterSeen[Letter] = true;
		}
		else
		{
			return false;
		}
	}
	return true;

/*	// loop in another way
	TMap<char, bool> MGuess;
	for (int GChar = 0; GChar < Guess.length(); GChar++)
	{
		if (!MGuess[Guess[GChar]])
		{
			MGuess[Guess[GChar]] = true;
		}
		else
		{
			return false;
		}
	}
	return true;
*/
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
