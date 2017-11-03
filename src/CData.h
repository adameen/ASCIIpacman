#ifndef CDATA_H_12356498652
#define	CDATA_H_12356498652

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include "CExceptions.h"

/**
 * \brief A Class which controls and holds all the loaded data.
 * 
 * It holds number of rows/columns, matrix of chars and ints, etc.
 */
class CData{
public:
    /**
     * \brief It initializes all the member variables.
     * 
     * It nulls them or make them recognizable as a first state. 
     */
            CData();
    /**
     * \brief It deletes all three 2D fields.
     */
            ~CData();
    /**
     * \brief It loads map from a file.
     * 
     * It also checks the number of pacmen/ghosts and saves and controls number of rows/columns in a map/display.
     */
    void    loadMap();
    /**
     * \breif It allocates a map into 2D fields. It also null them.
     */
    void    createMap();
    /**
     * \brief It transforms allowed chars into 0 or 1.
     * 
     * It also checks whether the char is allowed.
     * \param[in] loadedChar - character which is transformed into "bool" (int of 0 and 1 actually)
     * \return "bool" (int of 0 and 1 actually) to know where is possible to go in a map
     */
    int     transformChar(const char loadedChar) const;
    /**
     * \brief It returns a number of rows in a map.
     * \return number of rows in a map
     */
    int     getRows() const;
    /**
     * \brief It returns a number of columns in a map.
     * \return number of columns in a map
     */
    int     getColumns() const;
    /**
     * \brief It returns a pointer to 2D char field.
     * \return pointer to 2D char field
     */
    char ** getCharMap() const;
    /**
     * \brief It returns a char in the X and Y coordinates.
     * \param x[in] - X coordinate of char we need from 2D char field
     * \param y[in] - Y coordinate of char we need from 2D char field
     * \return char in the X and Y coordinates in the 2D char field
     */
    char    getChar(const int x, const int y) const;
    /**
     * \brief It returns a "bool" (int 0 or 1 actually) in the X and Y coordinates.
     * \param x[in] - X coordinate of "bool" (int 0 or 1 actually) we need from 2D "bool" field
     * \param y[in] - Y coordinate of "bool" (int 0 or 1 actually) we need from 2D "bool" field
     * \return "bool" (int 0 or 1 actually) in the X and Y coordinates in the 2D "bool" field
     */
    int     getBool(const int x, const int y) const;
    /**
     * \brief It puts the desired char in the desired position in the 2D char field.
     * \param[in] row - Y coordinate of the desired char we give
     * \param[in] column - X coordinate of the desired char we give
     * \param[in] letter - char which we want to have in the desired position
     */
    void    changeCharMap(const int row, const int column, const char letter);
    /**
     * \brief It finds and counts and stores all the food (. and @) in a map given.
     */
    void    checkFoodNumber();
    /**
     * \brief It add bonus and normal food points and returns it in one value.
     * \return total of food number points
     */
    int     getFoodNumber() const;
    /**
     * \brief It refreshes the char 2D field.
     * 
     * It also refreshes original ghosts coordinates. All this after the game ends.
     */
    void    refreshMap();
    /**
     * \brief It gives the ghost's original coordinates to the CGhost's constructor.
     * 
     * It happens before beginning of every game.
     * \param x[out] - takes X coordinates of a ghost
     * \param y[out] - takes Y coordinates of a ghost
     */
    void    getGhostIndex(int & x, int & y);
    /**
     * \brief It changes pacman index after his every move.
     * @param x[in] - new X coordinate of pacman
     * @param y[in] - new Y coordinate of pacman
     */
    void    changeCPacmanIndex(const int x, const int y);
    /**
     * \brief It sets (given) X and Y pacman coordinates.
     * 
     * The given variables are rewrote by current X and Y coordinates of pacman.
     * \param x[out] - variable which is set by current pacman X coordinate
     * \param y[out] - variable which is set by current pacman Y coordinate
     */
    void    getCPacmanIndex(int & x, int & y) const;

private:
    char ** m_CharMapArray; /**< pointer to 2D char field */
    char ** m_HelpCharMapArray; /**< pointer to 2D char field - backup */
    int  ** m_BoolMapArray; /**< pointer to 2D "bool" (int actually) field */
    int m_CntRow; /**< number of map rows */
    int m_CntColumn; /**< number of map columns */
    int m_CntNormalFood; /**< number of normal food points */
    int m_CntBonusFood; /**< number of bonus food points */
    int m_CPacman_X; /**< X coordinate of pacman */
    int m_CPacman_Y; /**< Y coordinate of pacman */
    int m_Ghost1_X; /**< X coordinate of the first ghost in a map */
    int m_Ghost1_Y; /**< Y coordinate of the first ghost in a map */
    int m_Ghost2_X; /**< X coordinate of the second ghost in a map */
    int m_Ghost2_Y; /**< Y coordinate of the second ghost in a map */
    int m_Ghost3_X; /**< X coordinate of the third ghost in a map */
    int m_Ghost3_Y; /**< Y coordinate of the third ghost in a map */
};


#endif	/* CDATA_H */
