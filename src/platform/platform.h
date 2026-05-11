#ifndef XUI_PLATFORM_H
#define XUI_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

// =====================================================
// Opaque handles (no OS leakage)
// =====================================================

typedef void* xui_window;
typedef void* xui_button;
typedef void* xui_textbox;
typedef void* xui_menu;
typedef void* xui_menu_item;

// =====================================================
// Event callbacks (platform → core)
// =====================================================

typedef void (*xui_btn_callback)(int id);
typedef void (*xui_key_callback)(int key, int down);
typedef void (*xui_mouse_callback)(int x, int y, int button, int down);

// =====================================================
// Lifecycle
// =====================================================

void xui_platform_init(const char* title, int width, int height);
void xui_platform_run();
void xui_platform_quit();

// =====================================================
// Callback registration
// =====================================================

void xui_platform_set_button_callback(xui_btn_callback cb);
void xui_platform_set_key_callback(xui_key_callback cb);
void xui_platform_set_mouse_callback(xui_mouse_callback cb);
// Called when OS receives character input
void xui_platform_set_text_input_callback(void (*cb)(int key));

// =====================================================
// UI creation (native widgets)
// =====================================================

xui_button xui_platform_create_button(
    int id,
    const char* label,
    int x, int y, int w, int h
);

xui_textbox xui_platform_create_textbox(
    int id,
    int x, int y, int w, int h
);

// =====================================================
// UI interaction
// =====================================================

void xui_platform_set_textbox_text(xui_textbox tb, const char* text);
void xui_platform_get_textbox_text(xui_textbox tb, char* buffer, int max);
void xui_platform_enable_text_input(int enabled);

// =====================================================
// Menu
// =====================================================

xui_menu xui_platform_create_menu(const char* name);
xui_menu xui_platform_create_submenu(xui_menu menu, const char* name);
xui_menu_item xui_platform_add_menu_item(xui_menu menu, const char* name, int id);

// =====================================================
// Window utilities
// =====================================================

void xui_platform_set_title(const char* title);

#ifdef __cplusplus
}
#endif

#endif
