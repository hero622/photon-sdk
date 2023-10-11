#pragma once

#include "source_sdk.h"

#include <vector>

class c_command {
public:
	sdk::con_command *ptr;

	bool is_registered;
	bool is_reference;

	static std::vector<c_command *> &get_list();

	c_command();
	c_command(const char *name);
	c_command(const char *name, sdk::fn_command_callback_t callback, const char *help_string, int flags = 0, sdk::fn_command_completion_callback completion_func = 0);
	~c_command();

	void reg();
	void unreg();

	static void regall();
	static void unregall();

	static bool hook(const char *name, sdk::fn_command_callback_t detour, sdk::fn_command_callback_t &original);
	static bool unhook(const char *name, sdk::fn_command_callback_t original);
};

class c_variable {
public:
	sdk::con_var *ptr;

	int orig_flags;
	sdk::utl_vector<sdk::fn_change_callback_t> orig_cbks;

	union {
		sdk::fn_change_callback_t orig_fn_change_cbk;
		int orig_size;
	};

	bool is_registered;
	bool is_reference;
	bool has_custom_cbk;
	bool is_unlocked;

	static std::vector<c_variable *> &get_list();

	c_variable();
	c_variable(const char *name);
	c_variable(const char *name, const char *value, const char *help_string, int flags = fcvar_never_as_string, sdk::fn_change_callback_t callback = nullptr);
	c_variable(const char *name, const char *value, float min, const char *help_string, int flags = fcvar_never_as_string, sdk::fn_change_callback_t callback = nullptr);
	c_variable(const char *name, const char *value, float min, float max, const char *help_string, int flags = fcvar_never_as_string, sdk::fn_change_callback_t callback = nullptr);
	~c_variable();

	void create(const char *name, const char *value, int flags = 0, const char *help_string = "", bool has_min = false, float min = 0, bool has_max = false, float max = 0, sdk::fn_change_callback_t callback = nullptr);
	void realloc();
	void add_cbk(sdk::fn_change_callback_t cbk);

	void reg();
	void unreg();

	static void clear_all_cbks();
	static void regall();
	static void unregall();
	static c_variable *find(const char *name);
};

#define create_con_command(name, description)                     \
	static void name##_cbk(const sdk::c_command &args);              \
	static c_command name##_command(#name, name##_cbk, description); \
	static void name##_cbk(const sdk::c_command &args)

#define decl_hk_cmd(name)                       \
	static inline sdk::fn_command_callback_t name; \
	static void name##_hk(const sdk::c_command &args)

#define hk_cmd_fn(name) \
	void name##_hk(const sdk::c_command &args)