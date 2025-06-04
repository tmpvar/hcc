
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>

typedef struct BC BC;
struct BC {
	HccRoBuffer(uint32_t) buffer;
};


HCC_COMPUTE(8, 8, 1)
void load_buffer_uint(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	const uint32_t* addrsp(BUFFER) addr = &bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
	uint32_t a = *addr;
	uint32_t b = bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
}
