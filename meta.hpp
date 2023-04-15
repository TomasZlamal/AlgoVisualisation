#pragma once
namespace meta {
	constexpr int text_padding = 40;
	constexpr int width = 800;
	constexpr int height = 800 + text_padding;
	constexpr int node_row_count = 50;
	constexpr int gap = 2;
	constexpr int pixel_alloc = height / node_row_count - gap;
	constexpr int formatting_factor = 40;
	constexpr int genesis_point = 376;
	constexpr int dest = 456;
}
