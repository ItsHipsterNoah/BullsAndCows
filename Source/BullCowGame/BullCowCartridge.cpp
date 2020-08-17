// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <ctime>
#include <cstdlib>


FString words[5]{ "unreal", "active", "game", "play", "dev" };
int32 lives = 3;
bool checkGuess(FString);

FString HiddenWord{};

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	srand(time(NULL));
	HiddenWord = words[rand() % 3];
    PrintLine(TEXT("Welcome to the Bulls and Cows game!\nPress enter to continue."));
	PrintLine(TEXT("The word is " + FString::FromInt(HiddenWord.Len()) + " characters long."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	
    ClearScreen();
	int32 start = 0;
	int32 bulls{ 0 }, cows{ 0 };
	// first check if it's a match
	if (Input == HiddenWord) {
		PrintLine("Correct!");
		return;
	}
	else if (lives == 0){
		PrintLine("Game over!");
		return;
	}
	else if (Input == "") {
		PrintLine("");
	}
	else if (Input.Len() != HiddenWord.Len()) {
		PrintLine(TEXT("Wrong number of characters"));
		PrintLine(HiddenWord);
		PrintLine(TEXT("The word is" + FString::FromInt(HiddenWord.Len()) + " characters long."));
		PrintLine(FString::FromInt(lives) + " lives left");
		lives--;
	}
	else {
		// check if isogram
		for (int i = 0; i < Input.Len(); i++) {
			if (i + 1 < Input.Len()) {
				int32 index = i + 1;
				if (!checkGuess(Input)) {
					PrintLine(TEXT("Not an isogram"));
					PrintLine(FString::FromInt(lives) + "lives left");
					lives--;
					return;
				}
			}
		}
		// check bulls & cows
		for (int i = 0; i < HiddenWord.Len(); i++) {
			if (HiddenWord[i] == Input[i]) {
				bulls++;
			}
			else {
				if (HiddenWord.FindChar(Input[i], start)) {
					cows++;
				}
			}
		}
		PrintLine("Your guess had " + FString::FromInt(bulls) + " bulls and " + FString::FromInt(cows) + " cows"  );
	}
}


bool checkGuess(FString word) {
	FString letters{""}; int32 dummy{ 0 };
	letters = letters.AppendChar(word[0]);
	for (int i = 1; i < word.Len()-1; i++) {
		if (!letters.FindChar(word[i], dummy)) {
			letters = letters.AppendChar(word[i]);
		}
		else {
			return false;
		}
	}
	return true;
}