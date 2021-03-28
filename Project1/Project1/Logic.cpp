#include "Logic.h"
#include <iostream>
#include <random>
#include <ctime>

namespace TetrisGame {
	void Logic::moveFigure(int dx, int** arr, int row, int coll)
	{
		if (checkCollizionLR(arr, row, coll, dx)) {
			clearFigure(arr, row, coll);
			for (int i = 0; i < 4; i++)
			{
				a[i].y -= dx;
			}
			drawFigure(arr, row, coll);
		}
	}

	void Logic::spawnFigure() {
		srand(time(0));
		n = rand()%7;
		for (int i = 0; i < 4; i++) {
			a[i].x = figures[n][i] / 2;
			a[i].y = figures[n][i] % 2;
		}
	}

	void Logic::drawFigure(int** arr, int row, int coll) {
		for (int i = 0; i < 4; i++) {
			int x = a[i].x;
			int y = a[i].y;
			arr[x][y] = n+1;
		}
	}

	bool Logic::checkCollizionDown(int** arr, int row, int coll) {
		Figure b[4];

		for (int i = 0; i < 4; i++)b[i].x = a[i].x+1;

		int** startArr = arr;
		for (int i = 0; i < 4; i++) {
			if (a[i].x >= row - 1) {
				checkLine(arr, row, coll);
				spawnFigure();
				return false;
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < coll; j++) {
				if (!arr[i][j]) {
					continue;
				}
				for (int z = 0; z < 4; z++) {
					if (i == a[z].x && j == a[z].y) {
						if (arr[i + 1][j] != 0) {
							if (a[0].x == i + 1)continue;
							if (a[1].x == i + 1)continue;
							if (a[2].x == i + 1)continue;
							if (a[3].x == i + 1)continue;
							checkLine(startArr, row, coll);
							spawnFigure();
							return false;
						}
					}
				}
			}
		}

		

		return true;
		
	}

	bool Logic::checkCollizionLR(int **arr, int row,int coll,int dx) {
		for (int i = 0; i < 4; i++) {
			if (a[i].y-dx < 0 || a[i].y-dx >= coll ) { return false; }
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < coll; j++) {
				for (int z = 0; z < 4; z++) {
					if (i == a[z].x && j == a[z].y) {
						if (dx < 0) {
							if (arr[i][j+1] != 0) {
								if (a[0].y == j - dx)continue;
								if (a[1].y == j - dx)continue;
								if (a[2].y == j - dx)continue;
								if (a[3].y == j - dx)continue;
								return false;
							}
						}
						else {
							if (arr[i][j - 1] != 0) {
								if (a[0].y == j - dx)continue;
								if (a[1].y == j - dx)continue;
								if (a[2].y == j - dx)continue;
								if (a[3].y == j - dx)continue;
								return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	/*Figure* Logic::getFigure() {
		return a;
	}*/

	void Logic::copyFigure() {

		for (int i = 0; i < 4; i++)
		{
			a[i].y -= 1;
		}

		for (int i = 0; i < 4; i++)
		{
			a[i].y -= 1;
		}
	}

	void Logic::downFigure(int** arr, int row, int coll)
	{
		
		if (checkCollizionDown(arr, row, coll)) {
			clearFigure(arr, row, coll);
			for (int i = 0; i < 4; i++)
			{
				a[i].x += 1;
			}
			drawFigure(arr, row, coll);
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
				replace(arr, row,coll, i);
			}
			temp = 0;
		}
	}

	void Logic::clearFigure(int** arr, int row, int coll) {
		for (int i = 0; i < row; i++) {
				for (int j = 0; j < coll; j++) {
					for (int z = 0; z < 4; z++) {
						if (i == a[z].x && j == a[z].y) {
							arr[i][j] = 0;
						}
					}
			}

		}
	}
}