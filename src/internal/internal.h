#ifndef XUI_INTERNAL_H
#define XUI_INTERNAL_H

#include <stddef.h>
#include "xui/xui.h"

// =====================================================
// Forward declarations (platform handles are opaque)
// =====================================================

typedef void* xui_button;
typedef void* xui_textbox;
typedef void* xui_menu;
typedef void* xui_menu_item;

// =====================================================
// Limits
// =====================================================

#define XUI_MAX_BUTTONS   128
#define XUI_MAX_TEXTBOXES 128
#define XUI_MAX_MENUS     128
#define XUI_MAX_MENU_ITEMS 128

// =====================================================
// Internal UI state structs
// =====================================================

typedef struct {
    int id;
    char label[64];
    int x, y, w, h;
    xui_button handle;
} xui_button_internal;

typedef struct {
    int id;
    int x, y, w, h;
    char text[256];
    xui_textbox handle;
} xui_textbox_internal;

typedef struct {
    int id;
    char label[64];
    xui_menu_item handle;
} xui_menu_item_internal;

typedef struct {
    int id;
    char label[64];
    xui_menu handle;
    xui_menu_item_internal items[XUI_MAX_MENU_ITEMS];
    int item_count;
} xui_menu_internal;


int xui_internal_to_native_ui_y(int y, int h);
int xui_internal_to_native_gfx_y(int y, int h);
void xui_strncpy(char* dst, const char* src, size_t n);

// =====================================================
// Callback types (public-facing, stored internally)
// =====================================================

typedef void (*xui_btn_callback)(int id);
typedef void (*xui_menu_callback)(int id);
typedef void (*xui_key_callback)(int key, int down);
typedef void (*xui_mouse_callback)(int x, int y, int button, int down);

// =====================================================
// Global state (defined in core.c)
// =====================================================

typedef struct {
    // widgets
    xui_button_internal buttons[XUI_MAX_BUTTONS];
    int button_count;

    xui_textbox_internal textboxes[XUI_MAX_TEXTBOXES];
    int textbox_count;

    // UI state
    int focused_textbox_id;

    // callbacks
    xui_btn_callback btn_cb;
    xui_menu_callback menu_cb;
    xui_key_callback key_cb;
    xui_mouse_callback mouse_cb;

    int window_width;
    int window_height;    

} xui_state;

extern xui_state g_xui;

// =====================================================
// Internal event bridges (platform → core)
// =====================================================

void xui_internal_on_button_clicked(int id);
void xui_internal_on_menu_item(int id);
void xui_internal_on_text_input(int key);
void xui_internal_on_mouse(int x, int y, int button, int down);

#endif
