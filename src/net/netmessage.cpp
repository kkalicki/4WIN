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
