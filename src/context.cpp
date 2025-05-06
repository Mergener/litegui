#include "context.h"

namespace litegui {

Event<ClickEvent>& EventContext::click_event() {
    return callable_events().click;
}

Event<ClickEvent>& EventContext::release_event() {
    return callable_events().release;
}

EventContext::CallableEventContext& EventContext::callable_events() {
    return m_events;
}

} // litegui