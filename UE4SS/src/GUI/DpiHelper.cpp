#include "GUI/DpiHelper.hpp"

#include <map>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <imgui.h>
#include <imgui_internal.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")

struct ImGuiStyleSizeInfo
{
    ImVec2 WindowPadding;
    float WindowRounding;
    ImVec2 WindowMinSize;
    float ChildRounding;
    float PopupRounding;
    ImVec2 FramePadding;
    float FrameRounding;
    ImVec2 ItemSpacing;
    ImVec2 ItemInnerSpacing;
    ImVec2 CellPadding;
    ImVec2 TouchExtraPadding;
    float IndentSpacing;
    float ColumnsMinSpacing;
    float ScrollbarSize;
    float ScrollbarRounding;
    float GrabMinSize;
    float GrabRounding;
    float LogSliderDeadzone;
    float TabRounding;
    float TabMinWidthForCloseButton;
    ImVec2 DisplayWindowPadding;
    ImVec2 DisplaySafeAreaPadding;
    float MouseCursorScale;
};

void scale_style_to(ImGuiStyle* style, float scale_factor)
{
    static std::map<ImGuiStyle*, ImGuiStyleSizeInfo> style_info_map;
    auto found = style_info_map.find(style);
    if (found == style_info_map.end())
    {
        ImGuiStyleSizeInfo info{.WindowPadding = style->WindowPadding,
                                .WindowRounding = style->WindowRounding,
                                .WindowMinSize = style->WindowMinSize,
                                .ChildRounding = style->ChildRounding,
                                .PopupRounding = style->PopupRounding,
                                .FramePadding = style->FramePadding,
                                .FrameRounding = style->FrameRounding,
                                .ItemSpacing = style->ItemSpacing,
                                .ItemInnerSpacing = style->ItemInnerSpacing,
                                .CellPadding = style->CellPadding,
                                .TouchExtraPadding = style->TouchExtraPadding,
                                .IndentSpacing = style->IndentSpacing,
                                .ColumnsMinSpacing = style->ColumnsMinSpacing,
                                .ScrollbarSize = style->ScrollbarSize,
                                .ScrollbarRounding = style->ScrollbarRounding,
                                .GrabMinSize = style->GrabMinSize,
                                .GrabRounding = style->GrabRounding,
                                .LogSliderDeadzone = style->LogSliderDeadzone,
                                .TabRounding = style->TabRounding,
                                .TabMinWidthForCloseButton = style->TabMinWidthForCloseButton,
                                .DisplayWindowPadding = style->DisplayWindowPadding,
                                .DisplaySafeAreaPadding = style->DisplaySafeAreaPadding,
                                .MouseCursorScale = style->MouseCursorScale};
        std::tie(found, std::ignore) = style_info_map.insert({style, info});
    }
    auto& info = found->second;

    style->WindowPadding = ImFloor(info.WindowPadding * scale_factor);
    style->WindowRounding = ImFloor(info.WindowRounding * scale_factor);
    style->WindowMinSize = ImFloor(info.WindowMinSize * scale_factor);
    style->ChildRounding = ImFloor(info.ChildRounding * scale_factor);
    style->PopupRounding = ImFloor(info.PopupRounding * scale_factor);
    style->FramePadding = ImFloor(info.FramePadding * scale_factor);
    style->FrameRounding = ImFloor(info.FrameRounding * scale_factor);
    style->ItemSpacing = ImFloor(info.ItemSpacing * scale_factor);
    style->ItemInnerSpacing = ImFloor(info.ItemInnerSpacing * scale_factor);
    style->CellPadding = ImFloor(info.CellPadding * scale_factor);
    style->TouchExtraPadding = ImFloor(info.TouchExtraPadding * scale_factor);
    style->IndentSpacing = ImFloor(info.IndentSpacing * scale_factor);
    style->ColumnsMinSpacing = ImFloor(info.ColumnsMinSpacing * scale_factor);
    style->ScrollbarSize = ImFloor(info.ScrollbarSize * scale_factor);
    style->ScrollbarRounding = ImFloor(info.ScrollbarRounding * scale_factor);
    style->GrabMinSize = ImFloor(info.GrabMinSize * scale_factor);
    style->GrabRounding = ImFloor(info.GrabRounding * scale_factor);
    style->LogSliderDeadzone = ImFloor(info.LogSliderDeadzone * scale_factor);
    style->TabRounding = ImFloor(info.TabRounding * scale_factor);
    style->TabMinWidthForCloseButton = (info.TabMinWidthForCloseButton != FLT_MAX) ? ImFloor(info.TabMinWidthForCloseButton * scale_factor) : FLT_MAX;
    style->DisplayWindowPadding = ImFloor(info.DisplayWindowPadding * scale_factor);
    style->DisplaySafeAreaPadding = ImFloor(info.DisplaySafeAreaPadding * scale_factor);
    style->MouseCursorScale = ImFloor(info.MouseCursorScale * scale_factor);
}

void setup_dpi_aware()
{
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
}

float monitor_scale()
{
    const HWND activate_window = GetActiveWindow();
    const UINT dpi = GetDpiForWindow(activate_window);
    return static_cast<float>(dpi) / 96.0f;
}

