#pragma once

// Basic Windows socket and communication class
class WinNet
{
public:
	WinNet();
	~WinNet();

	bool ConnectServerByName(const char *name, int port);
	bool ConnectToDefaultGameServer();
	void CloseServerConnection();
	int  SendDataToServer(const char* buffer, int size);
	int	 ReceiveDataFromServer(char*, int);

private:	
	const static unsigned	m_cPortNum;
	WSADATA					m_WSAData;
	SOCKET					m_Socket;
	SOCKET					m_SocketBackup;
	sockaddr_in				m_Connection;
	SOCKET					m_AcceptSocket;

//	bool ConnectServerByIP(char *ip, int port);
//	void fileSend(char*);
//	void fileReceive(char*);
//	void startServer(int);
//	void waitForClient();
};