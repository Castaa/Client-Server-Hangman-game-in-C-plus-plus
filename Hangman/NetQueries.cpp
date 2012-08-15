#include "stdafx.h"

#include <iphlpapi.h>
#include <iomanip>

#include "NetCode/wcomm.h"

using namespace std;

enum  { CL_REQ_HI_SCORE           = 1, 
        CL_SEND_SCORE             = 2,
        CL_REQ_HI_SCORE_LIST      = 3,
        CL_KILL_SERVER            = 4,
        CL_REQ_RANK               = 5,
        CL_REQ_RANK_OF_THIS_SCORE = 6,
        CL_VERSION_CHECK          = 7,
        CL_REQ_WORDS              = 8,
};

// upper 16 bits, major version, lower 16 bits minor version
const int CLIENT_VER = 0x00010001; 

string Network::m_MACAddr;
bool   Network::m_bNetworkEnabled;


int Network::QueryNetRank(bool& bTied, int OfThisScore /*=0*/)
{
  char buffer[1024] = "";
  int Rank = 0;
  
  bTied = false;

  WinNet network;
	// Connect To Server
  if( network.ConnectToDefaultGameServer() )
  {
	// Send Close Connection Signal

    int returnMessageSize; 

    if( OfThisScore <= 0 ) // request rank of best high score for player saved on the server
    {
      string ReqStr = static_cast<char>(CL_REQ_RANK) + Network::GetMACAddress();

	  network.SendDataToServer(ReqStr.c_str(), ReqStr.length());
      returnMessageSize = network.ReceiveDataFromServer(buffer, 1024);
    }
    else // request rank of another score
    {
      char Message[1024];
      int size = 0;
      
      Message[0] = static_cast<char>(CL_REQ_RANK_OF_THIS_SCORE);
      size += sizeof(char);

      int MACsize = Network::GetMACAddress().size();
      memcpy(&Message[size], Network::GetMACAddress().c_str(), MACsize );
      size += MACsize;
      
      memcpy( &Message[size], &OfThisScore, sizeof(OfThisScore));
      size += sizeof(OfThisScore);

      network.SendDataToServer( Message, size );
      returnMessageSize = network.ReceiveDataFromServer( buffer, 1024 );
    }

    memcpy(&Rank, buffer, sizeof(Rank));

    if( returnMessageSize >= sizeof(Rank) )
    {
      // Any additional non-zero value after the rank value return from the server means the score is tied in rank with another score
      bTied = buffer[sizeof(Rank)] > 0; 
    }

    network.CloseServerConnection();
  }

  return Rank; // zero means no rank
}

void Network::QueryNetHiScores( vector<int>& netHiScores, int &rank )
{
  char buffer[1024] = "";

  WinNet network;
  // Connect To game server
  if( network.ConnectToDefaultGameServer() )
  {
    string ReqStr = static_cast<char>(CL_REQ_HI_SCORE_LIST) + Network::GetMACAddress();
    
	network.SendDataToServer(ReqStr.c_str(), ReqStr.length());
    auto rsize = network.ReceiveDataFromServer(buffer, 1024);

    if( rsize >= sizeof(int) * 2 ) // return message should contain rank value and score(s)
    {
      char *ptr = buffer;
      memcpy(&rank, ptr, sizeof(rank));
      ptr += sizeof(rank);
      
      rsize -= sizeof(rank);

      for( int i = (rsize)/sizeof(int); i > 0; i--)
      {
        int tempScr;
        memcpy( &tempScr, ptr, sizeof(int));
        netHiScores.push_back(tempScr);
        ptr += sizeof(int);
      }
    }

    network.CloseServerConnection();
  }

  return;
}

// request from the  global server, the player's all-time recorded high score
int Network::QueryNetPersonalBestScore()
{
  WinNet network;
  char buffer[1024];
  int Score = 0;

  if( network.ConnectToDefaultGameServer() )
  {
    string ReqStr = static_cast<char>(CL_REQ_HI_SCORE) + Network::GetMACAddress();

    network.SendDataToServer( ReqStr.c_str(), ReqStr.length() ); // request my best high score in the global high sore list, if any

    int bytesRecv = network.ReceiveDataFromServer( buffer, 1024 );    // get score

    if( bytesRecv >= 4 )
    {
      memcpy( &Score, buffer, sizeof(Score) );
    }
    network.CloseServerConnection();
  }
     
  return Score;
}

