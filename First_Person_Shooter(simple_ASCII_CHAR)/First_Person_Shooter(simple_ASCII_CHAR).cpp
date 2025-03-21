#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <Windows.h>
using namespace std;


int nScreenWidth = 120;
int nScreenHeight = 40;
float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fplayerA = 0.0f;
int nMapHeight=16, nMapWidth=16;
float pi = 3.14159;
float fFOV = pi / 4.0f;
float fDepth = 16;
bool check_boundary(int C_X, int C_Y) {
	return C_X >= 0 && C_Y >= 0 && C_X < nScreenWidth && C_Y < nScreenHeight;
}
int main(){
	wchar_t* screen = new wchar_t[nScreenHeight * nScreenWidth];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwByteswritten = 0;


	wstring map;
	map += L"################";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#...##.........#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#.......#####..#";
	map += L"#.......#####..#";
	map += L"#.......#####..#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#....#.........#";
	map += L"#..............#";
	map += L"################";

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while (1) {

		tp2 = chrono::system_clock::now();
		chrono::duration<float>elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float  fElapsedTime = elapsedTime.count();

		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			fplayerA -= (0.8f* fElapsedTime);
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			fplayerA += (0.8f* fElapsedTime);
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			fPlayerX += sinf(fplayerA) * 5.0f * fElapsedTime;;
			fPlayerY += cosf(fplayerA) * 5.0f * fElapsedTime;;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#'){
				fPlayerX -= sinf(fplayerA) * 5.0f * fElapsedTime;;
				fPlayerY -= cosf(fplayerA) * 5.0f * fElapsedTime;;
			}
		}

		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			fPlayerX -= sinf(fplayerA) * 5.0f * fElapsedTime;;
			fPlayerY -= cosf(fplayerA) * 5.0f * fElapsedTime;;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#'){
				fPlayerX += sinf(fplayerA) * 5.0f * fElapsedTime;;
				fPlayerY += cosf(fplayerA) * 5.0f * fElapsedTime;;
			}
		}
		
		for (int x = 0;x < nScreenWidth;x++) {
			float fRayAngle = (fplayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
			float fDistancetoWall = 0;
			bool bHitWall = false;
			bool bBoundary = false;

			float fEyesX = sinf(fRayAngle);
			float fEyesY = cosf(fRayAngle);
			while (!bHitWall && fDistancetoWall < fDepth) {
				fDistancetoWall += 0.1f;
				int nTestX = fPlayerX + fDistancetoWall * fEyesX;
				int nTestY = fPlayerY + fDistancetoWall * fEyesY;

				if (!check_boundary(nTestX, nTestY)) {
					bHitWall = true;
					fDistancetoWall = fDepth;
					continue;
				}
				
				float fBound = 0.01;
				vector<pair<float, float>> p;
				if (map[nTestY * nMapWidth + nTestX] == '#') {
					bHitWall = true;
					for (int tx = 0; tx < 2; tx++)
						for (int ty = 0; ty < 2; ty++)
						{
							float vy = (float)nTestY + ty - fPlayerY;
							float vx = (float)nTestX + tx - fPlayerX;
							float d = sqrt(vx * vx + vy * vy);
							float dot = (fEyesX * vx / d) + (fEyesY * vy / d);
							p.push_back(make_pair(d, dot));
						}
						sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; });

						float fBound = 0.01;
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;
						if (acos(p.at(2).second) < fBound) bBoundary = true;
				}
			}

			int nCelling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistancetoWall);
			int nFloor = nScreenHeight - nCelling;

			int nShade = ' ';
			if (fDistancetoWall <= fDepth / 4.0f)			nShade = 0x2588;
			else if (fDistancetoWall < fDepth / 3.0f)		nShade = 0x2593;
			else if (fDistancetoWall < fDepth / 2.0f)		nShade = 0x2592;
			else if (fDistancetoWall < fDepth)				nShade = 0x2591;
			else                                            nShade = ' ';

			if (bBoundary)		nShade = ' ';

			for (int y = 0;y < nScreenHeight;y++) {
				if (y < nCelling) {
					screen[y * nScreenWidth + x] = ' ' ;
				}
				else if (y > nCelling && y <= nFloor) {
					screen[y * nScreenWidth + x] = nShade;
				}
				else {
					int nShade1;
					float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
					if (b < 0.25)		nShade1 = '#';
					else if (b < 0.5)	nShade1 = 'x';
					else if (b < 0.75)	nShade1 = '.';
					else if (b < 0.9)	nShade1 = '-';
					else				nShade1 = ' ';
					screen[y * nScreenWidth + x] = nShade1;
				}
			}
			swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fplayerA, 1.0f / fElapsedTime);
			for (int nx = 0; nx < nMapWidth; nx++) {
				for (int ny = 0; ny < nMapWidth; ny++)
				{
					screen[(ny + 1) * nScreenWidth + nx] = map[ny * nMapWidth + nx];
				}
			}
			screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';


		}
		screen[nScreenHeight * nScreenWidth - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwByteswritten);
	}




	return 0;
}
