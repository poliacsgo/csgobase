#pragma once

#include "../structs/int_rect.h"
#include "../structs/vertex.h"

namespace sdk {
    namespace interfaces {
        // https://github.com/pmrowla/hl2sdk-csgo/blob/master/public/vgui/ISurface.h

        namespace v_gui {
            typedef unsigned long h_font;
            typedef std::uint32_t v_panel;
        };

        enum font_feature {
            font_feature_antialiased_fonts = 1, font_feature_dropshadow_fonts = 2, font_feature_outline_fonts = 6
        };

        enum font_draw_type {
            font_draw_default = 0, font_draw_nonadditive, font_draw_additive, font_draw_type_count = 2
        };

        enum font_flags {
            fontflag_none,
            fontflag_italic = 0x001,
            fontflag_underline = 0x002,
            fontflag_strikeout = 0x004,
            fontflag_symbol = 0x008,
            fontflag_antialias = 0x010,
            fontflag_gaussianblur = 0x020,
            fontflag_rotary = 0x040,
            fontflag_dropshadow = 0x080,
            fontflag_additive = 0x100,
            fontflag_outline = 0x200,
            fontflag_custom = 0x400,
            fontflag_bitmap = 0x800
        };

        class gui_surface : public app_system {
        public:
            virtual void                 RunFrame() = 0;
            virtual v_gui::v_panel       GetEmbeddedPanel() = 0;
            virtual void                 SetEmbeddedPanel(v_gui::v_panel pPanel) = 0;
            virtual void                 PushMakeCurrent(v_gui::v_panel panel, bool useInsets) = 0;
            virtual void                 PopMakeCurrent(v_gui::v_panel panel) = 0;
            virtual void                 DrawSetColor(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a) = 0;
            virtual void                 DrawSetColor(sdk::classes::color col) = 0;
            virtual void                 DrawFilledRect(std::int32_t x0, std::int32_t y0, std::int32_t x1, std::int32_t y1) = 0;
            virtual void                 DrawFilledRectArray(sdk::structs::int_rect* pRects, std::int32_t numRects) = 0;
            virtual void                 DrawOutlinedRect(std::int32_t x0, std::int32_t y0, std::int32_t x1, std::int32_t y1) = 0;
            virtual void                 DrawLine(std::int32_t x0, std::int32_t y0, std::int32_t x1, std::int32_t y1) = 0;
            virtual void                 DrawPolyLine(std::int32_t* px, std::int32_t* py, std::int32_t numPoint32_ts) = 0;
            virtual void                 DrawSetApparentDepth(float f) = 0;
            virtual void                 DrawClearApparentDepth(void) = 0;
            virtual void                 DrawSetTextFont(v_gui::h_font font) = 0;
            virtual void                 DrawSetTextColor(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a) = 0;
            virtual void                 DrawSetTextColor(sdk::classes::color col) = 0;
            virtual void                 DrawSetTextPos(std::int32_t x, std::int32_t y) = 0;
            virtual void                 DrawGetTextPos(std::int32_t& x, std::int32_t& y) = 0;
            virtual void                 DrawPrintText(const wchar_t* text, std::int32_t textLen, font_draw_type drawType = font_draw_type::font_draw_default) = 0;
            virtual void                 DrawUnicodeChar(wchar_t wch, font_draw_type drawType = font_draw_type::font_draw_default) = 0;
            virtual void                 DrawFlushText() = 0;
            virtual void*                CreateHTMLWindow(void* events, v_gui::v_panel context) = 0;
            virtual void                 PaintHTMLWindow(void* htmlwin) = 0;
            virtual void                 DeleteHTMLWindow(void* htmlwin) = 0;
            virtual std::int32_t         DrawGetTextureId(char const* filename) = 0;
            virtual bool                 DrawGetTextureFile(std::int32_t id, char* filename, std::int32_t maxlen) = 0;
            virtual void                 DrawSetTextureFile(std::int32_t id, const char* filename, std::int32_t hardwareFilter, bool forceReload) = 0;
            virtual void                 DrawSetTextureRGBA(std::int32_t id, const unsigned char* rgba, std::int32_t wide, std::int32_t tall) = 0;
            virtual void                 DrawSetTexture(std::int32_t id) = 0;
            virtual void                 DeleteTextureByID(std::int32_t id) = 0;
            virtual void                 DrawGetTextureSize(std::int32_t id, std::int32_t& wide, std::int32_t& tall) = 0;
            virtual void                 DrawTexturedRect(std::int32_t x0, std::int32_t y0, std::int32_t x1, std::int32_t y1) = 0;
            virtual bool                 IsTextureIDValid(std::int32_t id) = 0;
            virtual std::int32_t         CreateNewTextureID(bool procedural = false) = 0;
            virtual void                 GetScreenSize(std::int32_t& wide, std::int32_t& tall) = 0;
            virtual void                 SetAsTopMost(v_gui::v_panel panel, bool state) = 0;
            virtual void                 BringToFront(v_gui::v_panel panel) = 0;
            virtual void                 SetForegroundWindow(v_gui::v_panel panel) = 0;
            virtual void                 SetPanelVisible(v_gui::v_panel panel, bool state) = 0;
            virtual void                 SetMinimized(v_gui::v_panel panel, bool state) = 0;
            virtual bool                 IsMinimized(v_gui::v_panel panel) = 0;
            virtual void                 FlashWindow(v_gui::v_panel panel, bool state) = 0;
            virtual void                 SetTitle(v_gui::v_panel panel, const wchar_t* title) = 0;
            virtual void                 SetAsToolBar(v_gui::v_panel panel, bool state) = 0;
            virtual void                 CreatePopup(v_gui::v_panel panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
            virtual void                 SwapBuffers(v_gui::v_panel panel) = 0;
            virtual void                 Invalidate(v_gui::v_panel panel) = 0;
            virtual void                 SetCursor(unsigned long cursor) = 0;
            virtual bool                 IsCursorVisible() = 0;
            virtual void                 ApplyChanges() = 0;
            virtual bool                 IsWithin(std::int32_t x, std::int32_t y) = 0;
            virtual bool                 HasFocus() = 0;
            virtual bool                 SupportsFeature(std::int32_t feature) = 0;
            virtual void                 RestrictPaint32_tToSinglePanel(v_gui::v_panel panel, bool bForceAllowNonModalSurface = false) = 0;
            virtual void                 SetModalPanel(v_gui::v_panel) = 0;
            virtual v_gui::v_panel       GetModalPanel() = 0;
            virtual void                 UnlockCursor() = 0;
            virtual void                 LockCursor() = 0;
            virtual void                 SetTranslateExtendedKeys(bool state) = 0;
            virtual v_gui::v_panel       GetTopmostPopup() = 0;
            virtual void                 SetTopLevelFocus(v_gui::v_panel panel) = 0;
            virtual v_gui::h_font        CreateGuiFont() = 0;
            virtual bool                 SetFontGlyphSet(v_gui::h_font font, const char* windowsFontName, std::int32_t tall, std::int32_t weight, std::int32_t blur, std::int32_t scanlines, std::int32_t flags, std::int32_t nRangeMin = 0, std::int32_t nRangeMax = 0) = 0;
            virtual bool                 AddCustomFontFile(const char* fontFileName) = 0;
            virtual std::int32_t         GetFontTall(v_gui::h_font font) = 0;
            virtual std::int32_t         GetFontAscent(v_gui::h_font font, wchar_t wch) = 0;
            virtual bool                 IsFontAdditive(v_gui::h_font font) = 0;
            virtual void                 GetCharABCwide(v_gui::h_font font, std::int32_t ch, std::int32_t& a, std::int32_t& b, std::int32_t& c) = 0;
            virtual std::int32_t         GetCharacterWidth(v_gui::h_font font, std::int32_t ch) = 0;
            virtual void                 GetTextSize(v_gui::h_font font, const wchar_t* text, std::int32_t& wide, std::int32_t& tall) = 0;
            virtual v_gui::v_panel       GetNotifyPanel() = 0;
            virtual void                 SetNotifyIcon(v_gui::v_panel context, unsigned long icon, v_gui::v_panel panelToReceiveMessages, const char* text) = 0;
            virtual void                 PlayGuiSound(const char* fileName) = 0;
            virtual std::int32_t         GetPopupCount() = 0;
            virtual v_gui::v_panel       GetPopup(std::int32_t index) = 0;
            virtual bool                 ShouldPaint32_tChildPanel(v_gui::v_panel childPanel) = 0;
            virtual bool                 RecreateContext(v_gui::v_panel panel) = 0;
            virtual void                 AddPanel(v_gui::v_panel panel) = 0;
            virtual void                 ReleasePanel(v_gui::v_panel panel) = 0;
            virtual void                 MovePopupToFront(v_gui::v_panel panel) = 0;
            virtual void                 MovePopupToBack(v_gui::v_panel panel) = 0;
            virtual void                 SolveTraverse(v_gui::v_panel panel, bool forceApplySchemeSettings = false) = 0;
            virtual void                 PaintTraverse(v_gui::v_panel panel) = 0;
            virtual void                 EnableMouseCapture(v_gui::v_panel panel, bool state) = 0;
            virtual void                 GetWorkspaceBounds(std::int32_t& x, std::int32_t& y, std::int32_t& wide, std::int32_t& tall) = 0;
            virtual void                 GetAbsoluteWindowBounds(std::int32_t& x, std::int32_t& y, std::int32_t& wide, std::int32_t& tall) = 0;
            virtual void                 GetProportionalBase(std::int32_t& width, std::int32_t& height) = 0;
            virtual void                 CalculateMouseVisible() = 0;
            virtual bool                 NeedKBInput() = 0;
            virtual bool                 HasCursorPosFunctions() = 0;
            virtual void                 SurfaceGetCursorPos(std::int32_t& x, std::int32_t& y) = 0;
            virtual void                 SurfaceSetCursorPos(std::int32_t x, std::int32_t y) = 0;
            virtual void                 DrawTexturedLine(const sdk::structs::vertex& a, const sdk::structs::vertex& b) = 0;
            virtual void                 DrawOutlinedCircle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments) = 0;
            virtual void                 DrawTexturedPolyLine(const sdk::structs::vertex* p, std::int32_t n) = 0;
            virtual void                 DrawTexturedSubRect(std::int32_t x0, std::int32_t y0, std::int32_t x1, std::int32_t y1, float texs0, float text0, float texs1, float text1) = 0;
            virtual void                 DrawTexturedPolygon(std::int32_t n, sdk::structs::vertex* pVertice, bool bClipVertices = true) = 0;
        };
    };
};