
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

typedef struct SimplePixel SimplePixel;
HCC_PIXEL_STATE struct SimplePixel {
	f32x4 color;
};

HCC_PIXEL void simple_pixel(
	HccPixelSV const* const sv,
	HccPixelSVOut* const sv_out,
	SimpleBC const* addrsp(BC) const bc,
	SimpleRasterizerState const* const state,
	SimplePixel* const pixel_out
) {
	pixel_out->color = state->color;
}

