#include "IRequestHandler.h"

short LoginRequestHandler::isRequestRelevant(RequestInfo message)
{
	if (message.BData.find("L") == 0) // for login message
	{
		return 1;
	}
	else if (message.BData.find("S") == 0) // for signup request
	{
		return 2;
	}
	else if (message.BData.find("O") == 0) //logout
	{
		return 3;
	}
	else if (message.BData.find("R") == 0) //get all rooms
	{
		return 4;
	}
	else if (message.BData.find("P") == 0) //get players in specific room
	{
		return 5;
	}
	else if (message.BData.find("J") == 0) //join room
	{
		return 6;
	}
	else if (message.BData.find("C") == 0) //create room
	{
		return 7;
	}
	else if (message.BData.find("H") == 0) //get high score
	{
		return 8;
	}
	else if (message.BData.find("T") == 0)
	{
		return 9;
	}
	else if (message.BData.find("K") == 0)
	{
		return 10;
	}
	else if (message.BData.find("Q") == 0)
	{
		return 11;
	}
	else if (message.BData.find("A") == 0)
	{
		return 12;
	}
	else if (message.BData.find("B") == 0)
	{
		return 13;
	}
	else if (message.BData.find("N") == 0)
	{
		return 14;
	}
	else if (message.BData.find("D") == 0)
	{
		return 15;
	}
	else if (message.BData.find("I") == 0)
	{
		return 16;
	}
	else if (message.BData.find("Z") == 0)
	{
		return 17;
	}
	return 0;
}
/*
getting the login message to send to the client
*/
Login LoginRequestHandler::getLogin(std::string message)
{
	RequestInfo req;
	Login login;
	req.BData = message;

	if (isRequestRelevant(req) == 1) // if it's a login request
	{
		std::string sLen;
		unsigned short len = 0;
		int i = 0;
		short part = 0;

		for (i = 1; i < message.length(); i++) // this loop will get the length of the message
		{
			if (message[i] != '`') // if it's not the end of the length part
			{
				sLen = sLen + message[i];
			}
			else
			{
				break; // stopping the loop
			}
		}
		len = atoi(sLen.c_str()); // getting the number as an int

		for (int j = 0; j < len - 1; j++) // this loop will get the data of the message
		{
			i++;
			if (message[i] != '`') // if it's not an end of a section
			{
				if (part == 0) // the first part is username
				{
					login.name = login.name + message[i];
				}
				else if (part == 1) // the second part is password
				{
					login.pass = login.pass + message[i];
				}
				else // stopping the loop
				{
					i = len + 1;
				}
			}
			else
			{
				part++;
			}
		}
	}

	return login;
}
/*
sign up request
*/
SignUp LoginRequestHandler::getSignUp(std::string message)
{
	RequestInfo req;
	SignUp signup;
	req.BData = message;

	if (isRequestRelevant(req) == 2) // if it's a login request
	{
		std::string sLen;
		unsigned short len = 0;
		int i = 0;
		short part = 0;

		for (i = 1; i < message.length(); i++) // this loop will get the length of the message
		{
			if (message[i] != '`') // if it's not the end of the length part
			{
				sLen = sLen + message[i];
			}
			else
			{
				break; // stopping the loop
			}
		}
		len = atoi(sLen.c_str()); // getting the number as an int

		for (int j = 0; j < len - 1; j++) // this loop will get the data of the message
		{
			i++;
			if (message[i] != '`') // if it's not an end of a section
			{
				if (part == 0) // the first part is username
				{
					signup.name = signup.name + message[i];
				}
				else if (part == 1) // the second part is password
				{
					signup.pass = signup.pass + message[i];
				}
				else if (part == 2) // the third part is email
				{
					signup.email = signup.email + message[i];
				}
				else
				{
					i = len + 1;
				}
			}
			else
			{
				part++;
			}
		}
	}

	return signup;
}

getPlayersInRoomRequest LoginRequestHandler::deserializeGetPlayersInRoomRequest(int roomId)
{
	getPlayersInRoomRequest g;
	g.roomId = roomId;
	return g;
}

JoinRoomRequest LoginRequestHandler::deserializeJoinRoomRequest(int roomId)
{
	JoinRoomRequest j;
	j.roomId = roomId;
	return j;
}

CreateRoomRequest LoginRequestHandler::deserializeCreateRoomRequest(std::string message)
{
	CreateRoomRequest c;
	int i = message.find("`");
	std::string s;
	char c1 = ' ';
	for (int j = 1; c1 != '`'; j++)
	{
		s = s + message[j];
		c1 = message[j + 1];
	}
	int size = atoi(s.c_str());
	std::string roomName;
	for (int j = 0; j < size; j++)
	{
		i++;
		roomName = roomName + message[i];
	}
	c.roomName = roomName;
	return c;
}
