#include "IDatabase.h"
#include <time.h>

std::string gUsername;
bool gFound = false;
std::string GBack;
std::vector<std::string> bestData;
std::pair<std::string, std::string> Gpair;

int c = 1;
int gCAns = 0;
int gAns = 0;
int gNumOfWins = 0;
/*
openning the database or creating a new one
*/
bool SqliteDataBase::open()
{
	std::string dbFileName = "DingDong.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db); // open/create a DB for the program

	if (res != SQLITE_OK)
	{
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	if (doesFileExist == -1) // if there is a new DB, this part will add the tables and questions it needs
	{
		char* sqlStatement = (char*)"CREATE TABLE USERS (USERNAME TEXT PRIMARY KEY,PASSWORD TEXT, EMAIL TEXT);";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)"CREATE TABLE QUESTIONS1 (ID INTEGER PRIMARY KEY,QUESTION TEXT, ANSWER TEXT);";
		res = this->ask(sqlStatement);

		char String[] = u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(1, '��� ����� �� ��������? `�.���� ����`�.����`�.�� ������`�.����', '�.���� ����');";
		sqlStatement = String;
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(2, '��� ����� ������� �� 680 ���? `�.450`�.784`�.128`�.824', '�.824');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(3, '�� ��� ����� �� ������� �� ��������? `�.��� �������`�.���� ��������`�.������ ��������`�.���� �������', '�.������ ��������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(4, '��� ������ �� ������ �� 450 ���? `�.21`�.27`�.66`�.32', '�.27');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(5, '�� ���� ���� ������ �� ������� ����� ����� ���� ����? `�.����� ����`�.��� ���`�.�� ����`�.�^�� ����', '�.�^�� ����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(6, '���� ����� ������ ��� ���� �����? `�.��������`�.�����`�.���`�.�����', '�.��������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(7, '���� ��� ���� ���� � �������? `�.��`�.����� �� �����`�.�����`�.������', '�.����� �� �����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(8, '��� �� �� ����� ��� ��� ���� ��� ��? `�.���`�.��������`�.������`�.�����', '�.������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(9, '���� ���� ���� ������ ������ ����� ��� ������? `�.���� �������������`�.���� �������`�.���� ����������`�.���� ��������', '�.���� �������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(10, '��� ����� ����� ����? `�.������ ���������`�.������ ��������`�.������ ����������`�.�������', '�.�������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(11, '��� ����� ��� ����� ������ ����? `�.����`�.�����`�.���`�.�����', '�.����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(12, '���� ����� ������ ��� ���� �����? `�.�����`�.�����`�.������`�.������', '�.�����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(13, '���� ���� �������� ������ �� ���������? `�.������`�.����`�.�����`�.��������', '�.������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(14, '��� ����� ����� ����� ����? `�.���� ���`�.�����`�.����`�.�����', '�.����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(15, '��� ����� �� ����� ����� ����� ����� ������? `�.52`�.51`�.49`�.50', '�.51');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(16, '��� ���� �������? `�.����� �� ��� ����`�.����� ������ ����`�.����� �� ��� ������ ��������`�.���� ������� ������ ������ ������', '�.���� ������� ������ ������ ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(17, '�� �� ���������? `�.��� ��� ������`�.��� ������`�.��� ������ ������`�.��� ������', '�.��� ��� ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(18, '��� ���� ������ ����� �����? `�.9`�.10`�.11`�.12', '�.12');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(19, '������ ���� �� ���� ����, ��� ���� ���� ���� ����? `�.6`�.12`�.18`�.24', '�.6');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(20, '��� ���� ������ �� �����? `�.1000`�.6860`�.7500`�.10020', '�.7500');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(21, '���� ���� ��� ������ ���� �� ����� ������? `�.����� ���������`�.������ ����`�.����� �������`�. ����� ������', '�.����� ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(22, '��� ���� ���� ������ ����� (��������) ��� ����� ���� �����? `�.10`�.11`�.12`�.13', '�.10');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(23, '���� ��� ���� ����� ���� �� ��� ��� ���? `�.����`�.���`�.�����`�.���', '�.���');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(24, '����� ��� ����� ��� ��� ������ ������? `�.�����`�.���`�.�����`�.���', '�.���');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(25, '��� ����� ����� �����? `�.����`�.������ ���������`�.�����`�.������', '�.����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(26, '�� ��� 1996 ��� ������� ���� ���� ���� �������? `�.500 ������`�.10 �����`�.�������`�.250 ������', '�.�������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(27, '����� ����� ��� ����� �����? `�.������`�.����`�.�����`�.�������', '�.�����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(28, '�� ��� ������ ����� ����� �� ����� ������ ������? `�.�����`�.�����`�.����`�.������', '�.�����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(29, '��� ���� ������ �� ����� ������? `�.8`�.9`�.10`�.11', '�.11');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(30, '���� ����� �� ������, ���� ���� ������ ����? `�.����`�.������`�.�����`�.�����', '�.������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)"CREATE TABLE QUESTIONS2 (ID INTEGER PRIMARY KEY,QUESTION TEXT, ANSWER TEXT);";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(1, '����� ������ �����:�._._._-_._._._-_._._._._-_._._._._-_._._._-_._._._-_._._._._._.�', '��� ���� ����� ����� ���� ���� �������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(2, '����� �����:�._._._._._._-_._._._._._-_._._.�', '������ ������ ����' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(3, '����:�._._._._._._.�', '�������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(4, '������:�._._._._-_._._._._._-_._._._._.�', '���� ������ ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(5, '��� �����:�._._._._._-_._._._-_._._._._.�', '����� ���� ������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(6, '���� ���:�._-_._._._-_.^._._._-_._._.�','�� ��� �^��� ����' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(7, '��� ����:�._._._._-_._._._._-_._._-_._._._._.�', '���� ����� ��� ������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(8, '������ ���:�._._._._._._._-_._._._._-_._._._._._.�', '������� ����� �������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(9, '����� �������:�._._._-_._._._._-_._._._._-_._.�', '��� ����� ����� ���' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(10, '���� �����:�._._._._._-_._._._-_._._.�', '����� ���� ����' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"CREATE TABLE STATISTICS (USERNAME TEXT PRIMARY KEY, NUMOFCORRANS INTEGER, NUMOFANS INTEGER, NUMOFGAMES INTEGER, NUMOFWINS INTEGER);";
		res = this->ask(sqlStatement);
	}
	return true;
}



/*
adding user to the database(getting the user as a param)
*/
bool SqliteDataBase::addUser(SignUp user)
{
	std::string sqlStatement = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES( '" + user.name + "', '" + user.pass + "', '" + user.email + "');";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage); // creating the table
	if (res != SQLITE_OK)
	{
		return false;
	}
	sqlStatement = "INSERT INTO STATISTICS (USERNAME, NUMOFCORRANS, NUMOFANS, NUMOFGAMES, NUMOFWINS) VALUES( '" + user.name + "', " + '0' + ", " + '0' + ", " + '0' + ", " + '0' + ");";
	errMessage = nullptr;
	res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage); // creating the table
	if (res != SQLITE_OK)
	{
		return false;
	}
	return true;
}
/*
checking if the user exist
*/
bool SqliteDataBase::doesUserExist(std::string username)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE USERNAME = '" + username + "';";
	char* errMessage = nullptr;
	gUsername = username;
	gFound = false;
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), callback, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return gFound;
}
/*
checking if the password match
*/
bool SqliteDataBase::doesPasswordMatch(Login user)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE USERNAME = '" + user.name + "' AND PASSWORD = '" + user.pass + "';";
	char* errMessage = nullptr;
	gUsername = user.name;
	gFound = false;
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), callback, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return gFound;
}
/*
	execute sql statment
*/
bool SqliteDataBase::ask(char* state)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, state, callback, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
}
/*
getting the num of the correct answers of a player
*/
int SqliteDataBase::getNumOfCorrectAnswers(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), corrAns, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}
/*
getting the number of the player's total answers
*/
int SqliteDataBase::getNumOfTotalAnswers(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), allAns, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}
/*
getting the number of games the player played.
*/
int SqliteDataBase::getNumOfPlayerGames(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), allGames, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}
/*
getting the num of wins of a player
*/
int SqliteDataBase::getNumOfPlayerWins(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), wins, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}
/*
getting the top 5 players
*/
std::vector<std::string> SqliteDataBase::getBestData()
{
	bestData.clear();

	std::string sqlStatement = "SELECT * FROM STATISTICS ORDER BY NUMOFWINS DESC LIMIT 5;";
	char* errMessage = nullptr;
	GBack = "";
	bestData.clear();
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), best5, nullptr, &errMessage);

	return bestData;
}
/*
getting the db pointer
*/
sqlite3* SqliteDataBase::get_db()
{
	return this->db;
}
/*
getting the 1st level players
*/
std::pair<std::string, std::string> SqliteDataBase::getQuestion1()
{
	srand(time(NULL));
	int r = rand() * rand() + (rand() % rand());
	r = (r % 30) + 1;

	std::string sqlStatement = "SELECT * FROM QUESTIONS1 WHERE ID = " + std::to_string(r) + ";";
	char* errMessage = nullptr;
	GBack = "";
	Gpair.first = "";
	Gpair.second = "";

	int res = sqlite3_exec(this->db, sqlStatement.c_str(), quest1, nullptr, &errMessage);
	return Gpair;
}

statistics::statistics(SqliteDataBase DB)
{
	this->DB = DB;
}

std::string statistics::getPersonalData(std::string username)
{
	std::string msg;
	msg = "`" + std::to_string(this->DB.getNumOfCorrectAnswers(username)) + "`" + std::to_string(this->DB.getNumOfTotalAnswers(username)) + "`" + std::to_string(this->DB.getNumOfPlayerGames(username)) + "`" + std::to_string(this->DB.getNumOfPlayerWins(username));
	return msg;
}

std::string statistics::getBest5()
{
	std::string msg;
	std::vector<std::string> final5 = this->DB.getBestData();

	for (std::vector<std::string>::iterator it = final5.begin(); it != final5.end(); ++it)
	{
		msg = msg + *it;
	}

	return msg;
}
/*
getting ALL the user's statistics
*/
void statistics::addStatistics(std::string username, int cAns, bool isWin, bool isEnd)
{
	int CANS = 0;
	int ANS = 0;
	int NUMOFGAMES = 0;
	int NUMOFWINS = 0;
	if (isWin)
	{
		CANS = cAns + this->DB.getNumOfCorrectAnswers(username);
		ANS = this->DB.getNumOfTotalAnswers(username) + 10;
		NUMOFGAMES = this->DB.getNumOfPlayerGames(username) + 1;
		NUMOFWINS = this->DB.getNumOfPlayerWins(username) + 1;
	}
	else
	{
		CANS = cAns + this->DB.getNumOfCorrectAnswers(username);
		ANS = this->DB.getNumOfTotalAnswers(username) + 7;
		NUMOFGAMES = this->DB.getNumOfPlayerGames(username) + 1;
		NUMOFWINS = this->DB.getNumOfPlayerWins(username) + 0;
	}

	std::string sqlStatement = "UPDATE STATISTICS SET NUMOFCORRANS = " + std::to_string(CANS) + ", NUMOFANS = " + std::to_string(ANS) + ", NUMOFGAMES = " + std::to_string(NUMOFGAMES) + ", NUMOFWINS = " + std::to_string(NUMOFWINS) + " WHERE USERNAME = '" + username + "';" ;
	char* errMessage = nullptr;

	int res = sqlite3_exec(this->DB.db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
}
/*
getting the question for the 2nd part
*/
std::pair<std::string, std::string> SqliteDataBase::getQuestion2()
{
	srand(time(NULL));
	int r = (rand() % 10) + 1;

	std::string sqlStatement = "SELECT * FROM QUESTIONS2 WHERE ID = " + std::to_string(r) + ";";
	char* errMessage = nullptr;
	GBack = "";
	Gpair.first = "";
	Gpair.second = "";

	int res = sqlite3_exec(this->db, sqlStatement.c_str(), quest1, nullptr, &errMessage);
	return Gpair;
}
void SqliteDataBase::printAllAns()
{
	for (int i = 1; i <= 30; i++)
	{
		std::string sqlStatement = "SELECT * FROM QUESTIONS1 WHERE ID = " + std::to_string(i) + ";";
		char* errMessage = nullptr;
		GBack = "";
		Gpair.first = "";
		Gpair.second = "";

		int res = sqlite3_exec(this->db, sqlStatement.c_str(), quest1, nullptr, &errMessage);
		std::cout << Gpair.second + "\n";
	}
	
}
void SqliteDataBase::countQuestions()
{
	std::string sqlStatement = "SELECT* FROM QUESTIONS1 ORDER BY ID;";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), count, nullptr, &errMessage);

}
/*
C A L L  B A C K S  F U N C T I O N S
*/
int callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "USERNAME")
		{
			if (argv[i] == gUsername)
			{
				gFound = true;
			}
		}
	}
	return 0;
}

int corrAns(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFCORRANS")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int allAns(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFANS")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int allGames(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFGAMES")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int wins(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFWINS")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int best5(void* data, int argc, char** argv, char** azColName)
{
	std::string final;
	final = "`";
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "USERNAME")
		{
			final = final + argv[i] + "`";
			bestData.push_back(final);
		}

	}
	return 0;
}

int quest1(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "QUESTION")
		{
			GBack = argv[i];
			Gpair.first = GBack;
		}
		if (std::string(azColName[i]) == "ANSWER")
		{
			GBack = argv[i];
			Gpair.second = GBack;
		}
	}
	return 0;
}

int count(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "QUESTION")
		{
			std::cout << c << std::endl;
			c++;
		}
	}
	return 0;
}
