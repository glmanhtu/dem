#include "graphicscomposite.h"
#include "graphics.h"

void GraphicsComposite::setMainGraphics(GraphicsComposite * parent)
{
    graphicsMain = parent;
}

void GraphicsComposite::setDemObject(DemInterface *dem)
{
    demObject = dem;
}

void GraphicsComposite::addVertex(Vertex vertex)
{
    graphicsMain->addVertex(vertex);
}

GraphicsComposite* GraphicsComposite::getMainGraphics()
{
    return graphicsMain;
}

void GraphicsComposite::setSize(int width, int height)
{
    graphicsMain->setSize(width, height);
}

void GraphicsComposite::updateGraphics()
{
    graphicsMain->updateGraphics();
}

QAction* GraphicsComposite::createQAction(QString name)
{
    return new QAction(name, (Graphics*)graphicsMain);
}

void GraphicsComposite::registerGraphics(GraphicsComposite* graphic)
{
    graphic->setMainGraphics(graphicsMain);
    if (graphic->addToGraphicsComponent() == addToGraphicsComponent()) {
        graphics.push_back(graphic);
    } else {
        for (int i=0; i<graphics.size(); i++) {
            graphics[i]->registerGraphics(graphic);
        }
    }
}

void GraphicsComposite::setActionPerform(ActionListener* action)
{
    actions = action;
}

bool GraphicsComposite::addMenu(QString menuName, QAction *action)
{
    /**
     * Check if menu already exists
    **/
    for (int i=0; i<menus.size(); i++) {
        if (menus[i]->existsMenuName(menuName)) {

            if (menus[i]->existsActionName(action->text())) {
                // Menu & Action already exists
                return false;
            } else {
                // Menu exists but Action
                menus[i]->addAction(action);
                return true;
            }
        }
    }

    /**
     * If not exists, create a new one
    **/
    Menu* menu = new Menu(menuName);
    menu->addAction(action);
    menus.push_back(menu);
    return true;
}



ActionInterface* GraphicsComposite::getAction(QString name)
{
    return this->actions->getAction(name);
}

bool GraphicsComposite::registerMenu(QMenuBar * qMenuBar)
{
    for (int i=0; i<menus.size(); i++) {
        qMenuBar->addMenu(menus[i]->getMenu());
    }
    for (int i=0; i<graphics.size(); i++)
    {
        graphics[i]->registerMenu(qMenuBar);
    }
    return true;
}

int GraphicsComposite::addToGraphicsComponent()
{
    return GRAPHICS_ID;
}
