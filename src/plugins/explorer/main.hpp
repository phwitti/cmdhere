#ifndef __CMDHERE_EXPLORER_MAIN_HPP__
#define __CMDHERE_EXPLORER_MAIN_HPP__

extern "C" __declspec(dllexport) bool current_directory(
	char *_in_module_name, char *_in_class_name, void* _handle,
	char **_out_string, int _in_max_length
);

#endif
