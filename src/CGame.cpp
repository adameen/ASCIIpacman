#include "CGame.h"

using namespace std;

CGame::CGame() : m_DisplayRows(0), m_DisplayColumns(0), m_Score(0), m_Lives(3), m_Difficulty(0), m_Colors(false), m_MovingObjects(NULL) {
    alldata.loadMap();
    alldata.checkFoodNumber();
    m_MaxScore = alldata.getFoodNumber();
    startDisplay();
    m_MovingObjects = new CMovingObject * [4];
    m_MovingObjects[0] = new CPacman(alldata); // polymorphism
    firstScreen();
    displayMenu(); // goes to the main game cycle
}

CGame::~CGame(){
    if(m_MovingObjects != NULL){
        delete m_MovingObjects[0]; // delete pacman
        delete [] m_MovingObjects;
    }
}

void CGame::gamePlay(){
    int result = 0;
    displayCounting();
    result = startGame();
    if(result == 0){
        displayYouWin();
    }
    else{ //result == 1
        displayGameOver();
    }
    alldata.refreshMap(); // adjust a map to the original state + set the original ghost indexes
    for(int i = 0; i < 4; i++){ // refresh original index of pacman
         m_MovingObjects[i] -> refreshIndex();
    }
    m_Lives = 3;
    m_Score = 0;
}

void CGame::startDisplay(){
    int matrix_rows = alldata.getRows();
    int matrix_columns = alldata.getColumns();
    int display_rows;
    int display_columns;
    initscr(); // start ncurses mode
    curs_set(0); // set the cursor visibility to invisible
    getmaxyx(stdscr, display_rows, display_columns); // gets terminal window size to the display_rows/columns variables
    if(display_rows < matrix_rows || display_columns <  matrix_columns*1.5){
        throw CTerminalSizeException(display_rows, display_columns, matrix_columns, matrix_rows);
    }
    else{
        m_DisplayColumns = display_columns;
        m_DisplayRows = display_rows;
    }
}

void CGame::firstScreen() const{
    char firstline[] =   " __     __     __             __         ";
    char secondline[] =  "|__|   |__|   |     |\\  /|   |__|   |\\  |";
    char thirdline[] =   "|      |  |   |     | \\/ |   |  |   | \\ |";
    char fourthline[] = "|      |  |   |__   |    |   |  |   |  \\|";
    char fifthline[] = "insert coin (press ENTER)";
    char blank[] =     "                         "; // to cover fifthline - because of blinking effect
    char ch = ' ';
    mvprintw(m_DisplayRows/3,(m_DisplayColumns-strlen(firstline))/2,"%s", firstline); // -strlen(firstline) to be really in the middle
    mvprintw((m_DisplayRows/3)+1,(m_DisplayColumns-strlen(secondline))/2,"%s", secondline);
    mvprintw((m_DisplayRows/3)+2,(m_DisplayColumns-strlen(thirdline))/2,"%s", thirdline);
    mvprintw((m_DisplayRows/3)+3,(m_DisplayColumns-strlen(fourthline))/2,"%s", fourthline);
    mvprintw((m_DisplayRows/3)+7,(m_DisplayColumns-strlen(fifthline))/2,"%s", fifthline);
    refresh();
    timeout(1000); // set waiting for getting char in getch() to 1 second (1000 ms)
    while(1){
        if((ch=getch())=='\n') break;
        mvprintw((m_DisplayRows/3)+7,(m_DisplayColumns-strlen(blank))/2,"%s", blank);
        refresh();
        if((ch=getch())=='\n') break;
        mvprintw((m_DisplayRows/3)+7,(m_DisplayColumns-strlen(fifthline))/2,"%s", fifthline);
        refresh();
    }
    timeout(-1); // set waiting for getting char in getch() to original infinity
    clear(); // clears the display as in bash
}

