/*
  ==============================================================================

    UIDemensions.h
    Created: 8 Sep 2019 2:37:38pm
    Author:  Silver

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define MAIN_PANEL_WIDTH    600
#define MAIN_PANEL_HEIGHT   350

#define GAIN_PANEL_WIDTH    MAIN_PANEL_WIDTH / 4
#define GAIN_PANEL_HEIGHT   MAIN_PANEL_HEIGHT

#define FX_PANEL_WIDTH      MAIN_PANEL_WIDTH - (2 * GAIN_PANEL_WIDTH)
#define FX_PANEL_HEIGHT     MAIN_PANEL_HEIGHT

#define SLIDER_SIZE         90
#define SLIDER_POS_X        40
#define SLIDER_POS_Y        70
#define SLIDER_INTERVAL     40

#define VUMETER_WIDTH       SLIDER_SIZE / 3
