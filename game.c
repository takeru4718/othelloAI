#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CIRCLE_RADIUS 30

int score = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_LBUTTONDOWN:
            // マウスの左ボタンがクリックされたとき
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            // 円の中心座標を取得
            int circleX = rand() % (SCREEN_WIDTH - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;
            int circleY = rand() % (SCREEN_HEIGHT - 2 * CIRCLE_RADIUS) + CIRCLE_RADIUS;

            // クリックされた位置が円の中心に近い場合、得点を加算して新しい円を表示
            if (sqrt(pow(mouseX - circleX, 2) + pow(mouseY - circleY, 2)) < CIRCLE_RADIUS) {
                score++;
                SetWindowTextA(hwnd, "Score: " + score);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        case WM_PAINT:
            {
                // 円を描画
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                Ellipse(hdc, circleX - CIRCLE_RADIUS, circleY - CIRCLE_RADIUS, circleX + CIRCLE_RADIUS, circleY + CIRCLE_RADIUS);
                EndPaint(hwnd, &ps);
            }
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    srand((unsigned)time(NULL));

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = L"SimpleGameWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        L"SimpleGameWindowClass",
        L"Simple Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL,
        GetModuleHandle(NULL),
        NULL
    );

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
