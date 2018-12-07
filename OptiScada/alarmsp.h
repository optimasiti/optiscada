#ifndef ALARMSP_H
#define ALARMSP_H

#include "alarm.h"

class TagScada;

class AlarmSP : public Alarm
{
public:
    AlarmSP( QString name, TagScada *pTagSP, TagScada *pTagPV, double tolerance );
    virtual ~AlarmSP();

    virtual void Evaluate();

private:
    TagScada *m_pTagSP;
    TagScada *m_pTagPV;
    double m_Tolerance;
};

#endif // ALARMSP_H
