#ifndef _TEXT_H
#define _TEXT_H
#include "Observer.h"
#include "Table.h"
#include <memory>

class TableObserver : public Observer {
private:
    shared_ptr<Table> subject;
public: 
    TableObserver(shared_ptr<Table> subject);
    void notify() override;
    ~TableObserver();
};

#endif
