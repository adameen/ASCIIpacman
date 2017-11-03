#ifndef CGHOSTHARD_H_2216548981
#define	CGHOSTHARD_H_2216548981

#include <stdlib.h>

#include "CMovingObject.h"
#include "CData.h"

/**
 * \brief A Class which controls a hard ghost.
 * 
 * It can manipulate with the ghost - move him in a map. It can also put him in "the house" after he kills pacman.
 * It (publicly) inherits from CMovingObject.
 */
class CGhostHard : public CMovingObject{
public:
    /**
     * \brief Initializes CGhostHard and get his index and save it.
     * \param[in] alldata - to get ghost index from CData
     */
                 CGhostHard(CData & alldata);
    /**
     * \brief Decides where to move.
     * 
     * It decides if the ghost moves up, down, right or left.
     * \param[in] button - pressed button (one of the arrows or 'p')
     * \param[out] alldata - to check opposite direction and possible ways to go
     * \return 0 if everything is OK or -1 for catching pacman
     */
    virtual int  move(const int button, CData & alldata);
    /**
     * \brief Moves the ghost up. Otherwise catches the pacman.
     * 
     * It decides if in this direction there is pacman, another ghost or free space in the next index.
     * \param[out] alldata - to check the barriers/ghosts/pacman around and to change data in a map
     * \return 0 if everything is OK or -1 for catching pacman
     */
    virtual int  moveUp(CData & alldata);
    /**
     * \brief Moves the ghost down. Otherwise catches the pacman.
     * 
     * It decides if in this direction there is pacman, another ghost or free space in the next index.
     * \param[out] alldata - to check the barriers/ghosts/pacman around and to change data in a map
     * \return 0 if everything is OK or -1 for catching pacman
     */
    virtual int  moveDown(CData & alldata);
    /**
     * \brief Moves the ghost left. Otherwise catches the pacman.
     * 
     * It decides if in this direction there is pacman, another ghost or free space in the next index.
     * \param[out] alldata - to check the barriers/ghosts/pacman around and to change data in a map
     * \return 0 if everything is OK or -1 for catching pacman
     */
    virtual int  moveLeft(CData & alldata);
    /**
     * \brief Moves the ghost right. Otherwise catches the pacman.
     * 
     * It decides if in this direction there is pacman, another ghost or free space in the next index.
     * \param[out] alldata - to check the barriers/ghosts/pacman around and to change data in a map
     * \return 0 if everything is OK or -1 for catching pacman
     */
    virtual int  moveRight(CData & alldata);
    /**
     * \brief Refreshes pacman's index to the startup values after the game is over.
     */
    virtual void refreshIndex () { return; }
    /**
     * \brief Takes the ghost "home".
     * 
     * After he kills pacman it also updates his coordinates.
     * \param[out] alldata - to put his m_LastChar on the place from where the ghost is transported to "home"
     */
    virtual void takeGhostHome(CData & alldata);
    /**
     * \brief Refreshes pacman's index in CData (alldata) to get the ghosts know.
     * 
     * It refreshes pacman's index every move in CData (alldata) to get the ghosts know.
     * \param[out] alldata - to change pacman index in CData to get the ghosts know
     */
    virtual void givePacmanIndex(CData & alldata) const { return; }
    
private:
    char m_LastChar; /**< a character on which a ghost is standing */
};


#endif	/* CGHOSTHARD_H */
