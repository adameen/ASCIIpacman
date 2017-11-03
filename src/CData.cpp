#include "CData.h"

using namespace std;

CData::CData() : m_CharMapArray(NULL), m_HelpCharMapArray(NULL), m_BoolMapArray(NULL), m_CntRow(0), m_CntColumn(0), m_CntNormalFood(0), m_CntBonusFood(0), 
                 m_CPacman_X(0), m_CPacman_Y(0), m_Ghost1_X(-1), m_Ghost1_Y(-1), m_Ghost2_X(-1), m_Ghost2_Y(-1), m_Ghost3_X(-1), m_Ghost3_Y(-1) { }


CData::~CData(){
    if(m_CharMapArray != NULL){
        for(int i = 0; i < m_CntRow; i++){ // destruction of all 2D fields
            delete [] m_BoolMapArray[i];
            delete [] m_CharMapArray[i];
            delete [] m_HelpCharMapArray[i];
        }
        delete [] m_BoolMapArray;
        delete [] m_CharMapArray;
        delete [] m_HelpCharMapArray;
    }
}

void CData::loadMap(){
    int ghostnumber = 0; // cnt of pacmen
    int pacmannumber = 0; //cnt of ghosts
    string line = " ";
    string max_line = " ";
    int i = 0;
    char loadedChar = ' ';
    int transformedChar = 0;
    ifstream mymap1 ( "./examples/pacmanmap" );
    if (!mymap1.is_open()) {throw COpenException();}
    while( getline ( mymap1, line ) ){
        if(i == 39) {throw CRowException(i);} // if there are too many rows
        if((int)line.size() > 84) {throw CColumnException(84);} // type conversion to not compare unsigned int with int (because of compilator warning)
        if(max_line < line) max_line = line;
        i++;
    }
    m_CntColumn = (int)max_line.size(); // saves counts of rows and columns
    m_CntRow = i;
    createMap(); // allocates 2D maps
    mymap1.close();
    ifstream mymap2 ( "./examples/pacmanmap" );
    if (!mymap2.is_open()) {throw COpenException();}
    i = 0;
    while ( getline ( mymap2, line ) ) {
        istringstream newstream;
        newstream.str(line);
        for(int j = 0; j < m_CntColumn; j++){
            loadedChar = newstream.get(); // load char one after another from this line
            if(loadedChar == EOF){ // to be able to have not only rectangle maps (lines are not equal length)
                break;
            }
            transformedChar = transformChar(loadedChar);
            m_BoolMapArray[i][j] = transformedChar;
            if (loadedChar == '-') { // replace "-" for " " ...ghosts and pacman can go only where "." and "-" are
                m_CharMapArray[i][j] = ' ';
                m_HelpCharMapArray[i][j] = ' ';
            }
            else {
                if(loadedChar == 'A'){
                    ghostnumber++;
                    if(ghostnumber == 4) throw CGhostCntException();
                    if(m_Ghost1_X == -1){ m_Ghost1_X = j; m_Ghost1_Y = i; } // sets each ghost's coordinates
                    else if(m_Ghost2_X == -1){ m_Ghost2_X = j; m_Ghost2_Y = i; }
                    else { m_Ghost3_X = j; m_Ghost3_Y = i; }
                }
                if(loadedChar == 'C'){
                    pacmannumber++;
                    if(pacmannumber == 2) throw CPacmanCntException();
                }
                m_CharMapArray[i][j] = loadedChar;
                m_HelpCharMapArray[i][j] = loadedChar;
            }
        }
        i++;
    }
    if(ghostnumber < 3) throw CGhostCntException();
    if(pacmannumber == 0) throw CPacmanCntException();
    mymap2.close();
}

void CData::createMap(){
    m_CharMapArray = new char * [m_CntRow];
    m_HelpCharMapArray = new char * [m_CntRow];
    m_BoolMapArray = new int * [m_CntRow];
    
    for(int i = 0; i < m_CntRow; i++){ //initialization of matrixes
        m_CharMapArray[i] = new char [m_CntColumn];
        m_HelpCharMapArray[i] = new char [m_CntColumn];
        m_BoolMapArray[i] = new int [m_CntColumn];
    }
    
    for(int i = 0; i < m_CntRow; i++){
            for(int j = 0; j < m_CntColumn; j++){ // null the matrixes
                m_BoolMapArray[i][j]=0;
                m_CharMapArray[i][j]=' ';
                m_HelpCharMapArray[i][j]=' ';
            }
    }
}

int CData::transformChar(const char loadedChar) const{
    if(loadedChar == '#') return 0;
    if(loadedChar == ' ') return 0;
    if(loadedChar == '.') return 1;
    if(loadedChar == '-') return 1;
    if(loadedChar == '@') return 1;
    if(loadedChar == 'C') return 1;
    if(loadedChar == 'A') return 1;
    throw CCharException(loadedChar); // if there is a bad char in a map
    return 0;
}

int CData::getRows() const{
    return m_CntRow;
}

int CData::getColumns() const{
    return m_CntColumn;
}

char ** CData::getCharMap() const{
    return m_CharMapArray;
}

char CData::getChar(const int x, const int y) const{
    return m_CharMapArray[y][x];
}

int CData::getBool(const int x, const int y) const{
    return m_BoolMapArray[y][x];
}

void CData::changeCharMap(const int row, const int column, const char letter){
    m_CharMapArray[row][column] = letter;
}

void CData::checkFoodNumber(){
    for(int i = 0 ; i < m_CntRow; i++){
        for(int j = 0; j < m_CntColumn; j++){
            if(m_CharMapArray[i][j] == '.'){
                m_CntNormalFood++;
            }
            if(m_CharMapArray[i][j] == '@'){
                m_CntBonusFood = m_CntBonusFood + 10;
            }
        }
    }
}

int CData::getFoodNumber() const{
    return m_CntNormalFood + m_CntBonusFood;
}

void CData::refreshMap(){
    for(int i = 0 ; i < m_CntRow; i++){
        for(int j = 0; j < m_CntColumn; j++){
            if(m_HelpCharMapArray[i][j] == 'A'){
                if(m_Ghost1_X == -1){ m_Ghost1_X = j; m_Ghost1_Y = i; }
                else if(m_Ghost2_X == -1){ m_Ghost2_X = j; m_Ghost2_Y = i; }
                else { m_Ghost3_X = j; m_Ghost3_Y = i; }
            }
            m_CharMapArray[i][j] = m_HelpCharMapArray[i][j];
        }
    }
}

void CData::getGhostIndex(int& x, int& y){
    if(m_Ghost1_X != -1){
        x = m_Ghost1_X;
        y = m_Ghost1_Y;
        m_Ghost1_X = -1; // sets on -1 because of the next ghost must take m_Ghost2_X and so on
        m_Ghost1_Y = -1;
    }
    else if(m_Ghost2_X != -1){
        x = m_Ghost2_X;
        y = m_Ghost2_Y;
        m_Ghost2_X = -1;
        m_Ghost2_Y = -1;
    }
    else{ //m_Ghost3_X != -1
        x = m_Ghost3_X;
        y = m_Ghost3_Y;
        m_Ghost3_X = -1;
        m_Ghost3_Y = -1;
    }
}

void CData::changeCPacmanIndex(const int x, const int y){
    m_CPacman_X = x;
    m_CPacman_Y = y;
}

void CData::getCPacmanIndex(int & x, int & y) const{
    x = m_CPacman_X;
    y = m_CPacman_Y;
}
