#include "Button.h"

using namespace std;

const int BUTTONSIZE = 30;

Button::Button(int x, int y, int val)
: Text(x,y,to_button_val(val)), _handler(nullptr), value(val), hasConflict(false)
{}

Button::~Button()
{
    delete _handler;
}

using namespace genv;

string Button::to_button_val(int val)
{
   string setVal = " ";
    if(val != 0)
    {
        stringstream ss;
        ss << val;
        setVal = ss.str();
    }

    return setVal;
}

void Button::increase()
{
    string setVal = " ";
    if(value == 9)
    {
        value = 0;
    }
    else
    {
        value++;
        stringstream ss;
        ss << value;
        setVal = ss.str();
    }

    Text::setText(setVal);
    Text::draw();
}

void Button::draw()
{
    gout << move_to(x(), y())
         << (hasConflict ? color(255,0,0) : color(0,180,100))
         << box_to(x() + BUTTONSIZE,
                   y() + BUTTONSIZE);
    Text::draw();
}

int Button::getValue()
{
    return value;
}

bool Button::contains(int xx, int yy) {
    return x() < xx
        && xx < x() + BUTTONSIZE
        && y() < yy
        && y() + BUTTONSIZE > yy;
}

void Button::setHandler(ClickHandler *ch) {
    _handler = ch;
}

void Button::handle(event ev) {
    Text::handle(ev);
    if (_handler != nullptr && ev.type == ev_mouse
        && ev.button == btn_left && contains(ev.pos_x, ev.pos_y))
        _handler->handleClick();
}

void Button::setConflict(bool conflict)
{
    hasConflict = conflict;
}
