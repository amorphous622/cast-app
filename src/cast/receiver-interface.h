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

#include "interface.h"

namespace cast {

class ReceiverInterface : public Interface {
    Q_OBJECT
public:
    ReceiverInterface(Channel *channel);
    virtual ~ReceiverInterface();

    static const std::string URN;

    bool launch(const QString& app_id);
    bool stop(const QString& session_id);
    bool getStatus();

private Q_SLOTS:
    void onMessageReceived(const QString& data);

private:
    int last_request_ = 0;
};

}