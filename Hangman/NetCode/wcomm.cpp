#include <iostream>
#include <fstream>
#include <sstream>
#include <winsock2.h>
#include <iphlpapi.h> 

#include "wcomm.h"
#include "../NetQueries.h"

using namespace std;

const unsigned WinNet::m_cPortNum = 20003;

WinNet::WinNet()
{
  // Initialize Winsock.
  int iResult = WSAStartup( MAKEWORD(2,2), &m_WSAData );
  if( iResult != NO_ERROR )
  {
      cout << "Error at WSAStartup()" << endl;
  }

  // Create a socket.
  m_Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

  if ( m_Socket == INVALID_SOCKET ) 
  {
      cout << "Error at socket(): " << WSAGetLastError() << endl;
      WSACleanup();
      return;
  }
  
  m_SocketBackup = m_Socket;
}

WinNet::~WinNet()
{
  WSACleanup();
}


bool WinNet::ConnectToDefaultGameServer()
{
  if( !Network::GetNetworkStatus() )
  { 
    return false; 
  }

  return ConnectServerByName(
    "localhost", // localhost is the hangman server running in cygwin, you can be changed to a URL like an ec2 instance

    m_cPortNum ); // port 20003

  //return ConnectServerByIP("192.168.0.1", m_cPortNum) // alternative, connect to server via its IP address

}


bool WinNet::ConnectServerByName(const string& name, int port)
{
	// Store information about the server
	LPHOSTENT hostEntry;

	hostEntry = gethostbyname( name.c_str() );	// Specifying the server by its name;

	if( !hostEntry ) 
	{
		WSACleanup();
		return false;
	}

	// Fill a SOCKADDR_IN struct with address information
	SOCKADDR_IN serverInfo;

	serverInfo.sin_family = AF_INET;

	// At this point, we've successfully retrieved vital information about the server,
	// including its hostname, aliases, and IP addresses.

	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons((u_short)port);		// Change to network-byte order and insert into port field

	int nret;
	// Connect to the server
	nret = connect( m_Socket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr) );

	if (nret == SOCKET_ERROR) 
	{
		WSACleanup();
		return false;
	}

	return true;
}


int WinNet::SendDataToServer(const char *sendbuf, int size)
{
	return send( m_Socket, sendbuf, size, 0 );
}


int WinNet::ReceiveDataFromServer(char *recvbuf, int size)
{
	int sz = recv( m_Socket, recvbuf, size, 0 );
	recvbuf[sz] = '\0';
	return sz;
}


void WinNet::CloseServerConnection()
{
	closesocket(m_Socket);
	m_Socket = m_SocketBackup;
}

/*
void WinNet::fileReceive(char *filename)
{
	char rec[50] = "";
			
	recv( m_socket, filename, 32, 0 );
	send( m_socket, "OK", strlen("OK"), 0 );

	FILE *fw; 
	fopen_s(&fw, filename, "wb");

	int recs = recv( m_socket, rec, 32, 0 );
	send( m_socket, "OK", strlen("OK"), 0 );

	rec[recs]='\0';
	int size = atoi(rec);
				
	while(size > 0)
	{
		char buffer[1030];

		if(size>=1024)
		{
			recv( m_socket, buffer, 1024, 0 );
			send( m_socket, "OK", strlen("OK"), 0 );
			fwrite(buffer, 1024, 1, fw);

		}
		else
		{
			recv( m_socket, buffer, size, 0 );
			send( m_socket, "OK", strlen("OK"), 0 );
			buffer[size]='\0';
			fwrite(buffer, size, 1, fw);
		}

		size -= 1024;
	}

	fclose(fw);

}
*/

/*
void WinNet::fileSend(char *fpath)
{

	// Extract only filename from given path.
	char filename[50];
	int i=strlen(fpath);
	for(;i>0;i--)if(fpath[i-1]=='\\')break;
	for(int j=0;i<=(int)strlen(fpath);i++)filename[j++]=fpath[i];
	////////////////////////////////////////

	ifstream myFile (fpath, ios::in|ios::binary|ios::ate);
	int size = (int)myFile.tellg();
	myFile.close();

	char filesize[10];
	//_itoa(size, filesize,10);
	_itoa_s(size, filesize, 10, 10);

	send( m_socket, filename, strlen(filename), 0 );
	char rec[32] = "";recv( m_socket, rec, 32, 0 );

	send( m_socket, filesize, strlen(filesize), 0 );
	recv( m_socket, rec, 32, 0 );

	
	FILE *fr; 
	fopen_s(&fr, fpath, "rb");

	while(size > 0)
	{
		char buffer[1030];

		if(size>=1024)
		{
			fread(buffer, 1024, 1, fr);
			send( m_socket, buffer, 1024, 0 );
			recv( m_socket, rec, 32, 0 );

		}
		else
		{
			fread(buffer, size, 1, fr);
			buffer[size]='\0';
			send( m_socket, buffer, size, 0 );
			recv( m_socket, rec, 32, 0 );
		}


		size -= 1024;

	}

	fclose(fr);

}
*/

/*
void WinNet::startServer(int port)
{
    // Connect to a server.
    con.sin_family = AF_INET;
    con.sin_addr.s_addr = inet_addr( "0.0.0.0" );
    con.sin_port = htons( port );

    if ( bind( m_socket, (SOCKADDR*) &con, sizeof(con) ) == SOCKET_ERROR) {
        printf( "Failed to connect.\n" );
        WSACleanup();
        return;
    }

    // Listen on the socket.
    if ( listen( m_socket, 1 ) == SOCKET_ERROR )
        printf( "Error listening on socket.\n");

}
*/
/*
void WinNet::waitForClient()
{
		AcceptSocket = SOCKET_ERROR;
        while ( AcceptSocket == SOCKET_ERROR ) {
            AcceptSocket = accept( m_backup, nullptr, nullptr );
        }
        m_socket = AcceptSocket;
}
*/
/*
bool WinNet::ConnectServerByIP(char *ip, int port)
{
    // Connect to a server.
    m_Connection.sin_family = AF_INET;
    m_Connection.sin_addr.s_addr = inet_addr( ip );
    m_Connection.sin_port = htons( port );

    if( connect( m_Socket, (SOCKADDR*) &m_Connection, sizeof(m_Connection) ) == SOCKET_ERROR) 
	{
        cout << "Failed to connect." << endl;
        WSACleanup();
        return false;
    }

    return true;
}
*/