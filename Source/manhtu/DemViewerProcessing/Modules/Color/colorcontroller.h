#ifndef COLORCONTROLLER_H
#define COLORCONTROLLER_H

#include <QObject>
#include "Controller/actioninterface.h"
#include "Controller/actionlistener.h"

class ColorRGBA
{
public:
    float r;
    float g;
    float b;

    ColorRGBA(){}
    ColorRGBA(float red, float green, float blue){
        r = red;
        g = green;
        b = blue;
    }

    float red(){
        return r;
    }
    float green()
    {
        return g;
    }
    float blue()
    {
        return b;
    }
};

class ColorController : public QObject, public ActionInterface
{
    Q_OBJECT
private:
    vector<ColorRGBA> data_colors;
    ActionListener* actionListener;
    void addColor(ColorRGBA color1, ColorRGBA color2, int step);
public:
    ColorController(QObject *parent = 0);

    // ActionInterface interface
public:
    void initAction();
    void terminalAction();
    QString getActionName();
    bool loadOnBoot();
    bool requireDemObject();
    void setDemObject(DemInterface *);
    DemInterface *getDemObject();
    void setGraphics(GraphicsComposite *);
    ColorRGBA getColor(float height);
    QVector3D getVectorColor(float height);
    void setActionPerform(ActionListener *);
};

#endif // COLORCONTROLLER_H
