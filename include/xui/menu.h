#ifndef XUI_MENU_H
#define XUI_MENU_H

#ifdef __cplusplus
extern "C" {
#endif

// =====================================================
// Menu API
// =====================================================

void xui_menu_create(void);

// Add a menu item
void xui_menu_add_item(const char* name, int id);

// Optional: future grouping support
// void xui_menu_add_submenu(const char* name);

#ifdef __cplusplus
}
#endif

#endif
