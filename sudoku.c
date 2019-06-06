#include "sudoku.h"

void showOptions() {
	move( OPTIONS_POS_Y, OPTIONS_POS_X );
	attron( A_BOLD );
	printw( "Options" );
	attroff( A_BOLD );
	
	move( OPTIONS_POS_Y + 1, OPTIONS_POS_X );
	printw( "========================"); 
	
	move( OPTIONS_POS_Y + 2, OPTIONS_POS_X );
	printw( "Use "); 
	attron( A_BOLD );
	printw("arrow keys" );
	attroff( A_BOLD );
	printw(" to move" );
	
	move( OPTIONS_POS_Y + 3, OPTIONS_POS_X );
	printw( "Use " );
	attron( A_BOLD );
	printw("numpad" );
	attroff( A_BOLD );
	printw(" to write" );
	
	move( OPTIONS_POS_Y + 4, OPTIONS_POS_X );
	printw( "Use " );
	attron( A_BOLD );
	printw("backspace" );
	attroff( A_BOLD );
	printw(" to clean" );
	
	move( OPTIONS_POS_Y + 5, OPTIONS_POS_X );
	printw( "Press " );
	attron( A_BOLD );
	printw("C" );
	attroff( A_BOLD );
	printw(" to restart" );

	move( OPTIONS_POS_Y + 6, OPTIONS_POS_X );
	printw( "Press " );
	attron( A_BOLD );
	printw("H" );
	attroff( A_BOLD );
	printw(" to help" );
	
	move( OPTIONS_POS_Y + 7, OPTIONS_POS_X );
	printw( "Press " );
	attron( A_BOLD );
	printw("S" );
	attroff( A_BOLD );
	printw(" to solve" );

	move( OPTIONS_POS_Y + 8, OPTIONS_POS_X );
	printw( "Press " );
	attron( A_BOLD );
	printw("Q" );
	attroff( A_BOLD );
	printw(" to exit" );
}

void showAll(Sudoku* s)	{
	int i, j;
	for ( i = 0; i < 9; i++ )	{
		for ( j = 0; j < 9; j++ )	{
			s->hidden[j][i] = FALSE;
		}
	}
}

void showTime(int time)	{
	move( OPTIONS_POS_Y + 3, OPTIONS_POS_X + 30 );
	printw( "Elapsed Time: %d", time);
}

void showFinalTime(int time)	{
	attron( A_BOLD );
	move( LINES-3, COLS/2 - (8/2) );
	printw("Time: %d", time);
	attroff( A_BOLD );
}

void showYouWin(){
	const int youwinMessageLength = strlen( YOUWIN_MESSAGE );
	move( LINES - 2, COLS/2 - (youwinMessageLength/2) );
	attron(A_BOLD);
	printw("%s", YOUWIN_MESSAGE);
	attroff(A_BOLD);
}

void showPressAnyKey()	{
	move( LINES - 2, COLS/2-strlen(PRESSANY_MESSAGE)/2);
	printw("%s", PRESSANY_MESSAGE );
}

void showFinalScore(int score)	{
	attron( A_BOLD );
	move( LINES-4, COLS/2 - (8/2) );
	printw("SCORE: %d", score);
	attroff( A_BOLD );
}

void showScore(int score)	{
	move( OPTIONS_POS_Y + 2, OPTIONS_POS_X + 30 );
	printw( "Score: %d", score);
}

void showNoCompleted()	{
	const int ncMessageLength = strlen( NOCOMPLETED_MESSAGE );
	move( LINES - 2, COLS/2 - (ncMessageLength/2) );
	attron(A_BOLD);
	printw("%s", NOCOMPLETED_MESSAGE);
	attroff(A_BOLD);
}

void help(Sudoku* sudoku)	{
	int col, row;
	int tryAgain = TRUE;

	do	{
		col = rand() % 9;
		row = rand() % 9;

		if ( sudoku->hidden[col][row] == TRUE )	{
			sudoku->hidden[col][row] = FALSE;
			tryAgain = FALSE;
		}
	} while ( tryAgain == TRUE );
}

void showTries(int tries)	{
	move( OPTIONS_POS_Y, OPTIONS_POS_X + 30 );
	printw( "Tries: %d", tries);
}

void showHelps(int helps)	{
	move( OPTIONS_POS_Y + 1, OPTIONS_POS_X + 30 );
	printw( "helps: %d", helps);
}

void showQuitDialog()	{
	const int quitMessageLength = strlen( QUIT_MESSAGE );
	move( LINES - 2, COLS/2 - (quitMessageLength/2) );
	printw("%s", QUIT_MESSAGE);
}

