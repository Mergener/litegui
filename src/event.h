#ifndef LITEGUI_EVENT_H
#define LITEGUI_EVENT_H

#include <algorithm>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>

namespace litegui {

//
// Forward declarations
//
template <typename T>
class ScopedHandlerRef;
template <typename T>
class HandlerRef;
//

template<typename T>
class Event {
public:
    using Handler = std::function<void(const T& arg)>;

    /**
     * Registers an event handler.
     * @param handler The handler functor.
     * @return A reference to the handler that allows unregistering it futurely.
     */
    HandlerRef<T> add_handler(const Handler& handler);

protected:
    using HandlerId = int;
    class State {
    public:
        void call(const T& arg) {
            std::shared_lock lock(m_mutex);
            for (const auto& hnd: m_handlers) {
                hnd.second(arg);
            }
        }

        bool has_handler(HandlerId id) {
            std::shared_lock lock(m_mutex);
            for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it) {
                if (it->first == id) {
                    return true;
                }
            }
            return false;
        }

        HandlerId add_handler(const Handler& handler) {
            std::unique_lock lock(m_mutex);
            HandlerId id = m_next_id++;
            m_handlers.push_back({ id, handler });
            return id;
        }

        void remove_handler(HandlerId id) {
            std::unique_lock lock(m_mutex);
            for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it) {
                if (it->first == id) {
                    m_handlers.erase(it);
                    break;
                }
            }
        }

        void clear() {
            std::unique_lock lock(m_mutex);
            m_handlers.clear();
        }

    private:
        std::deque<std::pair<HandlerId, Handler>> m_handlers;
        std::shared_mutex m_mutex;
        HandlerId m_next_id = 0;
    };

protected:
    std::shared_ptr<State> m_state = std::make_shared<State>();

    friend class ScopedHandlerRef<T>;
    friend class HandlerRef<T>;

    Event() = default;
};

template<typename T>
class CallableEvent : public Event<T> {
public:
    /**
     * Invokes this event.
     * @param arg The event arguments passed to each handler.
     */
    void call(const T& arg);

    CallableEvent() = default;
};

/**
 * A reference to an event handler stored in an event.
 * Use this reference to manage the lifetime of the handler.
 * If you want RAII style event unregistering, simply call .scoped()
 * and move the returned scoped ref to the desired scope.
 */
template <typename T>
class HandlerRef {
public:
    /**
     * Returns true if the event is still callable and the handler
     * is still registered.
     */
    [[nodiscard]] bool alive() const {
        auto ptr = m_ev.lock();
        if (ptr == nullptr) {
            return false;
        }
        return ptr->has_handler(m_id);
    }

    /**
     * Unregisters the handler. Does nothing if the handler had
     * already been unregistered.
     */
    void unregister() const {
        auto ptr = m_ev.lock();
        if (ptr == nullptr) {
            return;
        }
        return ptr->remove_handler(m_id);
    }

    /**
     * Returns a scoped reference to the event handler that automatically
     * unregisters the handler when it goes out of scope.
     */
    [[nodiscard]] ScopedHandlerRef<T> scoped() const;

    HandlerRef() = default;
    HandlerRef(const HandlerRef<T>& other) = default;
    HandlerRef<T>& operator=(const HandlerRef<T>& other) = default;
    HandlerRef(HandlerRef<T>&& other) noexcept = default;

private:
    using EvState = typename Event<T>::State;
    using HandlerId = typename Event<T>::HandlerId;

    std::weak_ptr<EvState> m_ev = nullptr;
    HandlerId m_id = 0;

    explicit HandlerRef(std::weak_ptr<EvState> ev,
                        HandlerId id)
        : m_ev(ev), m_id(id) { }

    friend class Event<T>;
    friend class ScopedHandlerRef<T>;
};

template <typename T>
class ScopedHandlerRef {
public:
    explicit ScopedHandlerRef(const HandlerRef<T>& ref) noexcept
        : m_ref(ref) {}
    ScopedHandlerRef(const ScopedHandlerRef&) = delete;
    ScopedHandlerRef& operator=(const ScopedHandlerRef&) = delete;

    ScopedHandlerRef(ScopedHandlerRef&& other) noexcept
        : m_ref(other.m_ref) {
        other.m_ref.m_ev = nullptr;
    }

    ~ScopedHandlerRef() {
        m_ref.unregister();
    }

private:
    HandlerRef<T> m_ref;
};

template <typename T>
ScopedHandlerRef<T> HandlerRef<T>::scoped() const {
    return ScopedHandlerRef<T>(*this);
}

template <typename T>
HandlerRef<T> Event<T>::add_handler(const Handler& handler) {
    return HandlerRef<T>(std::weak_ptr<State>(m_state), m_state->add_handler(handler));
}

template <typename T>
void CallableEvent<T>::call(const T& arg) {
    this->m_state->call(arg);
}

} // litegui

#endif // LITEGUI_EVENT_H