void Network::SendNetHiScore(int localHiScore)
{
  WinNet network;
  int Score = 0;

  if( network.ConnectToDefaultGameServer()  )
  {                                                                  
    char ReqStr[1024];
    
    char* ptr = ReqStr;
    ReqStr[0]= static_cast<char>(CL_SEND_SCORE);
    ptr += sizeof(char);
    memcpy( ptr, Network::GetMACAddress().c_str(), Network::GetMACAddress().length() );
    ptr += Network::GetMACAddress().length();
    memcpy( ptr, &localHiScore, sizeof(localHiScore) );
    ptr += sizeof(localHiScore);

    network.SendDataToServer( ReqStr, ptr - ReqStr ); // request my best high score in the global high score list, if any
    network.CloseServerConnection();
  }
}

// Shutdown remote server -- an admin command only
void Network::ShutdownNetServer() 
{
  WinNet network;

  if( network.ConnectToDefaultGameServer()  )
  {                                                                  
	string ReqStr = static_cast<char>(CL_KILL_SERVER) + Network::GetMACAddress();

	network.SendDataToServer( ReqStr.c_str(), ReqStr.length() ); // request server shutdown
    network.CloseServerConnection();
  }
}


void Network::SetMACAddress()
{
  // Get the buffer length required for IP_ADAPTER_INFO.
  ULONG BufferLength = 0;
  BYTE* pBuffer = 0;
  if( ERROR_BUFFER_OVERFLOW == GetAdaptersInfo( 0, &BufferLength ))
  {
      // Now the BufferLength contain the required buffer length.
      // Allocate necessary buffer.
      pBuffer = new BYTE[ BufferLength ];
  }
  else
  {
      // Error occurred.
      SetNetworkStatus(false);
      return;
  }

  // Get the Adapter Information.
  PIP_ADAPTER_INFO pAdapterInfo =
        reinterpret_cast<PIP_ADAPTER_INFO>(pBuffer);
  GetAdaptersInfo( pAdapterInfo, &BufferLength );

  // Iterate the network adapters and print their MAC address.
  while( pAdapterInfo )
  {
      // Assuming pAdapterInfo->AddressLength is 6.

      //CString csMacAddress;
      //csMacAddress.Format(_T("%02x:%02x:%02x:%02x:%02x:%02x"),
      //                    pAdapterInfo->Address[0],
      //                    pAdapterInfo->Address[1],
      //                    pAdapterInfo->Address[2],
      //                    pAdapterInfo->Address[3],
      //                    pAdapterInfo->Address[4],
      //                    pAdapterInfo->Address[5]);
      
    if( strcmp( pAdapterInfo->IpAddressList.IpAddress.String, "0.0.0.0") ) // if adpapter has IP assigned, use that MAC Addr
    {
       stringstream temp;
       temp << hex << setfill('0') << setw(2)
#ifdef _DEBUG
          << static_cast<unsigned int>(rand() & 0xFF) << ":"
#else
          << static_cast<unsigned int>pAdapterInfo->Address[0] << ":"
#endif
          << static_cast<unsigned int>(pAdapterInfo->Address[1]) << ":"
          << static_cast<unsigned int>(pAdapterInfo->Address[2]) << ":"
          << static_cast<unsigned int>(pAdapterInfo->Address[3]) << ":"
          << static_cast<unsigned int>(pAdapterInfo->Address[4]) << ":"
          << static_cast<unsigned int>(pAdapterInfo->Address[5]);

       m_MACAddr = temp.str();

#ifdef _DEBUG
      //cout << "Adapter Name :" << pAdapterInfo->AdapterName << " "
      //    << "MAC :" << hex 
      //    << (unsigned int)pAdapterInfo->Address[0] << ":"
      //    << (unsigned int)pAdapterInfo->Address[1] << ":"
      //    << (unsigned int)pAdapterInfo->Address[2] << ":"
      //    << (unsigned int)pAdapterInfo->Address[3] << ":"
      //    << (unsigned int)pAdapterInfo->Address[4] << ":"
      //    << (unsigned int)pAdapterInfo->Address[5]
      //    << dec << " IP :" << 
      //    pAdapterInfo->IpAddressList.IpAddress.String << endl;
#endif
      break;
    }

    // Get next adapter info.
    pAdapterInfo = pAdapterInfo->Next;
  }

  if( m_MACAddr.empty() ) // if no MAC address, then no internet access
  {
    SetNetworkStatus(false);
  }
}

