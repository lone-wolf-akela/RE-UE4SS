#pragma once

struct ImGuiStyle;
void scale_style_to(ImGuiStyle* style, float scale_factor);
float monitor_scale();
void setup_dpi_aware();