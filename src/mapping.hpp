#pragma once

#include <map>
#include <vector>

#include <ncurses.h>

#include "util.hpp"
#include "trie.hpp"

/// Defined secular actions
enum class Action {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    RESIZE,
    QUIT,
    SEARCH,
    SAVEQUIT,
    CMD,
    REDRAW,
    REPLACE,
    INSERT,
    APPEND,
    ERASE,
    FIRSTCOL,
    LASTCOL,
    NEXTBYTE,
    FIRSTBYTE,
    LASTBYTE,
    INCREMENT,
    DECREMENT,
    NEXTPRINTABLE,
    NEXTPRINTABLEBLOCK,
    NEXTFILLED,
    NEXTFILLEDBLOCK,
    NEXTTAB,
    UNDO,
    REDO,
};

class Mappings {
    using returnType = std::vector<Action>;
    using foo = std::map<std::vector<int>, returnType>;
    const foo defaults;
    Trie<int> bar;
public:
    Mappings();
    returnType operator ()(int);
};
