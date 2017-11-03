#include "CGhostEasy.h"


CGhostEasy::CGhostEasy(CData& alldata) : m_LastChar(' '), m_CycleCounter(0){
    int x, y;
    m_Direction = 8; // first direction is up
    alldata.getGhostIndex(x, y); // assigns coordinates to the ghost from member variable of CData
    m_X = x;
    m_Y = y;
    m_OriginalX = m_X; // saves original coordinates to refresh it after the game is over
    m_OriginalY = m_Y;
}

int CGhostEasy::move(const int button, CData & alldata){
    int value = 0;
    int random = -1;
    int lastX = 0; // to check last coordinates - ghost should not be able to go back
    int lastY = 0;
    int oppositeDirection = 0; // if there is a "dead-end street", turn around
    int up = alldata.getBool(m_X, m_Y-1); // to know if there is a free way in the up side
    int down = alldata.getBool(m_X, m_Y+1);
    int left = alldata.getBool(m_X-1, m_Y);
    int right = alldata.getBool(m_X+1, m_Y);
    srand (time(NULL)); // puts a seed of random number
    if(m_Direction == 8){ // check last index and opposite direction if ghost's direction is "up"
        lastX = m_X;
        lastY = m_Y+1;
        oppositeDirection = 2;       
    }
    else if(m_Direction == 2){
        lastX = m_X;
        lastY = m_Y-1;
        oppositeDirection = 8;
    }
    else if(m_Direction == 4){
        lastX = m_X+1;
        lastY = m_Y;
        oppositeDirection = 6;
    }
    else{ //m_Direction == 6 
        lastX = m_X-1;
        lastY = m_Y;
        oppositeDirection = 4;
    }
    while(1){
        m_CycleCounter++;
        if(m_CycleCounter == 50){ // if there are 50 unsuccessful tries (iterates), turn around
            if(oppositeDirection == 8) { value = moveUp(alldata); }
            else if(oppositeDirection == 2) { value = moveDown(alldata); }
            else if(oppositeDirection == 4) { value = moveLeft(alldata); }
            else value = moveRight(alldata);
            m_CycleCounter = 0;
            break;
        }
        random = rand() % 4;
        if(random == 0){ // check going up
            if(up == 0 || (m_Y-1 == lastY && m_X == lastX)) continue; // if can't go up or would go back
            else{
                m_CycleCounter = 0;
                value = moveUp(alldata);
                break;
            }
        }
        else if(random == 1){ // check going down
            if(down == 0 || (m_Y+1 == lastY && m_X == lastX)) continue;
            else{
                m_CycleCounter = 0;
                value = moveDown(alldata);
                break;
            }
        }
        else if(random == 2){ // check going left
            if(left == 0 || (m_X-1 == lastX && m_Y == lastY)) continue;
            else{
                m_CycleCounter = 0;
                value = moveLeft(alldata);
                break;
            }
        }
        else{ //random == 3 ...// check going right
            if(right == 0 || (m_X+1 == lastX && m_Y == lastY)) continue;
            else{
                m_CycleCounter = 0;
                value = moveRight(alldata);
                break;
            }
        }
    }
    return value;
}

int CGhostEasy::moveUp(CData& alldata){
    if(alldata.getChar(m_X, m_Y-1) == 'C' || alldata.getChar(m_X, m_Y-1) == 'O'){ // got pacman
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X, m_Y-1) == 'A'){ // on the next index is another ghost - dont move, just turn around
        m_Direction = 2;
        return 0;
    }
    else{
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X, m_Y-1);
        alldata.changeCharMap(m_Y-1, m_X, 'A');
        m_Direction = 8;
        m_Y--;
        return 0;
    }
}

int CGhostEasy::moveDown(CData& alldata){
    if(alldata.getChar(m_X, m_Y+1) == 'C' || alldata.getChar(m_X, m_Y+1) == 'O'){
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X, m_Y+1) == 'A'){
        m_Direction = 8;
        return 0;
    }
    else{
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X, m_Y+1);
        alldata.changeCharMap(m_Y+1, m_X, 'A');
        m_Direction = 2;
        m_Y++;
        return 0;
    }
}

int CGhostEasy::moveLeft(CData& alldata){
    if(alldata.getChar(m_X-1, m_Y) == 'C' || alldata.getChar(m_X-1, m_Y) == 'O'){
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X-1, m_Y) == 'A'){
        m_Direction = 6;
        return 0;
    }
    else{
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X-1, m_Y);
        alldata.changeCharMap(m_Y, m_X-1, 'A');
        m_Direction = 4;
        m_X--;
        return 0;
    }
}

int CGhostEasy::moveRight(CData& alldata){
    if(alldata.getChar(m_X+1, m_Y) == 'C' || alldata.getChar(m_X+1, m_Y) == 'O'){
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X+1, m_Y) == 'A'){
        m_Direction = 4;
        return 0;
    }
    else{
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X+1, m_Y);
        alldata.changeCharMap(m_Y, m_X+1, 'A');
        m_Direction = 6;
        m_X++;
        return 0;
    }
}

void CGhostEasy::takeGhostHome(CData& alldata){ // after every pacman killing - put last char down and transport "home"
    alldata.changeCharMap(m_Y, m_X, m_LastChar);
    m_X = m_OriginalX;
    m_Y = m_OriginalY;
    alldata.changeCharMap(m_Y, m_X, 'A'); // puts ghost gome
    m_LastChar = ' ';
}
