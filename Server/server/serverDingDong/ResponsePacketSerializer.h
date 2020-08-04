#pragma once
#include <iostream>
#include <vector>
#include "room.h"
/*
Messages From the server:

Login code - L
Signup code - S

respons data:
Success message code - 0
Error code - 1
*/

typedef struct loginRespons
{
	unsigned int status;
}loginResponse;

typedef struct signUpRespons
{
	unsigned int status;
}signUpResponse;

typedef struct errorResponse
{
	std::string message;
}errorResponse;

typedef struct logOutResponse
{
	unsigned int status;

}logOutResponse;

typedef struct getRoomsResponse
{
	unsigned int status;
	std::vector<room> rooms;

}getRoomsResponse;

typedef struct getPlayersInRoomResponse
{
	std::vector<std::string> players;

}getPlayersInRoomResponse;

typedef struct getStatisticsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;

}getStatisticsResponse;

typedef struct joinRoomResponse
{
	unsigned int status;

}JoinRoomResponse;

typedef struct createRoomResponse
{
	unsigned int status;

}createRoomResponse;

typedef struct HighScoreResponse
{
	unsigned int status;
	unsigned int score;
}HighScoreResponse;
class ResponsePacketSerializer
{
public:
	std::string serializeLoginResponse(loginRespons l);
	std::string serializeSignUpResponse(signUpRespons s);
	std::string serializeErrorResponse();
	std::string serializeLogoutResponse(logOutResponse l);
	std::string serializeGetRoomResponse(getRoomsResponse l);
	std::string serializeGetPlayersInRoomResponse(getPlayersInRoomResponse l);
	std::string serializeJoinRoomResponse(joinRoomResponse l);
	std::string serializeCreateRoomResponse(createRoomResponse l);
	std::string serializeHighScoreResponse(HighScoreResponse l);
	
};