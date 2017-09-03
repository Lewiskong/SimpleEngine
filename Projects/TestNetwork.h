#pragma once
// #include <WS2tcpip.h>
// #pragma comment (lib,"ws2_32.lib")



// #include "defines.h"
// #include "IUpdateDraw.h"



// #define MAX_BUFFER_SIZE (49152)

// // Forward declaration of class
// class CTcpListener;

// // Callback to data received
// typedef void(*MessageRecievedHandler)(CTcpListener* listener, int socketId, std::string msg);

// class CTcpListener
// {

// public:

// 	// Constructor
// 	CTcpListener(std::string ipAddress, int port, MessageRecievedHandler handler);

// 	// Destructor
// 	~CTcpListener();

// 	// Send a message to the specified client
// 	void Send(int clientSocket, std::string msg);

// 	// Initialize winsock
// 	bool Init();

// 	// The main processing loop
// 	void Run();

// 	// Clean up after using the service
// 	void Cleanup();

// private:

// 	// Create a socket
// 	SOCKET CreateSocket();

// 	// Wait for a connection
// 	SOCKET WaitForConnection(SOCKET listening);

// 	// Address of the server
// 	std::string				m_ipAddress;

// 	// Listening port
// 	int						m_port;

// 	// Message received event handler
// 	MessageRecievedHandler	MessageReceived;
// };


// class CQotd
// {
// public:

// 	// Constructor
// 	CQotd(std::string filename);

// 	// Get a random quote from the file
// 	std::string GetRandomQuote();

// private:

// 	// The quotes
// 	std::vector<std::string> quotes;
// };


// class TestNetwork :public IUpdateDraw
// {
// public:
// 	TestNetwork();
// 	~TestNetwork();

	
// 	void TestServer();
	
	

// 	virtual void Update() override;


// 	virtual void Draw() override;

// };