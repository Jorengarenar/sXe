#pragma once

#include <functional>
#include <memory>
#include <utility>

#include <ncurses.h>

#include "buffer.hpp"

enum class Direction { DOWN, UP, RIGHT, LEFT };

/// Window
///
/// Edits and displays buffers
class Window {
public:
    explicit Window(Buffer&);
    ~Window();

    std::size_t currentByte; ///< Byte cursor is currently over
    std::size_t prevByte;    ///< Byte cursor was previously over

    std::size_t startline; ///< "Line" of buffer from which to start printing

    void buf(Buffer&);         ///< Change buffer in window
    void redraw();             ///< Redraws window
    void applyToSubWindows(std::function<void (WINDOW*)>);  ///< Apply function to subwindows
    void delSubWindows();
    void save();                                            ///< Save currently loaded buffer

    int replaceByte(); ///< Replaces value of byte
    int insertByte();
    void eraseByte();
    void addToByte(unsigned char); ///< Adds value to current byte

    void mvCursor(Direction); ///< Movement
    void mvCursorToColumn(std::size_t X);
    void mvCursor(std::size_t, std::size_t); ///< Movement

    void gotoByte(std::size_t); ///< Move directly to byte of given number

    struct {
        WINDOW* numbers;
        WINDOW* hex;
        WINDOW* text;
    } subWindows;

    Buffer* buffer;
    std::pair<std::size_t, std::size_t> onScreenXY(std::size_t byte) const;

private:
    inline short height() const;
    inline short width()  const;

    void genSubWindows(); ///< Generate subwindows

    bool inputByte(char*); ///< Get byte value

    void printByte(const unsigned char b, std::size_t x, std::size_t y, int attr = A_NORMAL);
    void print(); ///< print content of current buffer in subWindows
    void printHexNum(const unsigned char) const;

    void placeCursor(); ///< Place cursor on current x,y coordinates

    struct Opts {
        explicit Opts(Window&);
        Window& w;

        unsigned short cols() const;  ///< Maximal number of columns of bytes
        char blank() const;           ///< Character used for unprintable chars
        const char* hexFmt() const;
        unsigned short scrolloff() const;
    };
    friend struct Opts;

public:
    Opts opts;
};
