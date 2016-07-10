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
public:
    ActionListener();
    ~ActionListener();
    void registerAction(ActionInterface*);
    ActionInterface* getAction(QString);

};

#endif // ACTIONLISTENER_H
