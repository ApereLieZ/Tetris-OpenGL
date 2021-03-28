#ifndef Logic_h
#define Logic_h

namespace TetrisGame {

	struct Figure
	{
		int x;
		int y;
	};

	class Logic
	{
		int figures[7][4] =
		{
			1,3,5,7, // I
			2,4,5,7, // Z
			3,5,4,6, // S
			3,5,4,7, // T
			2,3,5,7, // L
			3,5,7,6, // J
			2,3,4,5, // O
		};
	
		int n;
	public:
		Figure a[4]{};
		Figure b[4]{};
		Logic() {
			spawnFigure();
		}
		
		//Figure* getFigure();
		void moveFigure(int dx, int** arr, int row, int coll);
		void downFigure(int** arr, int row, int coll);
		void clearFigure(int** arr, int row, int coll);
		void checkLine(int** arr, int row, int coll);
		void spawnFigure();
	private:
		void replace(int** arr, int row, int coll, int currentRow);
		void drawFigure(int** arr, int row, int coll);
		void copyFigure();
		bool checkCollizionDown(int** arr, int row, int coll);
		bool checkCollizionLR(int** arr, int row, int coll,int dx);


	};
}

#endif 
