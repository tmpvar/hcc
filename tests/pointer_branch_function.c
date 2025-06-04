
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
void pointer_branch_function(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	uint32_t a;
	uint32_t b;
	uint32_t* addrsp(FUNCTION) p;

	p = sv->dispatch_idx.x < 16 ? &a : &b;
	*p = 1;

	if (sv->dispatch_idx.y < 16) {
		p = &a;
	} else {
		p = &b;
	}
	*p += 2;
}
