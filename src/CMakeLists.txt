cmake_minimum_required(VERSION 3.22)
project(sproutAmp VERSION 0.0.1)

juce_add_plugin(sproutAmp
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "JamesFerrarelli"
    COMPANY_WEBSITE "https://github.com/jsatof"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT TRUE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    VST3_COPY_DIR ${VST3_INSTALL_PREFIX}
    LV2_COPY_DIR ${LV2_INSTALL_PREFIX}
    AU_COPY_DIR ${AU_INSTALL_PREFIX}
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE JAMF
    PLUGIN_CODE SPRO
    FORMATS LV2
    PRODUCT_NAME "sproutAmp")

juce_generate_juce_header(sproutAmp)

target_sources(sproutAmp
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)

target_include_directories(sproutAmp
    PRIVATE
        .)

target_compile_definitions(sproutAmp
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(sproutAmp
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
