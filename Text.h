#ifndef TEXT_H
#define TEXT_H
#include <string>
#include "Widget.h"
#include "graphics.hpp"

class Text: public Widget
{
    public:
        Text(int x, int y, std::string);
        virtual ~Text();
        std::string getText();
        void setText(std::string);
        virtual void draw() override;
        bool contains(int x, int y) override;
        virtual void handle(genv::event) override;

    protected:

    private:
        std::string _text = " ";
};

#endif // TEXT_H
