#include "Text.h"

Text::Text(int x, int y, std::string t)
: Widget(x,y), _text(t) {}

Text::~Text()
{}

std::string Text::getText() {return _text;}

void Text::setText(std::string t) {_text = t;}

using namespace genv;

void Text::draw()
{
    gout << move_to(x() + 10,y() + 20) << color(255,255,255) << text(_text);
}

bool Text::contains(int xx, int yy) {
    return x() < xx
        && xx < x() + gout.twidth(_text)
        && y() - gout.cascent() < yy
        && y() + gout.cdescent() > yy;
}

void Text::handle(event ev) {
    Widget::handle(ev);
}
