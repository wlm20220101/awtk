﻿/**
 * File:   fill_image_argb8888.c
 * Author: AWTK Develop Team
 * Brief:  fill on argb8888
 *
 * Copyright (c) 2018 - 2022  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-10-10 Generated by gen.sh(DONT MODIFY IT)
 *
 */
#ifndef TK_FILL_IMAGE_ARGB8888_H
#define TK_FILL_IMAGE_ARGB8888_H

#include "base/bitmap.h"

ret_t fill_argb8888_rect(bitmap_t* fb, const rect_t* dst, color_t c);

ret_t clear_argb8888_rect(bitmap_t* fb, const rect_t* dst, color_t c);

#endif /*TK_FILL_IMAGE_ARGB8888_H*/
