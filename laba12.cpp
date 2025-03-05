#include <iostream>
#include <list>
#include <iterator>
#include <ctime>

struct Event {
    std::time_t timestamp;
    std::string description;

    Event(std::time_t t, std::string desc) : timestamp(t), description(desc) {}
};

class TimeIntervalIterator {
private:
    std::list<Event>::iterator current;
    std::list<Event>::iterator end;
    std::time_t startTime, endTime;

public:
    TimeIntervalIterator(std::list<Event>::iterator begin, std::list<Event>::iterator end, std::time_t start, std::time_t finish)
        : current(begin), end(end), startTime(start), endTime(finish) {
        while (current != end && (current->timestamp < startTime || current->timestamp > endTime)) {
            ++current;
        }
    }

    TimeIntervalIterator& operator++() {
        do {
            ++current;
        } while (current != end && (current->timestamp < startTime || current->timestamp > endTime));
        return *this;
    }

    bool operator!=(const TimeIntervalIterator& other) const {
        return current != other.current;
    }

    Event& operator*() {
        return *current;
    }
};

int main() {
    std::list<Event> log = {
        {1672531200, "Event 1"}, // 01.01.2023 00:00:00
        {1672617600, "Event 2"}, // 02.01.2023 00:00:00
        {1672704000, "Event 3"}, // 03.01.2023 00:00:00
        {1672790400, "Event 4"}  // 04.01.2023 00:00:00
    };

    std::time_t start = 1672617600; // 02.01.2023
    std::time_t end = 1672704000;   // 03.01.2023

    TimeIntervalIterator it(log.begin(), log.end(), start, end);
    TimeIntervalIterator endIt(log.end(), log.end(), start, end);

    std::cout << "Events in the selected time interval:\n";
    while (it != endIt) {
        std::cout << (*it).description << " (" << (*it).timestamp << ")\n";
        ++it;
    }

    return 0;
}
