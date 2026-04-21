#ifdef __APPLE__

#import <Cocoa/Cocoa.h>

#include "platform.h"
#include "../internal/internal.h"

// =====================================================
// Globals
// =====================================================

static NSWindow* g_window = nil;
static void (*g_text_cb)(int key) = NULL;

// =====================================================
// Text input callback registration
// =====================================================

void xui_platform_set_text_input_callback(void (*cb)(int))
{
    g_text_cb = cb;
}

// =====================================================
// Enable / disable text input (no-op for now)
// =====================================================

void xui_platform_enable_text_input(int enabled)
{
    (void)enabled;
    [NSApp activateIgnoringOtherApps:YES];
}

// =====================================================
// Window class (keyboard handling)
// =====================================================

@interface XUIWindow : NSWindow
@end

@implementation XUIWindow

- (void)keyDown:(NSEvent *)event
{
    NSString* chars = [event characters];

    if ([chars length] > 0 && g_text_cb)
    {
        unichar c = [chars characterAtIndex:0];
        g_text_cb((int)c);
    }
}

@end

// =====================================================
// Window delegate (OPTION 2: last window closes → quit)
// =====================================================

@interface XUIWindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation XUIWindowDelegate

- (void)windowWillClose:(NSNotification *)notification
{
    int visibleCount = 0;

    for (NSWindow* win in [NSApp windows])
    {
        if ([win isVisible])
        {
            visibleCount++;
        }
    }

    if (visibleCount <= 1)
    {
        xui_platform_quit();
    }
}

@end

static XUIWindowDelegate* g_delegate = nil;

// =====================================================
// Init
// =====================================================

void xui_platform_init(const char* title, int w, int h)
{
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSRect frame = NSMakeRect(100, 100, w, h);

    g_window = [[XUIWindow alloc]
        initWithContentRect:frame
        styleMask:(NSWindowStyleMaskTitled |
                   NSWindowStyleMaskClosable |
                   NSWindowStyleMaskResizable)
        backing:NSBackingStoreBuffered
        defer:NO];

    [g_window setTitle:[NSString stringWithUTF8String:title]];

    // IMPORTANT: attach delegate (Option 2 behavior)
    g_delegate = [XUIWindowDelegate new];
    [g_window setDelegate:g_delegate];

    [g_window makeKeyAndOrderFront:nil];

    [NSApp activateIgnoringOtherApps:YES];
}

// =====================================================
// Run loop
// =====================================================

void xui_platform_run()
{
    [NSApp run];
}

// =====================================================
// Quit
// =====================================================

void xui_platform_quit()
{
    [NSApp terminate:nil];
}

// =====================================================
// BUTTON
// =====================================================

@interface XUIButtonTarget : NSObject
@property int buttonId;
@end

@implementation XUIButtonTarget

- (void)onClick:(id)sender
{
    xui_internal_on_button_clicked(self.buttonId);
}

@end

xui_button xui_platform_create_button(
    int id,
    const char* label,
    int x, int y, int w, int h)
{
    NSButton* btn =
        [[NSButton alloc] initWithFrame:NSMakeRect(x, y, w, h)];

    [btn setTitle:[NSString stringWithUTF8String:label]];
    [btn setBezelStyle:NSBezelStyleRounded];

    XUIButtonTarget* target = [XUIButtonTarget new];
    target.buttonId = id;

    [btn setTarget:target];
    [btn setAction:@selector(onClick:)];

    [[g_window contentView] addSubview:btn];

    return (__bridge xui_button)btn;
}

// =====================================================
// TEXTBOX
// =====================================================

xui_textbox xui_platform_create_textbox(
    int id,
    int x, int y, int w, int h)
{
    (void)id; // currently unused, but reserved for future focus system

    NSTextField* field =
        [[NSTextField alloc] initWithFrame:NSMakeRect(x, y, w, h)];

    [[g_window contentView] addSubview:field];

    return (__bridge xui_textbox)field;
}

void xui_platform_set_textbox_text(xui_textbox tb, const char* text)
{
    NSTextField* field = (__bridge NSTextField*)tb;
    [field setStringValue:[NSString stringWithUTF8String:text]];
}

// =====================================================
// MENU
// =====================================================

static NSMenu* g_menu = nil;

@interface XUIMenuTarget : NSObject
@property int itemId;
@end

@implementation XUIMenuTarget

- (void)onSelect:(id)sender
{
    xui_internal_on_menu_item(self.itemId);
}

@end

void xui_platform_create_menu()
{
    g_menu = [[NSMenu alloc] initWithTitle:@"MainMenu"];

    NSMenuItem* rootItem =
        [[NSMenuItem alloc] initWithTitle:@"App"
                                    action:nil
                             keyEquivalent:@""];

    [g_menu addItem:rootItem];

    NSMenu* appMenu = [[NSMenu alloc] initWithTitle:@"App"];
    [rootItem setSubmenu:appMenu];

    [NSApp setMainMenu:g_menu];
}

void xui_platform_add_menu_item(const char* name, int id)
{
    NSString* title = [NSString stringWithUTF8String:name];

    XUIMenuTarget* target = [XUIMenuTarget new];
    target.itemId = id;

    NSMenuItem* item =
        [[NSMenuItem alloc] initWithTitle:title
                                    action:@selector(onSelect:)
                             keyEquivalent:@""];

    [item setTarget:target];

    NSMenu* appMenu =
        [[g_menu itemAtIndex:0] submenu];

    [appMenu addItem:item];
}

#endif
