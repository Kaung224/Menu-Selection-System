#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "constants.h"

namespace seneca {

    // Define the maximum number of menu items


    // MenuItem class declaration
    class MenuItem {
    private:
        char* m_content;
        unsigned int m_indentation;
        unsigned int m_indentationSize;
        int m_rowNumber;

    public:
        // Constructor
        MenuItem(const char* content, unsigned int indentation, unsigned int indentationSize, int rowNumber);

        // Destructor
        ~MenuItem();

        // Method to display the menu item
        void display() const;
    };

    // Menu class declaration
    class Menu {
    private:
        MenuItem* m_title;
        MenuItem* m_exitOption;
        MenuItem* m_selectionPrompt;
        MenuItem* m_menuItems[MaximumNumberOfMenuItems];
        unsigned int m_indentation;
        unsigned int m_indentationSize;
        unsigned int m_numberOfMenuItems;

    public:
        // Constructor
        Menu(const char* titleContent, const char* exitOptionContent, unsigned int indentation = 0, unsigned int indentationSize = 3);

        // Destructor
        ~Menu();

        // Method to handle menu item selection
        unsigned int select() const;

        // Operator overloading to add menu items
        Menu& operator<<(const char* menuItemContent);

        // Friend function for output streaming
        friend int operator<<(std::ostream& ostr, const Menu& m);
    };

} // namespace seneca

#endif // MENU_H
