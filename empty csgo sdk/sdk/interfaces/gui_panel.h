#pragma once

#include "../../handling/utils/memory.h"

namespace sdk {
    namespace interfaces {
        class gui_panel {
        public:
            const char* GetPanelName(uint32_t vgui_panel) {
                typedef const char* (__thiscall* OFn)(PVOID, uint32_t);
                return handling::memory::ScanVFunction <OFn> (this, 36)(this, vgui_panel);
            }
        };
    };
};