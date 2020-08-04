#include "Server.h"
#include "IRequestHandler.h"
#include "ResponsePacketSerializer.h"
#include "IDatabase.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <mutex>

#define MAX 1000

SqliteDataBase Database;
std::map<SOCKET, IRequestHandler*>m_clients;
std::thread* arr = new std::thread[MAX];
std::map<std::string, SOCKET>m_users;
int index = 0;
roomManager rm;
std::mutex mu;

Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	bool start = Database.open();

	if (start == true)
	{
		while (true)
		{
			// the main thread is only accepting clients 
			// and add then to the list of handlers
			std::cout << "Waiting for client connection request" << std::endl;
			accept();
		}
	}

}


void Server::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// the function that handle the conversation with the client
	arr[index] = std::thread(client, client_socket); //creating a thead for each client
	index++;
}

void client(SOCKET clientSocket)
{
	statistics stat(Database);
	IRequestHandler* l = new LoginRequestHandler;
	std::pair< SOCKET, IRequestHandler* >p(clientSocket, l);
	m_clients.insert(p);
	while (true)
	{
		char m[MAX] = "";
		int err = recv(clientSocket, m, MAX, 0); //getting from client
		if (err == -1)
		{
			std::string name;
			for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
			{
				if (it->second == clientSocket)
				{

					name = it->first;
					std::cout << "removing from users online: " << name << std::endl;
				}
			}
			m_users.erase(name);
			std::cout << m_users.size() << std::endl;
			break;
		}

		m[MAX - 1] = 0;
		std::string ans = m;
		RequestInfo r;
		r.BData = ans;
		r.code = ans[0];

		LoginRequestHandler lo;
		short type = lo.isRequestRelevant(r);
		if (type == 1) //login
		{
			loginSend(clientSocket, lo, r);
		}
		else if (type == 2) //sign up
		{
			signUpSend(clientSocket, lo, r);
		}
		else if (type == 3) //sign out
		{
			logOutSend(clientSocket);
		}
		else if (type == 4) //get all the rooms in a list
		{
			GetRoomsSend(clientSocket);
		}
		else if (type == 5) //get all players in specific room
		{
			getPlayersInRoomSend(clientSocket, r);
		}
		else if (type == 6) //join room
		{
			joinRoomsend(clientSocket, r);
		}
		else if (type == 7) //create room
		{
			CreateRoomSend(clientSocket, r, lo);
		}
		else if (type == 8) //statistics
		{
			std::string username;
			for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
			{
				if (it->second == clientSocket)
				{
					username = it->first;
					break;
				}
			}
			std::string data = stat.getPersonalData(username);
			std::string full = "H" + std::to_string(data.size()) + data;
			send(clientSocket, full.c_str(), full.size(), 0);  // last parameter: flag. for us will be 0.
			std::cout << "sent the statistics to the client" << std::endl;
		}
		else if (type == 9) //start game
		{
			startGameSend(clientSocket, r);
		}
		else if (type == 10) //check start game
		{
			getRoomBeginSend(clientSocket, r);
		}
		else if (type == 11) //getting question
		{
			std::string q;
			std::string a;
			for (int i = 0; i < rm.activate_rooms.size(); i++)
			{
				std::vector<std::string> names = rm.activate_rooms[i].getAllUsers();

				for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); ++it)
				{
					for (std::map<std::string, SOCKET>::iterator it2 = m_users.begin(); it2 != m_users.end(); ++it2)
					{
						if (it2->second == clientSocket)
						{
							if (*it == it2->first)
							{
								mu.lock(); //critic code segment(getting question)
								q = rm.activate_rooms[i].getQuestion(Database, rm.activate_rooms[i].is_final);
								a = rm.activate_rooms[i].getAns();
								mu.unlock();
							}
						}
					}
				}
			}

			q = "Q" + std::to_string(q.length() + a.length() + 2) + "`" + q + "`" + a;
			char* buffer = (char*)malloc(q.length() * sizeof(char));
			memcpy(buffer, q.data(), q.length());
			send(clientSocket, buffer, q.length(), 0);  // last parameter: flag. for us will be 0.

			free(buffer);
		}
		else if (type == 13) //getting the 2nd part question
		{
			std::string q;
			std::string a;
			for (int i = 0; i < rm.activate_rooms.size(); i++)
			{
				std::vector<std::string> names = rm.activate_rooms[i].getAllUsers();

				for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); ++it)
				{
					for (std::map<std::string, SOCKET>::iterator it2 = m_users.begin(); it2 != m_users.end(); ++it2)
					{
						if (it2->second == clientSocket)
						{
							if (*it == it2->first)
							{
								mu.lock(); //critic segment lock
								q = rm.activate_rooms[i].getQuestion2(Database);
								a = rm.activate_rooms[i].getAns();
								mu.unlock();
							}
						}
					}
				}
			}

			q = "B" + std::to_string(q.length() + a.length() + 2) + "`" + q + "`" + a;
			char* buffer = (char*)malloc(q.length() * sizeof(char));
			memcpy(buffer, q.data(), q.length());
			send(clientSocket, q.c_str(), q.size(), 0);  // last parameter: flag. for us will be 0.

			free(buffer);
		}
		else if(type == 14) //checking who is going to level 3
		{
			char num_b = r.BData[3];
			const char* c1 = &num_b;
			int num_a = atoi(c1);
			bool b2 = false;
			room* r1 = nullptr;
			std::string name1;

			for (int i = 0; i < rm.activate_rooms.size(); i++)
			{
				std::vector<std::string> names = rm.activate_rooms[i].getAllUsers();

				for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); ++it)
				{
					for (std::map<std::string, SOCKET>::iterator it2 = m_users.begin(); it2 != m_users.end(); ++it2)
					{
						if (it2->second == clientSocket)
						{
							if (*it == it2->first)
							{
								int si = rm.activate_rooms[i].players_in_room.size();
								rm.activate_rooms[i].s.insert(num_a);
								if (si >= 3)
								{
									while (rm.activate_rooms[i].s.size() + 1 < si)
									{
									}
								}
								else
								{
									while (rm.activate_rooms[i].s.size() < si)
									{
									}
								}
								//after we have all the 3 answers
								rm.activate_rooms[i].is_final = true; //REMOVABLE
								std::set<int> se = rm.activate_rooms[i].s;
								int biggest = 0;
								for (std::set<int>::iterator it3 = rm.activate_rooms[i].s.begin(); it3 != rm.activate_rooms[i].s.end(); ++it3)
								{
									if (*it3 > biggest)
									{
										biggest = *it3;
									}
								}
								if (biggest == num_a) //this is the winner
								{
									std::string q = "N10";
									send(clientSocket, q.c_str(), q.size(), 0);  // last parameter: flag. for us will be 0.
								}
								else
								{
									r1 = &rm.activate_rooms[i];
									name1 = *it;
									std::string q = "N11";
									b2 = true;
									send(clientSocket, q.c_str(), q.size(), 0);
								}
							}
						}
					}
				}
			}
			
			
		}
		else if (type == 15) //deleating room from the list of the room in rm
		{
			for (int i = 0; i < rm.activate_rooms.size(); i++)
			{
				std::vector<std::string> names = rm.activate_rooms[i].getAllUsers();

				for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); ++it)
				{
					for (std::map<std::string, SOCKET>::iterator it2 = m_users.begin(); it2 != m_users.end(); ++it2)
					{
						if (it2->second == clientSocket)
						{
							if (*it == it2->first)
							{
								rm.deleteRoom(rm.activate_rooms[i].getRoomNum());
							}
						}
					}
				}
			}
		}
		else if (type == 16) //statistics
		{
			std::string username;
			for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
			{
				if (it->second == clientSocket)
				{
					username = it->first;
					break;
				}
			}

			short place = 0;
			std::string part = "";
			short points = 0;
			bool isEnd = false;
			bool isWin = false;
			for (int i = 0; i < ans.length(); i++)
			{
				if (ans[i] == '`')
				{
					place++;
				}
				else if (place == 1)
				{
					part = part + ans[i];
				}
				else if (place == 2)
				{
					points = atoi(part.c_str());
					part = "";
					place++;
				}
				if (place == 3)
				{
					char temp = ans[i];
					char* t = &temp;
					isEnd = atoi(t);
				}
				else if (place == 4)
				{
					char temp = ans[i];
					char* t = &temp;
					isWin = atoi(t);
				}
			}
			stat.addStatistics(username, points, isWin, isEnd);
		}
		else if (type == 17) //top 5 players request
		{
			std::vector<std::string> bes = Database.getBestData();
			std::string fin = "";
			for (std::vector<std::string>::iterator it = bes.begin(); it != bes.end(); ++it)
			{
				fin = fin + *it;
			}
			std::string q = "Z" + std::to_string(fin.size()) + fin; //final message
			send(clientSocket, q.c_str(), q.size(), 0);
		}
	}



}

