#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

//#define __SUDOKU_DEBUG__
//#define __SUDOKU_STEPS__
#define __SUDOKU_ENABLE_ERRORS__

#undef FALSE
#undef TRUE
static const int TRUE = 1;
static const int FALSE = 0;

static const int OPTIONS_POS_X = 2;
static const int OPTIONS_POS_Y = 1;
static const char QUIT_MESSAGE[] = "Are you sure? (y/n)";
static const char YOUWIN_MESSAGE[] = "You Win!";
static const char NOCOMPLETED_MESSAGE[] = "Sudoku is not completed!";
static const char PRESSANY_MESSAGE[] = "Press any key to continue...";

static const char STR_AUTHOR[] = "A. Roldán";
static const char STR_YEAR[] = "2014";

static const int BOXES_HIDDEN = 40;

void showInfo();

void showOptions();
void showQuitDialog();
void hideQuitDialog();
void showNewDialog();
void hideNewDialog();
void getCenter(int* x, int* y);

void showPressAnyKey();

typedef struct c_sudoku {
	int box[9][9];
	int ai[9][9];
	int row;
	int col;
	int hidden[9][9];
#ifdef __SUDOKU_ENABLE_ERRORS__
	int error[9][9];
#endif
} Sudoku;

typedef struct c_tested {
	int numbers[9];
	int size;
} Tested;

void showAll(Sudoku* s);

void showTime(int time);
void showFinalTime(int time);

void showScore(int score);
void showFinalScore(int score);
void showYouWin();
void showNoCompleted();

void createSudoku(Sudoku* sudoku);
void generateSudoku(Sudoku* sudoku);
void __generateSudokuR(Sudoku* sudoku, int subsubbox, Tested tested[9]);
int validRow(Sudoku* sudoku, int row);
int validCol(Sudoku* sudoku, int col);
int validSubbox(Sudoku* sudoku, int subbox);
int getSubbox(int col, int row);
int valid(int* boxes);

void moveLeft(Sudoku* sudoku);
void moveDown(Sudoku* sudoku);
void moveRight(Sudoku* sudoku);
void moveUp(Sudoku* sudoku);
void drawSudoku(Sudoku* sudoku);
void refreshPosition(const Sudoku* sudoku);
void writeSudoku(Sudoku* sudoku, int ch);

void help(Sudoku* sudoku);

int validate(Sudoku* sudoku);

void showTries(int tries);
void showHelps(int helps);

