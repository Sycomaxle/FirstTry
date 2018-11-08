#include "FBullCowGame.h"
#include <map>
#define TMap std::map


using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTry() const { return FBullCowGame::MyMaxTurn; }

int32 FBullCowGame::GetCurrentTry() const { return FBullCowGame::MyCurrentTurn; }

int32 FBullCowGame::GetHowManyGuessesLeft() const { return (FBullCowGame::MyMaxTurn - FBullCowGame::MyCurrentTurn + 1); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsIsogram(FString Guess) const 
{ 
	if (Guess.length() <= 1) { return true; } //T0 ve 1 harfli kelimeleri isogram olarak kabul et.
	
	TMap<char,bool> LetterSeen; //map'i kur. Not: Her bir de�eri (bool de�eri ise) varsay�lan olarak false ayarlan�r.
	//Gelen tahminin harflerini ba�tan sona incele ve t�m harfleri tek tek not al.
	for (auto Letter : Guess) //Kelimenin t�m harfleri i�in.
	{
		Letter = tolower(Letter); //T�m harfleri k���k harf yapar.
		if (LetterSeen[Letter]) { return false; } //Bu esnada ayn� harf iki kere not al�nd�ysa i�lemi iptal et ve false de�eri d�n.
		else { LetterSeen[Letter] = true; }  //Bu esnada ayn� harf iki kere not al�nmad�ysa i�lemi normal bir �ekilde bitir ve true de�eri d�n.	 
	}
	
	return true; // �rnek olarak /0'�n girildi�i durumlar (string sonu anlam�na gelir)
} //YAPILACAK �al���r hale getir.

bool FBullCowGame::IsLowercase (FString Guess) const
{ 



	for (auto Letter : Guess) 
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{
	if (Guess.length() != GetHiddenWordLength()) //Tahminin uzunlu�u ge�erli de�ilse:
	{
		return EGuessStatus::Wrong_Length; //Hata ver.
	}
		
	else if (!IsLowercase(Guess)) //Tahminin i�inde b�y�k harf varsa: 
//�NEML� T�rk�e harflerde (� gibi) hata veriyor.
	{
		return EGuessStatus::Upper_Case_Detected; //Hata ver.
	}
	
	else if (!IsIsogram(Guess)) //Tahmin isogram de�ilse:
	{
        return EGuessStatus::Not_Isogram; //Hata ver.
	}
	else//Yukar�dakilerin hi�biri yoksa:
	{
		return EGuessStatus::OK; //Tahmini do�rula.
	}

}


void FBullCowGame::Reset() 
{
	constexpr int32 MAX_TURN = 8;
	MyMaxTurn = MAX_TURN;

	constexpr int32 CURRENT_TURN = 1;
	MyCurrentTurn = CURRENT_TURN;
	
	const FString SECRET_WORD = "hentai";
	MyHiddenWord = SECRET_WORD;

	bGameIsWon = false;

	return; 
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//Not: Ge�erli tahmin ald��� varsay�larak...
	FBullCowCount BullCowCount;
	MyCurrentTurn++;
	int32 WordLength = MyHiddenWord.length(); //Tahmin ve gizli kelimenin uzunlu�u ayn� oldu�u varsay�l�yor.
	// Tahmindeki t�m harfleri tara.
	for (int32 GChar = 0; GChar < WordLength; GChar++) 
	{
		//Tahmindeki harfleri gizli kelimeninkilerle kar��la�t�r.
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) { // Ayn� harf bulunursa:
			  //Ayn� yerdelerse:
				if (GChar == MHWChar) { BullCowCount.Bulls++; } // bulls'� artt�r.
              // De�illerse:
				else { BullCowCount.Cows++; } // cows'� artt�r.
			}
			
		}
	}
	bGameIsWon = (GetHiddenWordLength() == BullCowCount.Bulls);
	return BullCowCount;
}
