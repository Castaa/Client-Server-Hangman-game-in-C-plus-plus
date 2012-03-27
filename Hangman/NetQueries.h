#pragma once

#include <vector>
#include <string>

// singleton class for game client messaging to/from the game server
class Network
{
  static std::string m_MACAddr;
  static bool m_bNetworkEnabled;

public:
  static void        SetMACAddress(void);
  static std::string GetMACAddress(void);

  static int  QueryNetRank(bool& bTied, int OfThisScore = 0 );
  static void QueryNetHiScores( std::vector<int>& netHiScores, int &rank );
  static void SendNetHiScore( int localHiScores );
  static int  QueryNetPersonalBestScore();
  static void ShutdownNetServer();
  static bool QueryVersion();
  static void SetNetworkStatus(bool bStatis);
  static bool GetNetworkStatus();
  static void DisplayVersion(unsigned int Version);
  static void DisplayNetworkStatus();
  static bool GetWordsToGuess(const int cWordsToGuess, std::vector<std::string>& wordsToGuess);
};