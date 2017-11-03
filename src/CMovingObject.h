#ifndef CMOVINGOBJECT_H_8653654
#define	CMOVINGOBJECT_H_8653654

#include "CData.h"

/**
 * \brief A Class which controls moving objects.
 *
 * It can manipulate with pacman or ghost - move him in a map. It controls what he eats, where he goes and if he touches a ghost/pacman.
 */
class CMovingObject{
public:
    /**
     * \brief Initializes memeber variables for the descendants.
     */
                 CMovingObject();
                 virtual ~CMovingObject();
    /**
     * \brief Decides where to move.
     *
     * It decides if moving objects moves up, down, right or left depending on pressed button.
     * \param[in] button - pressed button (one of the arrows or 'p')
     * \param[out] alldata - to pass it on into moveUp, moveDown, moveLeft, moveRight
     * \return value which is added to score after it or -1 for touching a ghost
     */
    virtual int  move(const int button, CData & alldata) = 0;
    /**
     * \brief Moves a moving object up. Otherwise it stops it or kill it.
     *
     * It decides if in this direction there is a moving object or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/moving objects around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost
     */
    virtual int  moveUp(CData & alldata) = 0;
    /**
     * \brief Moves a moving object down. Otherwise it stops it or kill it.
     *
     * It decides if in this direction there is a moving object or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/moving objects around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost
     */
    virtual int  moveDown(CData & alldata) = 0;
    /**
     * \brief Moves a moving object left. Otherwise it stops it or kill it.
     *
     * It decides if in this direction there is a moving object or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/moving objects around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost
     */
    virtual int  moveLeft(CData & alldata) = 0;
    /**
     * \brief Moves a moving object right. Otherwise it stops it or kill it.
     *
     * It decides if in this direction there is a moving object or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/moving objects around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost
     */
    virtual int  moveRight(CData & alldata) = 0;
    /**
     * \brief Refreshes pacman's index to the startup values after the game is over.
     */
    virtual void refreshIndex() = 0;
    /**
     * \brief Takes the ghost "home".
     *
     * After he kills pacman it also updates his coordinates.
     * \param[out] alldata - to put his m_LastChar on the place from where the ghost is transported to "home"
     */
    virtual void takeGhostHome(CData & alldata) = 0;
    /**
     * \brief Refreshes pacman's index in CData (alldata) to get the ghosts know.
     *
     * It refreshes pacman's index every move in CData (alldata) to get the ghosts know.
     * \param[out] alldata - to change pacman index in CData to get the ghosts know
     */
    virtual void givePacmanIndex(CData & alldata) const = 0;

protected:
    int m_X; /**< X coordinate of a moving object */
    int m_Y; /**< Y coordinate of a moving object */
    int m_OriginalX; /**< saved X coordinate of a moving object for after-game update */
    int m_OriginalY; /**< saved Y coordinate of a moving object for after-game update */
    int m_Direction; /**< direction of a moving object (from down to up it is 8 - taken from numerical keyboard) */
};


#endif	/* CMOVINGOBJECT_H */
