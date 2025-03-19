﻿#include <iostream>
#include <ctime>
#include <iomanip>
const unsigned int MAPA_SZER = 40;
const unsigned int MAPA_WYS = 20;
const unsigned int SEGMENT_SIZE = 5;
using namespace std;
struct vertex {
	int value;
	vertex* next;
};

void wpiszDoMapy(int n, int m, int (*tablicaSegmentow[6])[SEGMENT_SIZE], int mapa[MAPA_WYS][MAPA_SZER]) {
	int losowa = rand() % 6;


	for (int i = 0; i < SEGMENT_SIZE; i++) {
		for (int j = 0; j < SEGMENT_SIZE; j++) {
			mapa[i + n][j + m] = tablicaSegmentow[losowa][i][j];
		}
	}

}
void printMapa(int mapa[MAPA_WYS][MAPA_SZER]) {
	for (int i = 0; i < MAPA_WYS; i++) {
		for (int j = 0; j < MAPA_SZER; j++) {
			cout << setw(3) << mapa[i][j];
		}
		cout << endl;
	}
}
void wypiszListeSasiadow(int dziesiatki, int jednosci, vertex* p, vertex** vertexArray) {
	p = vertexArray[dziesiatki * 10 + jednosci];
	cout << dziesiatki * 10 + jednosci;
	cout << " --> ";
	if (vertexArray[dziesiatki*10+jednosci] == nullptr) {
		cout << "Brak sasiadow" << endl;
	}
	else {

		while (p->next != nullptr) {
			cout << p->value << " ";
			p = p->next;
		}
	}
}
int main()
{
	srand(time(0));
	int mapa[MAPA_WYS][MAPA_SZER] = {};
	int segmentA[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,0,0},
		{0,1,1,0,0},
		{1,1,0,1,1},
		{0,1,1,1,0},
		{0,0,1,0,0}
	};
	int segmentB[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,1,0},
		{1,0,0,1,0},
		{1,1,1,1,1},
		{0,1,1,1,0},
		{0,0,1,1,0}
	};
	int segmentC[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{1,1,1,1,1},
		{1,1,0,1,1},
		{1,1,0,0,1},
		{0,1,0,0,0},
		{0,1,1,1,1}
	};
	int segmentD[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,1,1},
		{0,1,1,0,1},
		{1,1,0,1,1},
		{1,0,1,1,0},
		{0,1,1,0,0}
	};
	int segmentE[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{1,1,1,0,0},
		{0,1,1,1,0},
		{1,1,0,1,1},
		{1,1,0,1,1},
		{1,1,1,1,0}
	};
	int segmentF[SEGMENT_SIZE][SEGMENT_SIZE] = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,1,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0}
	};
	int (*tabSegmentow[6])[SEGMENT_SIZE] = { segmentA, segmentB,segmentC, segmentD,segmentE,segmentF };
	for (int j = 0; j < 20 - 1; j += 5) {
		for (int i = 0; i < 40 - 1; i += 5) {
			wpiszDoMapy(j, i, tabSegmentow, mapa);
		}
	}
	int liczbaWierzcholkow = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++)
			if (mapa[i][j] == 1) liczbaWierzcholkow++;
	}

	vertex* p;
	vertex** vertexArray = new vertex * [liczbaWierzcholkow];
	bool* visited = new bool[liczbaWierzcholkow];

	p = new vertex;

	for (int i = 0; i < MAPA_WYS; i++) {
		for (int j = 0; j < MAPA_SZER; j++) {

			if (mapa[i][j] == 0) {
				vertexArray[i * 10 + j] = nullptr;
				continue;
			}
			p = new vertex;
			vertexArray[i * 10 + j] = p;
			p->next = nullptr;
			if (j > 0) { //sprawdz lewo 
				if (mapa[i][j - 1] == 1) {
					p->value = i * 10 + j - 1;
					p->next = new vertex;
					p = p->next;
				}
			}
			if (i < MAPA_WYS - 1) { //sprawdz dol 
				if (mapa[i + 1][j] == 1) {

					p->value = (i + 1) * 10 + j;
					p->next = new vertex;
					p = p->next;
				}

			}
			if (j < MAPA_SZER - 1) {//sprawdz prawo 
				if (mapa[i][j + 1] == 1) {

					p->value = i * 10 + j + 1;
					p->next = new vertex;
					p = p->next;
				}
			}
			if (i > 0) { //sprawdz gore 
				if (mapa[i - 1][j] == 1) {

					p->value = (i - 1) * 10 + j;
					p->next = new vertex;
					p = p->next;
				}
			}
			p->next = nullptr;
		}
	}
	printMapa(mapa);
	int dziesiatki, jednosci;
	std::cin >> dziesiatki >> jednosci;
	wypiszListeSasiadow(dziesiatki, jednosci, p, vertexArray);
}

