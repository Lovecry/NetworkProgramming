#include "Client.h"

void Client::Initialize() {
	window.create(sf::VideoMode(800, 600), "SFML works!");
	window.setPosition({ 1000, 100 });

	serverShape = sf::CircleShape(50, 6);
	serverShape.setFillColor(sf::Color::Red);
	serverShape.setRadius(20);
	serverShape.setPosition(0, 0);

	clientShape = sf::CircleShape(50, 6);
	sf::Color colorClient(10,255,10,50);
	clientShape.setFillColor(colorClient);
	clientShape.setRadius(20);
	clientShape.setPosition(0,0);

	interpoledShape = sf::CircleShape(50, 6);
	sf::Color colorInterpoled(255, 255, 0, 50);
	interpoledShape.setFillColor(colorInterpoled);
	interpoledShape.setRadius(20);
	interpoledShape.setPosition(0, 0);

	InitializeNetwork();

}

void Client::draw(){
	window.clear();
	window.draw(serverShape);
	window.draw(clientShape);
	window.draw(interpoledShape);
	window.display();
}

void Client::Update() {
	
	EventHandle();
	receiveDataUdp();

	draw();
}

void Client::sendPacketTcp(){
	sf::Packet packet;

	packet << "Sono io";
	socketTCP.send(packet);
}



void Client::sendDataUdp(float x, float y){
	
	sf::Vector2<float> velocity(x,y);
	sf::Packet packetUdp;

	//create packet
	packetUdp << clientShape.getPosition().x << clientShape.getPosition().y << velocity.x << velocity.y;

	if (socketUDP.send(packetUdp, IpServer, portServerUDP) != sf::Socket::Done){
		std::cout << "error send UDP" << std::endl;
	}
	else{
		std::cout << "SEND OK :" << IpServer << "  "<<portServerUDP << clientShape.getPosition().x << clientShape.getPosition().y << velocity.x << velocity.y << std::endl;
	}

}


void Client::receiveDataUdp(){
	
	sf::Vector2<float> position, newInterpoledPosition;
	
	sf::Packet packetUdp;	
	sf::IpAddress IpAddress;
	unsigned short port;
		
	if (socketUDP.receive(packetUdp, IpAddress, port) == sf::Socket::Done){
		if (packetUdp >> position.x >> position.y){
			//encapsule data
			serverShape.setPosition(position);
			newInterpoledPosition = interpoledCalculate(position);
			interpoledShape.setPosition(newInterpoledPosition);
		}
		std::cout << " receive server: " << position.x << " " << position.y << std::endl;
	}
}

sf::Vector2<float> Client::interpoledCalculate(sf::Vector2<float> position)
{
	sf::Vector2<float> newInterpoledPosition;

	newInterpoledPosition = (clientShape.getPosition() + position) / 2.f;

	return newInterpoledPosition;
}

void Client::receivePacket(){

}

bool Client::clieWinIsOpen()
{
	return window.isOpen();
}

void Client::InitializeNetwork()
{
	//TCP settings
	std::cout << "connect TCP" << std::endl;
	sf::Socket::Status statusTCP = socketTCP.connect(IpServer, portServerTCP);
	if (statusTCP != sf::Socket::Done)
	{
		std::cout << "Error connect TCP" << std::endl;
	}	
	else{
		std::cout << "connect TCP OK" << std::endl;	
	}


	// UDP settings
	std::cout << "connect UDP" << std::endl;
	if (socketUDP.bind(portClientUDP) != sf::Socket::Done)
	{
		std::cout << "Error connect UDP" << std::endl;
	}
	else{
		std::cout << "connect UDP OK" << std::endl;
	}
	socketUDP.setBlocking(false);
		

}

void Client::UpdateNetwork(){
	
}

void Client::EventHandle()
{
	if (event.type == sf::Event::Closed) window.close();
	
	static int count = 0; // Non inviamo i pacchetti ogni frame ma ogni 10
	int limitCount = 5;

	sf::Vector2<float> velocity,newPosition;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	{ 
		if (count % limitCount == 0){
			sendDataUdp(1, 0);
		}
		velocity = { 1, 0 };
		newPosition = clientSidePrediction(velocity);
		clientShape.setPosition(newPosition);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	{ 
		if (count % limitCount == 0){
			sendDataUdp(-1, 0);
		}
		velocity = { -1, 0 };
		newPosition = clientSidePrediction(velocity);
		clientShape.setPosition(newPosition);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	{ 
		if (count % limitCount == 0){
			sendDataUdp(0, -1);
		}
		velocity = { 0, -1 };
		newPosition = clientSidePrediction(velocity);
		clientShape.setPosition(newPosition);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	{ 
		if (count % limitCount == 0){
			sendDataUdp(0, 1);
		}
		velocity = { 0, 1 };
		newPosition = clientSidePrediction(velocity);
		clientShape.setPosition(newPosition);
	}
	count++;
}

sf::Vector2<float> Client::clientSidePrediction(sf::Vector2<float> velocity)
{
	sf::Vector2<float> newPosition;

	newPosition = clientShape.getPosition() + velocity;

	return newPosition;
}