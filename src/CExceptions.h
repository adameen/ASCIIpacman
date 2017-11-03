#ifndef CEXCEPTIONS_H_5611984
#define	CEXCEPTIONS_H_5611984

#include <string.h>

#include <ncurses.h>

/**
 * \brief Controls map opening.
 * 
 * An exception which controls if the pacman map can be opened.
 */
class COpenException{
public:
    /** \brief Displays opening exception. */
    void displayException() const;
};

/**
 * \brief Controls number of rows.
 * 
 * An exception which controls if the pacman map does not have more then maximum number of rows.
 */
class CRowException{
public:
    /**
     * \brief Initializes member by maximum number of rows.
     * \param[in] i - maximum number of rows
     */
    CRowException(int i);
    /** \brief Displays max number of rows. */
    void displayException() const;
private:
    int m_MaxRows; /**< maximum number of rows */
};

/**
 * \brief Controls number of columns.
 * 
 * An exception which controls if the pacman map does not have more then maximum number of columns.
 */
class CColumnException{
public:
    /**
     * \brief Initializes member by maximum number of columns.
     * \param[in] i - maximum number of columns
     */
    CColumnException(int i);
    /** \brief Displays max number of columns. */
    void displayException() const;
private:
    int m_MaxColumns; /**< maximum number of columns */
};

/**
 * \brief Controls characters in a map.
 * 
 * An exception which controls if the pacman map does have only the allowed characters.
 */
class CCharException{
public:
    /**
     * \brief Initializes member by bad character.
     * \param[in] badchar - bad char in a pacman map
     */
    CCharException(char badchar);
    /** \brief Displays bad character in a map and allowed characters. */
    void displayException() const;
private:
    int m_BadChar; /**< unallowed char (appropriate number for char) in the map */
};

/**
 * \brief Controls number of pacmen.
 * 
 * An exception which controls if there is exactly one pacman in a pacman map.
 */
class CGhostCntException{
public:
    /** \brief Displays number of required ghosts. */
    void displayException() const;
};

/**
 * \brief Controls number of ghosts.
 * 
 * An exception which controls if there are exactly three ghosts in a pacman map.
 */
class CPacmanCntException{
public:
    /** \brief Displays number of required pacmen. */
    void displayException() const;
};

/**
 * \brief Controls size of teminal window.
 * 
 * An exception which controls if the size of terminal window is enough, considering pacman map size (at least: equal height and 1.5x bigger width).
 */
class CTerminalSizeException{
public:
    /**
     * \brief Initializes members by rows/columns number.
     * \param[in] display_rows - number of terminal rows
     * \param[in] display_columns - number of terminal columns
     * \param[in] matrix_columns - number of map columns
     * \param[in] matrix_rows - number of map rows
     */
    CTerminalSizeException(const int display_rows, const int display_columns, const int matrix_columns, const int matrix_rows);
    /** \brief Displays minimum size of terminal window. */
    void displayException() const;
private:
    int m_DisplayRows;    /**< number of display (terminal) rows */
    int m_DisplayColumns; /**< number of display (terminal) columns */
    int m_MatrixColumns;  /**< number of pacman map columns */
    int m_MatrixRows;     /**< number of pacman map rows */
};


#endif	/* CEXCEPTIONS_H */
