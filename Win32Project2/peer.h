#ifndef PEER_H
#define PEER_H

#include <SFML/Network.hpp>

#include <string.h>
#include <list>

class peer
{
public :
	sf::TcpSocket socket_peer ;
	std::list <sf::Packet> buffer_pack ;
	std::string str_peer ;
	int friend_pos ; // used to store the possition of the friend
	bool first_pack ;

	sf::Clock clock_peer ;
	sf::Time time_peer ;
public :
	void unpack( );
	peer( );
};
peer::peer( )
{
	socket_peer.setBlocking( false );
	first_pack = false ;
	str_peer = "-1" ;
	friend_pos = -1 ;
}
void peer::unpack( )
{
	sf::Packet pack ;
	if( socket_peer.receive( pack ) == sf::Socket::Done )
	{
		pack >> str_peer ;
		first_pack = true ;
	}
}
#endif