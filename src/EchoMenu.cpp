// EchoMenu.cpp
#include "EchoMenu.hpp"
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

EchoMenu& EchoMenu::get() {
    static EchoMenu instance;
    return instance;
}

void EchoMenu::init() {
    // Called from Geode's setup, initializes ImGui through gd-imgui-cocos
    ImGuiCocos::get().setup([] {
        // Configure touch input for mobile
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.FontGlobalScale = 1.15f; // Slightly larger font for mobile readability
    }).draw([this] {
        // This lambda runs every frame the ImGui layer is active
        if (m_open) {
            draw();
        }
    });
}

// ---------- STYLING (Matching the reference image) ----------
void EchoMenu::pushEchoStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding    = 12.0f;
    style.FrameRounding     = 8.0f;
    style.GrabRounding      = 8.0f;
    style.ScrollbarRounding = 8.0f;
    style.WindowBorderSize  = 1.5f;
    style.FrameBorderSize   = 1.0f;
    style.ItemSpacing       = ImVec2(10.0f, 10.0f);
    style.WindowPadding     = ImVec2(12.0f, 12.0f);

    // Colors derived from the reference image
    ImVec4 bgDark      = ImVec4(0.11f, 0.09f, 0.16f, 0.98f); // #1C1729
    ImVec4 bgPanel     = ImVec4(0.15f, 0.12f, 0.22f, 1.00f); // #261F38
    ImVec4 bgSidebar   = ImVec4(0.12f, 0.10f, 0.18f, 1.00f); // #1F192E
    ImVec4 accentPink  = ImVec4(0.77f, 0.15f, 0.60f, 1.00f); // #C4269A
    ImVec4 accentHover = ImVec4(0.92f, 0.25f, 0.75f, 1.00f); // #EB3FBF
    ImVec4 btnDark     = ImVec4(0.35f, 0.15f, 0.48f, 1.00f); // #59267A
    ImVec4 btnHover    = ImVec4(0.46f, 0.20f, 0.60f, 1.00f); // #753399
    ImVec4 textWhite   = ImVec4(0.95f, 0.95f, 0.98f, 1.00f);
    ImVec4 textGray    = ImVec4(0.65f, 0.65f, 0.70f, 1.00f);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, bgDark);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, bgPanel);
    ImGui::PushStyleColor(ImGuiCol_PopupBg, bgDark);
    ImGui::PushStyleColor(ImGuiCol_Border, accentPink);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, bgSidebar);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, btnHover);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, btnDark);
    ImGui::PushStyleColor(ImGuiCol_TitleBg, bgDark);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, accentPink);
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, bgDark);
    ImGui::PushStyleColor(ImGuiCol_Button, btnDark);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, btnHover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, accentPink);
    ImGui::PushStyleColor(ImGuiCol_Header, accentPink);
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, accentHover);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, accentPink);
    ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
    ImGui::PushStyleColor(ImGuiCol_TextDisabled, textGray);
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, accentPink);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, accentHover);
    ImGui::PushStyleColor(ImGuiCol_CheckMark, accentPink);
}

void EchoMenu::popEchoStyle() {
    ImGui::PopStyleColor(21); // Count must match PushStyleColor calls
}

// ---------- MAIN DRAW ROUTINE ----------
void EchoMenu::draw() {
    pushEchoStyle();

    // Center the window on the screen
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    ImVec2 windowSize(displaySize.x * 0.85f, displaySize.y * 0.75f);
    ImGui::SetNextWindowPos(ImVec2((displaySize.x - windowSize.x) * 0.5f, (displaySize.y - windowSize.y) * 0.5f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

    ImGui::Begin("Echo v2.2.0", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);

    // Top bar (title + close)
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,1));
    ImGui::Text("Echo v2.2.0");
    ImGui::SameLine(displaySize.x * 0.82f);
    if (ImGui::Button("X", ImVec2(40, 40))) {
        setOpen(false);
    }
    ImGui::PopStyleColor();
    ImGui::Separator();

    // Sidebar (left)
    ImGui::BeginChild("Sidebar", ImVec2(windowSize.x * 0.22f, 0), true);
    drawSidebar();
    ImGui::EndChild();

    ImGui::SameLine();

    // Main content (right)
    ImGui::BeginChild("Content", ImVec2(0, 0), false);
    switch (m_activeTab) {
        case 0: // Replay
            drawSessionPanel();
            drawSpeedTimingPanel();
            drawReplayPanel();
            drawFrameAdvancePanel();
            break;
        default:
            ImGui::Text("Coming soon...");
            break;
    }
    ImGui::EndChild();

    ImGui::End();
    popEchoStyle();
}

// ---------- SIDEBAR ----------
void EchoMenu::drawSidebar() {
    const char* tabs[] = { "Replay", "Assists", "Visuals", "Editor", "Library", "Clickbot", "Render", "Settings" };
    for (int i = 0; i < 8; ++i) {
        if (i == m_activeTab) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.77f, 0.15f, 0.60f, 1.00f)); // accent pink
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.12f, 0.22f, 0.0f)); // transparent
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.35f, 0.15f, 0.48f, 1.00f));
        }
        if (ImGui::Button(tabs[i], ImVec2(-1, 50))) {
            m_activeTab = i;
        }
        if (i == m_activeTab) ImGui::PopStyleColor(1);
        else ImGui::PopStyleColor(2);
    }
}

