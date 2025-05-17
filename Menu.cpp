#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include "Menu.h"

using namespace std;
namespace seneca {
    MenuItem::MenuItem(const char* content, unsigned int indentation, unsigned int indentationSize, int rowNumber) {
        if (content == nullptr) {
            m_content = nullptr;
            return;
        }
        else {
            m_content = new char[strlen(content) + 1];
            strcpy(m_content, content);
        }
        m_indentation = indentation;
        m_indentationSize = indentationSize;
        m_rowNumber = rowNumber;
    }

    MenuItem::~MenuItem() {
        delete[] m_content;
        m_content = nullptr;
    }

    void MenuItem::display() const {

        if (m_rowNumber == -1) {
            for (unsigned int i = 0; i < m_indentation * m_indentationSize; ++i) {
                cout << " ";
            }
            cout << m_content;
        }
        else {
            if (m_rowNumber < 10) {
                for (unsigned int i = 0; i <= m_indentation * m_indentationSize; ++i) {
                    cout << " ";
                }
                cout << m_rowNumber << "- " << m_content;
            }
            else {
                for (unsigned int i = 0; i < m_indentation * m_indentationSize; ++i) {
                    cout << " ";
                }
                cout << m_rowNumber << "- " << m_content;
            }

        }

    }

    Menu::Menu(const char* titleContent, const char* exitOptionContent, unsigned int indentation, unsigned int indentationSize)
    {
        m_indentation = indentation;
        m_indentationSize = indentationSize;
        m_numberOfMenuItems = 0;
        if (titleContent) {
            m_title = new MenuItem(titleContent, indentation, indentationSize, -1);
        }
        else {
            m_title = nullptr;
        }
        m_exitOption = new MenuItem(exitOptionContent, indentation, indentationSize, 0);
        m_selectionPrompt = new MenuItem("> ", indentation, indentationSize, -1);

        for (unsigned int i = 0; i < MaximumNumberOfMenuItems; ++i) {
            m_menuItems[i] = nullptr;
        }
    }

    Menu::~Menu() {
        delete m_title;
        delete m_exitOption;
        delete m_selectionPrompt;

        for (unsigned int i = 0; i < m_numberOfMenuItems; ++i) {
            delete m_menuItems[i];
        }
    }

    unsigned int Menu::select() const {
        if (m_title) {
            m_title->display();
            cout << endl;
        }

        for (unsigned int i = 0; i < m_numberOfMenuItems; ++i) {
            if (m_menuItems[i]) {
                m_menuItems[i]->display();
                cout << endl;
            }
        }

        if (m_exitOption) {
            m_exitOption->display();
            cout << endl;
        }

        if (m_selectionPrompt) {
            m_selectionPrompt->display();
        }
        
        int choice;
        string input;

        cin.ignore(2000, '\n');

        while (true) {
            getline(std::cin, input);
            if (input.empty()) {
                cout << "You must enter a value: ";
                continue;
            }

            istringstream iss(input);
            if (!(iss >> choice)) {
                cout << "Invalid integer: ";
                continue;
            }

            char trailingCha;
            if (iss >> trailingCha) {
                cout << "Only an integer please: ";
                continue;
            }

            if (choice < 0 || choice > static_cast<int>(m_numberOfMenuItems)) {
                cout << "Invalid value: [" << 0 << "<= value <=" << m_numberOfMenuItems << "], try again: ";
                continue;
            }

            break;
        }

        return static_cast<unsigned int>(choice);
    }

    Menu& Menu::operator<<(const char* menuItemContent) {
        if (m_numberOfMenuItems < MaximumNumberOfMenuItems) {
            m_menuItems[m_numberOfMenuItems] = new MenuItem(menuItemContent, m_indentation, m_indentationSize, m_numberOfMenuItems + 1);
            m_numberOfMenuItems++;
        }
        return *this;
    }

    int operator<<(ostream& ostr, const Menu& m) {
        if (&ostr == &cout) {
            return m.select();
        }
        return 0;
    }


}