void CGame::printMenu(WINDOW *menu_win, const int highlight, const int n_choices, const char *choices[], const int WIDTH, const char * addition) const{
    int x, y, i;
    x = 0;
    y = 2;
    box(menu_win, 0, 0); // creates box (window)
    for(i = 0; i < n_choices; i++){
        if(strcmp(choices[i], "Colors: ") == 0){ // to change "ON" or "OFF" after "Colors: "
            x = (WIDTH - (strlen(choices[i])) - strlen(addition))/2;
        }
        else{
            x = (WIDTH - (strlen(choices[i])))/2; // to write every word of menu in the middle of menu
        }
    	if(highlight == i + 1){ // present choice is highlighted
            if(m_Colors == true) wattron(menu_win, A_REVERSE | COLOR_PAIR(4)); // sets printing - reverse color and with special color pair
            else{ wattron(menu_win, A_REVERSE); }
            if(strcmp(choices[i],"Colors: ") == 0){
		mvwprintw(menu_win, y, x, "%s%s", choices[i], addition); // start printing in x, y coordinates in window
            }
            else{
		mvwprintw(menu_win, y, x, "%s", choices[i]);
            }
            if(m_Colors == true) wattroff(menu_win, A_REVERSE | COLOR_PAIR(4)); 
	    else { wattroff(menu_win, A_REVERSE); }
	}
	else{ // other choices except highlighted one
            if(strcmp(choices[i],"Colors: ") == 0){
                mvwprintw(menu_win, y, x, "%s%s", choices[i], addition);
            }
            else{
                mvwprintw(menu_win, y, x, "%s", choices[i]);
            }
        }
	y = y+2; // do 2 newlines after each word (print after 2 free Y lines)
    }
    wrefresh(menu_win); // refresh the window
}

void CGame::displayMenu() {
    int highlight = 1; // the choice is highlighted
    while(1){
        int WIDTH = 20, HEIGHT = 13; // sie of the window
        int startx = 0, starty = 0;
        const char *choices[] = { "New Game", "Colors: ", "How To Play", "Credits", "Exit" };
        int n_choices = sizeof(choices) / sizeof(const char *); // number of choices
        WINDOW *menu_win; // pointer to future window
        int choice = 0;
        int c;
        const char * addition = "OFF";
        if(m_Colors == true) { addition = "ON"; }
        noecho(); // controls whether characters typed by the user are echoed by getch() as they are typed - in this case we want them not to be typed
        cbreak(); // line buffering disabled, pass on everything
        startx = (m_DisplayColumns - WIDTH) / 2; // to have it (window) in the middle of the screen
        starty = (m_DisplayRows - HEIGHT) / 2;
        menu_win = newwin(HEIGHT, WIDTH, starty, startx); // creates the window
        keypad(menu_win, TRUE); // allows to get pushed buttons from keyboard
        clear();
        mvprintw(1, 1, "Use arrow keys to go up and down, press ENTER to select a choice."); // prints at x=1 and y=1 coordinates
        refresh();
        printMenu(menu_win, highlight, n_choices, choices, WIDTH, addition); // prints buffered menu
        while(1){
            c = wgetch(menu_win);
    	    switch(c)
    	    {	case KEY_UP:
			if(highlight == 1) { highlight = n_choices; } // from the first choice goes to the last choice
			else { --highlight; }
			break;
		case KEY_DOWN:
			if(highlight == n_choices) { highlight = 1; } // from the last choice goes to the first choice
			else { ++highlight; }
			break;
		case 10: // number for ENTER KEY
			choice = highlight; // choice is defined by highlighted option
			break;
		default: // if man pushes another button
                        if(m_Colors == true){
                            attron(COLOR_PAIR(6));
			    mvprintw(m_DisplayRows-2, (m_DisplayColumns-59)/2, "Charcter pressed is '%c'. Use only up and down arrows or ENTER!", c);
                            attroff(COLOR_PAIR(6));
                        }
                        else{
                            mvprintw(m_DisplayRows-2, (m_DisplayColumns-59)/2, "Charcter pressed is '%c'. Use only up and down arrows or ENTER!", c);
                        }
			refresh(); // refreshes the screen - dump buffered data on screen
			break;
	    }
	    printMenu(menu_win, highlight, n_choices, choices, WIDTH, addition);
	    if(choice != 0) { break; }	// user did a choice come out of the infinite loop
        }
        if(choice == 1){
            m_Difficulty = displayLevelMenu();
            initializeGhosts();
            gamePlay();
            deleteGhosts();
            continue;
        }
        else if(choice == 2){
            if(m_Colors == false){
                initializeColors();
            }
            else{
                m_Colors = false;
            }
        }
        else if(choice == 3){
            displayHowToPlay();
        }
        else if(choice == 4){
            displayCredits();
        }
        else{ //choice == 5 ... Exit
            endwin();
            return;
        }
    }
}

