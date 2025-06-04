
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hcc_atomic_intrinsics.h>
#include <hmaths.h>

typedef struct BC BC;
struct BC {
	HccRwBuffer(uint32_t) buffer;
};

HCC_COMPUTE(8, 8, 1)
void store_buffer_uint_atomic(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	uint32_t* addrsp(BUFFER) addr = &bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
	atomic_store_u32(addr, 1);
	atomic_store_u32(&bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x], 2);
}
