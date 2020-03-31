/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * Development of the code in this file was sponsored by Microbric Pty Ltd
 *
 * Author: Hontai Liu (hontai.liu@seeed.cc)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
 * The MIT License (MIT)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>

#include "py/nlr.h"
#include "py/runtime.h"
#include "modmachine.h"
#include "mphalport.h"

#include "wrapper_lcd.h"

extern const mp_obj_type_t machine_lcd_type;

m_generic_make(lcd)
{
    abstract_module_t *self = new_abstruct_module(type);
    mp_arg_check_num(n_args, n_kw, 0, 0, false);
    common_hal_lcd_construct(self);
    return self;
}

mp_obj_t lcd_fillScreen(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t color = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_fillScreen(self, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_fillScreen_obj, 1, lcd_fillScreen);

mp_obj_t lcd_setRotation(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t r = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setRotation(self, r);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setRotation_obj, 1, lcd_setRotation);

mp_obj_t lcd_getRotation(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t rotation = common_hal_lcd_getRotation(self);
    return MP_OBJ_NEW_SMALL_INT(rotation);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getRotation_obj, 0, lcd_getRotation);

mp_obj_t lcd_setTextFont(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t font = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextFont(self, font);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextFont_obj, 1, lcd_setTextFont);

mp_obj_t lcd_invertDisplay(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    bool i = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_invertDisplay(self, i);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_invertDisplay_obj, 1, lcd_invertDisplay);

mp_obj_t lcd_drawPixel(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t color = mp_obj_get_int(args[3]);

    common_hal_lcd_drawPixel(self, x, y, color);

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawPixel_obj, 4, 4, lcd_drawPixel);

mp_obj_t lcd_drawChar(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint16_t uniCode = mp_obj_get_int(args[1]);
    int32_t x = mp_obj_get_int(args[2]);
    int32_t y = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawChar(self, uniCode, x, y, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawChar_obj, 4, 5, lcd_drawChar);

mp_obj_t lcd_drawString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t poX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;

    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawString(self, string, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawString_obj, 4, 5, lcd_drawString);

mp_obj_t lcd_drawRightString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t dX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawRightString(self, string, dX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawRightString_obj, 4, 5, lcd_drawRightString);

mp_obj_t lcd_drawCentreString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t dX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawCentreString(self, string, dX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawCentreString_obj, 4, 5, lcd_drawCentreString);

mp_obj_t lcd_fontHeight(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint8_t font = 1;
    if (n_args == 2)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[1]);
    }
    int16_t xReturn = common_hal_lcd_fontHeight(self, font);
    return MP_OBJ_NEW_SMALL_INT(xReturn);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fontHeight_obj, 2, 3, lcd_fontHeight);

mp_obj_t lcd_textWidth(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    uint8_t font = 1;
    if (n_args == 2)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[1]);
    }
    int16_t xReturn = common_hal_lcd_textWidth(self, string, font);
    return MP_OBJ_NEW_SMALL_INT(xReturn);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_textWidth_obj, 2, 3, lcd_textWidth);

mp_obj_t lcd_drawNumber(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    long long_number = mp_obj_get_int(args[1]);
    int32_t poX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawNumber(self, long_number, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawNumber_obj, 4, 5, lcd_drawNumber);

mp_obj_t lcd_drawFloat(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    float floatNumber = mp_obj_get_float(args[1]);
    uint8_t decimal = mp_obj_get_int(args[2]);
    int32_t poX = mp_obj_get_int(args[3]);
    int32_t poY = mp_obj_get_int(args[4]);
    uint8_t font = 1;
    if (n_args == 5)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[5]);
    }
    common_hal_lcd_drawFloat(self, floatNumber, decimal, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawFloat_obj, 5, 6, lcd_drawFloat);


mp_obj_t lcd_setTextWrap(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    bool wrapX = mp_obj_get_int(args[1]);
    bool wrapY = false;
    if (n_args == 3)
    {
       wrapY = mp_obj_get_int(args[2]);
    }
 
    common_hal_lcd_setTextWrap(self, wrapX, wrapY);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_setTextWrap_obj, 2, 3, lcd_setTextWrap);