void CGame::displayCounting() const{
    clear();
    refresh();
    char blinking_text[] = "The game begins in...";
    int counter = 4;
    if(m_Colors == true) attron(COLOR_PAIR(5));
    for(int i = 0; i < 4; i++){
        mvprintw(m_DisplayRows/2,(m_DisplayColumns-strlen(blinking_text))/2,"%s%d", blinking_text, counter);
        refresh();
        sleep(1); // wait for 1 second
        counter--;
    }
    if(m_Colors == true) attroff(COLOR_PAIR(5)); // switch off special formating of the text
    clear();
}

int CGame::startGame(){
    displayMap();
    displayStats();
    int button = 0;
    int value = 0;
    int choice = -1;
    keypad (stdscr, TRUE);
    timeout(150); // 0.15 sec
    cbreak(); // line buffering disabled, pass on everything
    noecho(); // controls whether characters typed by the user are echoed by getch() as they are typed - in this case we want them not to be typed
    while(1){
        if(m_Score == m_MaxScore) { timeout(-1); return 0; } // all the food was eaten
        button = getch();
        for(int i = 0; i < 4; i++){
            value = m_MovingObjects[i] -> move(button, alldata); // move with all the objects in this cycle
            m_MovingObjects[0]->givePacmanIndex(alldata); //sets pacman's coordinates in CData to get the ghosts know where he is
            if(value == -1){ // pacman is caught
                m_Lives--;
                if(m_Lives == 0){ // last life is gone
                    timeout(-1);
                    return 1;
                }
                else{
                    for(int i = 0; i < 4; i++){
                        m_MovingObjects[i] ->takeGhostHome(alldata); // take ghosts to their original coordinates
                    }
                    displayCounting();
                }
            }
            else if(value == -2){ // pause
                choice = displayPauseMenu();
                if(choice == 2){ // end game which is kicked off
                    deleteGhosts();
                    endwin();
                    exit(0);
                }
            }
            else{
                m_Score = m_Score + value; // add returned value (pointes of meal) to score
            }
        }
        clear();
        displayMap();
        displayStats();
        refresh();
        value = 0;
        button = 0;
    }
}

void CGame::displayMap() const{
    int rows = alldata.getRows();
    int columns = alldata.getColumns();
    char ** map = alldata.getCharMap();
    if(m_Colors == true){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(map[i][j] == 'C' || map[i][j] == 'O'){
                    attron(COLOR_PAIR(1)); // yellow on original background
                    addch(map[i][j]);
                    attroff(COLOR_PAIR(1));
                }
                else if(map[i][j] == 'A'){
                    attron(COLOR_PAIR(2)); // red on original background
                    addch(map[i][j]);
                    attroff(COLOR_PAIR(2));
                }
                else if(map[i][j] == '#'){
                    attron(COLOR_PAIR(3)); // white on ncurses black
                    addch(map[i][j]);
                    attroff(COLOR_PAIR(3));
                }
                else{
                    addch(map[i][j]);
                }
            }
            printw("\n");
        }    
    }
    else{ // colors are not allowed
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                addch(map[i][j]);
            }
            printw("\n");
        }    
    }     
}

void CGame::displayStats() const{
    char score_text[] = "Score: ";
    char lives_text[] = "Lives: ";
    char pause_text[] = "Press 'p' to pause!";
    if(m_Colors == true){
        attron(COLOR_PAIR(4));
        mvprintw(m_DisplayRows/3,alldata.getColumns()+10,"%s%d", score_text, m_Score);
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(5));
        mvprintw((m_DisplayRows/3)-4,alldata.getColumns()+10,"%s%d", lives_text, m_Lives);
        attroff(COLOR_PAIR(5));
        mvprintw((m_DisplayRows/3)+4,alldata.getColumns()+10,"%s", pause_text);
    }
    else{
        mvprintw(m_DisplayRows/3,alldata.getColumns()+10,"%s%d", score_text, m_Score);
        mvprintw((m_DisplayRows/3)-4,alldata.getColumns()+10,"%s%d", lives_text, m_Lives);
        mvprintw((m_DisplayRows/3)+4,alldata.getColumns()+10,"%s", pause_text);
    }
}

int CGame::displayPauseMenu() const{
    int WIDTH = 25, HEIGHT = 7;
    int startx = 0, starty = 0;
    const char *choices[] = { "Continue", "Exit" };
    int n_choices = sizeof(choices) / sizeof(const char *);
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    noecho();
    cbreak();
    startx = (m_DisplayColumns - WIDTH) / 2;
    starty = (m_DisplayRows - HEIGHT) / 2;
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    printMenu(menu_win, highlight, n_choices, choices, WIDTH, " ");
    while(1)
    {	c = wgetch(menu_win);
    	switch(c)
    	{	case KEY_UP:
			if(highlight == 1) { highlight = n_choices; }
			else { --highlight; }
			break;
		case KEY_DOWN:
			if(highlight == n_choices) { highlight = 1; }
			else { ++highlight; }
			break;
		case 10: // ENTER KEY
			choice = highlight;
			break;
	}
	printMenu(menu_win, highlight, n_choices, choices, WIDTH, " ");
	if(choice != 0)	{ break; }
    }
    if(choice == 1) { return 1; } // continue
    else { return 2; } // exit
}

