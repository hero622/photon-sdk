#include "convar.h"

#include "wormhole.h"

// command
std::vector<c_command *> &c_command::get_list() {
	static std::vector<c_command *> list;
	return list;
}

c_command::c_command() {
}

c_command::c_command(const char *name) {
	this->ptr = reinterpret_cast<sdk::con_command *>(wh->portal2->cvar->find_command_base(name));
	this->is_registered = false;
	this->is_reference = true;
}

c_command::c_command(const char *name, sdk::fn_command_callback_t callback, const char *help_string, int flags, sdk::fn_command_completion_callback completion_func)
	: is_registered(false)
	, is_reference(false) {
	this->ptr = new sdk::con_command(name, callback, help_string, flags, completion_func);

	c_command::get_list().push_back(this);
}

c_command::~c_command() {
	if (!this->is_reference)
		delete_ptr(this->ptr);
}

void c_command::reg() {
	if (!this->is_registered) {
		*(void **)this->ptr = *(void **)wh->portal2->cvar->find_command_base("listdemo");
		wh->portal2->cvar->register_con_command(this->ptr);
	}
	this->is_registered = true;
}

void c_command::unreg() {
	if (this->is_registered)
		wh->portal2->cvar->unregister_con_command(this->ptr);
	this->is_registered = false;
}

void c_command::regall() {
	for (const auto &cmd : c_command::get_list()) {
		cmd->reg();
	}
}

void c_command::unregall() {
	for (const auto &cmd : c_command::get_list()) {
		cmd->unreg();
	}
}

bool c_command::hook(const char *name, sdk::fn_command_callback_t detour, sdk::fn_command_callback_t &original) {
	c_command cc(name);
	if (cc.ptr != nullptr) {
		original = cc.ptr->fn_command_callback;
		cc.ptr->fn_command_callback = detour;
		return true;
	}
	return false;
}

bool c_command::unhook(const char *name, sdk::fn_command_callback_t original) {
	c_command cc(name);
	if (cc.ptr != nullptr && original) {
		cc.ptr->fn_command_callback = original;
		return true;
	}
	return false;
}

// variable
std::vector<c_variable *> &c_variable::get_list() {
	static std::vector<c_variable *> list;
	return list;
}

c_variable::c_variable()
	: ptr(nullptr)
	, orig_flags(0)
	, is_registered(false)
	, is_reference(false)
	, has_custom_cbk(false)
	, is_unlocked(false) {
}

c_variable::c_variable(const char *name)
	: c_variable() {
	this->ptr = reinterpret_cast<sdk::con_var *>(wh->portal2->cvar->find_command_base(name));
	this->is_reference = true;
}

c_variable::c_variable(const char *name, const char *value, const char *help_string, int flags, sdk::fn_change_callback_t callback)
	: c_variable() {
	if ((flags & ~fcvar_dontrecord) != 0)
		create(name, value, flags, help_string, true, 0, true, 1, callback);
	else
		create(name, value, flags, help_string, false, 0, false, 0, callback);
}

c_variable::c_variable(const char *name, const char *value, float min, const char *help_string, int flags, sdk::fn_change_callback_t callback)
	: c_variable() {
	create(name, value, flags, help_string, true, min, false, 0, callback);
}

c_variable::c_variable(const char *name, const char *value, float min, float max, const char *help_string, int flags, sdk::fn_change_callback_t callback)
	: c_variable() {
	create(name, value, flags, help_string, true, min, true, max, callback);
}

c_variable::~c_variable() {
	if (!this->is_reference) {
		delete_ptr(this->ptr);
	}
}

void c_variable::create(const char *name, const char *value, int flags, const char *help_string, bool has_min, float min, bool has_max, float max, sdk::fn_change_callback_t callback) {
	this->ptr = new sdk::con_var(name, value, flags, help_string, has_min, min, has_max, max);
	this->add_cbk(callback);

	c_variable::get_list().push_back(this);
}

void c_variable::realloc() {
	auto newptr = new sdk::con_var(
		this->ptr->name,
		this->ptr->default_value,
		this->ptr->flags,
		this->ptr->help_string,
		this->ptr->has_min,
		this->ptr->min_val,
		this->ptr->has_max,
		this->ptr->max_val);
	delete this->ptr;
	this->ptr = newptr;
}

void c_variable::add_cbk(sdk::fn_change_callback_t callback) {
	if (callback != nullptr) {
		this->orig_cbks = this->ptr->fn_change_callback;
		this->ptr->fn_change_callback[this->ptr->fn_change_callback.add_to_tail()] = callback;
		this->has_custom_cbk = true;
		this->get_list().push_back(this);
	}
}

void c_variable::reg() {
	if (!this->is_registered && !this->is_reference && this->ptr) {
		this->is_registered = true;
		sdk::fn_change_callback_t callback = this->ptr->fn_change_callback.count() > 0 ? this->ptr->fn_change_callback.element(0) : nullptr;
		this->realloc();

		// i dont really like this method but i cant find anything better rn
		*(void **)this->ptr = *(void **)(wh->portal2->cvar->find_command_base("sv_lan"));
		this->ptr->vtable = ((sdk::con_var *)wh->portal2->cvar->find_command_base("sv_lan"))->vtable;

		using create_fn_t = void(__rescall *)(void *, const char *, const char *, int, const char *, bool, float, bool, float, sdk::fn_change_callback_t);
		const auto create_fn = reinterpret_cast<create_fn_t>(utils::memory::pattern_scan(modules::tier1, signatures::create));
		create_fn(this->ptr, this->ptr->name, this->ptr->default_value, this->ptr->flags, this->ptr->help_string, this->ptr->has_min, this->ptr->min_val, this->ptr->has_max, this->ptr->max_val, callback);
	}
}
void c_variable::unreg() {
	if (this->is_registered && !this->is_reference && this->ptr) {
		this->is_registered = false;
		wh->portal2->cvar->unregister_con_command(this->ptr);

#ifdef _WIN32
		const auto dtor_fn = reinterpret_cast<int(__rescall *)(void *, char)>(utils::memory::pattern_scan(modules::tier1, signatures::dtor));
		dtor_fn(this->ptr, 0);
#else
		const auto dtor_fn = reinterpret_cast<int(__rescall *)(void *)>(utils::memory::pattern_scan(modules::tier1, signatures::dtor));
		dtor_fn(this->ptr);
#endif

		delete_ptr(this->ptr);
	}
}

void c_variable::clear_all_cbks() {
	for (auto var : c_variable::get_list()) {
		if (var->has_custom_cbk) {
			var->ptr->fn_change_callback = var->orig_cbks;
			var->has_custom_cbk = false;
		}
	}
}

void c_variable::regall() {
	for (const auto &var : c_variable::get_list()) {
		var->reg();
	}
}

void c_variable::unregall() {
	for (const auto &var : c_variable::get_list()) {
		var->unreg();
	}
}

c_variable *c_variable::find(const char *name) {
	for (const auto &var : c_variable::get_list()) {
		if (!strcmp(var->ptr->name, name)) {
			return var;
		}
	}
	return nullptr;
}