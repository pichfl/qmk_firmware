// Copyright 2023 ziptyze
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define HAL_USE_I2C TRUE

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

#include_next <halconf.h>
