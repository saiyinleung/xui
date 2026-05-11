#include <stdio.h>
#include <string.h>

#include <xui/xui.h>
#include <xui/button.h>
#include <xui/textbox.h>
#include <xui/menu.h>

// =====================================================
// IDs (simple manual enum style)
// =====================================================

enum {
    BTN_HELLO = 1,
    BTN_CLEAR = 2,

    TXT_INPUT = 100,

    MENU_QUIT = 200
};

// =====================================================
// Callbacks
// =====================================================

void on_button(int id)
{
    if (id == BTN_HELLO)
    {
        printf("Hello button clicked!\n");

        xui_textbox_set_text(TXT_INPUT, "Hello from xui!");
    }

    if (id == BTN_CLEAR)
    {
        printf("Clear button clicked!\n");

        xui_textbox_set_text(TXT_INPUT, "");
    }
}

void on_menu(int id)
{
    if (id == MENU_QUIT)
    {
        printf("Quit menu clicked!\n");
        xui_quit();
    }
}

void on_key(int key, int down)
{
    (void)down;
    printf("Key: %d\n", key);
}

void on_mouse(int x, int y, int button, int down)
{
    (void)x;
    (void)y;
    (void)button;
    (void)down;
}

// =====================================================
// Main
// =====================================================

int main()
{
    // 1. Init window system
    xui_init("xui demo", 800, 600);

    // 2. Register callbacks
    xui_set_button_handler(on_button);
    xui_set_menu_handler(on_menu);
    xui_set_key_handler(on_key);
    xui_set_mouse_handler(on_mouse);

    // 3. Menu
    xui_menu m = xui_menu_create_ex("BBB");
    //xui_menu_create();
    xui_menu_add_item_ex(m, "Quit", MENU_QUIT);
    xui_menu_add_item_ex(m, "Bye", MENU_QUIT);

    // 4. UI elements
    xui_button_create(BTN_HELLO, "Say Hello", 50, 50, 120, 40);
    xui_button_create(BTN_CLEAR, "Clear", 200, 50, 120, 40);

    xui_textbox_create(TXT_INPUT, 50, 120, 300, 30);

    // 5. Run
    xui_run();

    return 0;
}
