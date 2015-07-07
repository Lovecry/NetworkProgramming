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

private:
	sf::RenderWindow window;
	sf::CircleShape clientShape;
	sf::CircleShape serverShape;

	sf::UdpSocket socket;
	sf::IpAddress ipServer = "127.0.0.1"; // ip of server (where i send)
	unsigned short port = 55001; // My port from where i send

	sf::IpAddress sender; // ip adress of message sender (that client receive)
	unsigned short portServer = 55002; // port of sender (Server)

	sf::Event event;
	sf::Packet packet;
};