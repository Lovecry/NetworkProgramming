#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>

class Server {

public:

	Server(){};
	Server(const Server&);
	~Server(){};

	void Initialize();
	void Update();
	bool servWinIsOpen();

private :
	void InitializeGraphic();
	void InitializeNetwork();
	void EventHandle();
	void UpdateGraphic();
	void UpdateNetwork();

	bool validateMovement(sf::Vector2<float>,sf::Vector2<float>);
	sf::Vector2<float> updatePosition(sf::Vector2<float>, sf::Vector2<float>);
	bool sendNewPosition(sf::Vector2<float>);

private:
	// Graphic
	sf::RenderWindow window;
	sf::CircleShape clientShape;
	sf::CircleShape serverShape;

	//Input
	sf::Event event;

	//TCP 
	sf::TcpListener listener;
	sf::TcpSocket socketTCP;
	unsigned short portSeverTCP = 56001; // Nel client deve essere uguale portServerTCP
	unsigned short portClientTCP;

	//UDP
	sf::UdpSocket socketUDP;
	unsigned short portSeverUDP = 55002; // my port from where i send message (my binded port)
	unsigned short portClientUDP = 56002;

	//Client Adress
	sf::IpAddress ipClient; // ip of frist message sender

	char data[100]; // buffer of welcome message
	std::size_t received = 0; //Welcome message	
};