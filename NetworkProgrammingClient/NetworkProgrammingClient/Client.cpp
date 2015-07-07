#include "Client.h"

void Client::Initialize() {
	window.create(sf::VideoMode(800, 600), "SFML works!");
	window.setPosition({ 500, 100 });

	serverShape = sf::CircleShape(50, 6);
	serverShape.setFillColor(sf::Color::Red);
	serverShape.setRadius(10);
	serverShape.setPosition(0, 0);

	clientShape = sf::CircleShape(50, 6);
	sf::Color colorClient(10,255,10,50);
	clientShape.setFillColor(colorClient);
	clientShape.setRadius(10);
	clientShape.setPosition(0,0);

	InitializeNetwork();

}

void Client::draw(){
	window.clear();
	window.draw(serverShape);
	window.draw(clientShape);	
	window.display();
}

void Client::Update() {
	
	EventHandle();
	receiveDataUdp();
	//sendPacketTcp();
	//while (window.pollEvent(event))
	//{
	//	if (event.type == sf::Event::Closed)
	//		window.close();
	//	// Send a message to 192.168.1.50 on port 55002
	//	std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
	//	socket.send(message.c_str(), message.size() + 1, "", 55002);
	//	//Receive an answer (most likely from 192.168.1.50, but could be anyone else)
	//	socket.receive(packet, IpServer, port);
	//	//socket.receive(buffer, sizeof(buffer), received, sender, port);
	//	//std::cout << sender.toString() << " said: " << buffer << std::endl;
	//	packet >> positionX >> positionY;
	//	
	//	
	//	
	//	if (IpServer.toString() == "0.0.0.0")
	//	{
	//		std::cout << "NOT VALID "<<IpServer.toString() << " said: " << positionX << " " << positionY << std::endl;
	//	}
	//	else{
	//		std::cout << "VALID " << IpServer.toString() << " said: " << positionX << " " << positionY << std::endl;
	//	}
	//	
	////}
	//
	//	serverShape.setPosition(positionX , positionY);

		draw();

}

void Client::sendPacketTcp(){
	//char data[100] = "Inviatooooooooooo";

	//// TCP socket:
	//if (socketTCP.send(data, 100) != sf::Socket::Done)
	//{
	//	std::cout << "error SEND" << std::endl;
	//	// error...
	//}
	//else{
	//	std::cout << "SEND" << std::endl;
	//}
	
	sf::Packet packet;

	packet << "Sono io";
	socketTCP.send(packet);

}



void Client::sendDataUdp(float x, float y){
	
	sf::Vector2<float> velocity(x,y);
	sf::Packet packetUdp;

	clientShape.move(velocity);

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
	
	sf::Vector2<float> position;
	
	sf::Packet packetUdp;	
	sf::IpAddress IpAddress;
	unsigned short port;
	
		
	if (socketUDP.receive(packetUdp, IpAddress, port) == sf::Socket::Done){
		if (packetUdp >> position.x >> position.y){
			//encapsule data
			serverShape.setPosition(position);
		}
		std::cout << " receive server: " << position.x << " " << position.y << std::endl;
	}
	else
	{
		//std::cout << " not" << std::endl;
	}

	

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
	static int count  = 0;
	if (event.type == sf::Event::Closed) window.close();

	
	
	if (count%20==0){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	{ sendDataUdp(1, 0); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	{ sendDataUdp(-1, 0); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	{ sendDataUdp(0, -1); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	{ sendDataUdp(0, 1); }
	}
	count++;
}
