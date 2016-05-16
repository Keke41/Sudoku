#ifndef BUTTON_H
#define BUTTON_H

#include <sstream>
#include <string>

#include "Text.h"
#include "ClickHandler.h"

class Button : public Text
{
    public:
        Button(int, int,int);
        virtual ~Button();
        virtual void draw() override;
        void setHandler(ClickHandler*);
        void handle(genv::event) override;
        bool contains(int x, int y) override;
        int getValue();
        void increase();
        void setConflict(bool conflict);
        std::string to_button_val(int val);
    protected:

    private:
        ClickHandler* _handler;
        int value;
        bool hasConflict;
};

#endif // BUTTON_H
