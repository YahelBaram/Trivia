#pragma once

#include "IRequestHandler.h"
#include "sqlite3.h"
#include <iostream>
#include <io.h>
#include <string>
#include <vector>

int callback(void* data, int argc, char** argv, char** azColName);
int AVGBack(void* data, int argc, char** argv, char** azColName);
int corrAns(void* data, int argc, char** argv, char** azColName);
int allAns(void* data, int argc, char** argv, char** azColName);
int allGames(void* data, int argc, char** argv, char** azColName);
int wins(void* data, int argc, char** argv, char** azColName);
int best5(void* data, int argc, char** argv, char** azColName);
int quest1(void* data, int argc, char** argv, char** azColName);
int count(void* data, int argc, char** argv, char** azColName);

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool open() = 0;
	virtual bool addUser(SignUp user) = 0;
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(Login user) = 0;
	virtual bool ask(char* state) = 0;
	virtual int getNumOfCorrectAnswers(std::string name) = 0;
	virtual int getNumOfTotalAnswers(std::string name) = 0;
	virtual int getNumOfPlayerGames(std::string name) = 0;
	virtual int getNumOfPlayerWins(std::string name) = 0;
	virtual std::vector<std::string> getBestData() = 0;
	virtual sqlite3* get_db() = 0;
	virtual std::pair<std::string, std::string> getQuestion1() = 0;
	virtual std::pair<std::string, std::string> getQuestion2() = 0;
	virtual void printAllAns() = 0;
	virtual void countQuestions() = 0;
};

class SqliteDataBase : virtual public IDatabase
{
public:
	virtual bool open();
	virtual bool addUser(SignUp user);
	virtual bool doesUserExist(std::string username);
	virtual bool doesPasswordMatch(Login user);
	virtual bool ask(char* state);
	virtual int getNumOfCorrectAnswers(std::string name);
	virtual int getNumOfTotalAnswers(std::string name);
	virtual int getNumOfPlayerGames(std::string name);
	virtual int getNumOfPlayerWins(std::string name);
	virtual std::vector<std::string> getBestData();
	virtual sqlite3* get_db();
	virtual std::pair<std::string, std::string> getQuestion1();
	virtual std::pair<std::string, std::string> getQuestion2();
	virtual void printAllAns();
	virtual void countQuestions();
	sqlite3* db;
};

class statistics
{
public:
	statistics(SqliteDataBase DB);
	~statistics() = default;

	std::string getPersonalData(std::string username);
	std::string getBest5();
	void addStatistics(std::string username, int cAns, bool isWin, bool isEnd);
private:
	SqliteDataBase DB;
};