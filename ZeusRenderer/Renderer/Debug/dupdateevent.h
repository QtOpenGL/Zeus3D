#ifndef DUPDATEEVENT_H
#define DUPDATEEVENT_H

#include <QEvent>
/*******************************************************************************
 * 定制KUpdateEvent,更新事件，继承自QEvent，例如用于Eror事件
 ******************************************************************************/
class DUpdateEvent : public QEvent
{
public:
    DUpdateEvent();
    // Static Access
    static QEvent::Type type();
};

inline DUpdateEvent::DUpdateEvent() : QEvent(DUpdateEvent::type()) {}
#endif // DUPDATEEVENT_H
