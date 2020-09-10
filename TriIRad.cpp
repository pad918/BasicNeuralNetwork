#include "TriIRad.h"

tre::TreIradIRad::TreIradIRad()
{
	smallGames = new TreSpel*[3];
	for (int i = 0; i < 3; i++) {
		smallGames[i] = new TreSpel[3];
	}
	int a[3][3];
	memset(a, 0, sizeof(a));
	bigGame = TreSpel(a);
	for (int x = 0; x < 3; x++) 
		for(int y = 0; y < 3; y++)
			smallGames[x][y] = TreSpel(a);
	
}

int tre::TreIradIRad::evaluate()
{
	for(int x=0; x<3; x++)
		for(int y = 0; y<3; y++)
			bigGame.rutor[x][y] = smallGames[x][y].evaluate();
	return bigGame.evaluate();
}

void tre::TreIradIRad::drawPlayField()
{
	std::cout << "Playfield;\n\n";
	for (int row = 0; row < 9; row++) {
		int yId = row / 3;
		int rowInGame = row % 3;
		if (rowInGame == 0 && row != 0) { std::cout << "\n"; }
		for (int col = 0; col < 9; col++) {
			int xId = col / 3;
			int colInGame = col % 3;
			if (colInGame == 0 && col != 0) { std::cout << " "; } //test
			std::cout << smallGames[xId][yId].rutor[colInGame][rowInGame] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\nBig game evaluation: \n\n";
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++)
			std::cout << bigGame.rutor[x][y] << " ";
		std::cout << "\n";
	}
}

void tre::TreIradIRad::doMove(int bX, int bY, int sX, int sY, int val)
{

	smallGames[bX][bY].rutor[sX][sY] = val;;

}

tre::TreSpel::TreSpel(int input[3][3])
{
	for(int x=0; x<3; x++)
		for(int y=0; y<3;y++)
			rutor[x][y] = input[x][y];
}

tre::TreSpel::TreSpel()
{

}

void tre::TreSpel::Initialize(int input[3][3])
{
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			rutor[x][y] = input[x][y];
}

int tre::TreSpel::evaluate()
{
	int winner = 0; // 0 = ingen; 1 = splare1; 2 = splare2
	for (int i = 0; i < 3 && winner==0; i++) {
		if (rutor[0][i] == rutor[1][i] && rutor[0][i] == rutor[2][i]) {
			winner = rutor[0][i];
		}
	}

	for (int i = 0; i < 3 && winner==0; i++) {
		if (rutor[i][0] == rutor[i][1] && rutor[i][0] == rutor[i][2]) {
			winner = rutor[i][0];
		}
	}

	if (winner == 0) {
		if (rutor[0][0] == rutor[1][1] && rutor[0][0] == rutor[2][2]) { winner = rutor[0][0]; }
		if(rutor[2][0] == rutor[1][1] && rutor[2][0] == rutor[0][2])  { winner = rutor[2][0]; }
	}
	if (winner == 0) {
		int notZero = 0;
		for(int x=0; x<3; x++)
			for(int y=0; y<3;y++)
				if (rutor[x][y] != 0) { notZero++; }
		if (notZero == 9) { return -1; }
	}
	return winner;
}


