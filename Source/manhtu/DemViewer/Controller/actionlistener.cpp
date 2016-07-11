#include "actionlistener.h"

ActionListener::ActionListener()
{

}

void ActionListener::registerAction(ActionInterface *action)
{
    if (action->requireDemObject()) {
        action->setDemObject(dem);
    }
    actions.push_back(action);
}

void ActionListener::setDemObject(DemInterface * demObj)
{
    dem = demObj;
}

ActionInterface* ActionListener::getAction(QString name)
{
    for(int i=0; i<actions.size(); i++) {
        if (actions[i]->getActionName() == name) {
            return actions[i];
        }
    }
    return NULL;
}

ActionListener::~ActionListener()
{
    for(int i=0; i<actions.size(); i++) {
        delete actions[i];
    }
}

