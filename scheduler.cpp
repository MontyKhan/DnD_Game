#include "scheduler.h"

OngoingEvent::OngoingEvent(std::function<void(float)> Func, float Interval, float Expiration, ExpirationType et)
    : interval{Interval}, expirationType{et}
{
    func = Func;
    expiration = Expiration;
}

ScheduledEvent::ScheduledEvent(std::function<void(float)> Func, float Expiration)
{
    func = Func;
    expiration = Expiration;
}

Scheduler::Scheduler()
{

}

int Scheduler::addEvent(std::function<void(float)> Func, float Interval, float Expiration, ExpirationType et)
{
    OngoingEvent *event = nullptr;

    if (et == ExpirationInSeconds)
    {
        float expirationTime = Expiration ? Expiration + clock.getElapsedTime().asSeconds() : 0;

        event = new OngoingEvent{ Func, Interval, expirationTime, ExpirationInSeconds };
    }
    else
    {
        event = new OngoingEvent{ Func, Interval, Expiration, ExpirationInIncrements };
    }

    event->setNextInterval(clock.getElapsedTime().asSeconds());

    events.push_back(event);

    return events.size();
}

int Scheduler::addEvent(std::function<void(float)> Func, float Expiration)
{
    float expirationTime = Expiration + clock.getElapsedTime().asSeconds();

    ScheduledEvent *event = new ScheduledEvent{ Func, expirationTime};

    events.push_back(event);

    return events.size();
}

void Scheduler::executeEvents()
{
    sf::Time elapsedTime = clock.getElapsedTime();
    float seconds = elapsedTime.asSeconds();

    if (events.size() == 0)
        return;

    TimeEvent *event = events.front();
    while (events.size() > 0 && event != nullptr)
    {
        bool expired = false;
        auto ongoingEvent = dynamic_cast<OngoingEvent *>(event);
        auto scheduledEvent = dynamic_cast<ScheduledEvent *>(event);

        if (ongoingEvent)
        {
            if (ongoingEvent->getExpiration() > 0 && seconds > ongoingEvent->getExpiration())
                expired = true;
            else if (ongoingEvent->getNextInterval() < seconds)
            {
                ongoingEvent->execute(seconds);
                ongoingEvent->setNextInterval();
            }
        }
        else if (scheduledEvent)
        {
            if (seconds > scheduledEvent->getExpiration())
            {
                expired = true;
                scheduledEvent->execute(seconds);
            }
        }

        auto index = std::find(events.begin(), events.end(), event);
        if (expired)
        {
            auto new_iter = events.erase(index);
            if (new_iter != events.end())
                event = *new_iter;
            else
                event = nullptr;
        }
        else
            event = (index + 1 != events.end() ? *(index + 1) : nullptr);
    }
}