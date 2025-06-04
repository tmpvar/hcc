#include "app.h"
#include "gpu_backend_api.h"
#include "platform_backend_api.h"

#include <hmaths.c>
#include <hcc_interop.c>

#ifdef __linux__
#include "platform_linux.c"
#include "gpu_vulkan.c"
#elif defined(_WIN32)
#include <windows.h>
#include "platform_win32.c"
#include "gpu_vulkan.c"
#else
#error "unsupported platform
#endif

#define TEST_LIST() \
	RENDER(simple_vertex, simple_pixel) \
	COMPUTE(load_thread_local) \
	COMPUTE(load_bc) \
	COMPUTE(load_buffer_uint) \
	COMPUTE(load_buffer_uint_atomic) \
	COMPUTE(load_buffer_struct) \
	COMPUTE(load_texture) \
	COMPUTE(load_texture_atomic) \
	COMPUTE(load_dispatch_group_uint) \
	COMPUTE(load_dispatch_group_uint_atomic) \
	COMPUTE(load_dispatch_group_struct) \
	COMPUTE(store_thread_local) \
	COMPUTE(store_buffer_uint) \
	COMPUTE(store_buffer_uint_atomic) \
	COMPUTE(store_buffer_struct) \
	COMPUTE(store_texture) \
	COMPUTE(store_texture_atomic) \
	COMPUTE(store_dispatch_group_uint) \
	COMPUTE(store_dispatch_group_uint_atomic) \
	COMPUTE(store_dispatch_group_struct) \
	COMPUTE(pointer_function_param) \
	COMPUTE(pointer_branch_function) \
	COMPUTE(pointer_branch_buffer) \
	COMPUTE(pointer_branch_dispatch_group) \

int main(int argc, char** argv) {
	APP_UNUSED(argc);
	APP_UNUSED(argv);

	platform_register_segfault_handler();
	gpu_init();

#define RENDER(vertex, pixel) printf("compiling %s & %s...", #vertex, #pixel); fflush(stdout); gpu_compile_pipeline_render(#vertex, #pixel); printf("SUCCESS!\n");
#define COMPUTE(compute) printf("compiling %s...", #compute); fflush(stdout); gpu_compile_pipeline_compute(#compute); printf("SUCCESS!\n");
TEST_LIST()
#undef RENDER
#undef COMPUTE

	return 0;
}

