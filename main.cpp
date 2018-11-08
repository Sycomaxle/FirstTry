#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskForPlayAgain();

FBullCowGame BCGame; // Yeni oyun olu�turulur.

//Program�n Ba�lang���
int main() 
{
	do {
		PrintIntro();
		// YAPILACAK Oyuncudan zorluk ama�l� maksimum deneme say�s�n� ve kelimenin harf say�s�n� al.
		PlayGame();
		PrintGameSummary();

	} while (AskForPlayAgain());
	return 0; //Program�n biti�i
}


void PrintIntro()
{
	std::cout << "Bulls & Cows'a hos geldin.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "\nAklimdan " << BCGame.GetHiddenWordLength() << " harfli bir kelime tuttum. Tahmin edebilir misin?\n";
	std::cout << "Ayrica isini kolaylastirmak icin aklimdan tuttugum kelimenin icinde hicbir tekrar eden harf yok.\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTry();


    // Mevcut tahmin say�s�n� denetleyen d�ng�
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTry())
	{ 
		FText Guess = GetValidGuess();

		// Tahmini oyuna g�nderir, bulls ve cows'lar� sayar.
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Bulls ve cows'lar� s�yler.
		std::cout << "Bulls: " << BullCowCount.Bulls << "    Cows: " << BullCowCount.Cows << "\n\n";
	}
		// YAPILACAK Oyun sonucunu g�ster.
	return;
}



FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Not_Valid;
	do
	{
		std::cout << BCGame.GetCurrentTry() << ". tahminin, " << BCGame.GetHowManyGuessesLeft() <<" tahmin hakkin kaldi. Lutfen tahminini gir: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Lutfen " << BCGame.GetHiddenWordLength() << " harfli bir kelime giriniz.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Lutfen tekrar eden harflerin bulunmadigi bir kelime giriniz.\n\n";
			break;
		case EGuessStatus::Upper_Case_Detected:
			std::cout << "Lutfen hepsini kucuk harf giriniz.\n\n";
			break;
		default:
			// Tahminin ge�erli oldu�u varsay.
			break;
		}
	} while (Status != EGuessStatus::OK); // Oyuncudan ge�erli bir tahmin alana kadar devam eder.
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) 
	{
	std::cout << "Tebrikler, gizli kelimeyi buldun!\n";
	}
	else 
	{
		std::cout << "Maalesef, gizli kelimeyi bulamadin.\n";
		//YAPILACAK Oyuna birden fazla gizli kelime ekleyince gizli kelimeyi s�yle.
	}
	return;
}

//Oyuncuya tekrar oynamak isteyip istemedi�ini sorar.
bool AskForPlayAgain()
{
	std::cout << "Ayni kelimeyle yeniden oynamak ister misin? (e/h)" << std::endl;
	std::cout << "Cevabin: ";
	FText Answer = "";
	std::getline(std::cin, Answer);

	return (Answer[0] == 'e') || (Answer[0] == 'E');
}