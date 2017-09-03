#include "TestNetwork.h"
#include "Logger.h"
#pragma comment (lib,"ws2_32.lib")

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
	std::string ipAddress = "127.0.0.1";
	int port = 8082;

	WSAData data;
	WORD version = MAKEWORD(2, 2);
	int wsResult = WSAStartup(version, &data);

	if (wsResult != 0)
	{
		std::cerr << "Can't start winsock ,Err #" << wsResult << std::endl;
		return;
	}

	// Create socket 
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		return;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);


	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server , Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	char buf[4096];
	std::string userInput;

	do
	{
		std::cout << "> ";
		getline(std::cin, userInput);

		if (userInput.size() > 0)
		{
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
				}
			}
		}
	} while (userInput.size() > 0);

	closesocket(sock);
	WSACleanup();

}

void TestNetwork::Update()
{
	
}

void TestNetwork::Draw()
{
	
}