// ---------- PANEL: SESSION ----------
void EchoMenu::drawSessionPanel() {
    ImGui::BeginChild("SessionPanel", ImVec2(0, 180), true);
    ImGui::TextColored(ImVec4(0.77f, 0.15f, 0.60f, 1.0f), "| Session");
    ImGui::Separator();

    // Record / Play buttons
    if (ImGui::Button(m_recording ? "Stop" : "Record", ImVec2(150, 45))) {
        m_recording = !m_recording;
        // TODO: Toggle recording logic
    }
    ImGui::SameLine();
    if (ImGui::Button(m_playing ? "Stop" : "Play", ImVec2(150, 45))) {
        m_playing = !m_playing;
        // TODO: Toggle playback logic
    }

    // Dropdowns
    const char* modes[] = { "Both", "Inputs", "None" };
    ImGui::Text("Record"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(200);
    ImGui::Combo("##recMode", &m_recordMode, modes, IM_ARRAYSIZE(modes));

    ImGui::Text("Play back"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(200);
    ImGui::Combo("##playMode", &m_playbackMode, modes, IM_ARRAYSIZE(modes));

    // Checkbox
    ImGui::Checkbox("Ignore Inputs During Playback", &m_ignoreInputs);

    // Action buttons
    if (ImGui::Button("Reset Level", ImVec2(200, 45))) {
        // TODO: Reset level
    }
    ImGui::SameLine();
    if (ImGui::Button("Close Menu", ImVec2(200, 45))) {
        setOpen(false);
    }
    ImGui::EndChild();
}

// ---------- PANEL: SPEED & TIMING ----------
void EchoMenu::drawSpeedTimingPanel() {
    ImGui::BeginChild("SpeedTimingPanel", ImVec2(0, 240), true);
    ImGui::TextColored(ImVec4(0.77f, 0.15f, 0.60f, 1.0f), "| Speed and Timing");
    ImGui::Separator();

    ImGui::Text("Speed"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("##speed", &m_speed, 0.1f, 1.0f, "%.3fx");

    ImGui::Text("TPS"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("##tps", &m_tps, 10.0f, 100.0f, "%.2f");
    ImGui::SameLine(); if (ImGui::Button("Set##tps", ImVec2(60, 30))) { /* TODO */ }

    ImGui::Text("FPS"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("##fps", &m_fps, 10.0f, 100.0f, "%.2f");
    ImGui::SameLine(); if (ImGui::Button("Set##fps", ImVec2(60, 30))) { /* TODO */ }

    // Toggles
    ImGui::Checkbox("Lock FPS", &m_lockFps); ImGui::SameLine(200);
    ImGui::Checkbox("Real Time", &m_realtime);

    ImGui::Checkbox("Audio Speedhack", &m_audioSpeedhack); ImGui::SameLine(200);
    ImGui::Checkbox("Sync Audio", &m_syncAudio);

    ImGui::EndChild();
}

// ---------- PANEL: REPLAY ----------
void EchoMenu::drawReplayPanel() {
    ImGui::BeginChild("ReplayPanel", ImVec2(0, 220), true);
    ImGui::TextColored(ImVec4(0.77f, 0.15f, 0.60f, 1.0f), "| Replay");
    ImGui::Separator();

    ImGui::Text("Replay");
    ImGui::InputText("##replayName", (char*)" ", 2, ImGuiInputTextFlags_ReadOnly); // Placeholder

    ImGui::Text("0 inputs  240 TPS");

    // Action buttons grid
    if (ImGui::Button("Save", ImVec2(140, 40))) { /* TODO */ }
    ImGui::SameLine();
    if (ImGui::Button("Load", ImVec2(140, 40))) { /* TODO */ }

    if (ImGui::Button("Merge In", ImVec2(140, 40))) { /* TODO */ }
    ImGui::SameLine();
    if (ImGui::Button("Clear", ImVec2(140, 40))) { /* TODO */ }

    ImGui::Checkbox("No Overwrite", &m_noOverwrite);
    ImGui::SameLine();
    if (ImGui::Button("Stop On Best Frame", ImVec2(200, 40))) { /* TODO */ }

    ImGui::Text("Search range"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("##searchRange", &m_searchRange, 10.0f, 100.0f, "%.0f steps");

    ImGui::EndChild();
}

// ---------- PANEL: FRAME ADVANCE ----------
void EchoMenu::drawFrameAdvancePanel() {
    ImGui::BeginChild("FrameAdvancePanel", ImVec2(0, 220), true);
    ImGui::TextColored(ImVec4(0.77f, 0.15f, 0.60f, 1.0f), "| Frame Advance");
    ImGui::Separator();

    ImGui::Checkbox("Frame Advance", &m_frameAdvance);
    ImGui::SameLine(180);
    if (ImGui::Button("Step", ImVec2(100, 40))) { /* TODO */ }

    ImGui::Text("Hold delay"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("##holdDelay", &m_holdDelay, 10.0f, 100.0f, "%.0f ms");

    ImGui::Text("Held speed"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("##heldSpeed", &m_heldSpeed, 10.0f, 100.0f, "%.0f%%");

    ImGui::Checkbox("Backstep", &m_backstep);
    ImGui::SameLine(180);
    if (ImGui::Button("Back", ImVec2(100, 40))) { /* TODO */ }

    ImGui::Text("Saved states"); ImGui::SameLine(180);
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("##savedStates", &m_savedStates, 10.0f, 100.0f, "%.0f%%");

    ImGui::EndChild();
}
