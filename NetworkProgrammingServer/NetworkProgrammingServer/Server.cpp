#include "Server.h"

void Server::Initialize() {
	InitializeGraphic();
	InitializeNetwork();
}

void Server::InitializeGraphic()
{
	window.create(sf::VideoMode(800, 600), "SFML works!");
	window.setPosition({ 100, 100 });

	serverShape = sf::CircleShape(80, 6);
	serverShape.setFillColor(sf::Color::Red);
	serverShape.setRadius(20);
	serverShape.setPosition(0, 0);

	clientShape = sf::CircleShape(80, 10);
	clientShape.setFillColor(sf::Color::Green);
	clientShape.setRadius(20);
	clientShape.setPosition(750, 0);
}

void Server::InitializeNetwork()
{
	//TCP Settings
	std::cout << "In Ascolto Sulla porta : " << portSeverTCP << std::endl;
	if (listener.listen(portSeverTCP) != sf::Socket::Done)
	{
		std::cout << "ERROR : LISTENER" << std::endl;
	}
	std::cout << "Waiting for connect ... " << std::endl;
	if (listener.accept(socketTCP) != sf::Socket::Done)
	{
		std::cout << "ERROR : ACCEPT" << std::endl;
	}
	else
	{
		std::cout << "Connection DONE! ... Ip : " << socketTCP.getRemoteAddress() << "  Port : " << socketTCP.getRemotePort() << std::endl;
		ipClient = socketTCP.getRemoteAddress();
		portClientTCP = socketTCP.getRemotePort();
	}
	// UDP Settings
	std::cout << "Binding UDP Socket to port : " << portSeverUDP << std::endl;
	if (socketUDP.bind(portSeverUDP) != sf::Socket::Done)
	{
		std::cout << "ERROR : BIND UDP" << std::endl;
	}
	else
	{
		std::cout << "Bind UDP DONE!" << std::endl;
		socketUDP.setBlocking(false);
	}
}

void Server::Update() {

	EventHandle();
	UpdateGraphic();
	UpdateNetwork();

	sf::Packet packet;
	sf::Vector2<float> position, velocity;

	socketUDP.receive(packet, ipClient, portClientUDP);
	if (packet >> position.x >> position.y >> velocity.x >> velocity.y) //Encapsule position of shape server before send it
	{
		std::cout << "Receiving UDP Packet ... :  Pos : " << position.x << "," << position.y << "  Vel : " << velocity.x << "," << velocity.y << std::endl;
		sf::Vector2<float> newPosition;
		std::cout << "Validating Movement ... : " << std::endl;
		if (validateMovement(position, velocity))
		{
			std::cout << "Calculate New Position ... : " << std::endl;
			newPosition = updatePosition(position, velocity);
			std::cout << "Sending New position ... : " << std::endl;
			if (!sendNewPosition(newPosition))
				std::cout << "ERROR : New Position send" << std::endl;
			std::cout << "New Position SENDED" << std::endl;
		}
	}
	else
	{
		std::cout << "ERROR Receiving" << std::endl;
	}
}

bool Server::validateMovement(sf::Vector2<float> position, sf::Vector2<float> velocity)
{
	return true; // Da implementare, al momento nuova posizione sempre accettata
}

sf::Vector2<float> Server::updatePosition(sf::Vector2<float> position, sf::Vector2<float> velocity)
{
	return position + velocity;
}

bool Server::sendNewPosition(sf::Vector2<float> newPosition)
{
	sf::Packet packet;
	packet << newPosition.x << newPosition.y;
	if (socketUDP.send(packet, ipClient, portClientUDP) != sf::Socket::Done) // Send position to client
	{
		std::cout << "ERROR : Send New Position" << std::endl;
		return false;
	}
	else
	{
		std::cout << "Update Position Send" << std::endl;
		return true;
	}
}

void Server::EventHandle()
{
	if (event.type == sf::Event::Closed)	
		window.close();
}

void Server::UpdateGraphic()
{
	window.clear();
	window.draw(serverShape);
	window.draw(clientShape);
	window.display();
}

void Server::UpdateNetwork()
{

}

bool Server::servWinIsOpen()
{
	return window.isOpen();
}