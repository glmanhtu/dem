#include "colorcontroller.h"

ColorController::ColorController(QObject *parent): QObject(parent)
{
    addColor(ColorRGBA(25,0,40), ColorRGBA(35,0,58), 4000);
    addColor(ColorRGBA(35,0,58), ColorRGBA(20,0,75), 2000);
    addColor(ColorRGBA(20,0,75), ColorRGBA(6,0,111), 2000);
    addColor(ColorRGBA(6,0,111), ColorRGBA(0,19,156), 1000);
    addColor(ColorRGBA(0,19,156), ColorRGBA(6,60,166), 1000);
    addColor(ColorRGBA(6,60,166), ColorRGBA(21,100,171), 850);
    addColor(ColorRGBA(21,100,171), ColorRGBA(51,147,201), 100);
    addColor(ColorRGBA(51,147,201), ColorRGBA(71,183,190), 30);
    addColor(ColorRGBA(71,183,190), ColorRGBA(103,186,191), 15);
    addColor(ColorRGBA(103,186,191), ColorRGBA(131,193,196), 5);

    addColor(ColorRGBA(31,83,54), ColorRGBA(26,103,37), 10);
    addColor(ColorRGBA(26,103,37), ColorRGBA(181,171,88), 490);
    addColor(ColorRGBA(181,171,88), ColorRGBA(145,57,9), 1500);
    addColor(ColorRGBA(145,57,9), ColorRGBA(130,0,1), 1000);
    addColor(ColorRGBA(130,0,1), ColorRGBA(91,85,85), 2000);
    addColor(ColorRGBA(91,85,85), ColorRGBA(223,223,223), 2500);
    addColor(ColorRGBA(223,223,223), ColorRGBA(255,255,255), 1500);
}

void ColorController::addColor(ColorRGBA color1, ColorRGBA color2, int step)
{
    float interval_R = (float)(color2.red() - color1.red()) / step;
    float interval_G = (float)(color2.green() - color1.green()) / step;
    float interval_B = (float)(color2.blue() - color1.blue()) / step;

    float current_R = color1.red();
    float current_G = color1.green();
    float current_B = color1.blue();

    data_colors.push_back(color1);
    for (int i = 0; i <= step; i++)
    {
        current_R += interval_R;
        current_G += interval_G;
        current_B += interval_B;
        data_colors.push_back(ColorRGBA(current_R, current_G, current_B));
    }
    data_colors.push_back(color2);
}

ColorRGBA ColorController::getColor(float height) {

    ColorRGBA* c = new ColorRGBA();
    ColorRGBA color = data_colors[height+11000];
    c->r = color.red()/255;
    c->g = color.green()/255;
    c->b = color.blue()/255;
    return *c;
}

QVector3D ColorController::getVectorColor(float height)
{
    ColorRGBA color = data_colors[height+11000];
    return QVector3D(
        color.red()/255,
        color.green()/255,
        color.blue()/255
    );
}

void ColorController::initAction()
{
}

void ColorController::terminalAction()
{
}

QString ColorController::getActionName()
{
    return "Color.ColorController";
}

bool ColorController::loadOnBoot()
{
    return true;
}

bool ColorController::requireDemObject()
{
    return false;
}

void ColorController::setDemObject(DemInterface *)
{
}

DemInterface *ColorController::getDemObject()
{
    return NULL;
}

void ColorController::setGraphics(GraphicsComposite *)
{
}


void ColorController::setActionPerform(ActionListener *)
{
}
