#ifndef ALARMSMANAGER_SPY_H
#define ALARMSMANAGER_SPY_H

#include "alarmsmanager.h"

class AlarmsManager_Spy : public AlarmsManager
{
public:
    QList<Alarm*> *get_Alarms();

    AlarmsManager_Spy( AlarmsManager *pAlarmsManager );
};

#endif // ALARMSMANAGER_SPY_H
