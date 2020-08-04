#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "IDatabase.h"
#define MAX_NUM_OF_USERS_IN_ROOM 3
#define TIME_FOR_QUESTION 10

class room
{
private:
	unsigned int room_num;
	std::string room_name;

	int switchQ = 0;
	std::string question;
	std::string answer;
	std::set<std::string> questions;

public:
	std::vector<std::string>players_in_room;
	bool is_final = false;
	bool is_started;
	bool is_active;
	std::set<int> s;
	room(int room_num, std::string room_name);
	void addUser(std::string player);
	void removeUser(std::string player);
	std::vector<std::string> getAllUsers();
	unsigned int getRoomNum();
	bool getRoomState();
	std::string getRoomName();
	std::string getQuestion(SqliteDataBase DB, bool is_3);
	std::string getAns();
	std::string getQuestion2(SqliteDataBase DB);
};

class roomManager
{
private:
	unsigned int number_of_rooms;

public:
	std::vector<room> activate_rooms;

	void createRoom(std::string roomName);
	void deleteRoom(int room_num);
	bool getRoomState(int room_num);
	std::vector<room> getActiveRooms();
	bool addPlayerToRoom(std::string roomName, std::string player);
};
