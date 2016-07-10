#ifndef MENU_H
#define MENU_H

#include <QMenuBar>
#include <iostream>

using namespace std;
class Menu
{
private:
    QMenu* menu;
public:
    Menu(QString name);
    ~Menu();
    bool existsMenuName(QString name);
    bool existsActionName(QString action);
    bool addAction(QAction*);
    QMenu* getMenu();
};

#endif // MENU_H
