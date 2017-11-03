#include "CExceptions.h"

void COpenException::displayException() const{
    int display_rows = 0;
    int display_columns = 0;
    char mesg1[] = "The file with map can not be opened!";
    char mesg2[] = "It is missing or you do not have rights to open it.";
    initscr();
    curs_set(0);
    getmaxyx(stdscr, display_rows, display_columns);
    mvprintw(display_rows/2,(display_columns-strlen(mesg1))/2,"%s",mesg1);
    mvprintw((display_rows/2)+1,(display_columns-strlen(mesg2))/2,"%s",mesg2);
    refresh();
    getch();
    endwin();
}

CRowException::CRowException(int i) : m_MaxRows(i) { }

void CRowException::displayException() const{
    int display_rows = 0;
    int display_columns = 0;
    char mesg1[] = "The map can not have more then";
    initscr();
    curs_set(0);
    getmaxyx(stdscr, display_rows, display_columns);
    mvprintw(display_rows/2,(display_columns-strlen(mesg1)-8)/2,"%s %d rows!",mesg1, m_MaxRows);
    refresh();
    getch();
    endwin();
}

CColumnException::CColumnException(int i) : m_MaxColumns(i) { }

void CColumnException::displayException() const{
    int display_rows = 0;
    int display_columns = 0;
    char mesg1[] = "The map can not have more then";
    initscr();
    curs_set(0);
    getmaxyx(stdscr, display_rows, display_columns);
    mvprintw(display_rows/2,(display_columns-strlen(mesg1)-11)/2,"%s %d columns!",mesg1, m_MaxColumns);
    refresh();
    getch();
    endwin();
}

CCharException::CCharException(char badchar) : m_BadChar(badchar) { }

void CCharException::displayException() const{
    int display_rows = 0;
    int display_columns = 0;
    char mesg1[] = "There is a bad char in the map! (this one: '";
    char mesg2[] = "Only these are allowed: C A # . - @";
    initscr();
    curs_set(0);
    getmaxyx(stdscr, display_rows, display_columns);
    mvprintw(display_rows/2,(display_columns-strlen(mesg1)-3)/2,"%s%c')",mesg1, m_BadChar);
    mvprintw(display_rows/2+1,(display_columns-strlen(mesg2))/2,"%s",mesg2);
    refresh();
    getch();
    endwin();
}

void CGhostCntException::displayException() const{
    int display_rows = 0;
    int display_columns = 0;
    char mesg1[] = "You must have exactly 3 ghosts in a map!";
    initscr();
    curs_set(0);
    getmaxyx(stdscr, display_rows, display_columns);
    mvprintw(display_rows/2,(display_columns-strlen(mesg1))/2,"%s",mesg1);
    refresh();
    getch();
    endwin();
}

void CPacmanCntException::displayException() const{
    int display_rows = 0;
    int display_columns = 0;
    char mesg1[] = "You must have exactly 1 Pacman in a map!";
    initscr();
    curs_set(0);
    getmaxyx(stdscr, display_rows, display_columns);
    mvprintw(display_rows/2,(display_columns-strlen(mesg1))/2,"%s",mesg1);
    refresh();
    getch();
    endwin();
}

CTerminalSizeException::CTerminalSizeException(const int display_rows, const int display_columns, const int matrix_columns, const int matrix_rows) : 
        m_DisplayRows(display_rows), m_DisplayColumns(display_columns), m_MatrixColumns(matrix_columns), m_MatrixRows(matrix_rows) { }

void CTerminalSizeException::displayException() const{
    int pom_columns = -1;
    char mesg1[] = "Please, enlarge you terminal window and start game again.";
    char mesg2[] = "At least: ";
    pom_columns = (m_MatrixColumns*1.5) +1; // +1 because of rounding, *1.5 because of stats on the right side
    mvprintw(m_DisplayRows/2,(m_DisplayColumns-strlen(mesg1))/2,"%s",mesg1);
    mvprintw((m_DisplayRows/2)+1,(m_DisplayColumns-strlen(mesg2))/2,"%s%d x %d.",mesg2,m_MatrixRows,pom_columns);
    refresh();
    getch();
    endwin();
}