mp_obj_t lcd_setTextColor(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int16_t fgcolor = mp_obj_get_int(args[1]);
    int16_t bgcolor = 0;
    if (n_args == 3)
    {
       bgcolor = mp_obj_get_int(args[2]);
    }
 
    common_hal_lcd_setTextColor(self, fgcolor, bgcolor);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_setTextColor_obj, 2, 3, lcd_setTextColor);


mp_obj_t lcd_setTextSize(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t size = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextSize(self, size);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextSize_obj, 1, lcd_setTextSize);

mp_obj_t lcd_setTextDatum(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t datum = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextDatum(self, datum);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextDatum_obj, 1, lcd_setTextDatum);

mp_obj_t lcd_getTextDatum(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t datum = common_hal_lcd_getTextDatum(self);
    return MP_OBJ_NEW_SMALL_INT(datum);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getTextDatum_obj, 0, lcd_getTextDatum);

mp_obj_t lcd_setTextPadding(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t x_width = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextPadding(self, x_width);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextPadding_obj, 1, lcd_setTextPadding);

void lcd_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    abstract_module_t *self = (abstract_module_t *)(self_in);
    if (dest[0] == MP_OBJ_NULL)
    {
        if (attr == MP_QSTR_width)
        {
            dest[0] = mp_obj_new_int(common_hal_lcd_width(self));
            return;
        }
        else if (attr == MP_QSTR_height)
        {
            dest[0] = mp_obj_new_int(common_hal_lcd_height(self));
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

#ifdef MICROPY_PY_LVGL
DEFINE_PTR_OBJ(common_hal_lcd_monitor_flush);
#endif

const mp_rom_map_elem_t lcd_locals_dict_table[] = {
    // instance methods
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&lcd_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&lcd_obj___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR_fillSreen), MP_ROM_PTR(&lcd_fillScreen_obj)},
    {MP_ROM_QSTR(MP_QSTR_setRotation), MP_ROM_PTR(&lcd_setRotation_obj)},
    {MP_ROM_QSTR(MP_QSTR_getRotation), MP_ROM_PTR(&lcd_getRotation_obj)},
    {MP_ROM_QSTR(MP_QSTR_inverDisplay), MP_ROM_PTR(&lcd_invertDisplay_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawRightString), MP_ROM_PTR(&lcd_drawRightString_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawChar), MP_ROM_PTR(&lcd_drawChar_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawString), MP_ROM_PTR(&lcd_drawString_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawCentreString), MP_ROM_PTR(&lcd_drawCentreString_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextFont), MP_ROM_PTR(&lcd_setTextFont_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawPixel), MP_ROM_PTR(&lcd_drawPixel_obj)},
    {MP_ROM_QSTR(MP_QSTR_fontHeight), MP_ROM_PTR(&lcd_fontHeight_obj)},
    {MP_ROM_QSTR(MP_QSTR_textWidth), MP_ROM_PTR(&lcd_textWidth_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawNumber), MP_ROM_PTR(&lcd_drawNumber_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawFloat), MP_ROM_PTR(&lcd_drawFloat_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextColor), MP_ROM_PTR(&lcd_setTextColor_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextSize), MP_ROM_PTR(&lcd_setTextSize_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextWrap), MP_ROM_PTR(&lcd_setTextWrap_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextDatum), MP_ROM_PTR(&lcd_setTextDatum_obj)},
    {MP_ROM_QSTR(MP_QSTR_getTextDatum), MP_ROM_PTR(&lcd_getTextDatum_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextPadding), MP_ROM_PTR(&lcd_setTextPadding_obj)},
#ifdef MICROPY_PY_LVGL
    {MP_ROM_QSTR(MP_QSTR_flush), MP_ROM_PTR(&PTR_OBJ(common_hal_lcd_monitor_flush))},
#endif
};

MP_DEFINE_CONST_DICT(lcd_locals_dict, lcd_locals_dict_table);

const mp_obj_type_t machine_lcd_type = {
    {&mp_type_type},
    .name = MP_QSTR_LCD,
    .make_new = lcd_make_new,
    .locals_dict = (mp_obj_t)&lcd_locals_dict,
    .attr = lcd_obj_attr,
};
