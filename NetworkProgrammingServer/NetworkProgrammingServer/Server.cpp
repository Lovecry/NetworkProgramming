#include "Server.h"

void Server::Initialize() {
	window.create(sf::VideoMode(800, 600), "SFML works!");
	window.setPosition({ 100, 100 });

	serverShape = sf::CircleShape(80, 6);
	serverShape.setFillColor(sf::Color::Red);
	serverShape.setRadius(20);
	serverShape.setPosition(0, 0);

	clientShape = sf::CircleShape(80, 10);
	clientShape.setFillColor(sf::Color::Green);
	clientShape.setRadius(20);
	clientShape.setPosition(750,0);

	socket.bind(55002);
	socket.setBlocking(false);

	
}

void Server::Update() {

	window.clear();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	{ serverShape.move(1, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		{ serverShape.move(-1, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		{ serverShape.move(0, -1); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		{ serverShape.move(0, 1); }

	/*while (window.pollEvent(event))
	{*/

		if (event.type == sf::Event::Closed)	window.close();

		socket.receive(buffer, sizeof(buffer), received, sender, port);
		std::cout << sender.toString() << " said: " << buffer << std::endl;
		// Send an answer
		sf::Packet packet;

		positionX = serverShape.getPosition().x;
		positionY = serverShape.getPosition().y;
		packet << positionX << positionY;
		//std::string message = "Welcome" + sender.toString();
		socket.send(packet, sender, port);
	/*}*/
		packet.clear();
	window.draw(serverShape);
	window.draw(clientShape);
	window.display();
}

bool Server::servWinIsOpen()
{
	return window.isOpen();
}