void CGame::displayGameOver() const{
    clear();
    char ch = ' ';
    char firstline[] =   " ___    __             __     ___          __   __  ";
    char secondline[] =  "|      |__|   |\\  /|  |      |   | |    | |    |  | " ;
    char thirdline[] =   "| __   |  |   | \\/ |  |_     |   |  \\  /  |_   |__| ";
    char fourthline[] =  "|___|  |  |   |    |  |__    |___|   \\/   |__  |  \\ ";
    timeout(1000); // nastavi na 1 sekundu cekani getch()
    if(m_Colors == true){ attron( A_BOLD | COLOR_PAIR(6)); }
    for(int i = 0; i < 3; i++){
        if((ch=getch())=='\n') break;
        mvprintw(m_DisplayRows/3,(m_DisplayColumns-strlen(firstline))/2,"%s", firstline);
        mvprintw((m_DisplayRows/3)+1,(m_DisplayColumns-strlen(secondline))/2,"%s", secondline);
        mvprintw((m_DisplayRows/3)+2,(m_DisplayColumns-strlen(thirdline))/2,"%s", thirdline);
        mvprintw((m_DisplayRows/3)+3,(m_DisplayColumns-strlen(fourthline))/2,"%s", fourthline);
        refresh();
        if((ch=getch())=='\n') break;
        clear();
        refresh();
    }
    if(m_Colors == true){ attroff( A_BOLD | COLOR_PAIR(6)); }
    timeout(-1);
    clear();
}

void CGame::displayYouWin() const{
    clear();
    char ch = ' ';
    char firstline[] =   "        __                               ";
    char secondline[] =  " \\ /   |  |  |   |     |     |  |  |\\  | " ;
    char thirdline[] =   "  |    |  |  |   |     |  |  |  |  | \\ | ";
    char fourthline[] =  "  |    |__|  |___|      \\/ \\/   |  |  \\| ";
    timeout(1000);
    if(m_Colors == true){ attron( A_BOLD | COLOR_PAIR(5)); }
    for(int i = 0; i < 3; i++){
        if((ch=getch())=='\n') break;
        mvprintw(m_DisplayRows/3,(m_DisplayColumns-strlen(firstline))/2,"%s", firstline);
        mvprintw((m_DisplayRows/3)+1,(m_DisplayColumns-strlen(secondline))/2,"%s", secondline);
        mvprintw((m_DisplayRows/3)+2,(m_DisplayColumns-strlen(thirdline))/2,"%s", thirdline);
        mvprintw((m_DisplayRows/3)+3,(m_DisplayColumns-strlen(fourthline))/2,"%s", fourthline);
        refresh();
        if((ch=getch())=='\n') break;
        clear();
        refresh();
    }
    if(m_Colors == true){ attroff( A_BOLD | COLOR_PAIR(5)); }
    timeout(-1);
    clear();
}

int CGame::displayLevelMenu() const{
    clear();
    int WIDTH = 25, HEIGHT = 9;
    int startx = 0, starty = 0;
    const char *choices[] = { "Easy", "Medium", "Hard" };
    int n_choices = sizeof(choices) / sizeof(const char *);
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    noecho();
    cbreak();
    startx = (m_DisplayColumns - WIDTH) / 2;
    starty = (m_DisplayRows - HEIGHT) / 2;
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    printMenu(menu_win, highlight, n_choices, choices, WIDTH, " ");
    while(1)
    {	c = wgetch(menu_win);
    	switch(c)
    	{	case KEY_UP:
			if(highlight == 1) { highlight = n_choices; }
			else { --highlight; }
			break;
		case KEY_DOWN:
			if(highlight == n_choices) { highlight = 1; }
			else { ++highlight; }
			break;
		case 10: // ENTER KEY
			choice = highlight;
			break;
	}
	printMenu(menu_win, highlight, n_choices, choices, WIDTH, " ");
	if(choice != 0)	{ break; }
    }
    if(choice == 1) { return 1; } // easy
    else if(choice == 2) { return 2; } // medium
    else { return 3; } // hard
}

