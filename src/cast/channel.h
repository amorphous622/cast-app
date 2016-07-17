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

#pragma once

#include "caster.h"

#include <QByteArray>
#include <QObject>
#include <QString>

#include <string>

namespace cast {

class Interface;

class Channel : public QObject {
    Q_OBJECT
public:
    Channel(Caster *caster, const std::string& source_id,
            const std::string& destination_id);
    virtual ~Channel();

    Q_INVOKABLE cast::Interface* addInterface(const QString& namespace_);
    Q_INVOKABLE void close();

Q_SIGNALS:
    void closed();

private:
    Caster& caster();
    const Caster& caster() const;
    void handleMessage(const Caster::Message& message);

    const std::string source_id_;
    const std::string destination_id_;

    bool closed_ = false;
    std::map<std::string,Interface*> interfaces_;

    friend class Caster;
    friend class Interface;
};

}