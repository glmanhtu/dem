#include "menu.h"

Menu::Menu(QString name)
{
    menu = new QMenu(name);
}

bool Menu::existsMenuName(QString name)
{
    if (menu->accessibleName() == name) {
        return true;
    } else {
        return false;
    }
}

bool Menu::existsActionName(QString action)
{
    for(int i=0; i< menu->actions().size(); i++) {
        if (menu->actions().at(i)->text() == action) {
            return true;
        }
    }
    return false;
}

bool Menu::addAction(QAction * action)
{
    menu->addAction(action);
    return true;
}

QMenu* Menu::getMenu()
{
    return menu;
}

Menu::~Menu()
{
    delete menu;
}