/*
sending the login request answer
*/
void loginSend(SOCKET clientSocket, LoginRequestHandler lo, RequestInfo r)
{
	Login log = lo.getLogin(r.BData);
	std::cout << "username: " << log.name << "\npassword - " << log.pass << std::endl;

	std::string login = "";
	ResponsePacketSerializer rps;

	if (log.name == "" || log.pass == "")
	{
		loginRespons loginRes;
		loginRes.status = 1; //error
		login = rps.serializeLoginResponse(loginRes);
	}
	else
	{
		loginRespons loginRes;
		if (Database.doesPasswordMatch(log))
		{
			loginRes.status = 0;
			std::pair<std::string, SOCKET>p(log.name, clientSocket);
			m_users.insert(p);
		}
		else
		{
			loginRes.status = 1;
		}
		login = rps.serializeLoginResponse(loginRes);
	}

	send(clientSocket, login.c_str(), login.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status to the client" << std::endl;
}
/*
sign up answer
*/
void signUpSend(SOCKET clientSocket, LoginRequestHandler lo, RequestInfo r)
{
	SignUp log = lo.getSignUp(r.BData);
	std::cout << "username: " << log.name << "\npassword - " << log.pass << "\nemail: " << log.email << std::endl;

	std::string login = "";
	ResponsePacketSerializer rps;

	if (log.name == "" || log.pass == "" || log.email == "")
	{
		signUpRespons signRes;
		signRes.status = 1; //error
		login = rps.serializeSignUpResponse(signRes);
	}
	else
	{
		if (Database.doesUserExist(log.name))
		{
			signUpRespons signRes;
			signRes.status = 1; //error
			login = rps.serializeSignUpResponse(signRes);
		}
		else if (Database.addUser(log))
		{
			signUpRespons signRes;
			signRes.status = 0; //not error
			login = rps.serializeSignUpResponse(signRes);
		}
		else
		{
			signUpRespons signRes;
			signRes.status = 1; //error
			login = rps.serializeSignUpResponse(signRes);
		}
	}

	send(clientSocket, login.c_str(), login.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status to the client" << std::endl;
}
/*
log out send
*/
void logOutSend(SOCKET clientSocket)
{
	ResponsePacketSerializer rps;
	logOutResponse l;
	l.status = 0;
	std::string s = rps.serializeLogoutResponse(l); //sending log out response
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the logout to the client" << std::endl;

	std::string name;
	for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->second == clientSocket)
		{
			name = it->first;
			std::cout << "removing from users online: " << name << std::endl;
		}
	}
	m_users.erase(name);
	std::cout << m_users.size() << std::endl;
}

