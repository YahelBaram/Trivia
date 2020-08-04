#pragma once
#include <iostream>

typedef struct RequestInfo
{
	char code;
	unsigned int time;
	std::string BData;
}RequestInfo;

typedef struct Login
{
	std::string name;
	std::string pass;
}Login;

typedef struct SignUp
{
	std::string name;
	std::string pass;
	std::string email;
}SignUp;

typedef struct getPlayersInRoomRequest
{
	unsigned int roomId;

}getPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;

}JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;

}CreateRoomRequest;

class IRequestHandler
{

};

class LoginRequestHandler : virtual public IRequestHandler
{
public:
	/*
		function that checking if it's a real message
		input: the message
		output: a success or error code
	*/
	short isRequestRelevant(RequestInfo message);
	/*
		function that creating a login struct
		input: the message
		output: struct with the data
	*/
	Login getLogin(std::string message);
	/*
		function that creating a signup struct
		input: the message
		output: struct with the data
	*/
	SignUp getSignUp(std::string message);
	
	getPlayersInRoomRequest deserializeGetPlayersInRoomRequest(int roomId);
	JoinRoomRequest deserializeJoinRoomRequest(int roomId);
	CreateRoomRequest deserializeCreateRoomRequest(std::string message);
};