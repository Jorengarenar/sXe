#include "mapping.hpp"
#include "editor.hpp"

Mappings::Mappings() :
    defaults{
        { { KEY_RESIZE }, { Action::RESIZE } },
        { { ':' }, { Action::CMD } },
        { { 'h' }, { Action::LEFT } },
        { { 'j' }, { Action::DOWN } },
        { { 'k' }, { Action::UP } },
        { { 'l' }, { Action::RIGHT } },
        { { 'r' }, { Action::REPLACE } },
        { { 'i' }, { Action::INSERT } },
        { { 'I' }, { Action::FIRSTCOL, Action::INSERT } },
        { { 'a' }, { Action::APPEND } },
        { { 'A' }, { Action::FIRSTCOL, Action::APPEND } },
        { { 'x' }, { Action::ERASE } },
        { { '0' }, { Action::FIRSTCOL } },
        { { ' ' }, { Action::NEXTBYTE } },
        { { '$' }, { Action::LASTCOL } },
        { { 'G' }, { Action::LASTBYTE } },
        { { 'w' }, { Action::NEXTPRINTABLE } },
        { { 'W' }, { Action::NEXTPRINTABLEBLOCK } },
        { { '\n' }, { Action::DOWN, Action::FIRSTCOL } },
        { { 'g', '0' }, { Action::FIRSTCOL } },
        { { 'g', 'g' }, { Action::FIRSTBYTE } },
        { { 'g', 't' }, { Action::NEXTTAB } },
        { { 'Z', 'Z' }, { Action::SAVEQUIT } },
        { { CTRL('a') }, { Action::INCREMENT } },
        { { CTRL('x') }, { Action::DECREMENT } },
        { { 'u' }, { Action::UNDO } },
        { { CTRL('r') }, { Action::REDO } },
    }
{
    for (auto m: defaults) {
        bar.add(m.first);
    }
}

Mappings::returnType Mappings::operator ()(int c)
{
    auto endings = bar.getEndings(c);
    if (endings != nullptr) {
        std::vector<int> compound{c};

        do {
            c = Editor().input();
            compound.push_back(c);
            endings = bar.getEndings(compound);
        } while (endings != nullptr);

        auto r = defaults.find(compound);
        if (r != defaults.end()) {
            return r->second;
        }
        else {
            compound.pop_back();
            r = defaults.find(compound);
            if (r != defaults.end()) {
                return r->second;
            }
            return { Action::NONE };
        }

    }
    else {
        auto x = defaults.find({ c });
        if (x != defaults.end()) {
            return x->second;
        }
    }

    return { Action::NONE };
}
