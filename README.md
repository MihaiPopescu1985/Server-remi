# Server-remi
A small server written in C++ for my remi game.

It listen to a port.
It uses TCP/IP protocol.
When a new connection is established, the first packet is opened and gets the number inside.
If two numbers matched, the packets received from one IP are sended to the other IP that had the same number initialy.
Many upgrades must be made, for example threads, and error support.
