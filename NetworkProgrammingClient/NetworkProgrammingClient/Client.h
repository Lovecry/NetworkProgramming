#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>

class Client {

public:

	Client(){};
	Client(const Client&);
	~Client(){};

	void Initialize();
	void Update();
	bool clieWinIsOpen();
	void draw();
	void sendPacketTcp();
	void receivePacket();
	void InitializeNetwork();
	void UpdateNetwork();
	void sendDataUdp(float , float);
	void receiveDataUdp();
	void EventHandle();
private:

	//Graphic
	sf::RenderWindow window;
	sf::CircleShape clientShape;
	sf::CircleShape serverShape;

	//Tcp
	sf::TcpSocket socketTCP;
	//unsigned short portClientTCP = 55001;
	unsigned short portServerTCP = 56001;

	//Udp
	sf::UdpSocket socketUDP;
	unsigned short portClientUDP= 56002;
	unsigned short portServerUDP = 55002;

	sf::IpAddress IpServer="127.0.0.1";
	//sf::IpAddress IpServer = "192.168.43.112";
	
	unsigned short port;
	char buffer[1024];
	std::size_t received = 0;
	
	sf::Event event;
	

	float positionX, positionY;

};