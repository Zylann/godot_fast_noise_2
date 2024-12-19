#include "fast_noise_2.h"
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

namespace zylann {

void initialize_gdfastnoise2(godot::ModuleInitializationLevel level) {
	using namespace godot;

	if (level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<FastNoise2>();
	}
}

void deinitialize_gdfastnoise2(godot::ModuleInitializationLevel level) {
	//
}

} // namespace zylann

extern "C" {
// Library entry point
GDExtensionBool GDE_EXPORT gdfastnoise2_library_init(
		GDExtensionInterfaceGetProcAddress p_get_proc_address,
		GDExtensionClassLibraryPtr p_library,
		GDExtensionInitialization *r_initialization
) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(zylann::initialize_gdfastnoise2);
	init_obj.register_terminator(zylann::deinitialize_gdfastnoise2);
	init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
