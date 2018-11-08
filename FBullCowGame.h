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
	Non_letter // YAPILACAK Harf d���nda karakter girimini denetle.
	
};

enum class EResetStatus 
{
    // YAPILACAK Harf uzunlu�u se�me eklendi�inde oyuncunun girdi�i say�y� max ile kar��la�t�r ve geri d�n�� ver.
	OK,
};

class FBullCowGame {
public:
	
	FBullCowGame(); // constructor

	int32 GetMaxTry() const ;
	int32 GetCurrentTry() const ;
	int32 GetHiddenWordLength() const ;
	int32 GetHowManyGuessesLeft() const ;
	//YAPILACAK Gizli kelimeyi almay� sa�layan bir fonksiyon yaz.

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const ; // YAPILACAK Daha a��klay�c� bir geri d�n�� ekle. (Hatalar hangileri vb.)
	
	void Reset(); // YAPILACAK Daha a��klay�c� bir geri d�n�� ekle. (Cevap neydi vb.)
	// YAPILACAK Ge�erli tahmini al�p Bulls & Cows'lar� say�p deneme say�s�n� artt�racak kod ekle.
	FBullCowCount SubmitValidGuess(FString);
	// YAPILACAK MyMaxTurn ve kelimedeki harf say�s�n� kullan�c�dan alacak kodu ekle. (Zorluk se�imi)
	// YAPILACAK Skor mekani�i ekle.

private:
	//De�erler i�in reset fonksiyonuna bak.
	int32 MyMaxTurn;
	int32 MyCurrentTurn;


	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const; 
};