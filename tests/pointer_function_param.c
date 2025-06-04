
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>

typedef struct BC BC;
struct BC {
	HccRwBuffer(uint32_t) buffer;
};

void f(uint32_t* addrsp(FUNCTION) a, uint32_t* addrsp(BUFFER) b) {
	*a = 1;
	*b = 2;
}

HCC_COMPUTE(8, 8, 1)
void pointer_function_param(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	uint32_t a;
	uint32_t* addrsp(BUFFER) b = &bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
	f(&a, b);
}
