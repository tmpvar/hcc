
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
	HccRwBuffer(Struct) buffer;
};


HCC_COMPUTE(8, 8, 1)
void store_buffer_struct(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	Struct* addrsp(BUFFER) addr = &bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x];
	*addr = (Struct){0};
	bc->buffer[sv->dispatch_idx.y * 8 + sv->dispatch_idx.x] = (Struct){0};
}
