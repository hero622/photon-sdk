#pragma once

namespace sdk {
	enum signonstate_t {
		signonstate_none = 0,
		signonstate_challenge = 1,
		signonstate_connected = 2,
		signonstate_new = 3,
		signonstate_prespawn = 4,
		signonstate_spawn = 5,
		signonstate_full = 6,
		signonstate_changelevel = 7,
	};

	typedef unsigned long h_font;

	enum paint_mode_t {
		paint_uipanels = (1 << 0),
		paint_ingamepanels = (1 << 1),
	};

	enum font_flags_t {
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
		fontflag_bitmap = 0x800,
	};
}  // namespace sdk

#define fcvar_none 0
#define fcvar_unregistered (1 << 0)
#define fcvar_developmentonly (1 << 1)
#define fcvar_gamedll (1 << 2)
#define fcvar_clientdll (1 << 3)
#define fcvar_hidden (1 << 4)
#define fcvar_protected (1 << 5)
#define fcvar_sponly (1 << 6)
#define fcvar_archive (1 << 7)
#define fcvar_notify (1 << 8)
#define fcvar_userinfo (1 << 9)
#define fcvar_cheat (1 << 14)
#define fcvar_printableonly (1 << 10)
#define fcvar_unlogged (1 << 11)
#define fcvar_never_as_string (1 << 12)
#define fcvar_replicated (1 << 13)
#define fcvar_demo (1 << 16)
#define fcvar_dontrecord (1 << 17)
#define fcvar_reload_materials (1 << 20)
#define fcvar_reload_textures (1 << 21)
#define fcvar_not_connected (1 << 22)
#define fcvar_material_system_thread (1 << 23)
#define fcvar_archive_xbox (1 << 24)
#define fcvar_accessible_from_threads (1 << 25)
#define fcvar_server_can_execute (1 << 28)
#define fcvar_server_cannot_query (1 << 29)
#define fcvar_clientcmd_can_execute (1 << 30)