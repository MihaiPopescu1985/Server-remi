#include <windows.h>
#include <list>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "peer.h"


#pragma warning(suppress: 28251)
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	int max_peers = 0 ;

	sf::TcpListener listener ;
	listener.setBlocking( false );

	peer client[100] ;
	sf::Packet received_pack ;

	sf::Font font ;
	font.loadFromFile( "Sansation.ttf" );
	sf::Text text ;
	text.setFont( font );
	text.setCharacterSize( 20 );
	text.setFillColor( sf::Color::White );

	sf::RenderWindow window( sf::VideoMode( 400, 200), "Server remi - V0.2" );

	while( window.isOpen( ))
	{
		sf::Event event ;
		window.pollEvent( event );
		if( event.type == sf::Event::Closed )
		{
			window.close( );
		}
		// receive a new peer
		if( max_peers < 100 )
		{
			listener.listen( 31111 );
			if( listener.accept( client[max_peers].socket_peer ) == sf::Socket::Done )
			{
				max_peers++ ;
			}
		}
		// how many peers are connected
		text.setString( std::to_string( max_peers ));

		for( int i = 0; i < max_peers; i++ )
		{
			if( client[i].first_pack == false )
			{
				client[i].unpack( );
			}
		}

		for( int i = 0; i < max_peers; i++ )
		{
			for( int j = 0; j < max_peers; j++ )
			{
				if( j != i && client[i].str_peer != "-1" && client[j].str_peer != "-1" )
				{
					if( client[i].str_peer == client[j].str_peer )
					{
						client[i].friend_pos = j ;
						client[j].friend_pos = i ;
					}
				}
			}
		}
		for( int i = 0; i < max_peers; i++ )
		{
			int n = client[i].friend_pos ;
			if( client[i].first_pack == true && client[i].socket_peer.receive( received_pack ) == sf::Socket::Done )
			{
				client[i].buffer_pack.push_back( received_pack );
				received_pack.clear( );
			}
			if( client[i].buffer_pack.size( ) > 0 && client[n].first_pack == true )
			{
				if( client[n].socket_peer.send( client[i].buffer_pack.front( )) == sf::Socket::Done )
				{
					client[i].buffer_pack.pop_front( );
				}
			}
		}

		window.clear( );
		window.draw( text );
		window.display( );
	}

    return 0 ;
}