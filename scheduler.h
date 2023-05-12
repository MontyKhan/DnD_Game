#pragma once
#include <vector>
#include <functional>

#include "SFML/System.hpp"

typedef enum {
    ExpirationInSeconds,
    ExpirationInIncrements,
} ExpirationType;

class TimeEvent
{
protected:
    std::function<void(float)> func;
    float expiration;

public:
    TimeEvent() {
        func = [](float f) {return f; };
    };
    TimeEvent(std::function<void(float)> Func) { func = Func; };
    virtual void setFunc(std::function<void(float)> Func) { func = Func; };
    virtual std::function<void(float)> getFunc() { return func; };

    void execute(float time) { func(time); };

    float getExpiration() { return expiration; };
};

class OngoingEvent : public virtual TimeEvent
{
private:
    float interval;
    float nextInterval;
    ExpirationType expirationType;

public:
    OngoingEvent() : interval{ 0 }, nextInterval{ 0 }, expirationType { ExpirationInSeconds } {};
    OngoingEvent(std::function<void(float)> Func, float Interval, float Expiration = 0, ExpirationType et = ExpirationInSeconds);
    
    void setNextInterval(float currentTime) { nextInterval = currentTime + interval; };
    void setNextInterval() { nextInterval += interval; };
    float getNextInterval() { return nextInterval; };
};

class ScheduledEvent : public virtual TimeEvent
{
private:

public:
    ScheduledEvent() {};
    ScheduledEvent(std::function<void(float)> Func, float Expiration);
};

class Scheduler
{
private:
    sf::Clock clock;
    std::vector<TimeEvent*> events;

public:
    Scheduler();
    int addEvent(TimeEvent *event) { events.push_back(event); return events.size(); };
    int addEvent(std::function<void(float)> Func, float Interval, float Expiration, ExpirationType et = ExpirationInSeconds);
    int addEvent(std::function<void(float)> Func, float Expiration);
    void executeEvents();
};

