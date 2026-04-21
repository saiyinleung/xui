#ifndef XUI_H
#define XUI_H
#include "xui/textbox.h"
#include "xui/button.h"
#include "xui/menu.h"
#ifdef __cplusplus
extern "C" {
#endif

// =====================================================
// Core lifecycle
// =====================================================

void xui_init(const char* title, int width, int height);
void xui_run();
void xui_quit();

// =====================================================
// UI creation
// =====================================================

void xui_button_create(int id, const char* label,
                       int x, int y, int w, int h);

void xui_textbox_create(int id,
                        int x, int y, int w, int h);

// =====================================================
// Textbox API
// =====================================================

void xui_textbox_set_text(int id, const char* text);
void xui_textbox_get_text(int id, char* out, int max);

// =====================================================
// Event callbacks (user side)
// =====================================================

typedef void (*xui_btn_callback)(int id);
typedef void (*xui_key_callback)(int key, int down);
typedef void (*xui_mouse_callback)(int x, int y, int button, int down);
typedef void (*xui_menu_callback)(int id);

void xui_set_button_handler(xui_btn_callback cb);
void xui_set_key_handler(xui_key_callback cb);
void xui_set_mouse_handler(xui_mouse_callback cb);
void xui_set_menu_handler(xui_menu_callback cb);

#ifdef __cplusplus
}
#endif

#endif
