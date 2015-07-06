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

private:
	sf::RenderWindow window;
	sf::CircleShape clientShape;
	sf::CircleShape serverShape;

	sf::UdpSocket socket;
	sf::IpAddress sender = "127.0.0.1";
	char buffer[1024];
	std::size_t received = 0;
	unsigned short port;
	sf::Event event;
	float positionX, positionY;
};