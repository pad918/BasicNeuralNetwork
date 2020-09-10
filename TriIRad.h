#pragma once
#include <iostream>
#include <array>

namespace tre {
	
	class TreSpel {
	private:
		
	public:
		
		TreSpel(int input[3][3]);
		TreSpel();
		void Initialize(int input[3][3]);
		int evaluate();
		int rutor[3][3];
	};


	class TreIradIRad {
	private:
		TreSpel **smallGames;
		TreSpel **test;
		TreSpel bigGame;
	public:
		TreIradIRad();
		int evaluate();
		void drawPlayField();
		void doMove(int bX, int bY, int sX, int sY, int val);
	};

}