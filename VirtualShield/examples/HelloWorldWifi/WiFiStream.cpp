/******************************************************************************
 * Includes
 ******************************************************************************/

#include "WiFiStream.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

 WiFiStream::WiFiStream()
 {
    
 }

int WiFiStream::begin(char *ssid, uint16_t port)
{
	if( !verify_connection_ready() ) return 0;
	
	int result = WiFi.begin( ssid );
	if( result == 0 )
		return 0;
	
	server = WiFiServer( port );
	server.begin();
	return result;
}

int WiFiStream::begin(char *ssid, uint8_t key_idx, const char *key, uint16_t port)
{
	if( !verify_connection_ready() ) return 0;
	
	int result = WiFi.begin( ssid, key_idx, key );
	if( result == 0 ) return 0;
	
	server = WiFiServer( port );
	server.begin();
	return result;
}

int WiFiStream::begin(char *ssid, const char *passphrase, uint16_t port)
{
	if( !verify_connection_ready() ) return 0;
	
	int result = WiFi.begin( ssid, passphrase);
	if( result == 0 ) return 0;
	
	server = WiFiServer( port );
	server.begin();
	return result;
}

int WiFiStream::begin(char *ssid, IPAddress local_ip, uint16_t port)
{
	if( !verify_connection_ready() ) return 0;
	
	WiFi.config( local_ip );
	int result = WiFi.begin( ssid );
	if( result == 0 ) return 0;
	
	server = WiFiServer(port);
	server.begin();
	return result;
}

int WiFiStream::begin(char *ssid, IPAddress local_ip, uint8_t key_idx, const char *key, uint16_t port)
{
	if( !verify_connection_ready() ) return 0;
	
	WiFi.config( local_ip );
	int result = WiFi.begin( ssid, key_idx, key );
	if( result == 0 ) return 0;
	
	server = WiFiServer(port);
	server.begin();
	return result;
}

int WiFiStream::begin(char *ssid, IPAddress local_ip, const char *passphrase, uint16_t port)
{
	if( !verify_connection_ready() ) return 0;
	
	WiFi.config( local_ip );
	int result = WiFi.begin( ssid, passphrase);
	if( result == 0 ) return 0;
	
	server = WiFiServer( port );
	server.begin();
	return result;
}

int WiFiStream::verify_connection_ready()
{
	uint8_t status = WiFi.status();
	return ( status == WL_NO_SHIELD || status == WL_CONNECTED ) ? 0 : 1;
}

void WiFiStream::config(IPAddress local_ip)
{
	WiFi.config( local_ip );
}

IPAddress WiFiStream::localIP()
{
    return WiFi.localIP();
}

void WiFiStream::setName(char* name, int length)
 {
     int len = min(length, 15);
     strncpy(this->name, name, len);
     this->name[len + 1] = 0;
 }

int WiFiStream::connect_client() 
{
    if (!(client && client.connected()))
	{
        WiFiClient newClient = server.available();
        if (!newClient)
		{
            return 0;
		}

        client = newClient;
    }
    
    return 1;
}

int WiFiStream::available()
{
    return connect_client() ? client.available() : 0;
}

int WiFiStream::read()
{
    return connect_client() ? client.read() : 0;
}

void WiFiStream::flush() {
    if (client) client.flush();
}

int WiFiStream::peek() {
    return client ? client.peek(): 0;
}

size_t WiFiStream::write(uint8_t outgoingByte) {  
    if(connect_client()) client.write(outgoingByte);
}

int WiFiStream::broadcastBeacon(int port)
 {
   Udp.beginPacket(broadcast, port);
   Udp.write("VS:A:");
   Udp.print(WiFi.localIP());
   Udp.write(':');
   Udp.print(port);
   Udp.write('=');
   Udp.print(name);
   Udp.endPacket();
 }
