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

#include "veins/veins.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "../messages/DataMessage_m.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include <algorithm>

#include "veins/base/utils/FindModule.h"
#include "veins/modules/mac/ieee80211p/Mac1609_4.h"
//TODO: Added for Game theory Solution
#include "veins/modules/phy/DeciderResult80211.h"
#include "veins/base/phyLayer/PhyToMacControlInfo.h"
#include "veins/modules/messages/PhyControlMessage_m.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/mobility/base/MobilityBase.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
simsignal_t mobilityStateChangedSignal;


using namespace veins;
using namespace inet;

class Flooding : public veins::DemoBaseApplLayer {
protected:

    struct NeighborEntry {
        int senderAddress;
        inet::Coord position; // Neighbor position

        cMessage* beaconHoldTimer;
    };

    struct MessageInfoEntry {
        int messageID; // Message unique ID

        inet::Coord messageOriginPosition; // Message origin
        double messageROI; // Region of Interest in meters
        simtime_t messageOriginTime; // Time of message inception at source host
        simtime_t messageTTL; // Message's time-to-live
        int hops; // Message's number of hops

        simtime_t receptionTime;
        int messageLength;
        double distanceToOrigin;
    };

    enum {
        BACK_TRAFFIC_ENTRY_TIMEOUT = SEND_BEACON_EVT + 1,
        CCH_START,
        SCH_START,
    };

    //TODO: Added for Game theory Solution
    double curTxPower;
    int powerLevel;
    double myUtilityValue;

    bool wasInROI;

    bool disseminationStarted;

    simtime_t disseminationStartTime;

    veins::Mac1609_4* mac;

    cMessage* CCHStartTimer;

    cMessage* SCHStartTimer;

    long lastNumCollisions;

    long totalCollisions;

    veins::TraCIMobility* traci;

    // Used by the back-traffic application. Every time a node receives a beacon that has not been received in the last 3 seconds, then
    // it stores the info about the transmitter of the beacon and transmits 60 packets of 1000B. This simulates other applications
    // sharing the channel with the primary data dissemination.
    std::map<int, NeighborEntry*> lastRequesters;

    std::map<int, MessageInfoEntry*> messagesRcvd;

    virtual void initialize(int stage);
    virtual void finish();
    virtual void handleSelfMsg(cMessage* msg);
    virtual void onBeacon(veins::BaseFrame1609_4* wsm);
    virtual void onData(veins::BaseFrame1609_4* wsm);
    virtual bool isCCHActive();

    //TODO: Added for Game theory Solution
    virtual void adjustTxPower(veins::BaseFrame1609_4* wsm);
    virtual void decreaseTxPower();
    virtual void increaseTxPower();

    virtual MessageInfoEntry* extractMsgInfo(veins::BaseFrame1609_4* wsm);
    virtual bool isDuplicateMsg(int messageID);
    virtual bool isInsideROI(MessageInfoEntry* info);
    virtual bool isMessageAlive(MessageInfoEntry* info);
    virtual veins::BaseFrame1609_4* createDataMsg(MessageInfoEntry* info);
    virtual void processBackTraffic(int senderAddr);

    virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details);
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, const SimTime& t);

public:
    //TODO: Added for Game theory Solution
    simsignal_t lastTxPower;
    simsignal_t meanSNR;

    simsignal_t sentDownMACInCCH; // Indicate the total number of messages sent down to MAC when the CCH was active
    simsignal_t collisions; // Indicate the total number of collisions
    simsignal_t duplicatedMessages; // Indicate the number of duplicate messages received by a vehicle
    simsignal_t messagesTransmitted; // Indicate the number of messages transmitted by a vehicle
    simsignal_t messagesReceived; // Indicate whether the message was received or not
    simsignal_t isInROI; // Indicate whether the vehicle is inside the ROI at the time the dissemination starts

    virtual ~Flooding();
};
