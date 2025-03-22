#include <iostream>
#include <ctime>
#include <iomanip>
const unsigned int MAPA_SZER = 40;
const unsigned int MAPA_WYS = 20;
const unsigned int SEGMENT_SIZE = 5;
using namespace std;
struct vertexStruct {
	int value;
	vertexStruct* next;
};
struct queueStruct {
	vertexStruct* front=nullptr; 
	vertexStruct* rear=nullptr; 
};
bool isEmpty(queueStruct queue){
	if (queue.front == nullptr && queue.rear == nullptr) return true;
	else return false;
	
}
void enqueue(queueStruct queue, vertexStruct* vertex) {
		vertexStruct* temp;
	if (isEmpty(queue)) {
		temp->value = vertex->value; 
		temp->next = nullptr;
		queue.front = queue.rear = temp;
	}
	else {
		temp->value = vertex->value;
		temp->next= nullptr;
		queue.rear->next = temp; 
		queue.rear = temp;
		
	}
	delete temp; 
}
void dequeue(queueStruct queue) {
	vertexStruct* temp; 
	temp = queue.front; 
	queue.front = queue.front->next; 
	delete temp; 
}
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
void wypiszListeSasiadow(int x, int y, vertexStruct* p, vertexStruct** vertexArray) {
	p = vertexArray[y * MAPA_SZER + x];
	cout << "["<<x<<","<<y<<"]";
	cout << " --> ";
	if (vertexArray[y*MAPA_SZER+x] == nullptr) {
		cout << "Wierzcholek nie istnieje" << endl;
	}
	else if(p->next==nullptr){
		cout << "Brak sasiadow" << endl;

	}
	else {

		while (p->next != nullptr) {
			//cout << "[" << p->value % MAPA_SZER << "," << (p->value - ((p->value) % MAPA_SZER))/MAPA_WYS<< "] ";
			cout << "[" << p->value % MAPA_SZER << ";" << (p->value - (p->value % MAPA_SZER))/MAPA_SZER << "] "; 
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
	for (int j = 0; j < MAPA_WYS - 1; j += 5) {
		for (int i = 0; i < MAPA_SZER - 1; i += 5) {
			wpiszDoMapy(j, i, tabSegmentow, mapa);
		}
	}
	int liczbaWierzcholkow = 0;
	for (int i = 0; i < MAPA_WYS; i++) {
		for (int j = 0; j < MAPA_SZER; j++)
			if (mapa[i][j] == 1) liczbaWierzcholkow++;
	}
	printMapa(mapa);

	vertexStruct* p;
	vertexStruct** vertexArray = new vertexStruct * [liczbaWierzcholkow];
	bool* visited = new bool[liczbaWierzcholkow];
	vertexStruct** queue = new vertexStruct * [liczbaWierzcholkow]; 

	p = new vertexStruct;

	for (int i = 0; i < MAPA_WYS; i++) {
		for (int j = 0; j < MAPA_SZER; j++) {

			if (mapa[i][j] == 0) {
				vertexArray[i * MAPA_SZER + j] = nullptr;
				continue;
			}
			p = new vertexStruct;
			vertexArray[i * MAPA_SZER + j] = p;
			p->next = nullptr;
			if (j > 0) { //sprawdz lewo 
				if (mapa[i][j - 1] == 1) {
					p->value = i * MAPA_SZER + j - 1;
					p->next = new vertexStruct;
					p = p->next;
				}
			}
			if (i < MAPA_WYS - 1) { //sprawdz dol 
				if (mapa[i + 1][j] == 1) {

					p->value = (i + 1) * MAPA_SZER + j;
					p->next = new vertexStruct;
					p = p->next;
				}

			}
			if (j < MAPA_SZER - 1) {//sprawdz prawo 
				if (mapa[i][j + 1] == 1) {

					p->value = i * MAPA_SZER + j + 1;
					p->next = new vertexStruct;
					p = p->next;
				}
			}
			if (i > 0) { //sprawdz gore 
				if (mapa[i - 1][j] == 1) {

					p->value = (i - 1) * MAPA_SZER + j;
					p->next = new vertexStruct;
					p = p->next;
				}
			}
			p->next = nullptr;
		}
	}
	int xStart, yStart, xEnd, yEnd;

	do {
		xStart = rand() % MAPA_SZER;
		yEnd = rand() % MAPA_WYS;
		yStart = rand() % MAPA_WYS;
		xEnd = rand() % MAPA_SZER;
	} while (mapa[yStart][xStart] == 1 && mapa[yEnd][xEnd] == 1);
	/*while (true) {
		int x, y;
	std::cin >> x>>y;
	wypiszListeSasiadow(x, y, p, vertexArray);
	char stop = 'c';
	cin >> stop;
	if (stop == 'b') break;

	}*/
}

