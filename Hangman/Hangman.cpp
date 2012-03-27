// Hangman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

  // Enable game server access by default 
  Network::SetNetworkStatus(true); 

  // Determine the unique identifier for this player -- Can Fail
  Network::SetMACAddress();

  // Query if this client version is still valid  -- Can Fail
  Network::QueryVersion();

  // Display server connection failure if needed
  Network::DisplayNetworkStatus();

  // Seed the random number generator with a time value
  srand( static_cast<unsigned>(time(nullptr)) );

  const char ESC_CHAR = 27;

#ifdef _DEBUG
  cout << "~ DEBUG BUILD! ~" << endl;
#endif
  cout << "*******************************" << endl;
  cout << " Double Jeopardy Hangman  v1.0 " << endl;
  cout << "*******************************" << endl;

  GameLogic ActiveGame;
  ActiveGame.LoadConfig();
  ActiveGame.SetBestHighScore( Network::QueryNetPersonalBestScore() );

  vector<int> RelativeNetHiScoresList;
  int rank;
  Network::QueryNetHiScores( RelativeNetHiScoresList, rank );

  if( !RelativeNetHiScoresList.empty() )
  {
    bool bFound = false;
	for( const auto& it : RelativeNetHiScoresList )
    {
      cout << rank++ << ". ";
      if( ActiveGame.GetBestHighScore() == it && !bFound )
      {
        ActiveGame.DisplayScore(it);
        cout << " (your high score)";
      }
      else
      {
        ActiveGame.DisplayScore(it);
      }
      cout << endl;
    }
  }

  ActiveGame.DisplayHighScores();
  ActiveGame.DisplayGlobalRank();
  cout << endl << endl << "Press any key to begin.";
  DetectKeyInput();


  char cKeyInput;
  bool bExit = false;
  bool bShutdownServer = false;
  
  vector<string> wordsToGuess;

  do
  {
    ActiveGame.NewRound();
    wordsToGuess.clear();

    while( !ActiveGame.GameOver() )
    {
      cls( GetStdHandle(STD_OUTPUT_HANDLE) ); // clear console window

      cout << "SCORE: ";
      ActiveGame.DisplayScore(ActiveGame.GetCurrScore());
      cout << endl;

      ActiveGame.DisplayMan();
      ActiveGame.DisplayRoundResult();
      ActiveGame.DisplayPartialWord();
      cout << endl;
      ActiveGame.DisplayGuessList();
      cout << endl << "Guess a Letter>";
    
      cKeyInput = static_cast<char>(DetectKeyInput());

      if( cKeyInput == ESC_CHAR )
      {
        bExit = true; // force immediate exit
        break;
      }

      if( ActiveGame.AddLetterToGuessList(cKeyInput) )
      {
         ActiveGame.CheckGuess(cKeyInput);
      }
      //cout << endl << endl;

    } // round loop
    
    if( ActiveGame.GameOver() ) // round or game naturally ended in win or lose state
    {
      if( !ActiveGame.WonGame() ) // player lost, save his data to the high score lists, local and global.
      {
        ActiveGame.AdjustHighScoreList();
      }

      ActiveGame.DisplayGameResults();

      if( !ActiveGame.WonGame() )
      {
        cout << endl << "Play a New Game";
      }
      else
      {
        cout << endl << "Keep Playing";
      }
      cout << " (y/n)? ";

      cKeyInput = static_cast<char>(DetectKeyInput());

      cout << endl;

      if( cKeyInput == 'N' || cKeyInput == ESC_CHAR )
      {
        bExit = true;
      }
#ifdef _DEBUG
	  // Pressing Q in debug mode at the end of the game will shutdown the game server
      else if( cKeyInput == 'Q' )
      {
        bShutdownServer = true;
        bExit = true;
      }
#endif
    }

    // game was ended before the player had lost, via ESC mid-game or quitting earily after a round
    if( ActiveGame.WonGame() || !ActiveGame.GameOver() )
    {
      // Save the current score if needed
      ActiveGame.AdjustHighScoreList();
    }

    if( bExit )
    {
      ActiveGame.SaveConfig(); // save high score data, etc
      if( bShutdownServer )
      {
        Network::ShutdownNetServer();  // hack to shutdown remote server
      }
    }
  } while( !bExit );

	exit(0);
}

