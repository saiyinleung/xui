#ifndef XUI_BUTTON_H
#define XUI_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

// =====================================================
// Button API
// =====================================================

void xui_button_create(int id, const char* label,
                       int x, int y, int w, int h);

// =====================================================
// Optional future extensions (safe to keep minimal now)
// =====================================================

// You can later add:
// void xui_button_set_text(int id, const char* label);
// void xui_button_enable(int id, int enabled);

#ifdef __cplusplus
}
#endif

#endif