void GetRoomsSend(SOCKET clientSocket)
{
	ResponsePacketSerializer rps;
	getRoomsResponse l;
	std::vector<room> tm = rm.getActiveRooms();
	std::vector<room> tm1;
	for (std::vector<room>::iterator iter = tm.begin(); iter != tm.end(); ++iter)
	{
		if (iter->is_active == true) //can show in game menu
		{
			tm1.push_back(*iter);
		}
	}
	l.status = 0;
	l.rooms = tm1;
	std::string s = rps.serializeGetRoomResponse(l);
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the rooms list to the client" << std::endl;
}

void getPlayersInRoomSend(SOCKET clientSocket, RequestInfo r)
{
	char c1 = ' ';
	std::string num_s = "";
	int i = 1;
	for (i; c1 != '`'; i++)
	{
		c1 = r.BData[i + 1];
		num_s = num_s + r.BData[i];
	}
	int size = atoi(num_s.c_str());
	i = i + 1;
	std::string name = "";
	for (int j = 0; j < size; j++)
	{
		name = name + r.BData[i];
		i++;
	}
	std::vector<room>ro = rm.getActiveRooms();
	std::vector<std::string>list;
	for (int i = 0; i < ro.size(); i++)
	{
		if (ro.at(i).getRoomName() == name)
		{
			list = ro.at(i).getAllUsers();
		}
	}
	ResponsePacketSerializer rps;
	getPlayersInRoomResponse g;
	g.players = list;
	std::string s = rps.serializeGetPlayersInRoomResponse(g);
	char* buffer = (char*)malloc(s.length() * sizeof(char));
	memcpy(buffer, s.data(), s.length());
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	//std::cout << "sent the players list of a room to the client" << std::endl;

	free(buffer); //freeing the heap memory
}

