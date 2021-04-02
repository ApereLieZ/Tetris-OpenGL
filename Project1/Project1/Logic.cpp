#include "Logic.h"
#include <iostream>
#include <random>
#include <ctime>

namespace TetrisGame {

	void Logic::spawnFigure() 
	{
		srand(time(0));
		typeOfTetramino = rand() % 7;
		for (int i = 0; i < 4; i++) {
			a[i].x = figures[typeOfTetramino][i] / 2;
			a[i].y = figures[typeOfTetramino][i] % 2;
		}
	}

	void Logic::downFigure(int** arr, int row, int coll)
{
	if (checkCollizionDown(arr, row, coll)) {
		for (int i = 0; i < 4; i++)
		{
			a[i].x += 1;
		}
	}
}

	bool Logic::checkCollizionDown(int** arr, int row, int coll) {
		for (int i = 0; i < 4; i++)
			if (a[i].x >= row - 1 || arr[a[i].x + 1][a[i].y] != 0) {
				addFigureToGameField(arr, row, coll );
				spawnFigure();
				checkLine(arr, row, coll);
				return false;
			}
		return 1;
	}

	void Logic::moveFigure(int dx, int** arr, int row, int coll)
	{
		if (checkCollizionLR(arr, row, coll, dx)) {
			for (int i = 0; i < 4; i++)
			{
				a[i].y -= dx;
			}
		}
	}

	bool Logic::checkCollizionLR(int** arr, int row, int coll, int dx) {
		for (int i = 0; i < 4; i++) {
			if (a[i].y - dx  < 0 || a[i].y - dx >= coll) {
				return false;
			}
			else if (arr[a[i].x][a[i].y - dx] != 0) {
				return false;
			}
		}
		return true;
	}

	void Logic::tryToRotate(int** arr, int row, int coll) {
		Figure p = a[1]; // указываем центр вращения
		Figure tempA[4];
		if (typeOfTetramino == 6) return;
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y; // y - y0
			int y = a[i].x - p.x; // x - x0
			if (p.y + y >= coll || p.y - y < 0 || arr[p.x - x][p.y - y] != 0) return;
			b[i].x = p.x - x;
			b[i].y = p.y + y;
		}
		for (int i = 0; i < 4; i++) {
			a[i].x = b[i].x;
			a[i].y = b[i].y;
		}
	}

	void Logic::ScoreUp() {
		this->score += this->deltaScore;
	}
	
	unsigned int Logic::getScore() {
		return this->score;
	}

	void Logic::addFigureToGameField(int** arr, int row,int coll) {
		for (int i = 0; i < 4; i++) {
			arr[a[i].x][a[i].y] = typeOfTetramino + 1;
		}
	}



	void Logic::replace(int** arr, int row, int coll, int currentRow) {
		//Clean array
		for (int i = 0; i < coll; i++) {
			arr[currentRow][i] = 0;
		} 

		for (int i = currentRow; i > 1; i--) {
			for (int j = 0; j < coll; j++) {
				arr[i][j] = arr[i - 1][j];
			}
		}

	}

	void Logic::checkLine(int** arr, int row, int coll) {
		int temp = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < coll; j++) {
				if (arr[i][j] != 0) {
					temp++; 
				}
			}
			if (temp == coll) {
				ScoreUp();
				replace(arr, row,coll, i);
			}
			temp = 0;
		}
	}
}