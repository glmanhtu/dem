#ifndef ACTIONLISTENER_H
#define ACTIONLISTENER_H

#include <iostream>
#include <vector>
#include "actioninterface.h"
#include <QWidget>



using namespace std;
class ActionListener
{
private:
    vector<ActionInterface*> actions;
    DemInterface* dem;
public:
    ActionListener();
    ~ActionListener();
    void registerAction(ActionInterface*);
    ActionInterface* getAction(QString);
    void setDemObject(DemInterface*);
};

#endif // ACTIONLISTENER_H
