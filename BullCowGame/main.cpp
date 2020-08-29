/*This is the executable console, which run and loop the game.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;

void PrintIntro();
void PlayGame();
void PrintGuessBack(FText& Guess);
void PrintSummary();
bool AskToPlayAgain();
int AskForWordLength();
FText GetValidGuess();

FBullCowGame BCGame(3); // instantiate a new game with default word length 3

// entry point of the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // exit the application
}

void PlayGame()
{
	int wordLength = AskForWordLength();
	BCGame.Reset(wordLength);
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();
		PrintGuessBack(Guess);

		FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BCCount.bulls;
		std::cout << ". Cows = " << BCCount.cows << "\n\n";
	}

	PrintSummary();	// print summary of the game
	return;
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows.\n";
	std::cout << "Can you guess the letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

FText GetValidGuess() {
	EGuessStatus status = EGuessStatus::Invalid;
	FText Guess = "";
	do
	{
		// get a guess from the player and print back
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		status = BCGame.checkGuessValidity(Guess);
		switch (status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " length letter.\n\n";
			break;
		case EGuessStatus::Not_Lower_Case:
			std::cout << "Please enter a letter in lower case.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter a isogram. \n\n";
			break;
		default:
			break;
		}
	} while (status != EGuessStatus::OK);
	return Guess;
}

void PrintGuessBack(FText& Guess)	// repeat the guess
{
	std::cout << "Your guess was: " << Guess;
	std::cout << std::endl;
}

void PrintSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "nice duuuuude!\n";
	}
	else
	{
		std::cout << "better luck next time\n";
	}
}

bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again (y/n)? ";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return Response[0] == 'y' || Response[0] == 'Y';
}

int AskForWordLength()
{
	int wordLength;
	std::cout << "Print word length between 3~6: ";
	std::cin >> wordLength;
	std::cin.get();
	if (wordLength < 3 || wordLength > 6)
	{
		return 3;
	}
	return wordLength;
}
