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
	sf::IpAddress sender;
	char buffer[1024];
	std::size_t received = 0;
	unsigned short port;
	sf::Event event;
	sf::Packet packet;

	float positionX, positionY;

};