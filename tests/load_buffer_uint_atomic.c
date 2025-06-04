
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hcc_atomic_intrinsics.h>
#include <hmaths.h>

typedef struct BC BC;
struct BC {
	HccRoBuffer(uint32_t) buffer;
};


HCC_COMPUTE(8, 8, 1)
void load_buffer_uint_atomic(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	const uint32_t* addrsp(BUFFER) addr = &bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
	uint32_t a = atomic_load_u32(addr);
	uint32_t b = atomic_load_u32(&bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x]);
}
