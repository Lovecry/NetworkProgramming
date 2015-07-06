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

	// Create a socket and bind it to the port 55001
	socket.bind(55001);
	socket.setBlocking(false);
}

void Client::Update() {
	window.clear();

	//while (window.pollEvent(event))
	//{
		if (event.type == sf::Event::Closed)
			window.close();
		// Send a message to 192.168.1.50 on port 55002
		std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
		socket.send(message.c_str(), message.size() + 1, "", 55002);
		//Receive an answer (most likely from 192.168.1.50, but could be anyone else)
		socket.receive(packet, sender, port);
		//socket.receive(buffer, sizeof(buffer), received, sender, port);
		//std::cout << sender.toString() << " said: " << buffer << std::endl;
		packet >> positionX >> positionY;
		std::cout << sender.toString() << " said: " << positionX << positionY << std::endl;
	//}
	
		serverShape.setPosition(positionX , positionY);

	window.draw(clientShape);
	window.draw(serverShape);
	window.display();
}

bool Client::clieWinIsOpen()
{
	return window.isOpen();
}