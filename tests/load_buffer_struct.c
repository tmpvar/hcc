
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>

typedef struct Struct Struct;
struct Struct {
	uint32_t v;
};

typedef struct BC BC;
struct BC {
	HccRoBuffer(Struct) buffer;
};


HCC_COMPUTE(8, 8, 1)
void load_buffer_struct(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	const Struct* addrsp(BUFFER) addr = &bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
	Struct a = *addr;
	Struct b = bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
}
