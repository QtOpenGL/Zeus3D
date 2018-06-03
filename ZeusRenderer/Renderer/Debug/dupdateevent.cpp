#include "DUpdateEvent.h"

/*******************************************************************************
 * OpenGLError methods
 ******************************************************************************/
QEvent::Type DUpdateEvent::type()
{
    static QEvent::Type customEventType =
            static_cast<QEvent::Type>(QEvent::registerEventType());
    return customEventType;
}
