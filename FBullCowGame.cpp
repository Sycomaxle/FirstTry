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
	
	TMap<char,bool> LetterSeen; //map'i kur. Not: Her bir deðeri (bool deðeri ise) varsayýlan olarak false ayarlanýr.
	//Gelen tahminin harflerini baþtan sona incele ve tüm harfleri tek tek not al.
	for (auto Letter : Guess) //Kelimenin tüm harfleri için.
	{
		Letter = tolower(Letter); //Tüm harfleri küçük harf yapar.
		if (LetterSeen[Letter]) { return false; } //Bu esnada ayný harf iki kere not alýndýysa iþlemi iptal et ve false deðeri dön.
		else { LetterSeen[Letter] = true; }  //Bu esnada ayný harf iki kere not alýnmadýysa iþlemi normal bir þekilde bitir ve true deðeri dön.	 
	}
	
	return true; // örnek olarak /0'ýn girildiði durumlar (string sonu anlamýna gelir)
} //YAPILACAK Çalýþýr hale getir.

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
	if (Guess.length() != GetHiddenWordLength()) //Tahminin uzunluðu geçerli deðilse:
	{
		return EGuessStatus::Wrong_Length; //Hata ver.
	}
		
	else if (!IsLowercase(Guess)) //Tahminin içinde büyük harf varsa: 
//ÖNEMLÝ Türkçe harflerde (þ gibi) hata veriyor.
	{
		return EGuessStatus::Upper_Case_Detected; //Hata ver.
	}
	
	else if (!IsIsogram(Guess)) //Tahmin isogram deðilse:
	{
        return EGuessStatus::Not_Isogram; //Hata ver.
	}
	else//Yukarýdakilerin hiçbiri yoksa:
	{
		return EGuessStatus::OK; //Tahmini doðrula.
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
	//Not: Geçerli tahmin aldýðý varsayýlarak...
	FBullCowCount BullCowCount;
	MyCurrentTurn++;
	int32 WordLength = MyHiddenWord.length(); //Tahmin ve gizli kelimenin uzunluðu ayný olduðu varsayýlýyor.
	// Tahmindeki tüm harfleri tara.
	for (int32 GChar = 0; GChar < WordLength; GChar++) 
	{
		//Tahmindeki harfleri gizli kelimeninkilerle karþýlaþtýr.
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) { // Ayný harf bulunursa:
			  //Ayný yerdelerse:
				if (GChar == MHWChar) { BullCowCount.Bulls++; } // bulls'ý arttýr.
              // Deðillerse:
				else { BullCowCount.Cows++; } // cows'ý arttýr.
			}
			
		}
	}
	bGameIsWon = (GetHiddenWordLength() == BullCowCount.Bulls);
	return BullCowCount;
}
