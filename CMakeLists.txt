cmake_minimum_required(VERSION 3.24.1)

project(DelayAudioPluginDemo VERSION 0.0.1)

set (CMAKE_CXX_STANDARD 17)

# Adds all the module sources so they appear correctly in the IDE
# Must be set before JUCE is added as a sub-dir (or any targets are made)
# https://github.com/juce-framework/JUCE/commit/6b1b4cf7f6b1008db44411f2c8887d71a3348889
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Create a /Modules directory in the IDE with the JUCE Module code
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Show all module sources in IDE projects" ON)

set(TargetName ${PROJECT_NAME})

# JUCE is setup as a submodule in the /JUCE folder
# Locally, you must run `git submodule update --init --recursive` once
# and later `git submodule update --remote --merge` to keep it up to date
# On Github Actions, this is done as a part of actions/checkout
add_subdirectory(JUCE)

# find_package(JUCE CONFIG REQUIRED)
juce_add_plugin(${TargetName}
    PLUGIN_MANUFACTURER_CODE SILA               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Dem0                            # A unique four-character plugin id with exactly one upper-case character
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "My Delay Plugin")

file(GLOB_RECURSE SourceFiles 
"${CMAKE_SOURCE_DIR}/Source/*.cpp"
"${CMAKE_SOURCE_DIR}/Source/*.h"
)

target_sources(${TargetName} PRIVATE ${SourceFiles})

source_group("Source Files" FILES 
    ${CMAKE_SOURCE_DIR}/Source/PluginEditor.h
    ${CMAKE_SOURCE_DIR}/Source/PluginEditor.cpp
    ${CMAKE_SOURCE_DIR}/Source/PluginProcessor.h
    ${CMAKE_SOURCE_DIR}/Source/PluginProcessor.cpp
)

source_group("Source Files/DSP" FILES 
    ${CMAKE_SOURCE_DIR}/Source/DSP/Delay.cpp
    ${CMAKE_SOURCE_DIR}/Source/DSP/Delay.h
    ${CMAKE_SOURCE_DIR}/Source/DSP/Gain.cpp
    ${CMAKE_SOURCE_DIR}/Source/DSP/Gain.h
)

source_group("Source Files/Other" FILES 
    ${CMAKE_SOURCE_DIR}/Source/Other/AudioHelpers.h
    ${CMAKE_SOURCE_DIR}/Source/Other/ParameterList.h
    ${CMAKE_SOURCE_DIR}/Source/Other/Preset_Manager.h
    ${CMAKE_SOURCE_DIR}/Source/Other/Preset_Manager.cpp
)

source_group("Source Files/UI" FILES 
    ${CMAKE_SOURCE_DIR}/Source/UI/MyLookAndFeel.h
    ${CMAKE_SOURCE_DIR}/Source/UI/UIDemensions.h
)

source_group("Source Files/UI/Panels" FILES 
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/FX_Panel.h
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/FX_Panel.cpp
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/Gain_Panel.h
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/Gain_Panel.cpp
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/Main_Panel.h
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/Main_Panel.cpp
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/Panel_Base.h
    ${CMAKE_SOURCE_DIR}/Source/UI/Panels/Panel_Base.cpp
)

source_group("Source Files/UI/UI_Units" FILES 
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/ParameterButton.h
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/ParameterButton.cpp
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/Rotary_Slider.h
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/Rotary_Slider.cpp
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/Slider_Text.h
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/Slider_Text.cpp
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/VU_Meter.h
    ${CMAKE_SOURCE_DIR}/Source/UI/UI_Units/VU_Meter.cpp
)

target_include_directories(${TargetName} PRIVATE 
    "${CMAKE_SOURCE_DIR}/Source"
    "${CMAKE_SOURCE_DIR}/Source/DSP"
    "${CMAKE_SOURCE_DIR}/Source/Other"
    "${CMAKE_SOURCE_DIR}/Source/UI"
    "${CMAKE_SOURCE_DIR}/Source/UI/Panels"
    "${CMAKE_SOURCE_DIR}/Source/UI/UI_Units")

# We don't want our source buried in extra nested folders
# set_target_properties("${PROJECT_NAME}" PROPERTIES FOLDER "")
target_compile_definitions(${TargetName}
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${TargetName}
    PRIVATE
    juce::juce_analytics
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_core
    juce::juce_data_structures
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_audio_utils
    juce::juce_dsp
    PUBLIC
    juce::juce_recommended_warning_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_config_flags)

# ----------------------------------------------------------------------------------------------------
# adding any custom modules you might have:
# add_subdirectory(Modules)

# optionally, we're also adding the unit tests:
# option(BUILD_UNIT_TESTS "Build JUCE prototype examples" OFF)

# if(BUILD_UNIT_TESTS)
# enable_testing()
# add_subdirectory(Tests)
# endif()