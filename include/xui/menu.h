#ifndef XUI_MENU_H
#define XUI_MENU_H

#ifdef __cplusplus
extern "C" {
#endif

// =====================================================
// Menu API
// =====================================================
typedef void* xui_menu;
typedef void* xui_menu_item;

xui_menu xui_menu_create(const char* name);
xui_menu xui_menu_create_submenu(xui_menu menu, const char* name);
xui_menu_item xui_menu_add_item(xui_menu menu, const char* name, int id);


// Optional: future grouping support
// void xui_menu_add_submenu(const char* name);

#ifdef __cplusplus
}
#endif

#endif
