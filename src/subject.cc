#include "subject.h"

void Subject::attach(std::shared_ptr<Observer> ob) {
    observers.emplace_back(ob);
}

void Subject::detach(std::string type) {
    if (type == "Cli") {
        observers.erase(observers.begin());
    } else if (!observers.empty()) {
        // erase(end()) is undefined behavior; the last element is prev(end()).
        observers.erase(std::prev(observers.end()));
    }
}

void Subject::drawBoard(std::string value, int posn1, int posn2, int posn3, int posn4) {
    for (auto ob: observers) {
        ob->drawBoard(value, posn1, posn2, posn3, posn4);
    }
}
