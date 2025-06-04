
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
void load_bc(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	//HccRoBuffer(uint32_t) buffer = bc->buffer;
	BC b = *bc;
}
