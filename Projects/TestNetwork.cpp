#include "TestNetwork.h"
#include "Logger.h"
#include <asio.hpp>

// CTcpListener::CTcpListener(std::string ipAddress, int port, MessageRecievedHandler handler)
// 	: m_ipAddress(ipAddress), m_port(port), MessageReceived(handler)
// {

// }

// CTcpListener::~CTcpListener()
// {
// 	Cleanup();
// }

// // Send a message to the specified client
// void CTcpListener::Send(int clientSocket, std::string msg)
// {
// 	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
// }

// // Initialize winsock
// bool CTcpListener::Init()
// {
// 	WSAData data;
// 	WORD ver = MAKEWORD(2, 2);

// 	int wsInit = WSAStartup(ver, &data);
// 	// TODO: Inform caller the error that occured

// 	return wsInit == 0;
// }

// // The main processing loop
// void CTcpListener::Run()
// {
// 	char buf[MAX_BUFFER_SIZE];

// 	while (true)
// 	{
// 		// Create a listening socket
// 		SOCKET listening = CreateSocket();
// 		if (listening == INVALID_SOCKET)
// 		{
// 			break;
// 		}

// 		SOCKET client = WaitForConnection(listening);
// 		if (client != INVALID_SOCKET)
// 		{
// 			closesocket(listening);
// 			std::cout << "Client connect ok!" << std::endl;
// 			int bytesReceived = 0;
// 			do
// 			{
// 				ZeroMemory(buf, MAX_BUFFER_SIZE);

// 				bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
// 				if (bytesReceived > 0)
// 				{
// 					if (MessageReceived != NULL)
// 					{
// 						MessageReceived(this, client, std::string(buf, 0, bytesReceived));
// 					}
// 				}

// 			} while (bytesReceived > 0);

// 			closesocket(client);
// 		}
// 	}
// }

// void CTcpListener::Cleanup()
// {
// 	WSACleanup();
// }

// // Create a socket
// SOCKET CTcpListener::CreateSocket()
// {
// 	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
// 	if (listening != INVALID_SOCKET)
// 	{
// 		sockaddr_in hint;
// 		hint.sin_family = AF_INET;
// 		hint.sin_port = htons(m_port);
// 		inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

// 		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
// 		if (bindOk != SOCKET_ERROR)
// 		{
// 			int listenOk = listen(listening, SOMAXCONN);
// 			if (listenOk == SOCKET_ERROR)
// 			{
// 				return -1;
// 			}
// 		}
// 		else
// 		{
// 			return -1;
// 		}
// 	}

// 	return listening;
// }

// // Wait for a connection
// SOCKET CTcpListener::WaitForConnection(SOCKET listening)
// {
// 	SOCKET client = accept(listening, NULL, NULL);
// 	return client;
// }


// // Constructor
// CQotd::CQotd(std::string filename)
// {
// 	std::ifstream file;
// 	file.open(filename);
// 	if (file.is_open())
// 	{
// 		std::string line;
// 		std::string running = "";

// 		while (getline(file, line))
// 		{
// 			if (line != "%")
// 			{
// 				running = running + line + "\n";
// 			}
// 			else
// 			{
// 				quotes.push_back(running);
// 				running = "";
// 			}
// 		}
// 	}
// }

// // Get a random quote from the file
// std::string CQotd::GetRandomQuote()
// {
// 	int r = rand() % quotes.size();
// 	return quotes[r];
// }


// //#include <iostream>
// //#include <string>
// //
// //#include "TcpListener.h"
// //#include "Qotd.h"
// //
// //using namespace std;
// //
// //void Listener_MessageReceived(CTcpListener* listener, int client, string msg);
// //
// //// This is kinda bad because it's global.
// //CQotd quotes("wisdom.txt");
// //
// //void main()
// //{
// //	CTcpListener server("127.0.0.1", 8082, Listener_MessageReceived);
// //
// //	if (server.Init())
// //	{
// //		server.Run();
// //	}
// //}
// //
// //void Listener_MessageReceived(CTcpListener* listener, int client, string msg)
// //{
// //	if (msg == "QUOTE")
// //	{
// //		listener->Send(client, quotes.GetRandomQuote());
// //	}
// //}


 TestNetwork::TestNetwork()
 {
 	Logger::Error("hello");
 	TestServer();
 }

 TestNetwork::~TestNetwork()
 {

 }

 void TestNetwork::TestServer()
 {
	 asio::ip::tcp::iostream s("www.boost.org", "http");
	 s.expires_from_now(std::chrono::seconds(60));
	 s << "GET / HTTP/1.0\r0.2cm\n";
	 s << "Host: www.boost.org\r\n";
	 s << "Accept: */*\r\n";
	 s << "Connection: close\r\n\r\n";
	 std::string header;
	 while (std::getline(s, header) && header != "\r")
		 std::cout << header << "\n";
	 std::cout << s.rdbuf();
	 if (!s)
	 {
		 std::cout << "Socket error: " << s.error().message() << "\n";
		 return ;
	 }
 }

 void TestNetwork::Update()
 {

 }

 void TestNetwork::Draw()
 {

 }


 //void TestNetwork::TestServer()
 //{
 //	std::string ipAddress = "127.0.0.1";
 //	int port = 8082;

 //	WSAData data;
 //	WORD version = MAKEWORD(2, 2);
 //	int wsResult = WSAStartup(version, &data);

 //	if (wsResult != 0)
 //	{
 //		std::cerr << "Can't start winsock ,Err #" << wsResult << std::endl;
 //		return;
 //	}

 //	// Create socket 
 //	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
 //	if (sock == INVALID_SOCKET)
 //	{
 //		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
 //		return;
 //	}

 //	sockaddr_in hint;
 //	hint.sin_family = AF_INET;
 //	hint.sin_port = htons(port);
 //	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);


 //	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
 //	if (connResult == SOCKET_ERROR)
 //	{
 //		std::cerr << "Can't connect to server , Err #" << WSAGetLastError() << std::endl;
 //		closesocket(sock);
 //		WSACleanup();
 //		return;
 //	}

 //	char buf[4096];
 //	std::string userInput;

 //	do
 //	{
 //		std::cout << "> ";
 //		getline(std::cin, userInput);

 //		if (userInput.size() > 0)
 //		{
 //			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
 //			if (sendResult != SOCKET_ERROR)
 //			{
 //				int bytesReceived = recv(sock, buf, 4096, 0);
 //				if (bytesReceived > 0)
 //				{
 //					std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
 //				}
 //			}
 //		}
 //	} while (userInput.size() > 0);

 //	closesocket(sock);
 //	WSACleanup();

 //}

 