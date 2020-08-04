#include "ResponsePacketSerializer.h"
#include <iostream>
#include <string>

/*
the function getting the status of the login response and creating a msg to send to client
input: the status
output: the full msg
*/
std::string ResponsePacketSerializer::serializeLoginResponse(loginRespons l)
{
	std::string all = "";
	std::string part = "";
	
	all = all + "L"; //the letter L(login message)
	all = all + "1"; //size of the msg.(alwayse 8 because its alwayse 0 or 1).
	
	if (l.status == 0) //is success
	{
		all = all + "0"; //0 in binary
	}
	else //error occured
	{
		all = all + "1"; //1 in binary
	}
	
	return all;
}

/*
the function getting the status of the login response and creating a msg to send to client
input: the status
output: the full msg
*/

std::string ResponsePacketSerializer::serializeSignUpResponse(signUpRespons s)
{
	std::string all = "";
	std::string part = "";

	all = all + "S"; //the letter S(signUp message)
	all = all + "1"; //size of the msg.(alwayse 8 because its alwayse 0 or 1).

	if (s.status == 0) //is success
	{
		all = all + "0"; //0 in binary
	}
	else //error occured
	{
		all = all + "1"; //1 in binary
	}

	return all;
	
}

std::string ResponsePacketSerializer::serializeErrorResponse()
{
	return std::string();
}

std::string ResponsePacketSerializer::serializeLogoutResponse(logOutResponse l)
{
	std::string all = "";
	std::string part = "";

	all = all + "O"; //the letter O(sign out message)
	all = all + "1"; //size of the msg.(alwayse 8 because its alwayse 0 or 1).

	if (l.status == 0) //is success
	{
		all = all + "0"; //0 in binary
	}
	else //error occured
	{
		all = all + "1"; //1 in binary
	}

	return all;
}

std::string ResponsePacketSerializer::serializeGetRoomResponse(getRoomsResponse l)
{
	std::string all = "";
	std::string part = "";

	all = all + "R"; //the letter R(get rooms message)
	

	if (l.status == 0) //is success
	{
		for (int i = 0; i < l.rooms.size(); i++)
		{
			part = part + '`';
			part = part + l.rooms.at(i).getRoomName();
		}
		int s = part.size();
		std::string s1 = std::to_string(s);
		all = all + s1; //the size
		all = all + part; //the data itself
	}
	else //error occured
	{
		all = all + "1"; //size of msg
		all = all + "1"; //1 in binary
	}

	return all;
}

std::string ResponsePacketSerializer::serializeGetPlayersInRoomResponse(getPlayersInRoomResponse l)
{
	std::string all = "";
	std::string part = "";

	all = all + "P"; //the letter R(get rooms message)

	for (int i = 0; i < l.players.size(); i++)
	{
		part = part + '`';
		part = part + l.players.at(i);
	}
	int s = part.size();
	std::string s1 = std::to_string(s);
	all = all + s1; //the size
	all = all + part; //the data itself



	return all;
}

std::string ResponsePacketSerializer::serializeJoinRoomResponse(joinRoomResponse l)
{
	std::string all = "";
	std::string part = "";

	all = all + "J"; //the letter J(join room message)
	all = all + "1"; //size of the msg.(alwayse 8 because its alwayse 0 or 1).
	
	if (l.status == 0) //is success
	{
		all = all + "0"; //0 in binary
	}
	else //error occured
	{
		all = all + "1"; //1 in binary
	}
	
	return all;
}

std::string ResponsePacketSerializer::serializeCreateRoomResponse(createRoomResponse l)
{
	std::string all = "";
	std::string part = "";

	all = all + "C"; //the letter C(create room message)
	all = all + "1"; //size of the msg.(alwayse 8 because its alwayse 0 or 1).
	
	if (l.status == 0) //is success
	{
		all = all + "0"; //0 in binary
	}
	else //error occured
	{
		all = all + "1"; //1 in binary
	}

	return all;
}

std::string ResponsePacketSerializer::serializeHighScoreResponse(HighScoreResponse l)
{
	std::string all = "";
	std::string part = "";

	all = all + "H"; //the letter C(create room message)

	if (l.status == 0) //is success
	{
		part = std::to_string(l.score);
		int size = part.size();
		all = all + std::to_string(size) + part;
	}
	else //error occured
	{
		all = all + "11"; //1 in binary
	}

	return all;
}
