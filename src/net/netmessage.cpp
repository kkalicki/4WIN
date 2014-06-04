#include "../h/net/netmessage.h"


NetworkMessage::NetworkMessage(NetMessageType id)
{
    this->id = id;
}

NetworkMessage::~NetworkMessage()
{
    // Nicht implementiert --> Kein New
}

NetMessageType NetworkMessage::getId() const
{
    return id;
}

void NetworkMessage::setId(const NetMessageType &value)
{
    id = value;
}

char *NetworkMessage::toCharArray()
{
    char* buffer = static_cast<char*>(static_cast<void*>(this));
    return buffer;
}

void NetworkMessage::fromCharArray(char *buffer)
{
    NetworkMessage* temp = static_cast<NetworkMessage *>(static_cast<void*>(buffer));
    this->id = temp->id;
}
