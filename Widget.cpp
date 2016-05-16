#include "Widget.h"

Widget::Widget(int x, int y): _x(x), _y(y), focused(false)
{}

Widget::~Widget()
{}

int Widget::x() {return _x;}
int Widget::y() {return _y;}

using namespace genv;

void Widget::handle(event ev){
    if (ev.type == ev_mouse && ev.button == btn_left) {
        focused = contains(ev.pos_x, ev.pos_y);
    }
}
