#ifndef TAGHISTORICAL_H
#define TAGHISTORICAL_H

#include <QDateTime>

class TagScada;

class TagHistorical
{
public:
    int get_FrequencySecs();
    TagScada *get_TagScada();
    QDateTime get_LastSave();

    TagHistorical( TagScada *pTagScada, int frequencySecs );

    void SetLastSave();

private:
    TagScada *m_pTagScada;
    int m_FrequencySecs    ;
    QDateTime m_LastSave;
};

#endif // TAGHISTORICAL_H
