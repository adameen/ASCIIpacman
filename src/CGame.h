#ifndef CGAME_H_9165126219894
#define	CGAME_H_9165126219894

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "CData.h"
#include "CMovingObject.h"
#include "CPacman.h"
#include "CGhostEasy.h"
#include "CGhostHard.h"

/**
 * \brief A Class which controls whole game.
 * 
 * It displays all the necessary things as menus, texts, etc. It also controls moving of pacman and the ghosts and it calls important functions.
 */
class CGame{
public:
    /**
     * \brief It initializes member variables and it calls the most important functions.
     * 
     * It calls loading the map, loading the food number points, starts display and allocate field of moving objects and pacman in it.
     * It also call the main game cycle - displayMenu() function.
     */
         CGame();
    /**
     * \brief It deletes pacman and the field of moving objects.
     */
         ~CGame();
    /**
     * \brief It prepares the game and watches the game result.
     * 
     * It also refreshes the map and pacman's and ghost's indexes after the game and it calls "game over" or "you win" displaying.
     * Resets score and lives.
     */
    void gamePlay();
    /**
     * \brief It tests if terminal window size is large enough and sets display member variables.
     * 
     * Otherwise it throws the CTerminalSizeException.
     */
    void startDisplay();
    /**
     * \brief It shows the first screen with "PACMAN".
     */
    void firstScreen() const;
    /**
     * \brief It is the main game cycle - it shows the main menu.
     * 
     * It calls important functions and it controls what you chose - it is "never-ending" cycle.
     */
    void displayMenu();
    /**
     * \brief It prints correctly desired words from menu on the screen.
     * 
     * It highlights current choice and it prints window around the menu.
     * \param[out] menu_win - variable which holds pointer to ncurses WINDOW
     * \param[in] highlight - current choice - to know which choice to highlight
     * \param[in] n_choices - number of choices
     * \param[in] choices - pointer to field of choices (C strings)
     * \param[in] WIDTH - width of ncurses window
     * \param[in] addition - additional C string to one of choices
     */
    void printMenu(WINDOW *menu_win, const int highlight, const int n_choices, const char *choices[], const int WIDTH, const char * addition) const;
    /**
     * \brief It displays counting before the game starts using sleep().
     */
    void displayCounting() const;
    /**
     * \brief It controls button pressing while playing and moves moving_objects.
     * 
     * It also checks whether the game is over or you win or if pacman's life is not spared. It moves with objects every 150ms.
     * It calls takeGhostHome() when pacman dies and it checkes if pause is ON.
     * \return 1 if game is over or 0 if you win
     */
    int  startGame();
    /**
     * \brief After every move it redisplays map (with colors if its ON).
     */
    void displayMap() const;
    /**
     * \brief After every move it redisplays stats like: score, lives and potential pause.
     */
    void displayStats() const;
    /**
     * \brief It displays pause menu which can be launched during the game.
     * \return choice (1 for Continue and 2 for Exit)
     */
    int  displayPauseMenu() const;
    /**
     * \brief Displays blinking "Game Over" - can be speeded up by pressing enter.
     */
    void displayGameOver() const;
    /**
     * \brief Displays blinking "You Win" - can be speeded up by pressing enter.
     */
    void displayYouWin() const;
    /**
     * \brief It displays level menu after choosing New Game in main menu.
     * \return choice (1 for Easy, 2 for Medium and 3 for Hard)
     */
    int  displayLevelMenu() const;
    /**
     * \brief It displays useful information about how to play and what to do.
     */
    void displayHowToPlay() const;
    /**
     * \brief It displays some information about author, project, used library, etc.
     */
    void displayCredits() const;
    /**
     * \brief It initializes modes of color pairs.
     * 
     * It also checks if your terminal is capable of using colors.
     */
    void initializeColors();
    /**
     * \brief It initializes and allocates ghosts depending on chosen level.
     */
    void initializeGhosts();
    /**
     * It deletes all 3 allocated ghosts after every game (win or lose).
     */
    void deleteGhosts();

private:
    CData alldata; /**< instance of all data we need (map, row count, etc.) to have access */
    int m_DisplayRows; /**< number of terminal (display) rows */
    int m_DisplayColumns; /**< number of terminal (display) columns */
    int m_Score; /**< number of eaten food */
    int m_MaxScore; /**< number of maximal food, which cat be eaten */
    int m_Lives; /**< number of pacman lives */
    int m_Difficulty; /**< chosen level (easy, medium, hard) */
    bool m_Colors; /**< chosen mode - colored or not colored (owner's original) */
    CMovingObject ** m_MovingObjects; /**< pointer to field of moving objects (pacman and 3 ghosts) */
};


#endif	/* CGAME_H */
