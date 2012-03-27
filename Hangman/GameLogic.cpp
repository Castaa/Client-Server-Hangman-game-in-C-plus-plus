// GameLogic.cpp

#include "stdafx.h"

using namespace std;

const int GameLogic::m_cMaxFailedGuesses = 7;
const int GameLogic::m_cHeightOfMan = 8;
const int GameLogic::m_cMaxHighScoreListSize = 100;

GameLogic::GameLogic()
{
  m_FailedGuesses			= 0;
  m_CurrScore				= 0;
  m_RoundNum				= 0;
  m_BestHiScore				= 0;
  m_XmlDocument				= nullptr;
  m_bWonRound				= false;
  m_bChallengeRound			= 0;
  m_CorrectGuessesStreak	= 0;

  // Scrabble letter scores
  m_LetterScore.insert(pair<char, int>('E', 1));  // 1 point: E, A, I, O, N, R, T, L, S, U
  m_LetterScore.insert(pair<char, int>('A', 1));  
  m_LetterScore.insert(pair<char, int>('I', 1));  
  m_LetterScore.insert(pair<char, int>('O', 1));  
  m_LetterScore.insert(pair<char, int>('N', 1));  
  m_LetterScore.insert(pair<char, int>('R', 1));  
  m_LetterScore.insert(pair<char, int>('T', 1));  
  m_LetterScore.insert(pair<char, int>('L', 1));  
  m_LetterScore.insert(pair<char, int>('S', 1)); 
  m_LetterScore.insert(pair<char, int>('U', 1)); 

  m_LetterScore.insert(pair<char, int>('D', 2));  // 2 points: D, G
  m_LetterScore.insert(pair<char, int>('G', 2)); 
												 
  m_LetterScore.insert(pair<char, int>('B', 3));  // 3 points: B, C, M, P
  m_LetterScore.insert(pair<char, int>('C', 3));  
  m_LetterScore.insert(pair<char, int>('M', 3));  
  m_LetterScore.insert(pair<char, int>('P', 3));  
												  
  m_LetterScore.insert(pair<char, int>('F', 4));  // 4 points: F, H, V, W, Y
  m_LetterScore.insert(pair<char, int>('H', 4));  
  m_LetterScore.insert(pair<char, int>('V', 4));  
  m_LetterScore.insert(pair<char, int>('W', 4));  
  m_LetterScore.insert(pair<char, int>('Y', 4)); 

  m_LetterScore.insert(pair<char, int>('K', 5));  // 5 points: K
												  
  m_LetterScore.insert(pair<char, int>('J', 8));  // 8 points: J, X
  m_LetterScore.insert(pair<char, int>('X', 8));  

  m_LetterScore.insert(pair<char, int>('Q', 10)); // 10 points: Q, Z
  m_LetterScore.insert(pair<char, int>('Z', 10)); 


  m_VisualMan.resize(m_cMaxFailedGuesses); // 7 hangman states: head, neck, body, right arm, left arm, left leg, right leg
  for( auto i = 0; i < m_cMaxFailedGuesses; i++ )
  {
    m_VisualMan[i].resize(8);
  }

  // using extended ASCII characters, construct the hangman gallows
  m_VisualStand.push_back("  ÉÍÍÍÍÍÍÍ»");
  m_VisualStand.push_back("  º       º");
  m_VisualStand.push_back("  º");        
  m_VisualStand.push_back("  º");        
  m_VisualStand.push_back("  º");        
  m_VisualStand.push_back("  º");        
  m_VisualStand.push_back("  º");
  m_VisualStand.push_back("  º");        
  m_VisualStand.push_back("  º");        
  m_VisualStand.push_back("  º");        
  m_VisualStand.push_back("ÍÍÊÍÍ");

  m_VisualMan[0][0]="     (-_-)";
  m_VisualMan[0][1]="       ";
  m_VisualMan[0][2]="       ";
  m_VisualMan[0][3]="       ";
  m_VisualMan[0][4]="       ";
  m_VisualMan[0][5]="       ";
  m_VisualMan[0][6]="       ";
  m_VisualMan[0][7]="       ";


  m_VisualMan[1][0]="     (-_ø)";
  m_VisualMan[1][1]="       þ";
  m_VisualMan[1][2]="       ";
  m_VisualMan[1][3]="       ";
  m_VisualMan[1][4]="       ";
  m_VisualMan[1][5]="       ";
  m_VisualMan[1][6]="       ";
  m_VisualMan[1][7]="       ";


  m_VisualMan[2][0]="     (o_ø)";
  m_VisualMan[2][1]="       þ";
  m_VisualMan[2][2]="       Û";
  m_VisualMan[2][3]="       Û";
  m_VisualMan[2][4]="       Û";
  m_VisualMan[2][5]="       ";
  m_VisualMan[2][6]="       ";
  m_VisualMan[2][7]="       ";


  m_VisualMan[3][0]="     (O_o)";
  m_VisualMan[3][1]="       þ";
  m_VisualMan[3][2]="       Û----o";
  m_VisualMan[3][3]="       Û";
  m_VisualMan[3][4]="       Û";
  m_VisualMan[3][5]="       ";
  m_VisualMan[3][6]="       ";
  m_VisualMan[3][7]="       ";


  m_VisualMan[4][0]="     (o_O)";
  m_VisualMan[4][1]="       þ";
  m_VisualMan[4][2]="  o----Û----o";
  m_VisualMan[4][3]="       Û";
  m_VisualMan[4][4]="       Û";
  m_VisualMan[4][5]="       ";
  m_VisualMan[4][6]="       ";
  m_VisualMan[4][7]="       ";


  m_VisualMan[5][0]="     (O_O)";
  m_VisualMan[5][1]="       þ";
  m_VisualMan[5][2]="  o----Û----o";
  m_VisualMan[5][3]="       Û";
  m_VisualMan[5][4]="      /Û";
  m_VisualMan[5][5]="     /  ";
  m_VisualMan[5][6]="    /   ";
  m_VisualMan[5][7]="  _/    ";


  m_VisualMan[6][0]="     (x_x)";
  m_VisualMan[6][1]="       þ";
  m_VisualMan[6][2]="  o----Û----o";
  m_VisualMan[6][3]="       Û";
  m_VisualMan[6][4]="      /Û\\";
  m_VisualMan[6][5]="     /   \\";
  m_VisualMan[6][6]="    /     \\";
  m_VisualMan[6][7]="  _/       \\_";

#ifdef _DEBUG  
//  cout << "Loading Dictionary...";
#endif
  if( !Network::GetNetworkStatus() && !LoadWordFile(m_Dictionary) )
  {
    cout << "Dictionary file not found.  This file must be found in the same directory as Hangman program." << endl; 
    exit(-1);
  }
#ifdef _DEBUG  
  //cout << "Finished." << endl;
#endif
}

