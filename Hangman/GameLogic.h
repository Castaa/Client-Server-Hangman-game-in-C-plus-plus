// GameLogic.h

#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>

class GameLogic
{
private:
	enum RoundMode { eSINGLE_WORD, eDOUBLE_WORD  };

	std::vector<const std::string>			m_Dictionary;
	std::string								m_GuessList;
	std::vector<std::string>				m_WordsToGuess;
	std::vector<std::string>				m_PartialWord;
	std::vector<std::string>				m_VisualStand;
	std::vector<std::vector<std::string>>	m_VisualMan;
	static const int						m_cMaxHighScoreListSize;
	static const int						m_cMaxFailedGuesses;
	static const int						m_cHeightOfMan;
	int										m_FailedGuesses;
	int										m_CorrectGuessesStreak;
	bool									m_bWonRound;
	int										m_CurrScore;
	int										m_BestHiScore;
	std::list<int>							m_HighScores;
	int										m_RoundLettersCorrect;
	int										m_RoundScore;
	int										m_RoundNum;
	bool									m_bChallengeRound;
	char									m_RoundLetterGuessed;
	std::string								m_BonusExplanationStr;
	std::map<char, int>						m_LetterScore;
	TiXmlDocument*							m_XmlDocument;


public:
    GameLogic();
    ~GameLogic()
    {
      delete m_XmlDocument;
    }

    void InitRoundData();
    void InitGuessList();
    void NewRound();
    void DisplayGuessList();
    bool AddLetterToGuessList(char& letter);
    bool CheckGuess(char letter);
    void InitPartialWord();
    void DisplayPartialWord();
    void DisplayGameResults();
    void DisplayMan();
    void DisplayScore(int ScoreToDisplay);
    void DisplayHighScores();
    void DisplayRoundResult();
    void DisplayGlobalRank(int Score = 0);
    void DisplayCurrScoreLocalRank(bool bActiveGame);
    std::string DisplayOrdinalString(int value);

    void AdjustHighScoreList();
    void AdjustScore(int ScoreDelta);
    void SetBestHighScore( int NewScore );
    int  GetBestHighScore() { return m_BestHiScore; }
    int  CalcBonus(int value);
    int  GetCurrScore();
    bool WonGame();

    void SaveConfig();
    void LoadConfig();

    bool GameOver();
};