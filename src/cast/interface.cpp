/*
 * cast-qml: Chromecast binding for QML
 * Copyright (C) 2016  James Henstridge
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "interface.h"
#include "channel.h"

namespace cast {

Interface::Interface(Channel *channel, const std::string& namespace_)
    : QObject(channel), namespace_(namespace_) {
}

Interface::~Interface() = default;

Channel& Interface::channel() {
    return *static_cast<Channel*>(parent());
}

const Channel& Interface::channel() const {
    return *static_cast<const Channel*>(parent());
}

bool Interface::send(const QString& data) {
    Caster::Message message;
    message.set_protocol_version(Caster::Message::CASTV2_1_0);
    message.set_source_id(channel().source_id_);
    message.set_destination_id(channel().destination_id_);
    message.set_namespace_(namespace_);
    message.set_payload_type(Caster::Message::STRING);
    message.set_payload_utf8(data.toStdString());
    return channel().caster().sendMessage(message);
}

bool Interface::sendBinary(const QByteArray& data) {
    Caster::Message message;
    message.set_protocol_version(Caster::Message::CASTV2_1_0);
    message.set_source_id(channel().source_id_);
    message.set_destination_id(channel().destination_id_);
    message.set_namespace_(namespace_);
    message.set_payload_type(Caster::Message::BINARY);
    message.set_payload_binary(data.constData(), data.size());
    return channel().caster().sendMessage(message);
}

void Interface::handleMessage(const Caster::Message& message) {
    switch (message.payload_type()) {
    case Caster::Message::STRING:
        Q_EMIT messageReceived(QString::fromStdString(message.payload_utf8()));
        break;
    case Caster::Message::BINARY: {
        const auto& data = message.payload_binary();
        Q_EMIT binaryMessageReceived(QByteArray(&data[0], data.size()));
        break;
    }
    default:
        qWarning() << "Unsupported payload type:" << message.payload_type();
        break;
    }
}

}
