/**
 * \mainpage PAC-MAN
 *
 * This program was developed as a semestral work in summer semester 2012/2013.\n\n
 * It is a semestral work for PA2 (Programming and algorithm development 2) at CVUT university in Prague, Czech republic.\n
 *
 *
 * \image html pacman.png "Pacman start screen"
 *
 * \section sect1 Description
 *
 * \li This project was developed under school supervision.
 * \li Report bugs here: pecead(at)centrum.cz.
 *
 * If you want to use your own main.cpp, then use the following code in it:
 * \code
 * #include "CGame.h"
 * #include "CExceptions.h"
 * 
 *
 * int main(int argc, char** argv) {
 * 
 * 	 try{
 *          CGame Pacman;
 *       }
 *       catch(COpenException & e){ e.displayException(); }
 *       catch(CRowException & e) { e.displayException(); }
 *       catch(CColumnException & e) { e.displayException(); }
 *       catch(CCharException & e) { e.displayException(); }
 *       catch(CGhostCntException & e) { e.displayException(); }
 *       catch(CPacmanCntException & e) { e.displayException(); }
 *       catch(CTerminalSizeException & e) { e.displayException(); }
 *  
 *       return 0;
 * }
 * \endcode
 *
 * \section sect2 A few words before playing
 * If you have any ideas to improve this game or anything, email me on pecead(at)centrum.cz
 * Now only thing I can wish you is to enjoy this game and share it with your friends.
 */

#include "CGame.h"
#include "CExceptions.h"

using namespace std;

int main(int argc, char** argv) {
   
    // swith the game on
    try{
        CGame Pacman;
    }
    // catch all known exceptions
    catch(COpenException & e){ e.displayException(); }
    catch(CRowException & e) { e.displayException(); }
    catch(CColumnException & e) { e.displayException(); }
    catch(CCharException & e) { e.displayException(); }
    catch(CGhostCntException & e) { e.displayException(); }
    catch(CPacmanCntException & e) { e.displayException(); }
    catch(CTerminalSizeException & e) { e.displayException(); }
    
    return 0;
}
