#include <string.h>
#include <stdio.h>

#include "xui/xui.h"
#include "internal/internal.h"
#include "platform/platform.h"

// =====================================================
// Global state
// =====================================================

xui_state g_xui = {0};

// =====================================================
// Init / run / quit
// =====================================================

void xui_init(const char* title, int w, int h)
{
    memset(&g_xui, 0, sizeof(g_xui));
    g_xui.focused_textbox_id = -1;

    g_xui.window_width  = w;
    g_xui.window_height = h;
    xui_platform_init(title, w, h);
}

void xui_run()
{
    xui_platform_run();
}

void xui_quit()
{
    xui_platform_quit();
}

// =====================================================
// Callback registration
// =====================================================

void xui_set_button_handler(xui_btn_callback cb)
{
    g_xui.btn_cb = cb;
}

void xui_set_menu_handler(xui_menu_callback cb)
{
    g_xui.menu_cb = cb;
}

void xui_set_key_handler(xui_key_callback cb)
{
    g_xui.key_cb = cb;

    // forward to platform
    xui_platform_set_text_input_callback(xui_internal_on_text_input);
}

void xui_set_mouse_handler(xui_mouse_callback cb)
{
    g_xui.mouse_cb = cb;
}

// =====================================================
// BUTTON API
// =====================================================

void xui_button_create(int id, const char* label, int x, int y, int w, int h)
{
    if (g_xui.button_count >= XUI_MAX_BUTTONS)
        return;

    xui_button_internal* b = &g_xui.buttons[g_xui.button_count++];

    b->id = id;
    b->x = x;
    b->y = y;
    b->w = w;
    b->h = h;

    xui_strncpy(b->label, label, sizeof(b->label) - 1);

    b->handle = xui_platform_create_button(id, label, x, y, w, h);
}

// =====================================================
// TEXTBOX API
// =====================================================

void xui_textbox_create(int id, int x, int y, int w, int h)
{
    if (g_xui.textbox_count >= XUI_MAX_TEXTBOXES)
        return;

    xui_textbox_internal* t = &g_xui.textboxes[g_xui.textbox_count++];

    t->id = id;
    t->x = x;
    t->y = y;
    t->w = w;
    t->h = h;

    t->text[0] = '\0';

    t->handle = xui_platform_create_textbox(id, x, y, w, h);
}

void xui_textbox_set_text(int id, const char* text)
{
    for (int i = 0; i < g_xui.textbox_count; i++)
    {
        if (g_xui.textboxes[i].id == id)
        {
            xui_strncpy(g_xui.textboxes[i].text, text,
                    sizeof(g_xui.textboxes[i].text) - 1);

            xui_platform_set_textbox_text(
                g_xui.textboxes[i].handle,
                text
            );

            return;
        }
    }
}

// =====================================================
// MENU API
// =====================================================

xui_menu xui_menu_create(const char* name)
{
    return xui_platform_create_menu(name);
}

xui_menu xui_menu_create_submenu(xui_menu menu, const char* name)
{
    return xui_platform_create_submenu(menu, name);
}

xui_menu_item xui_menu_add_item(xui_menu menu, const char* name, int id)
{
    return xui_platform_add_menu_item(menu, name, id);
}       

// =====================================================
// INTERNAL EVENT BRIDGES
// =====================================================

void xui_internal_on_button_clicked(int id)
{
    if (g_xui.btn_cb)
        g_xui.btn_cb(id);
}

void xui_internal_on_menu_item(int id)
{
    if (g_xui.menu_cb)
        g_xui.menu_cb(id);
}

// =====================================================
// TEXT INPUT ROUTING
// =====================================================

void xui_internal_on_text_input(int key)
{
    if (g_xui.focused_textbox_id < 0)
        return;

    for (int i = 0; i < g_xui.textbox_count; i++)
    {
        if (g_xui.textboxes[i].id == g_xui.focused_textbox_id)
        {
            size_t len = strlen(g_xui.textboxes[i].text);

            if (key == 8) // backspace
            {
                if (len > 0)
                    g_xui.textboxes[i].text[len - 1] = '\0';
            }
            else if (len < sizeof(g_xui.textboxes[i].text) - 1)
            {
                g_xui.textboxes[i].text[len] = (char)key;
                g_xui.textboxes[i].text[len + 1] = '\0';
            }

            xui_platform_set_textbox_text(
                g_xui.textboxes[i].handle,
                g_xui.textboxes[i].text
            );

            return;
        }
    }
}

// =====================================================
// MOUSE (future expansion hook)
// =====================================================

void xui_internal_on_mouse(int x, int y, int button, int down)
{
    (void)x;
    (void)y;
    (void)button;
    (void)down;

    if (g_xui.mouse_cb)
        g_xui.mouse_cb(x, y, button, down);
}
