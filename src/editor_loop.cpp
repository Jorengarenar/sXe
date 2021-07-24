#include "editor.hpp"

int Editor::loop()
{
    while (true) {
        int c = input();

        for (auto a: mappings(c)) {
            switch (a) {
                case Action::RESIZE:
                    cw->redraw();
                    cli.redraw();
                    break;

                case Action::LEFT:
                    cw->mvCursor(Direction::LEFT);
                    break;
                case Action::DOWN:
                    cw->mvCursor(Direction::DOWN);
                    break;
                case Action::UP:
                    cw->mvCursor(Direction::UP);
                    break;
                case Action::RIGHT:
                    cw->mvCursor(Direction::RIGHT);
                    break;

                case Action::NEXTBYTE:
                    cw->gotoByte(cw->currentByte + 1);
                    break;

                case Action::FIRSTCOL:
                    cw->mvCursorToColumn(0);
                    break;
                case Action::LASTCOL:
                    cw->mvCursorToColumn(cw->opts.cols() - 1);
                    break;
                case Action::FIRSTBYTE:
                    cw->gotoByte(0);
                    break;
                case Action::LASTBYTE:
                    cw->gotoByte(cw->buffer->size() - 1);
                    break;

                case Action::NEXTPRINTABLE:
                    cw->gotoByte(
                        cw->buffer->findByte(
                            [&](Buffer::byteType x) { return isprint(x); },
                            cw->currentByte
                        )
                    );
                    break;
                case Action::NEXTPRINTABLEBLOCK:
                    cw->gotoByte(
                        cw->buffer->findBlock(
                            [&](Buffer::byteType x) { return isprint(x); },
                            cw->currentByte
                        )
                    );
                    break;
                case Action::NEXTFILLED:
                    cw->gotoByte(
                        cw->buffer->findByte(
                            [&](Buffer::byteType x) { return x > 0; },
                            cw->currentByte
                        )
                    );
                    break;
                case Action::NEXTFILLEDBLOCK:
                    cw->gotoByte(
                        cw->buffer->findBlock(
                            [&](Buffer::byteType x) { return x > 0; },
                            cw->currentByte
                        )
                    );
                    break;

                case Action::NEXTTAB:
                    if (auto i = winNr(); i < windows.size()-1) {
                        switchWin(i+1);
                    }
                    else {
                        switchWin(0);
                    }
                    break;

                case Action::CMD:
                    if (!cli()) {
                        return 0;
                    }
                    break;
                case Action::SEARCH:
                    break;

                case Action::REPLACE:
                    replaceByte();
                    break;
                case Action::INSERT:
                    while (cw->insertByte() == 0) {
                        cw->currentByte++;
                    }
                    break;
                case Action::APPEND:
                    cw->currentByte += 1;
                    cw->insertByte();
                    break;
                case Action::ERASE:
                    cw->eraseByte();
                    break;
                case Action::INCREMENT:
                    cw->addToByte(1);
                    break;
                case Action::DECREMENT:
                    cw->addToByte(-1);
                    break;

                case Action::SAVEQUIT:
                    cw->save();
                    [[fallthrough]];
                case Action::QUIT:
                    return 0;

                case Action::UNDO:
                    break;
                case Action::REDO:
                    break;

                default:
                    break;
            }
        }
    }
}

// vim: fdl=4
