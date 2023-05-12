#include "scheduler.h"

OngoingEvent::OngoingEvent(std::function<int(float)> Func, float interval, float Expiration, ExpirationType et)
    : interval{interval}, expirationType{et}
{
    func = Func;
    expiration = expiration;
}

ScheduledEvent::ScheduledEvent(std::function<int(float)> Func, float expiration)
{
    func = Func;
    expiration = expiration;
}

Scheduler::Scheduler()
{

}

int Scheduler::addEvent(std::function<int(float)> Func, float interval, float expiration, ExpirationType et)
{
    OngoingEvent *event = nullptr;

    if (et == ExpirationInSeconds)
    {
        float expirationTime = expiration ? expiration + clock.getElapsedTime().asSeconds() : 0;

        event = new OngoingEvent{ Func, interval, expirationTime, ExpirationInSeconds };
    }
    else
    {
        event = new OngoingEvent{ Func, interval, expiration, ExpirationInIncrements };
    }

    event->setNextInterval(clock.getElapsedTime().asSeconds());

    events.push_back(event);

    return events.size();
}

int Scheduler::addEvent(std::function<int(float)> Func, float expiration)
{
    float expirationTime = expiration + clock.getElapsedTime().asSeconds();

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
    while (events.size() > 0 && event <= events.back())
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

        if (expired)
        {
            auto index = std::find(events.begin(), events.end(), event);
            auto new_iter = events.erase(index);
            if (new_iter != events.end())
                event = *new_iter;
        }
        else
            event++;
    }
}