#ifndef XUI_TEXTBOX_H
#define XUI_TEXTBOX_H

#ifdef __cplusplus
extern "C" {
#endif

// =====================================================
// Textbox API
// =====================================================

void xui_textbox_create(int id,
                        int x, int y, int w, int h);

void xui_textbox_set_text(int id, const char* text);

void xui_textbox_get_text(int id, char* out, int max);

// Optional later:
// void xui_textbox_set_focus(int id);

#ifdef __cplusplus
}
#endif

#endif
