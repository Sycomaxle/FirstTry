#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Not_Valid,
	OK,
	Wrong_Length,
	Not_Isogram,
	Upper_Case_Detected,
	Non_letter // YAPILACAK Harf dýþýnda karakter girimini denetle.
	
};

enum class EResetStatus 
{
    // YAPILACAK Harf uzunluðu seçme eklendiðinde oyuncunun girdiði sayýyý max ile karþýlaþtýr ve geri dönüþ ver.
	OK,
};

class FBullCowGame {
public:
	
	FBullCowGame(); // constructor

	int32 GetMaxTry() const ;
	int32 GetCurrentTry() const ;
	int32 GetHiddenWordLength() const ;
	int32 GetHowManyGuessesLeft() const ;
	//YAPILACAK Gizli kelimeyi almayý saðlayan bir fonksiyon yaz.

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const ; // YAPILACAK Daha açýklayýcý bir geri dönüþ ekle. (Hatalar hangileri vb.)
	
	void Reset(); // YAPILACAK Daha açýklayýcý bir geri dönüþ ekle. (Cevap neydi vb.)
	// YAPILACAK Geçerli tahmini alýp Bulls & Cows'larý sayýp deneme sayýsýný arttýracak kod ekle.
	FBullCowCount SubmitValidGuess(FString);
	// YAPILACAK MyMaxTurn ve kelimedeki harf sayýsýný kullanýcýdan alacak kodu ekle. (Zorluk seçimi)
	// YAPILACAK Skor mekaniði ekle.

private:
	//Deðerler için reset fonksiyonuna bak.
	int32 MyMaxTurn;
	int32 MyCurrentTurn;


	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const; 
};