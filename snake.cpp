#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const int WINDOW_W = 400;
const int WINDOW_H = 400;
const int GRID = 20;
const int MAX_APPLES = 6;

struct Point { int x, y; };

std::vector<Point> snake = { {10, 10} };
std::vector<Point> apples;

int dirX = 1, dirY = 0;
bool running = true;
bool keys[256] = { false };

int score = 0;
int highScore = 0;

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            running = false;
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            keys[wParam] = true;
            return 0;
        case WM_KEYUP:
            keys[wParam] = false;
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Spawn apple, pastikan tidak tabrakan dengan snake atau apple lain
void SpawnApples() {
    int maxX = WINDOW_W / GRID;
    int maxY = WINDOW_H / GRID;

    while ((int)apples.size() < MAX_APPLES) {
        Point a;
        a.x = rand() % maxX;
        a.y = rand() % maxY;

        bool conflict = false;
        for (auto &s : snake) if (s.x == a.x && s.y == a.y) { conflict = true; break; }
        for (auto &ap : apples) if (ap.x == a.x && ap.y == a.y) { conflict = true; break; }

        if (!conflict) apples.push_back(a);
    }
}

// Cek tabrakan dengan snake
bool CheckCollision(Point p) {
    for (auto &s : snake) if (s.x == p.x && s.y == p.y) return true;
    return false;
}

// Draw text
void DrawTextCentered(HDC hdc, int x, int y, const std::string &text, COLORREF color) {
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    RECT rect = { x-50, y-10, x+50, y+10 };
    DrawText(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    srand(time(0));

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "SnakeClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, "Snake C++ Wrap-Around",
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                               WINDOW_W, WINDOW_H, NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nCmdShow);
    HDC hdc = GetDC(hwnd);

    HBRUSH bgBrush = (HBRUSH)(COLOR_WINDOW+1);
    HBRUSH snakeBrush = CreateSolidBrush(RGB(0,200,0));
    HBRUSH appleBrush = CreateSolidBrush(RGB(255,0,0));

    SpawnApples();

    MSG msg = {};
    while (running) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Input
        if (keys[VK_LEFT]  && dirX != 1) { dirX=-1; dirY=0; }
        if (keys[VK_RIGHT] && dirX != -1){ dirX=1; dirY=0; }
        if (keys[VK_UP]    && dirY != 1) { dirX=0; dirY=-1;}
        if (keys[VK_DOWN]  && dirY != -1){ dirX=0; dirY=1;}

        // Move snake
        Point newHead = { snake[0].x + dirX, snake[0].y + dirY };

        // Wrap-around
        int maxX = WINDOW_W / GRID;
        int maxY = WINDOW_H / GRID;
        if (newHead.x < 0) newHead.x = maxX - 1;
        if (newHead.y < 0) newHead.y = maxY - 1;
        if (newHead.x >= maxX) newHead.x = 0;
        if (newHead.y >= maxY) newHead.y = 0;

        // Check self collision
        if (CheckCollision(newHead)) { running=false; break; }

        // Add new head
        snake.insert(snake.begin(), newHead);

        // Check apples
        bool ateApple = false;
        for (size_t i = 0; i < apples.size(); ++i) {
            if (newHead.x == apples[i].x && newHead.y == apples[i].y) {
                apples.erase(apples.begin() + i);
                score++;
                if (score > highScore) highScore = score;
                ateApple = true;
                break;
            }
        }

        if (!ateApple) snake.pop_back(); // remove tail only if not eating

        // Spawn new apples if less than MAX
        SpawnApples();

        // Render
        RECT bg = {0,0,WINDOW_W,WINDOW_H};
        FillRect(hdc, &bg, bgBrush);

        // Draw apples
        RECT rect;
        for (auto &a : apples) {
            rect.left = a.x*GRID;
            rect.top  = a.y*GRID;
            rect.right=rect.left + GRID;
            rect.bottom=rect.top + GRID;
            FillRect(hdc, &rect, appleBrush);
        }

        // Draw snake
        for (auto &s : snake) {
            rect.left = s.x*GRID;
            rect.top  = s.y*GRID;
            rect.right=rect.left+GRID;
            rect.bottom=rect.top+GRID;
            FillRect(hdc, &rect, snakeBrush);
        }

        // Draw score
        DrawTextCentered(hdc, WINDOW_W/2, 10, "Score: " + std::to_string(score), RGB(0,0,0));
        DrawTextCentered(hdc, WINDOW_W/2, 30, "High Score: " + std::to_string(highScore), RGB(0,0,0));

        Sleep(100);
    }

    // Cleanup
    DeleteObject(snakeBrush);
    DeleteObject(appleBrush);
    ReleaseDC(hwnd, hdc);

    return 0;
}
