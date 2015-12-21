//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <cassert>

#include "comms/CompileControl.h"

CC_DISABLE_WARNINGS()
#include <QtNetwork/QHostAddress>
CC_ENABLE_WARNINGS()

#include "ClientSocket.h"

namespace comms_champion
{

namespace plugin
{

namespace tcp_socket
{

ClientSocket::ClientSocket()
{
    connect(
        &m_socket, SIGNAL(connected()),
        this, SLOT(socketConnected()));
    connect(
        &m_socket, SIGNAL(disconnected()),
        this, SLOT(socketDisconnected()));
    connect(
        &m_socket, SIGNAL(readyRead()),
        this, SLOT(readFromSocket()));
    connect(
        &m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(socketErrorOccurred(QAbstractSocket::SocketError)));
}

ClientSocket::~ClientSocket() = default;

bool ClientSocket::setConnected(bool connected)
{
    if (connected) {
        return connectToServer();
    }

    return disconnectFromServer();
}

bool ClientSocket::connectToServer()
{
    if (m_tryingToConnect || m_connected) {
        assert(!"Already connected or trying to connect.");
        static const QString AlreadyConnectedError(
            tr("TCP/IP Client is already connected or trying to connect."));
        reportError(AlreadyConnectedError);
        return false;
    }

    if (m_host.isEmpty()) {
        m_host = QHostAddress(QHostAddress::LocalHost).toString();
    }

    m_tryingToConnect = true;
    m_forcedDisconnection = false;
    m_socket.connectToHost(m_host, m_port);
    return true;
}

bool ClientSocket::disconnectFromServer()
{
    m_tryingToConnect = false;
    m_forcedDisconnection = true;
    m_socket.disconnectFromHost();
    return true;
}

bool ClientSocket::startImpl()
{
    if (m_connectOnStart) {
        return connectToServer();
    }
    return true;
}

void ClientSocket::stopImpl()
{
    disconnectFromServer();
    disconnect(&m_socket);
    m_socket.close();
}

void ClientSocket::sendDataImpl(DataInfoPtr dataPtr)
{
    assert(dataPtr);
    m_socket.write(
        reinterpret_cast<const char*>(&dataPtr->m_data[0]),
        dataPtr->m_data.size());
}

void ClientSocket::socketConnected()
{
    m_connected = true;
    m_tryingToConnect = false;
    emit sigConnectionStatus(true);
}

void ClientSocket::socketDisconnected()
{
    bool mustReport = !m_forcedDisconnection;
    m_connected = false;
    m_tryingToConnect = false;
    m_forcedDisconnection = false;
    emit sigConnectionStatus(false);

    if (mustReport) {
        static const QString DisconnectedError(
            tr("Connection to TCP/IP Server was disconnected."));
        reportError(DisconnectedError);
    }
}

void ClientSocket::readFromSocket()
{
    auto* socket = qobject_cast<QTcpSocket*>(sender());
    assert(socket != nullptr);

    auto dataPtr = makeDataInfo();
    dataPtr->m_timestamp = DataInfo::TimestampClock::now();

    auto dataSize = socket->bytesAvailable();
    dataPtr->m_data.resize(dataSize);
    auto result =
        socket->read(reinterpret_cast<char*>(&dataPtr->m_data[0]), dataSize);
    if (result != dataSize) {
        dataPtr->m_data.resize(result);
    }

    // TODO: provide origin information
    reportDataReceived(std::move(dataPtr));
}

void ClientSocket::socketErrorOccurred(QAbstractSocket::SocketError err)
{
    static_cast<void>(err);
    auto* socket = qobject_cast<QTcpSocket*>(sender());
    assert(socket != nullptr);

    reportError(socket->errorString());
    disconnectFromServer();
}

}  // namespace tcp_socket

} // namespace plugin

} // namespace comms_champion