void GameLogic::NewRound()
{
	if(!m_bWonRound) // did the player lose the previous round?
	{
		m_CurrScore = 0;
		m_RoundNum = 0;
	}

	m_WordsToGuess.clear();

	auto iWordsToGuess = 2;
	m_RoundNum++;


	if( m_RoundNum % 3 == 0 )
	{
		iWordsToGuess = 1; // Challenge Round!
		m_bChallengeRound = true;
	}
	else
	{
		m_bChallengeRound = false;
	}

	if( !Network::GetWordsToGuess(iWordsToGuess, m_WordsToGuess) )  // ask server for words
	{
		// network request for words failed, just use local dictionary words as a fall back option
		/////////////////////////////// random pick from local word list
		for( auto i = 0; i < iWordsToGuess; i++ )
		{
			// pick a random index into our locally stored dictionary
			int randIndex = (int)((double)rand() / RAND_MAX * m_Dictionary.size());
			m_WordsToGuess.push_back( m_Dictionary[randIndex] );
		}
	}


  //m_WordsToGuess = GameWordList;
  InitGuessList();
  InitPartialWord();
  m_FailedGuesses = 0;
  m_CorrectGuessesStreak = 0;
  m_bWonRound = false;
  m_RoundLettersCorrect = 0;
  m_RoundScore = 0;
}

