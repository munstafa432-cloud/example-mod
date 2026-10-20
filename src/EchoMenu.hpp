// EchoMenu.hpp
#pragma once
#include <Geode/Geode.hpp>
#include <imgui-cocos.hpp>

class EchoMenu {
public:
    static EchoMenu& get();

    void init();
    void draw();

    bool isOpen() const { return m_open; }
    void setOpen(bool open) { m_open = open; }

private:
    bool m_open = false;
    int m_activeTab = 0; // 0: Replay, 1: Assists, etc.

    // Session state (stubs)
    bool m_recording = false;
    bool m_playing = false;
    int m_recordMode = 0;    // 0: Both, 1: Inputs, 2: None
    int m_playbackMode = 0;  // 0: Both, 1: Inputs, 2: None
    bool m_ignoreInputs = true;

    // Speed & Timing state
    float m_speed = 1.0f;
    float m_tps = 240.0f;
    float m_fps = 240.0f;
    bool m_lockFps = false;
    bool m_realtime = true;
    bool m_audioSpeedhack = false;
    bool m_syncAudio = false;

    // Replay state
    float m_searchRange = 379.0f;
    bool m_noOverwrite = false;

    // Frame Advance
    bool m_frameAdvance = false;
    float m_holdDelay = 300.0f;
    float m_heldSpeed = 100.0f;
    bool m_backstep = true;
    float m_savedStates = 100.0f;

    // Helper functions for UI blocks
    void drawSidebar();
    void drawSessionPanel();
    void drawSpeedTimingPanel();
    void drawReplayPanel();
    void drawFrameAdvancePanel();

    // Styling
    void pushEchoStyle();
    void popEchoStyle();
};
