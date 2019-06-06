#include <stdio.h>
#include <ncurses.h>
#include <curses.h>
#include <pthread.h>
#include "sudoku.h"

void* countTime(void* p);

int gSolved;
pthread_mutex_t gSolvedMutex;

int main(int argc, char* argv[])	{
	
	srand( time( NULL) );

	gSolved = FALSE;
	
	int ch;
	int quitSudoku = 0;
	int quitDialog = 0;
	int newDialog = 0;
	int youWin = 0;
	
	int tries = 0;
	int helps = 0;
	//int score = 0;
	
	int gameTime = 0;
	pthread_t threadTimer;
	
	Sudoku sudoku;

	srand( time( NULL) );

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	cbreak();

	start_color();
	init_pair( 1, COLOR_WHITE, COLOR_BLACK );
	init_pair( 2, COLOR_CYAN, COLOR_BLACK );
#ifdef __SUDOKU_ENABLE_ERRORS__
	init_pair( 3, COLOR_WHITE, COLOR_RED );
#endif

	refresh();

	pthread_mutex_init( &gSolvedMutex, 0 );
	pthread_create( &threadTimer, NULL, countTime, (void*)&gameTime );

	createSudoku( &sudoku );
	generateSudoku( &sudoku );

	while ( quitSudoku == 0 )	{

		//score = (tries*2-BOXES_HIDDEN) - helps;

		showOptions();
		showTries( tries );
		showHelps( helps );
		//showScore( score );
		showInfo();
		showTime( gameTime );
		drawSudoku( &sudoku );
		
		ch = getch();
		clear();
		switch( ch )	{
			case 'q':
				showQuitDialog();
				quitDialog = 1;
				break;
			
			case 'y':
				if ( quitDialog == 1 )	{
					quitSudoku = 1;
				}
				else if ( newDialog == 1 )	{
					hideNewDialog();
					createSudoku( &sudoku );
					generateSudoku( &sudoku );
					gameTime = 0;
				}
				break;
			case 'n':
				if ( quitDialog == 1 )	{
					hideQuitDialog();
				}
				else if ( newDialog == 1 )	{
					hideNewDialog();
					newDialog = 0;
				}
				break;
			
			case KEY_LEFT:
				moveLeft(&sudoku);
				break;
			case KEY_DOWN:
				moveDown(&sudoku);
				break;
			case KEY_RIGHT:
				moveRight(&sudoku);
				break;
			case KEY_UP:
				moveUp(&sudoku);
				break;
		
			case 'h':
				help( &sudoku );
				helps++;
				break;

			case '1': case '2': case '3': 
			case '4': case '5': case '6': case '7':
			case '8': case '9':
				writeSudoku( &sudoku, ch );
				tries++;
				break;

			case 's':
				showAll( &sudoku );
				break;
			
			case 'c':
				showNewDialog();
				newDialog = 1;
				break;

			case KEY_BACKSPACE:
				cleanBox( &sudoku );
				break;
		}
		
		refresh();

		if ( validate( &sudoku ) == TRUE )	{
			showYouWin();
			youWin = 1;
		}

		if ( youWin == 1 )	{
			pthread_mutex_lock( &gSolvedMutex );
				gSolved = TRUE;
			pthread_mutex_unlock( &gSolvedMutex );
			
			pthread_join( threadTimer, NULL );
			
			//showFinalScore( score );
			showFinalTime( gameTime );
			
			quitSudoku = 1;
			showPressAnyKey();

			showOptions();
			showTries( tries );
			showHelps( helps );
			drawSudoku( &sudoku );

			getch();
		}


	}
	
	if ( gSolved == FALSE )	{
		gSolved = TRUE;
		pthread_join( threadTimer, NULL );
	}
	
	pthread_mutex_destroy( &gSolvedMutex );

	endwin();
	return 0;
}

void* countTime(void* p)	{
	pthread_detach( pthread_self() );
	
	int* timer = (int*)p;
	int next = TRUE;
	
	do {
		usleep( 1000 * 1000 );
		(*timer)++;
		
		pthread_mutex_lock( &gSolvedMutex );
			if ( gSolved == TRUE ) { 
				next = FALSE;
			}
		pthread_mutex_unlock( &gSolvedMutex );

		int cx, cy;
		getyx(stdscr, cy, cx);

		showTime( *timer );
		move(cy, cx);
		refresh();
	} while ( next == TRUE );
	
	pthread_exit( 0 );
}

