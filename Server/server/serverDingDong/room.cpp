#include "room.h"
/*
constractor
*/
room::room(int room_num, std::string room_name)
{
	this->room_num = room_num;
	this->room_name = room_name;
	this->is_active = true;
	this->is_started = false;
	this->is_final = false;
}
/*
adding user to room
*/
void room::addUser(std::string player)
{
	this->players_in_room.push_back(player);
}

/*
removing user from room
*/
void room::removeUser(std::string player)
{

	for (std::vector<std::string>::iterator it = this->players_in_room.begin(); it != this->players_in_room.end(); ++it)
	{
		if (*it == player)
		{
			this->players_in_room.erase(it);
		}
	}
}

/*
getting all the users in the room
*/
std::vector<std::string> room::getAllUsers()
{
	return this->players_in_room;
}
/*
getting the room number
*/
unsigned int room::getRoomNum()
{
	return this->room_num;
}
/*
gietting the state of the room(active)
*/
bool room::getRoomState()
{
	return this->is_active;
}
/*
getting the room name
*/
std::string room::getRoomName()
{
	return this->room_name;
}
/*
getting question for a room
input: the db for the question
*/
std::string room::getQuestion(SqliteDataBase DB, bool is_3)
{
	if (is_3 == false)
	{

		if (this->switchQ % this->players_in_room.size() == 0)
		{
			bool b1 = false;
			while (b1 == false)
			{
				std::pair<std::string, std::string> p = DB.getQuestion1();
				bool b = false;
				for (std::set<std::string>::iterator iter = this->questions.begin(); iter != this->questions.end(); ++iter)
				{
					if (*iter == p.first) //same question
					{
						b = true;
					}
				}
				if (!b)
				{
					this->question = p.first;
					this->answer = p.second;
					this->questions.insert(p.first);
					b1 = true;
				}
			}

		}
		this->switchQ++;
	}
	else
	{
		bool b1 = false;
		while (b1 == false)
		{
			std::pair<std::string, std::string> p = DB.getQuestion1();
			bool b = false;
			for (std::set<std::string>::iterator iter = this->questions.begin(); iter != this->questions.end(); ++iter)
			{
				if (*iter == p.first) //same question
				{
					b = true;
				}
			}
			if (!b)
			{
				this->question = p.first;
				this->answer = p.second;
				this->questions.insert(p.first);
				b1 = true;
			}
		}
	}
	return this->question;
}
/*
getting answer
*/
std::string room::getAns()
{
	return this->answer;
}

/*
getting questions for level 2 of the game
*/
std::string room::getQuestion2(SqliteDataBase DB)
{
	if (this->switchQ % this->players_in_room.size() == 0)
	{
		std::pair<std::string, std::string> p = DB.getQuestion2();
		this->question = p.first;
		this->answer = p.second;
	}
	this->switchQ++;

	return this->question;
}


/*
creating a new room with a room name(param)
*/
void roomManager::createRoom(std::string roomName)
{
	this->number_of_rooms++;
	room newRoom(this->number_of_rooms, roomName);
	newRoom.is_final = false;
	this->activate_rooms.push_back(newRoom);

}
/*
deleting room from the room list
*/
void roomManager::deleteRoom(int room_num)
{
	for (std::vector<room>::iterator it = this->activate_rooms.begin(); it != this->activate_rooms.end(); ++it)
	{
		if (it->getRoomNum() == room_num)
		{
			this->activate_rooms.erase(it);
			break;
		}
	}
}
/*
getting the room activation state
*/
bool roomManager::getRoomState(int room_num)
{
	for (std::vector<room>::iterator it = this->activate_rooms.begin(); it != this->activate_rooms.end(); ++it)
	{
		if (it->getRoomNum() == room_num)
		{
			return it->getRoomState();
		}
	}
	return false;
}
/*
getting all the active rooms
*/
std::vector<room> roomManager::getActiveRooms()
{
	return this->activate_rooms;
}
/*
adding player to the room
*/
bool roomManager::addPlayerToRoom(std::string roomName, std::string player)
{
	int j = -1;
	
	for (int i = 0; i < this->activate_rooms.size(); i++)
	{
		if (this->activate_rooms.at(i).getRoomName() == roomName)
		{
			if (!(this->activate_rooms.at(i).getAllUsers().size() >= MAX_NUM_OF_USERS_IN_ROOM))
			{
				this->activate_rooms.at(i).addUser(player);
				j = 1;
			}
		}
	}
	if (j == -1)
	{
		return false;
	}
	return true;
}
