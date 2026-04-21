#ifdef _WIN32

#include <windows.h>
#include <stdlib.h>

#include "platform.h"
#include "../internal/internal.h"

// =====================================================
// Globals
// =====================================================

static HWND g_hwnd = NULL;

// Text input callback (for textbox typing)
static void (*g_text_cb)(int key) = NULL;

// =====================================================
// Text input callback registration
// =====================================================

void xui_platform_set_text_input_callback(void (*cb)(int))
{
    g_text_cb = cb;
}

// =====================================================
// Enable / disable text input (no-op for Win32)
// =====================================================

void xui_platform_enable_text_input(int enabled)
{
    (void)enabled;
}

// =====================================================
// Window procedure
// =====================================================

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
        {
            int id = LOWORD(wParam);

            // Button click OR menu click (same ID system)
            xui_internal_on_button_clicked(id);
            xui_internal_on_menu_item(id);

            return 0;
        }

        case WM_CHAR:
        {
            if (g_text_cb)
                g_text_cb((int)wParam);

            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// =====================================================
// Init
// =====================================================

void xui_platform_init(const char* title, int width, int height)
{
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "xui_window_class";

    RegisterClass(&wc);

    g_hwnd = CreateWindow(
        "xui_window_class",
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, width, height,
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );
}

// =====================================================
// Run loop
// =====================================================

void xui_platform_run()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// =====================================================
// Quit
// =====================================================

void xui_platform_quit()
{
    PostQuitMessage(0);
}

// =====================================================
// BUTTON
// =====================================================

xui_button xui_platform_create_button(
    int id,
    const char* label,
    int x, int y, int w, int h)
{
    HWND btn = CreateWindow(
        "BUTTON",
        label,
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        x, y, w, h,
        g_hwnd,
        (HMENU)(intptr_t)id,
        GetModuleHandle(NULL),
        NULL
    );

    return (xui_button)btn;
}

// =====================================================
// TEXTBOX
// =====================================================

xui_textbox xui_platform_create_textbox(
    int id,
    int x, int y, int w, int h)
{
    HWND edit = CreateWindow(
        "EDIT",
        "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        x, y, w, h,
        g_hwnd,
        (HMENU)(intptr_t)id,
        GetModuleHandle(NULL),
        NULL
    );

    return (xui_textbox)edit;
}

void xui_platform_set_textbox_text(xui_textbox tb, const char* text)
{
    HWND h = (HWND)tb;
    SetWindowTextA(h, text);
}

// =====================================================
// MENU
// =====================================================

static HMENU g_menu = NULL;

void xui_platform_create_menu()
{
    g_menu = CreateMenu();
    SetMenu(g_hwnd, g_menu);
}

void xui_platform_add_menu_item(const char* name, int id)
{
    AppendMenuA(g_menu, MF_STRING, id, name);
    DrawMenuBar(g_hwnd);
}

#endif