string Network::GetMACAddress(void)
{
  assert(!m_MACAddr.empty());

  return m_MACAddr;
}

bool Network::GetNetworkStatus()
{
  return m_bNetworkEnabled;
}

void Network::SetNetworkStatus(bool bStatis)
{
  m_bNetworkEnabled = bStatis;
}

bool Network::QueryVersion(void)
{
  WinNet network;

  if( network.ConnectToDefaultGameServer()  )
  {                                                                  
    char ReqStr[1024];
    
    char* ptr = ReqStr;
    ReqStr[0]= static_cast<char>(CL_VERSION_CHECK);
    ptr += sizeof(char);
    memcpy( ptr, Network::GetMACAddress().c_str(), Network::GetMACAddress().length());
    ptr += Network::GetMACAddress().length();

    unsigned int ClientVer = CLIENT_VER;
    memcpy( ptr, &ClientVer, sizeof(ClientVer) );
    ptr += sizeof(ClientVer);

    network.SendDataToServer( ReqStr, ptr - ReqStr ); // send client version

    int bytesRecv = network.ReceiveDataFromServer( ReqStr, 1024 );   // get version results

    unsigned int VersionReturned;
    if( bytesRecv >= sizeof(VersionReturned) )
    {
      memcpy( &VersionReturned, ReqStr, sizeof(VersionReturned) );
    }
    else
    {
      SetNetworkStatus(false);
      return false;
    }

    if( VersionReturned == 0 ) // client is too out of date for server
    {
      SetNetworkStatus(false);
      cout << "Client version is too out of date." << endl;;
    }
    else if( VersionReturned > CLIENT_VER )
    {
      SetNetworkStatus(true);

      cout << "New Client version exists: v";
      DisplayVersion(VersionReturned);
      cout << "  Download new version!" << endl;
    }
    else
    {
      SetNetworkStatus(true);
    }
  }
  else
  {  
    SetNetworkStatus(false);
  }

  return GetNetworkStatus();
}

void Network::DisplayVersion(unsigned int Version)
{
  unsigned int HiVer, LowVer;
  
  HiVer  = Version >> 16;
  LowVer = Version & 0x0000ffff; 

  cout << HiVer << "." << setfill('0') << setw(2)<< LowVer;
}

void Network::DisplayNetworkStatus()
{ 
  if( GetNetworkStatus() )
  {
    //cout << "Game server access not available." << endl;
  }
  else
  {
    cout << "Game server access NOT available!  Switching to local game mode." << endl;
  }

}


bool Network::GetWordsToGuess(const int cWordsToGuess, vector<string>& wordsToGuess)
{
  WinNet network;

  if( network.ConnectToDefaultGameServer() )
  {                                                                  
    char ReqStr[1024];
    
    char* ptr = ReqStr;
    ReqStr[0]= static_cast<char>(CL_REQ_WORDS);
    ptr += sizeof(char);
    
    memcpy( ptr, Network::GetMACAddress().c_str(), Network::GetMACAddress().length());
    ptr += Network::GetMACAddress().length();

    *ptr = static_cast<char>(cWordsToGuess);
    ptr += sizeof(char);


    network.SendDataToServer( ReqStr, ptr - ReqStr ); // send client version
    int bytesRecv = network.ReceiveDataFromServer( ReqStr, 1024 );   // get version results

    if( bytesRecv )
    {
      ptr = ReqStr;
      string tempStr;

      for(int i= 0; i < bytesRecv; i++, ptr++)
      {
        if( *ptr != '\0' )
        {
          tempStr.push_back(*ptr);
        }
        else
        {
          if( !tempStr.empty() )
          {
            wordsToGuess.push_back(tempStr);
            tempStr.clear();
          }
        }
      }      
    }
  }

  if( wordsToGuess.size() == cWordsToGuess ) // sanity check that we got the random dictoray words we requested //
  {
    return true;
  }

  return false;
}