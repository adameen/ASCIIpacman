#ifndef CPACMAN_H_89451951
#define	CPACMAN_H_89451951

#include <ncurses.h>

#include "CMovingObject.h"
#include "CData.h"

/**
 * \brief A Class which controls pacman.
 * 
 * It can manipulate with pacman - move him in a map. It controls what he eats and if he touches a ghost.
 * It (publicly) inherits from CMovingObject.
 */
class CPacman : public CMovingObject{
public:
    /**
     * \brief Initializes CPacman and get his index and save it.
     * \param[in] alldata - to get pacman index from CData
     */
                 CPacman(const CData & alldata);
    /**
     * \brief Decides where to move.
     * 
     * It decides if pacman moves up, down, right or left depending on pressed button.
     * \param[in] button - pressed button (one of the arrows or 'p')
     * \param[out] alldata - to pass it on into moveUp, moveDown, moveLeft, moveRight
     * \return value which is added to score after it or -1 for touching a ghost
     */
    virtual int  move(const int button, CData & alldata);
    /**
     * \brief Moves pacman up. Otherwise it stops him or kill him.
     * 
     * It decides if in this direction there is a ghost or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/ghosts around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost 
     */
    virtual int  moveUp(CData & alldata);
    /**
     * \brief Moves pacman down. Otherwise it stops him or kill him.
     * 
     * It decides if in this direction there is a ghost or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/ghosts around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost 
     */
    virtual int  moveDown(CData & alldata);
    /**
     * \brief Moves pacman left. Otherwise it stops him or kill him.
     * 
     * It decides if in this direction there is a ghost or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/ghosts around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost 
     */
    virtual int  moveLeft(CData & alldata);
    /**
     * \brief Moves pacman right. Otherwise it stops him or kill him.
     * 
     * It decides if in this direction there is a ghost or free space or a part of wall in the next index.
     * \param[out] alldata - to check the barriers/ghosts around and to change data in a map
     * \return value which is added to score after it or -1 for touching a ghost 
     */
    virtual int  moveRight(CData & alldata);
    /**
     * \brief Refreshes pacman's index to the startup values after the game is over.
     */
    virtual void refreshIndex ();
    /**
     * \brief Takes the ghost "home".
     * 
     * After he kills pacman it also updates his coordinates.
     * \param[out] alldata - to put his m_LastChar on the place from where the ghost is transported to "home"
     */
    virtual void takeGhostHome(CData & alldata) { return; }
    /**
     * \brief Refreshes pacman's index in CData (alldata) to get the ghosts know.
     * 
     * It refreshes pacman's index every move in CData (alldata) to get the ghosts know.
     * \param[out] alldata - to change pacman index in CData to get the ghosts know
     */
    virtual void givePacmanIndex(CData & alldata) const;
    
private:
    int m_PacmanLook; /**< a value for changing appearance of pacman when eating food */
};


#endif	/* CPACMAN_H */
