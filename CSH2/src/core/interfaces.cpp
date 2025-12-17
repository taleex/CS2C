#include "interfaces.hpp"

#include <stdexcept>
#include <format>


namespace interfaces{

template <class T>
T* capture_interface(const char* module_name, const char* interface_name){
	const HMODULE module_handle = GetModuleHandleA(module_name);
	if(module_handle == nullptr){
		throw std::runtime_error(
			std::format("Failed to get handle for module: {}", module_name)
		)
			;
	}

	using create_interface_fn = T* (*)(const char*, int*);
	const auto create_interface = reinterpret_cast<create_interface_fn>(
		GetProcAddress(module_handle, "CreateInterface")
		);

	if (create_interface == nullptr) {
		
		throw std::runtime_error(
			std::format("Failed to get CreateInterface from module: {}", module_name)
		);
	}

	T* interface_ptr = create_interface(interface_name, nullptr);
	if(interface_ptr == nullptr) {
		throw std::runtime_error(
			std::format("Failed to capture interface: {} from module: {}", interface_name, module_name)
		);
	}
	return interface_ptr;
}

static void create_d3d11_resources() {

}

void create() {

	{
		std::uint8_t* address =
		sdk::find_pattern("client.dll", "48 8B OD ? ? ? ? 4C 8D 8F ? ? ? ? 45 33 F6");

		csgo_input = *reinterpret_cast<sdk::interface_csgo_input**>(
			sdk::resolve_absolute_rip_address(address, 3,7));

		if (csgo_input == nullptr) {
			throw std::runtime_error("Failed to capture interface_csgo_input");
		}

	}

	input_system = capture_interface<sdk::interface_input_system>(
		"inputsystem.dll",
		"InputSystemVersion001"
	);
}
void destroy() {}



}