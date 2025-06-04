
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>

typedef struct BC BC;
struct BC {
	HccRwBuffer(uint32_t) buffer;
};

HCC_COMPUTE(8, 8, 1)
void pointer_branch_buffer(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	uint32_t* addrsp(BUFFER) p = sv->dispatch_idx.x < 16 ? &bc->buffer[0] : &bc->buffer[1];
	*p = 1;

	if (sv->dispatch_idx.y < 16) {
		p = &bc->buffer[1];
	} else {
		p = &bc->buffer[2];
	}
	*p += 2;
}
