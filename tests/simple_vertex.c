
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>

typedef struct SimpleBC SimpleBC;
struct SimpleBC {
	uint32_t placeholder;
};

typedef struct SimpleRasterizerState SimpleRasterizerState;
HCC_RASTERIZER_STATE struct SimpleRasterizerState {
	HCC_INTERP f32x4 color;
};

HCC_VERTEX void simple_vertex(
	HccVertexSV const* const sv,
	HccVertexSVOut* const sv_out,
	SimpleBC const* addrsp(BC) const bc,
	SimpleRasterizerState* const state_out
) {
	f32x4 colors[3] = {
		f32x4(1.f, 0.f, 0.f, 1.f),
		f32x4(0.f, 1.f, 0.f, 1.f),
		f32x4(0.f, 0.f, 1.f, 1.f),
	};

	sv_out->position = f32x4(sv->vertex_idx % 2, sv->vertex_idx / 2, 0, 1);
	state_out->color = colors[sv->vertex_idx];
}
