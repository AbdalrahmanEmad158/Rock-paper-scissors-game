#include<iostream>
using namespace std;
#include<iomanip>
#include <cmath>
#include<cstdlib>
#include<string>
enum enGameChoice { Stone = 1, Paper = 2, scissors = 3 };
enum enWinner { player1 = 1, computer = 2, Draw = 3 };
struct StRoundInfo
{
	short RoundNumber = 0;
	enGameChoice player1Choice;
	enGameChoice computerChoice;
	enWinner winner;
	string WinnerName;
};
struct StGameResult
{
	short NumberOfRound = 0;
	short player1Winner = 0;
	short Draw = 0;
	short computerWinner = 0;
	enWinner WINNER;
	string WinnerName = "";
};
short ReadHowManyRounds()
{
	short GameRounds = 1;
	do
	{
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds >10);
	return
		GameRounds;
}
int RandomNumber(int from, int to)
{
	int Random;
	Random = rand() % (to - from + 1) + from;
	return Random;
}
string WinnerName(enWinner Winner)
{
	string ArrWinner[4] = { "","player1","computer","no winner" };
	return ArrWinner[Winner];
}
enWinner whoWonTheRound(StRoundInfo RoundInfo)
{
	if (RoundInfo.computerChoice == RoundInfo.player1Choice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.player1Choice)
	{
	case enGameChoice::scissors:
		if (RoundInfo.computerChoice == enGameChoice::Stone)
		{
			return enWinner::computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.computerChoice == enGameChoice::scissors)
		{
			return enWinner::computer;
		}
		break;
	case enGameChoice::Stone:
		if (RoundInfo.computerChoice == enGameChoice::Paper)
		{
			return enWinner::computer;
		}
		break;
	}
	return enWinner::player1;
}
string choiceName(enGameChoice choice)
{
	string arrChoice[4] = { "","Stone","Paper","Scissors" };
	return arrChoice[choice];
}
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::player1:
		system("color 2F");
		break;
		//turn screen to Greenbreak;
	case enWinner::computer:
		system("color 4F");
		//turn screen to Red     
		cout << "\a";
		break;
	default:
		system("color 6F");
		//turn screen to Yellowbreak;    
	}
}
void PrintResule(StRoundInfo RoundInfo)
{
	cout << "\n____________Round [" << RoundInfo.RoundNumber << "_________\n";
	cout << "\n____________computerChoic [" << choiceName(RoundInfo.computerChoice) << "_________]\n";
	cout << "\n____________player1Choice [" << choiceName(RoundInfo.player1Choice) << "_________]\n";
	cout << "\n____________WinnerName [" << RoundInfo.WinnerName << "_________\n";
	cout << "\n_______________\n\n";
	SetWinnerScreenColor(RoundInfo.winner);
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::player1;

	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::computer;

	else
		return enWinner::Draw;
}
StGameResult FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	StGameResult GameResult;
	GameResult.computerWinner = ComputerWinTimes;
	GameResult.Draw = DrawTimes;
	GameResult.NumberOfRound = GameRounds;
	GameResult.player1Winner = Player1WinTimes;
	GameResult.WINNER = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.WINNER);
	return GameResult;
}
enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice >3);
	return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
	return  (enGameChoice)RandomNumber(1, 3);
}
string  Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
StGameResult PlayGame(int HowManyRound)
{
	StRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (int GameROUND = 1; GameROUND <= HowManyRound; GameROUND++)
	{
		cout << "\nRound [" << GameROUND << "] begins:\n";
		RoundInfo.RoundNumber = GameROUND;
		RoundInfo.player1Choice = ReadPlayer1Choice();
		RoundInfo.computerChoice = GetComputerChoice();
		RoundInfo.winner = whoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.winner);
		if (RoundInfo.winner == enWinner::player1)
			Player1WinTimes++;
		else if (RoundInfo.winner == enWinner::computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
		PrintResule(RoundInfo);
	}
	return FillGameResults(HowManyRound, Player1WinTimes, ComputerWinTimes, DrawTimes);
}
void ShowGameOverScreen()
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}
void ShowFinalGameResults(StGameResult GameResults)
{
	cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.NumberOfRound << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResults.player1Winner << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.computerWinner << endl;
	cout << Tabs(2) << "Draw times         : " << GameResults.Draw << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";
	SetWinnerScreenColor(GameResults.WINNER);
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		StGameResult GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);
		cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}