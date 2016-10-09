//if you have saved code as ttt.cpp
//compile as: $ g++ -o ttt ttt.cpp 


#include <string> 
#include <cstdio> //used to call printf so that spots can be marked as chars
#include <iostream>

using namespace std;

struct TicTacSqs { //this is the board, as a struct
	char UP_LEFT;
	char UP_MID;
	char UP_RIGHT ;
	char MID_LEFT ;
	char MID_MID ;
	char MID_RIGHT ;
	char LOW_LEFT ;
	char LOW_MID ;
	char LOW_RIGHT ;
};

void showBoard(TicTacSqs brd) {
	printf(" %c | %c | %c \n",brd.UP_LEFT,brd.UP_MID,brd.UP_RIGHT);
	printf("___|___|___\n");
	printf(" %c | %c | %c \n",brd.MID_LEFT,brd.MID_MID,brd.MID_RIGHT);
	printf("___|___|___\n");
	printf(" %c | %c | %c \n",brd.LOW_LEFT,brd.LOW_MID,brd.LOW_RIGHT);
	printf("   |   |   \n");
}

int winCheck(TicTacSqs brd) {
	int winStatus = 0;
	//top parallel
	if ((brd.UP_LEFT == brd.UP_MID) && (brd.UP_MID==brd.UP_RIGHT) && (brd.UP_MID != ' ')) {
		if (brd.UP_LEFT=='x') {
			winStatus = 1; //player 1 wins
		}
		else { winStatus = 2; }	//player 2 wins
	}
	if ((brd.MID_LEFT == brd.MID_MID) && (brd.MID_MID==brd.MID_RIGHT) && (brd.MID_RIGHT != ' ')) {
		if (brd.MID_LEFT == 'x') {
			winStatus = 1;
		}
		else { winStatus = 2; }
	}
	if ((brd.LOW_LEFT == brd.LOW_MID) && (brd.LOW_MID == brd.LOW_RIGHT) && (brd.LOW_MID != ' ')) {
		if (brd.LOW_LEFT == 'x') {
			winStatus = 1;
		}
		else { winStatus = 2; }
	}
	//left perpendicular
	if ((brd.UP_LEFT == brd.MID_LEFT) && (brd.MID_LEFT == brd.LOW_LEFT) && (brd.MID_LEFT != ' ' )) {
		if (brd.MID_LEFT == 'x') {
			winStatus = 1;
		}
		else {winStatus = 2; }
	}
	if ((brd.UP_MID == brd.MID_MID) && (brd.MID_MID == brd.LOW_MID) && (brd.MID_MID != ' ' )) {
		if (brd.MID_MID == 'x') {
			winStatus = 1;
		}
		else {winStatus = 2; }
	}
	if ((brd.UP_RIGHT == brd.MID_RIGHT) && (brd.MID_RIGHT == brd.LOW_RIGHT) && (brd.MID_RIGHT != ' ' )) {
		if (brd.MID_RIGHT == 'x') {
			winStatus = 1;
		}
		else {winStatus = 2; }
	}
	//diagonals
	if ((brd.UP_LEFT == brd.MID_MID) && (brd.MID_MID == brd.LOW_RIGHT) && (brd.MID_MID != ' ')) {
		if (brd.MID_MID == 'x') {
			winStatus = 1;
		}
		else {winStatus = 2;}
	}
	if ((brd.LOW_LEFT == brd.MID_MID) && (brd.MID_MID == brd.UP_RIGHT) && (brd.MID_MID != ' ')) {
		if (brd.MID_MID == 'x') {
			winStatus = 1;
		}
		else { winStatus = 2; }
	}
	return winStatus;
}

int takeTurn(int turnCnt, TicTacSqs& brd) {
	char sign;
	if (turnCnt&1) { //if turn is odd, bit-wise, then player 1 should go
		sign = 'x';
	}
	else { sign = 'o'; }
	int sqNo,err=0;
	std::cout<<"Enter the square to mark with a "<< sign <<": ";
	std::cin>>sqNo;
	switch (sqNo) {
		case 1: 
			if (brd.UP_LEFT == ' ') //check that square is not yet claimed
			{ brd.UP_LEFT = sign; }
			else { err = 1; }
			break;
		case 2: if (brd.UP_MID == ' ')
			{ (brd.UP_MID =  sign); }
			else { err = 1; }
			break;
		case 3: if (brd.UP_RIGHT == ' ')
			{ (brd.UP_RIGHT =  sign); }
			break;
		case 4: if (brd.MID_LEFT == ' ')
			{ (brd.MID_LEFT = sign); }
			else { err = 1; }
			break;
		case 5: if (brd.MID_MID == ' ')
			{ (brd.MID_MID = sign); }
			else { err = 1; }
			break;
		case 6: if (brd.MID_RIGHT == ' ')
			{ brd.MID_RIGHT = sign; }
			else { err = 1; }
			break;
		case 7: if (brd.LOW_LEFT == ' ')
			{ brd.LOW_LEFT = sign; }
			else { err = 1; }
			break;
		case 8: if (brd.LOW_MID == ' ')
			{ brd.LOW_MID = sign; }
			else { err = 1; }
			break;
		case 9: if (brd.LOW_RIGHT == ' ')
			{ brd.LOW_RIGHT = sign; }
			else { err = 1; }
			break;
		default:
			std::cout<<"Pick a square, 1-9\n";
			err = 1;		
			break;
		}
	return err;
}


int main() {
	int win = 0;
	int turnCnt = 0;
	int err = 0;
	int maxTurns = 9;
	std::cout<<"Welcome to Tic Tac Toe\n";
	std::cout<<"Squares go from 1 in left top corner to 9 in bottom right...\n";
	std::cout<<"Best of luck!\n";
	TicTacSqs board {' ',' ',' ',' ',' ',' ',' ',' ',' '}; //initialize empty board as a struct
	showBoard(board); //show the initial setup, for appearances' sake
	do {	
		
		turnCnt++;
		maxTurns--;
		err = takeTurn(turnCnt,board);
		if (err==1) {
			turnCnt--; //revert to previous player's turn
			maxTurns++;
		}
		showBoard(board); //display board, so the winner sees outcome
		win = winCheck(board);
		if (win != 0) {
			std::cout<<"Player " << win <<" has won the game!\n";
			break;
		}
		if ((maxTurns==0) && (win == 0)) {
			//if win variable still 0 and no plays remaining, game is drawn
			std::cout<<"The game's a draw! PLAY AGAIN....\n";
			break;
		}
		err = 0;
	} while (win == 0);

}