void joinRoomsend(SOCKET clientSocket, RequestInfo r)
{
	char c1 = ' ';
	std::string num_s = "";
	int i = 1;
	for (i; c1 != '`'; i++)
	{
		c1 = r.BData[i + 1];
		num_s = num_s + r.BData[i];
	}
	int size = atoi(num_s.c_str());
	i = i + 1;
	std::string name = "";
	for (int j = 0; j < size; j++)
	{
		name = name + r.BData[i];
		i++;
	}
	std::string username = "";
	for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->second == clientSocket) //finding the name of the client
		{
			username = it->first;
		}
	}
	bool b = rm.addPlayerToRoom(name, username);
	ResponsePacketSerializer rps;
	JoinRoomResponse j2;
	j2.status = 0;
	if (b == false)
	{
		j2.status = 1;
	}
	std::string final = rps.serializeJoinRoomResponse(j2);
	send(clientSocket, final.c_str(), final.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status of joining to room to the client" << std::endl;
}
/*
create room answer
*/
void CreateRoomSend(SOCKET clientSocket, RequestInfo r, LoginRequestHandler lo)
{
	CreateRoomRequest g = lo.deserializeCreateRoomRequest(r.BData);
	rm.createRoom(g.roomName);
	std::string name;
	for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (clientSocket == it->second)
		{
			name = it->first;
		}
	}
	rm.addPlayerToRoom(g.roomName, name);
	ResponsePacketSerializer rps;
	createRoomResponse f;
	f.status = 0;
	std::string s = rps.serializeCreateRoomResponse(f);

	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status of creating new room to the client" << std::endl;
}
/*
begin game answare
*/
void getRoomBeginSend(SOCKET clientSocket, RequestInfo r)
{
	int ind = 0;
	for (ind = 0; ind < r.BData.size(); ind++)
	{
		if (r.BData[ind] == '`')
		{
			break;
		}
	}
	std::string str = "";
	for (ind = ind + 1; ind < r.BData.size(); ind++)
	{
		if (r.BData[ind] != '`')
		{
			str = str + r.BData[ind];
		}
		else
		{
			break;
		}
	}
	int toSend = 1;
	for (std::vector<room>::iterator it = rm.activate_rooms.begin(); it != rm.activate_rooms.end(); ++it)
	{
		if (it->getRoomName() == str)
		{
			if (it->is_started == true) //game started
			{
				toSend = 0;
			}
		}
	}

	std::string full = "K1" + std::to_string(toSend);
	send(clientSocket, full.c_str(), full.size(), 0);  // last parameter: flag. for us will be 0.
}

void startGameSend(SOCKET clientSocket, RequestInfo r)
{
	int ind = 0;
	for (ind = 0; ind < r.BData.size(); ind++)
	{
		if (r.BData[ind] == '`')
		{
			break;
		}
	}
	std::string str = "";
	for (ind = ind + 1; ind < r.BData.size(); ind++)
	{
		if (r.BData[ind] != '`')
		{
			str = str + r.BData[ind];
		}
		else
		{
			break;
		}
	}
	for (std::vector<room>::iterator it = rm.activate_rooms.begin(); it != rm.activate_rooms.end(); ++it)
	{
		if (it->getRoomName() == str)
		{
			it->is_started = true; //starting the game;
			it->is_active = false; //so the list wont show this room anymore
		}
	}
}
