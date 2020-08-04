#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"

class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:

	void accept();
	void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;
};
void client(SOCKET clientSocket);
void loginSend(SOCKET clientSocket, LoginRequestHandler lo, RequestInfo r);
void signUpSend(SOCKET clientSocket, LoginRequestHandler lo, RequestInfo r);
void logOutSend(SOCKET clientSocket);
void GetRoomsSend(SOCKET clientSocket);
void getPlayersInRoomSend(SOCKET clientSocket, RequestInfo r);
void joinRoomsend(SOCKET clientSocket, RequestInfo r);
void CreateRoomSend(SOCKET clientSocket, RequestInfo r, LoginRequestHandler lo);
void getRoomBeginSend(SOCKET clientSocket, RequestInfo r);
void startGameSend(SOCKET clientSocket, RequestInfo r);