void CGame::displayHowToPlay() const{
    clear();
    char firstline[] =   "Use the arrows to move up, down, left and right.";
    char secondline[] = "The aim is to eat all the food (. and @) in a map.";
    char thirdline[] =  "You have 3 lives. Don't let a ghost touch you." ;
    char fourthline[] =   "You can pause game, while playing, by pressing 'p'.";
    char fifthline[] = "Easy ghosts decide where to go randomly. Hard ones go after you.";
    char sixthline[] = "You can make your own map with the allowed chars (.-#@AC)!!";
    if(m_Colors == true){ attron(COLOR_PAIR(7)); }
    mvprintw(m_DisplayRows/3,(m_DisplayColumns-strlen(firstline))/2,"%s", firstline);
    mvprintw((m_DisplayRows/3)+2,(m_DisplayColumns-strlen(secondline))/2,"%s", secondline);
    mvprintw((m_DisplayRows/3)+4,(m_DisplayColumns-strlen(thirdline))/2,"%s", thirdline);
    mvprintw((m_DisplayRows/3)+6,(m_DisplayColumns-strlen(fourthline))/2,"%s", fourthline);
    mvprintw((m_DisplayRows/3)+8,(m_DisplayColumns-strlen(fifthline))/2,"%s", fifthline);
    mvprintw((m_DisplayRows/3)+10,(m_DisplayColumns-strlen(sixthline))/2,"%s", sixthline);
    if(m_Colors == true){ attroff(COLOR_PAIR(7)); }
    getch(); // waiting for pushing a button
    clear();
}

void CGame::displayCredits() const{
    clear();
    char firstline[] =   "Author: Adam Pecev (pecead@centrum.cz)";
    char secondline[] = "This program was developed as a semestral work.";
    char thirdline[] =  "FIT CVUT, Prague, Czech republic, 2013" ;
    char fourthline[] =   "Developed in C++ with ncurses library.";
    if(m_Colors == true){ attron(COLOR_PAIR(6)); }
    mvprintw(m_DisplayRows/3,(m_DisplayColumns-strlen(firstline))/2,"%s", firstline);
    if(m_Colors == true){ attroff(COLOR_PAIR(6)); }
    if(m_Colors == true){ attron(COLOR_PAIR(7)); }
    mvprintw((m_DisplayRows/3)+2,(m_DisplayColumns-strlen(secondline))/2,"%s", secondline);
    mvprintw((m_DisplayRows/3)+4,(m_DisplayColumns-strlen(thirdline))/2,"%s", thirdline);
    mvprintw((m_DisplayRows/3)+6,(m_DisplayColumns-strlen(fourthline))/2,"%s", fourthline);
    if(m_Colors == true){ attroff(COLOR_PAIR(7)); }
    getch();
    clear();
}

void CGame::initializeColors(){
    if(has_colors() == TRUE){ // if it is possible to change terminal colors
        m_Colors = true;
        start_color(); // start colors mode
        use_default_colors(); // use default colors for everything...change just the things below
        init_pair(1, COLOR_YELLOW, -1); // pacman - yellow letter on default (-1) background
        init_pair(2, COLOR_RED, -1); // ghost
        init_pair(3, COLOR_WHITE, COLOR_BLACK); // others # chars
        init_pair(4, COLOR_BLUE, -1); // normal text (menu choices)
        init_pair(5, COLOR_GREEN, -1); // special1 text (you win, counting)
        init_pair(6, COLOR_RED, -1); // special2 text (game over, author)
        init_pair(7, COLOR_CYAN, -1); // paragraph text (credits and how to play)
    }
}

void CGame::initializeGhosts(){
    if(m_Difficulty == 1){
        for(int i = 1; i < 4; i++){
            m_MovingObjects[i] = new CGhostEasy(alldata);
        }
    }
    else if(m_Difficulty == 2){
        m_MovingObjects[1] = new CGhostEasy(alldata);
        m_MovingObjects[2] = new CGhostEasy(alldata);
        m_MovingObjects[3] = new CGhostHard(alldata);
    }
    else{ //m_Difficulty == 3
        m_MovingObjects[1] = new CGhostHard(alldata);
        m_MovingObjects[2] = new CGhostEasy(alldata);
        m_MovingObjects[3] = new CGhostHard(alldata);
    }
}

void CGame::deleteGhosts(){
    for(int i = 1; i < 4; i++){
        delete m_MovingObjects[i];
    }
}
