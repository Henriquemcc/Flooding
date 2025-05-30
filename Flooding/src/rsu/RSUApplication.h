//
// This program is free software: you can redistribute it and/or modify
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
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "../messages/DataMessage_m.h"
#include "inet/mobility/base/MobilityBase.h"

#include <fstream>

class RSUApplication : public veins::DemoBaseApplLayer
{

private:
    struct MessageEntryInfo {
        int ID;
        int length;
    };

    enum {
        SEND_DATA = SEND_BEACON_EVT + 1,
        END_SIMULATION,
    };

protected:
    cMessage* sendDataTimer;

    double datarate;

    bool disseminationStarted;

    std::map<simtime_t, MessageEntryInfo*> loggingInfo;

    std::list<MessageEntryInfo*> outputQueue;

    virtual void initialize(int stage);
    virtual void finish();

    virtual void handleSelfMsg(cMessage* msg);
    virtual void onBeacon(veins::BaseFrame1609_4* wsm);
    virtual void onData(veins::BaseFrame1609_4* wsm);

    virtual void sendData();
    virtual void readDataFromFile();

    virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details);

public:
    // Signal used to inform vehicles that the dissemination has started. Once a vehicle receives the signal, it
    // verifies whether it is inside the ROI or not. Therefore, this signal is used to identify the vehicles
    // inside the ROI at the time the dissemination starts. This information is used in the calculation of the
    // coverage
    simsignal_t disseminationStartTime;
    ~RSUApplication();
};
