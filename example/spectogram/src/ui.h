/**
 * File: example/src/ui.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: UI example interface.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <string>

#include "specto/spectogram.h"

namespace example_ui {

void drawSpectogram(const specto::Spectogram&,
                    float durationInS,
                    const std::string& fontPath);

}  // namespace example_ui