void hideQuitDialog() {
	int i;
	const int quitMessageLength = strlen( QUIT_MESSAGE );
	for (i = 0; i < strlen(QUIT_MESSAGE); i++ )	{
		move(LINES - 2, COLS/2 - (quitMessageLength/2) + i);
		addch(' ');
	}
}

void showNewDialog()	{
	const int quitMessageLength = strlen( QUIT_MESSAGE );
	move( LINES - 2, COLS/2 - (quitMessageLength/2) );
	printw("%s", QUIT_MESSAGE);
}

void hideNewDialog() {
	int i;
	const int quitMessageLength = strlen( QUIT_MESSAGE );
	for (i = 0; i < strlen(QUIT_MESSAGE); i++ )	{
		move(LINES - 2, COLS/2 - (quitMessageLength/2) + i);
		addch(' ');
	}
}

int valid(int* boxes)	{
	int i, j;
	for ( i = 0; i < 9; i++ )	{
		for ( j = 0; j < 9; j++ )	{
			if ( boxes[i] != -1 && boxes[j] != -1 ) {
				if ( j != i ) 	{
					if ( boxes[i] == boxes[j] )	{
						return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
}

void __generateSudokuR(Sudoku* sudoku, int subsubbox, Tested tested[9])	{
	int n;
	int i;
	int tryAgain = TRUE;
	int tries = 0;
	int col = subsubbox % 9;
	int row = subsubbox / 9;

	#ifdef __SUDOKU_STEPS__
	drawSudoku( sudoku );
	getch();
	#endif

	#ifdef __SUDOKU_DEBUG__
	printf("\n__generateSudokuR(%d) {%d,%d}\n", subsubbox, col, row );
	#endif	// __SUDOKU_DEBUG__

	if ( col < 0 || row < 0 )	{
		#ifdef __SUDOKU_DEBUG__
		printf("\tNo se ha generado!\n");
		#endif
		exit( 1 );
		return;
	}

	if ( subsubbox >= 81 )	{
		#ifdef __SUDOKU_DEBUG__
		printf("\tGenerado!\n");
		#endif
		return;
	}

	if ( tested[subsubbox].size >= 9 )	{
		#ifdef __SUDOKU_DEBUG__
		printf("\tNo se pueden probar más números. Vuelvo.\n" );
		#endif
		tested[subsubbox].size = 0;
		sudoku->box[ col ][ row ] = -1;
		return __generateSudokuR(sudoku, subsubbox - 1, tested );
	}
	
	do {
		tryAgain = FALSE;
		n = ( rand() % 9 ) + 1;
		for ( i = 0; i < tested[subsubbox].size; i++ )	{
			if ( n == tested[subsubbox].numbers[i] )	{	
				tryAgain = TRUE;
			}
		}
		tries++;
		if ( tries >= 9 )	{
			tryAgain = FALSE;
		}
	} while ( tryAgain == TRUE );
	if ( tries >= 9 ) {
		#ifdef __SUDOKU_DEBUG__
		printf("\tTodos los números probados. Vuelvo.\n" );
		#endif

		tested[subsubbox].size = 0;
		sudoku->box[ col ][ row ] = -1;
		return __generateSudokuR(sudoku, subsubbox - 1, tested);
	}

	sudoku->box[ col ][ row ] = n;

	#ifdef __SUDOKU_DEBUG__
	printf("\tProbando el número %d.\n", n );
	#endif

	if ( validRow(sudoku, row) == FALSE )	{
		tested[subsubbox].numbers[tested[subsubbox].size++] = n;
		
		#ifdef __SUDOKU_DEBUG__
		printf("\tError validando fila %d.\n", row );
		printf("\tNumeros {");
		for(i=0;i<tested[subsubbox].size;i++)	{
			printf("%d ", tested[subsubbox].numbers[i]);
		}
		printf("}\n");
		#endif

		return __generateSudokuR( sudoku, subsubbox, tested );
	}
	else	{
		if ( validCol(sudoku, col) == FALSE )	{
			tested[subsubbox].numbers[tested[subsubbox].size++] = n;
	
			#ifdef __SUDOKU_DEBUG__
			printf("\tError validando columna %d.\n", row );
			printf("\tNumeros {");
			for(i=0;i<tested[subsubbox].size;i++)	{
				printf("%d ", tested[subsubbox].numbers[i]);
			}
			printf("}\n");
			#endif

			return __generateSudokuR( sudoku, subsubbox, tested );
		}
		else {
			int subbox = getSubbox(col, row);
			if ( validSubbox( sudoku, subbox ) == FALSE )	{
				tested[subsubbox].numbers[tested[subsubbox].size++] = n;

				#ifdef __SUDOKU_DEBUG__
				printf("\tError validando subcasilla %d.\n", subbox );
				printf("\tNumeros {");
				for(i=0;i<tested[subsubbox].size;i++)	{
					printf("%d ", tested[subsubbox].numbers[i]);
				}
				printf("}\n");
				#endif

				return __generateSudokuR( sudoku, subsubbox, tested );
			}
			else {
				tested[subsubbox].numbers[tested[subsubbox].size++] = n;

				#ifdef __SUDOKU_DEBUG__
				printf("\tNúmero puesto. Siguiente\n" );
				printf("\tNumeros {");
				for(i=0;i<tested[subsubbox].size;i++)	{
					printf("%d ", tested[subsubbox].numbers[i]);
				}
				printf("}\n");
				#endif
				
				return __generateSudokuR( sudoku, subsubbox + 1, tested );
			}
		}
	}
}

void generateSudoku(Sudoku* sudoku)	{
	int i, j;
	int hidden = 0;
	Tested testedStruct[81];
	for ( i = 0; i < 81; i++ ) {
		testedStruct[i].size = 0;
	}

	__generateSudokuR( sudoku, 0, testedStruct );

	do {
		int hiddenCol = (rand() % 9);
		int hiddenRow = (rand() % 9);
		
		if ( sudoku->hidden[hiddenCol][hiddenRow] == FALSE )	{
			sudoku->hidden[hiddenCol][hiddenRow] = TRUE;
			hidden++;
		}

	} while ( hidden < BOXES_HIDDEN );

	for ( i = 0; i < 9; i++ )	{
		for ( j = 0; j < 9; j++ ){
			if ( sudoku->hidden[j][i] == FALSE )		{
				sudoku->ai[j][i] = TRUE;
			}
		}
	}
}


void createSudoku(Sudoku* sudoku)	{
	int row;
	int col;

	for ( row = 0; row < 9; row++ )	{
		for ( col = 0; col < 9; col++ )	{
			sudoku->box[col][row] = -1;
			sudoku->hidden[col][row] = FALSE;
			sudoku->ai[col][row] = FALSE;
#ifdef __SUDOKU_ENABLE_ERRORS__
			sudoku->error[col][row] = FALSE;
#endif
		}
	}
	
	sudoku->col = 0;
	sudoku->row = 0;
}

int validRow(Sudoku* sudoku, int row){
	int rowNumbers[9];
	int i;

	for ( i = 0; i < 9; i++ )	{
		if ( sudoku->hidden[i][row] == FALSE )	{
			rowNumbers[i] = sudoku->box[i][row];
		}
		else {
			rowNumbers[i]=-1;
		}
	}

	return valid( rowNumbers );
}

int validCol(Sudoku* sudoku, int col){
	int colNumbers[9];
	int i;

	for ( i = 0; i < 9; i++ )	{
		if ( sudoku->hidden[col][i] == FALSE )	{
			colNumbers[i] = sudoku->box[col][i];
		}
		else {
			colNumbers[i]=-1;
		}
	}

	return valid( colNumbers );
}

int getSubbox(int col, int row)	{
	int _subbox;
	_subbox = (row / 3) *3 + (col / 3);
	return _subbox;
}

int validSubbox(Sudoku* sudoku, int subbox){
	int c, r;
	int iterations = 0;
	int i = 0;
	int x = (subbox % 3)*3, y = (subbox / 3)*3;
	int numbers[9];
	
	for ( r=0; r <3; r++ )	{
		for ( c=0; c < 3; c++ ){
			if ( sudoku->hidden[x+c][y+r] == FALSE )	{
				numbers[i] = sudoku->box[x+c][y+r];
			}
			else {
				numbers[i] = -1;
			}
			i++;
		}
	}

	return valid( numbers );
}

void getCenter(int* x, int* y)	{
	*x = COLS / 2;
	*y = LINES / 2;
}

void moveLeft(Sudoku* sudoku)	{
	sudoku->col--;
	if ( sudoku->col < 0 )	{
		sudoku->col = 8;
	}
	
	refreshPosition(sudoku);
}

void moveDown(Sudoku* sudoku)	{
	sudoku->row++;
	if ( sudoku->row > 8 )	{
		sudoku->row = 0;
	}
	
	refreshPosition(sudoku);
}

void moveRight(Sudoku* sudoku)	{
	sudoku->col++;
	if ( sudoku->col > 8 )	{
		sudoku->col = 0;
	}
	
	refreshPosition(sudoku);
}

void moveUp(Sudoku* sudoku)	{
	sudoku->row--;
	if ( sudoku->row < 0 )	{
		sudoku->row = 8;
	}
	
	refreshPosition(sudoku);
}

void refreshPosition(const Sudoku* sudoku)	{
	int sourceY = (LINES/2) - ((9*2)/2);
	int sourceX = (COLS/2) - ((9*4)/2);
	int x = sourceX+(sudoku->col*4)+2;
	int y = sourceY+(sudoku->row*2)+1;

	move(y, x);
}

void showInfo()	{
	move( LINES - 2, COLS-strlen(STR_AUTHOR) - strlen(STR_YEAR) - 2);
	printw("%s %s", STR_AUTHOR, STR_YEAR);
}

void drawSudoku(Sudoku* sudoku)	{
	int row;
	int col;
	
	int sourceY = (LINES/2) - ((9*2)/2);
	int sourceX = (COLS/2) - ((9*4)/2);
	
	for ( row = 0; row < 9; row++ )	{
		for ( col = 0; col < 9; col++ )	{
		
			move( sourceY+row*2, sourceX+col*4 );
			if ( row == 0 || row == 3 || row == 6 ) { attron(A_BOLD); }
			printw("+---+");
			if ( row == 0 || row == 3 || row == 6 ) { attroff(A_BOLD); }
			
			move(sourceY+ (row*2)+1, sourceX+col*4 );
			if ( col == 0 || col == 3 || col == 6 ) { attron(A_BOLD); }
			printw("|");
			if ( col == 0 || col == 3 || col == 6 ) { attroff(A_BOLD); }
			if ( sudoku->box[col][row] != -1 && sudoku->hidden[col][row] == FALSE )	{ 
				#ifdef __SUDOKU_ENABLE_ERRORS__
				if ( sudoku->error[col][row] == TRUE )	{
					attron(COLOR_PAIR(3));
				}
				else {
					if ( sudoku->ai[col][row] == TRUE ) {
						attron(COLOR_PAIR(2));
					}
					else {
						attron(COLOR_PAIR(1));
					}
				}
				#endif

				printw(" %d ", sudoku->box[col][row]); 
			
				#ifdef __SUDOKU_ENABLE_ERRORS__
				if ( sudoku->error[col][row] == TRUE )	{
					attroff(COLOR_PAIR(3));
				}
				else {
					if ( sudoku->ai[col][row] == TRUE ) {
						attroff(COLOR_PAIR(2));
					}
					else {
						attroff(COLOR_PAIR(1));
					}
				}
				#endif
			}
			else { printw("   "); }
			if ( col == 8 ) { attron(A_BOLD); }
			printw("|");
			if ( col == 8 ) { attroff(A_BOLD); }
					
			move(sourceY+ (row*2)+2, sourceX+col*4 );
			if ( row == 8 ) { attron(A_BOLD); }
			printw("+---+");
			if ( row == 8 ) { attroff(A_BOLD); }
		}
	}
	
	refreshPosition(sudoku);
}

void writeSudoku(Sudoku* sudoku, int ch)	{
	switch ( ch ) {
		case '1': ch = 1; break;
		case '2': ch = 2; break;
		case '3': ch = 3; break;
		case '4': ch = 4; break;
		case '5': ch = 5; break;
		case '6': ch = 6; break;
		case '7': ch = 7; break;
		case '8': ch = 8; break;
		case '9': ch = 9; break;
	}
	sudoku->box[sudoku->col][sudoku->row] = ch;
	sudoku->hidden[sudoku->col][sudoku->row] = FALSE;

	#ifdef __SUDOKU_ENABLE_ERRORS__
	if ( validRow(sudoku, sudoku->row) == FALSE )	{
		sudoku->error[sudoku->col][sudoku->row] = TRUE;
	}
	else {
		if ( validCol(sudoku, sudoku->col) == FALSE )	{
			sudoku->error[sudoku->col][sudoku->row] = TRUE;
		}
		else {
			if ( validSubbox(sudoku, getSubbox(sudoku->col,sudoku->row)) == FALSE )	{
				sudoku->error[sudoku->col][sudoku->row] = TRUE;
			}
			else {
				sudoku->error[sudoku->col][sudoku->row] = FALSE;
			}
		}
	}
	#endif

	refreshPosition(sudoku);
}

void cleanBox(Sudoku* sudoku)	{
	sudoku->box[sudoku->col][sudoku->row] = -1;
	refreshPosition(sudoku);
}

int validate(Sudoku* sudoku)	{
	int i = 0;
	int j = 0;
	for ( i = 0; i < 9; i++ ) {	
		for ( j = 0; j < 9; j++ ) {
			if ( sudoku->hidden[j][i] == TRUE )	{
				return FALSE;
			}

			if ( validRow(sudoku, i) == FALSE )	{
				return FALSE;
			}
			if ( validCol(sudoku, j) == FALSE )	{
				return FALSE;
			}
			if ( validSubbox(sudoku, getSubbox(j,i)) == FALSE )	{
				return FALSE;
			}
		}
	}

	return TRUE;
}

