#include "Client.h"

void Client::Initialize() {
	window.create(sf::VideoMode(800, 600), "SFML works!");
	window.setPosition({ 1000, 100 });

	serverShape = sf::CircleShape(80, 6);
	serverShape.setFillColor(sf::Color::Red);
	serverShape.setRadius(20);
	serverShape.setPosition(0,0);

	clientShape = sf::CircleShape(80, 10);
	clientShape.setFillColor(sf::Color::Green);
	clientShape.setRadius(20);
	clientShape.setPosition(750, 0);

	socket.bind(port);
	socket.setBlocking(false);
}

void Client::Update() {
	window.clear();

	if (event.type == sf::Event::Closed)
		window.close();

	std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
	socket.send(message.c_str(), message.size() + 1, ipServer, 55002); //Send Message to ipServer at port

	socket.receive(packet, sender, portServer); //Receve message from sender (ip) at port(portServer)
	float positionX, positionY;
	packet >> positionX >> positionY; // Decripd Packet

	std::cout << sender.toString() << " said: " << positionX << " , " <<positionY << std::endl;
		
	serverShape.setPosition(positionX , positionY); //Update position of Server Shape

	window.draw(clientShape);
	window.draw(serverShape);
	window.display();
}

bool Client::clieWinIsOpen()
{
	return window.isOpen();
}