
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>

typedef struct BC BC;
struct BC {
	HccRoBuffer(uint32_t) buffer;
};

_Thread_local uint32_t v;

HCC_COMPUTE(8, 8, 1)
void load_thread_local(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	const uint32_t* addrsp(THREAD) addr = &v;
	uint32_t a = *addr;
	uint32_t b = v;
}