void GameLogic::InitGuessList()
{
  m_GuessList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

void GameLogic::DisplayGuessList()
{
  cout << m_GuessList << endl;
}

bool GameLogic::AddLetterToGuessList(char& letter)
{
  // convert to upper case if needed
  if( letter >= 'a' && letter <= 'z' )
  {
    letter -= 32;
  }

  auto pos = m_GuessList.find(letter);

  // if found?
  if( pos != m_GuessList.npos )
  {
    m_GuessList[pos] = '_';//'þ';
    return true;
  }
  
  return false;
}

void GameLogic::InitPartialWord()
{
  m_PartialWord.clear();
  m_PartialWord.resize( m_WordsToGuess.size() );
  
  auto it2 = m_PartialWord.begin();

  for( const auto& it : m_WordsToGuess )
  {
    auto length = it.length();
    char ctemp = '_';
   
    for( unsigned int j = 0; j < length; j++ )
    {
      (*it2).append(&ctemp, 1);
    }
    it2++;
  }
}

void GameLogic::DisplayPartialWord()
{
  int count = 0;
  for ( auto it = m_PartialWord.begin(); it < m_PartialWord.end(); it++ )
  {
    cout << "      " ;
    count++;

    auto length = (*it).length();

    if( length > 0 )
    {
      for( unsigned int j = 0; j < length; j++)
      {
        cout << (*it)[j] << " ";
      }

      cout << endl;
    }
  }
}

// Once a game of hangman is finished, display the results win or lose
void GameLogic::DisplayGameResults()
{
  auto numCorrect = 0;
  vector<string> solvedList;

  auto it2 = m_WordsToGuess.begin();
  for ( auto it = m_PartialWord.begin(); it < m_PartialWord.end(); it++ )
  {
    if( (*it) == (*it2) )
    {
      numCorrect++;
      solvedList.push_back((*it2)+"  (solved)");
    }
    else
    {
      solvedList.push_back((*it2)+"  (unsolved)");
    }
    it2++;
  }

  cout << endl << endl;
 
  if ( numCorrect > 0 )
  {
    if( numCorrect > 1 && numCorrect == m_WordsToGuess.size() ) // multiwords
    {
      cout << "Perfect Round!  All words solved." << endl; 
    }
    else
    {
      cout << "You win the Round!  ";
        
      if( m_WordsToGuess.size() > 1 )
      {
        cout << numCorrect << " out of " << m_WordsToGuess.size() << ' ' << (numCorrect==1 ? "word" : "words") << " solved.";
      }

      cout << endl;
    }
  }
  else
  {
    cls(GetStdHandle(STD_OUTPUT_HANDLE)); // clear console window

    DisplayMan();
    cout << "  You lose." << endl << endl;
    cout << "Final Score: ";
    DisplayScore(GetCurrScore());
    cout << endl << endl;

    DisplayCurrScoreLocalRank(true); // display rank in high score list if it ranks //
    if( GetCurrScore() == GetBestHighScore() )
    {
      DisplayGlobalRank();
    }
    else
    {
      DisplayGlobalRank( GetCurrScore() );
    }
    cout << endl;
  }

  for ( auto it = solvedList.begin(); it < solvedList.end(); it++ )
  {
    cout << (*it) << endl;
  }
}

bool GameLogic::GameOver()
{
  // exhausted our max guess, game over
  if( m_FailedGuesses < m_cMaxFailedGuesses )
  {
    // player still has guesses remaining, check if all words are completed
    auto it2 = m_WordsToGuess.begin();
    for( const auto& it : m_PartialWord ) 
    {
      if( (*it2) != it )
      {
        return false;  // game not over, we have more guesses left and words to guess remaining 
      }

	  it2++;
    }
  }

  return true;
}

bool GameLogic::WonGame()
{
  if( m_bWonRound )
  {
    return m_bWonRound;
  }

  auto it2 = m_WordsToGuess.begin();
  for( const auto& it : m_PartialWord )
  {
    if( (*it2) == it )
    {
      m_bWonRound = true;
    }
	it2++;
  }

  return m_bWonRound;
}

int GameLogic::CalcBonus( int value )
{
  int newValue = value;

  if( m_bChallengeRound ) // double scoring round
  {
	  newValue *= 2;
  }

  if( m_FailedGuesses == 0 )
  {
    if( m_CorrectGuessesStreak >= 1 && m_CorrectGuessesStreak <= 2 )
    {
      newValue *= m_CorrectGuessesStreak+1; // double or triple letter score for the guessing correctly to start the game
      if( m_BonusExplanationStr.empty() )
      {
          m_BonusExplanationStr = string((m_CorrectGuessesStreak==1?"First Guess Double":"Second Guess Triple")) + " Multipler!";
      }
    }
  }

  if( m_CorrectGuessesStreak >= 3 )  // hot streak of correct guesses?
  {
    newValue *= m_CorrectGuessesStreak+1;
    if( m_BonusExplanationStr.empty() )
    {
      stringstream st;
      st << m_CorrectGuessesStreak+1;
      m_BonusExplanationStr = "Hot Steak " + st.str() + "x Multipler!";
    }
  }

  return newValue;
}

bool GameLogic::CheckGuess(char letter)
{
  auto ret = false;

  m_RoundLetterGuessed = letter;

  // check each word
  auto it2 = m_PartialWord.begin();
  for( const auto& it : m_WordsToGuess )
  {
    auto length = it.length();

    for( unsigned int j = 0; j < length; j++ )
    {
      if( it[j] == letter )
      {
        if( ret == false ) // add to consectutive guess streak
        {
          m_CorrectGuessesStreak++;
        }
        ret = true;
        (*it2)[j] = letter;
        AdjustScore( CalcBonus(m_LetterScore[letter]) );
        m_RoundLettersCorrect++;
      }
    }
    it2++;
  }

  if( ret == false )
  {
    m_CorrectGuessesStreak = 0; // streak broken!
    m_FailedGuesses++;
  }
  return ret;
}

void GameLogic::DisplayMan() // display the entire man, used for a losing game
{
  cout << m_VisualStand[0];
  if( m_bChallengeRound )
  {
	cout << "  ***  CHALLENGE ROUND!  ***";
  }

  cout << endl << m_VisualStand[1] << endl;

  for(int i = 0; i < m_cHeightOfMan; i++)
  {
    cout << m_VisualStand[i+2];

    // draw part or all of the man if needed
    if( m_FailedGuesses > 0 )
    {
      cout << m_VisualMan[m_FailedGuesses-1][i];
    }
      
     cout << endl;
  }

  cout << m_VisualStand[10];
}

void GameLogic::DisplayRoundResult()
{
  if( m_FailedGuesses > 0 || m_CorrectGuessesStreak > 0 ) // if round has occurred one of these values with be positive //
  {
    cout << "  ";

    if( m_RoundLettersCorrect > 0 )
    {
      cout << m_RoundLettersCorrect << " \"" << m_RoundLetterGuessed << (m_RoundLettersCorrect>1?"'s":"") 
             << "\" found. Bonus: +"; 
             
      DisplayScore(m_RoundScore); 
      cout << (m_BonusExplanationStr.empty()?"":" -- ") << m_BonusExplanationStr;
    }
    else
    {
      if( m_RoundLetterGuessed == ' ' )
      {
        cout << "Letter already guessed. Try another.";
      }
      else
      {
        cout << "Letter: \"" << m_RoundLetterGuessed << "\" not found.";
      }
    }

    InitRoundData();
  }
  cout << endl;
}

void GameLogic::InitRoundData()
{
   m_RoundLettersCorrect = 0;
   m_RoundLetterGuessed = ' ';
   m_RoundScore = 0;
   m_BonusExplanationStr.clear();
}

void GameLogic::AdjustHighScoreList( )
{
  if( m_CurrScore <= 0 )
  {
    return;
  }

  if( m_HighScores.size() >= m_cMaxHighScoreListSize ) // limit the size of the local high score list to a fixed amount
  {
    if(m_HighScores.back() < m_CurrScore ) // check the lowest score in our hi score list
    {
      m_HighScores.back() = m_CurrScore;
      m_HighScores.sort(std::greater<int>());
    }
  }
  else
  {
    m_HighScores.push_back(m_CurrScore);
    m_HighScores.sort(std::greater<int>());
  }
  if( m_BestHiScore < m_CurrScore )
  {
    SetBestHighScore( m_CurrScore );
    Network::SendNetHiScore( m_BestHiScore ); // update the global high score list, we might have a new personal high score
  }
}

void GameLogic::AdjustScore(int ScoreDelta)
{
  m_CurrScore += ScoreDelta;
  m_RoundScore += ScoreDelta;

  if( m_CurrScore < 0 )
  {
    m_CurrScore = 0;
  }
}

int GameLogic::GetCurrScore()
{
  return m_CurrScore;
}


void GameLogic::SaveConfig()
{
  if( m_XmlDocument )
  {
    TiXmlElement* elemScore = m_XmlDocument->FirstChildElement("hiscores");
    if( elemScore )
    {
      elemScore->Clear();
      stringstream temp;
      string tmpStr;

      int i = 1;
	  for( const auto& it : m_HighScores )
      {
        temp << 's' << i;
        tmpStr = temp.str();
        temp.clear();
        temp.str(std::string()); // clear buffer
 
        TiXmlElement* elemRank = elemScore->LinkEndChild( new TiXmlElement(tmpStr.c_str()) )->ToElement();

        // convert int value to string
        temp << it;
        tmpStr = temp.str();
        temp.clear();
        temp.str(std::string()); // clear buffer

        elemRank->LinkEndChild( new TiXmlText(tmpStr.c_str()) );
		i++;
      }
    }
    m_XmlDocument->SaveFile();
  }
}

void GameLogic::LoadConfig()
{
  char configFilename[] = "config.txt";

  delete m_XmlDocument;
  m_XmlDocument = nullptr;

	m_XmlDocument = new TiXmlDocument( configFilename );

  if( !m_XmlDocument )
  {		
    return;
  }

  bool bConfigFileCorrupted = false;

  if( m_XmlDocument->LoadFile() ) // if the file loaded correctly  
  {
    TiXmlNode * configNode = m_XmlDocument->FirstChild("config");
    if( configNode )
    {
      TiXmlNode * nodeHiScore = m_XmlDocument->FirstChild("hiscores");
      if( nodeHiScore )
      {
        if( nodeHiScore->FirstChild() )
        {
          for( auto it = nodeHiScore->FirstChild(); it != nullptr; it = it->NextSibling() )
          {
            string hiStr = it->FirstChild()->Value();
            stringstream strStream(hiStr);
            int intVal;
            strStream >> intVal;
            strStream.clear();
            strStream.str(std::string()); // clear buffer
            m_HighScores.push_back( intVal );
          }

          m_HighScores.sort(std::greater<int>());   // high score list should be loaded as sorted but do it again to make sure

//          if( m_HighScores.size() != cHighScoreSize )
//          {
//            bConfigFileCorrupted = true;
//          }
        }
      } // if hi score node
//      else
//      {
//        bConfigFileCorrupted = true;
//      }
    }
    else
    {
      bConfigFileCorrupted = true;
    }
  } // if loaded
  else
  {
      bConfigFileCorrupted = true;
  }


  if ( bConfigFileCorrupted )  // if file is missing or empty for some reason
  {
    delete m_XmlDocument;
    m_XmlDocument = nullptr;

    // config file is missing or corrupted, create it from scratch using our defaults //
	  m_XmlDocument = new TiXmlDocument( configFilename );
    
    // add xml version info to the first line //
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	  m_XmlDocument->LinkEndChild( decl );

    TiXmlElement* elemConfig = m_XmlDocument->LinkEndChild( new TiXmlElement("config") )->ToElement();
    TiXmlElement* elemScore = m_XmlDocument->LinkEndChild( new TiXmlElement("hiscores") )->ToElement();
	//stringstream temp;
	//string tmpStr;
	//int j = 1;
	//m_HighScores.clear();
	//for( int i = cHighScoreSize; i >= 1; i--, j++ ) // set default high scores
	//{
	//m_HighScores.push_back( i*10 ); // 2500 to 100

	//// create s# tag name
	//temp << 's' << j;
	//tmpStr = temp.str();
	//temp.clear();
	//temp.str(std::string()); // clear buffer
	//TiXmlElement* elemRank = elemScore->LinkEndChild( new TiXmlElement(tmpStr.c_str()) )->ToElement();

	//// convert int value to string
	//temp << m_HighScores.back();
	//tmpStr = temp.str();
	//temp.clear();
	//temp.str(std::string()); // clear buffer

	//elemRank->LinkEndChild( new TiXmlText(tmpStr.c_str()) );
	//}

	  m_XmlDocument->SaveFile();
  }
}

void GameLogic::DisplayScore(int ScoreToDisplay)
{
  stringstream temp;
  string DisplayStr;

  temp << ScoreToDisplay << (ScoreToDisplay ? "0" : ""); // add trailing zero character if value is not zero
  DisplayStr = temp.str();

  // add commas to score string
  for( int i = DisplayStr.length() - 3; i > 0; i -= 3 ) 
  {
      DisplayStr.insert(i, ",");
  }
  cout << DisplayStr;
}

void GameLogic::DisplayHighScores()
{
  if( !m_HighScores.empty() )
  {
    cout << "All-time High Score: ";
    DisplayScore( *(m_HighScores.begin()) );
    cout << endl;
  }
}

void GameLogic::DisplayGlobalRank(int Score /*=0*/)
{
  bool bTied;
  auto Rank = Network::QueryNetRank(bTied, Score); // passing in zero, will return best score on the server

  if( Rank > 0 )
  { 
    if( Score )
    {
      cout << "This score is "; 
    }
    else
    {
      cout << "Your best score is ";
    }
    cout << (bTied?"tied for ":"") << DisplayOrdinalString(Rank) << " in the world high score list.";
  }
}

void GameLogic::DisplayCurrScoreLocalRank(bool bActiveGame)
{
  auto i = 1;
  bool bFoundPosition = false;
  bool bTied = false;
  for(auto it = m_HighScores.begin(); it != m_HighScores.end(); it++, i++) // find our score in list (can't use a range based for loop here)
  {
     if( m_CurrScore >= (*it) )
     {
       bFoundPosition = true;
       
	   it++;
	   if( it != m_HighScores.end() && (*it) == m_CurrScore ) // check next score to see if we are tied with it
       {
          bTied = true;
       }

       break;
     }
  }

  if( bFoundPosition )
  {
    cout << "Your score is " << (bTied?"tied for ":"");

    cout << DisplayOrdinalString(i) << " in your high score list!" << endl;
  }
}

std::string GameLogic::DisplayOrdinalString(int value)
{
    stringstream place;
    place << value;

    switch( value % 10) // create ordinal string
    {
      case 1:  place << "st"; break; 
      case 2:  place << "nd"; break;
      case 3:  place << "rd"; break;
      default: place << "th"; break;
    }

    return place.str();
}

void GameLogic::SetBestHighScore( int NewScore )
{
  if( NewScore > 0 )
  {
    m_BestHiScore = NewScore;
  }
}
