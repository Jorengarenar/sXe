#pragma once

#include <vector>
#include <memory>

#include <ncurses.h>

#include "buffer.hpp"
#include "cli.hpp"
#include "mapping.hpp"
#include "options.hpp"
#include "parser.hpp"
#include "window.hpp"

/// Editor
///
/// Contains main functionalities of program
class Editor {
    Editor() {}
public:
    Editor(const Editor&)         = delete;
    void operator=(const Editor&) = delete;

    // singleton, bc I ain't gonna throw handles all around
    static Editor& getInstance()
    {
        static Editor instance;
        return instance;
    }

private:
    /// Initializes curses
    struct InitCurses {
        InitCurses();
        ~InitCurses();
    } initCurses;

    std::vector<Buffer> buffers; ///< List of opened buffers
    std::vector<std::shared_ptr<Window>> windows; ///< List of existing windows

    void replaceByte(); ///< Wrapper over cw->replaceByte()

public:
    std::shared_ptr<Window> cw;       ///< Current window
    Cli cli;          ///< Command line
    Parser parser;    ///< Parses configs and commands
    Options options;
    Mappings mappings;

    void init(int argc, char* argv[], int optind); // yes, copy of main() arguments
    ~Editor() = default;

    int input(); ///< Gets keystrokes
    int loop();  ///< Interprets keystrokes into actions

    void setOption(std::string);

    WINDOW* statusline;
    WINDOW* tabline;

    void updateStatusline();
    void updateTabline();

    std::size_t winNr();
    void newWin();
    void switchWin(int);
};

#define Editor() Editor::getInstance()
