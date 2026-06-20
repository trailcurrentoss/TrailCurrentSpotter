#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_page_drive() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_drive = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // drive_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.drive_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_top_status_bar(obj, 5);
        }
        {
            // drive_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.drive_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 800, 368);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // drive_card_bat
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_card_bat = obj;
                    lv_obj_set_pos(obj, 8, 8);
                    lv_obj_set_size(obj, 256, 280);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_bat_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_bat_title = obj;
                            lv_obj_set_pos(obj, 0, 12);
                            lv_obj_set_size(obj, 256, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "BATTERY");
                        }
                        {
                            // drive_bat_arc
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.drive_bat_arc = obj;
                            lv_obj_set_pos(obj, 33, 36);
                            lv_obj_set_size(obj, 190, 190);
                            lv_arc_set_value(obj, 87);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_arc_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 14, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_rounded(obj, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                        }
                        {
                            // drive_bat_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_bat_value = obj;
                            lv_obj_set_pos(obj, 58, 101);
                            lv_obj_set_size(obj, 100, 60);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "87");
                        }
                        {
                            // drive_bat_pct_sym
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_bat_pct_sym = obj;
                            lv_obj_set_pos(obj, 164, 119);
                            lv_obj_set_size(obj, 30, 28);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "%");
                        }
                        {
                            // drive_bat_volts
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_bat_volts = obj;
                            lv_obj_set_pos(obj, 33, 163);
                            lv_obj_set_size(obj, 190, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "12.9 V");
                        }
                        {
                            // drive_bat_remain
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_bat_remain = obj;
                            lv_obj_set_pos(obj, 0, 248);
                            lv_obj_set_size(obj, 256, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "13h 40m left");
                        }
                    }
                }
                {
                    // drive_card_tires
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_card_tires = obj;
                    lv_obj_set_pos(obj, 272, 8);
                    lv_obj_set_size(obj, 256, 280);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_tire_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_tire_title = obj;
                            lv_obj_set_pos(obj, 0, 14);
                            lv_obj_set_size(obj, 256, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "TIRE PRESSURE");
                        }
                        {
                            // drive_tire_sub
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_tire_sub = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 256, 16);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Tandem | Target 65 PSI");
                        }
                        {
                            // drive_tire_l1
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_tire_l1 = obj;
                            lv_obj_set_pos(obj, 14, 64);
                            lv_obj_set_size(obj, 110, 90);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // drive_tire_l1_psi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_l1_psi = obj;
                                    lv_obj_set_pos(obj, 0, 16);
                                    lv_obj_set_size(obj, 110, 36);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "63");
                                }
                                {
                                    // drive_tire_l1_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_l1_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 60);
                                    lv_obj_set_size(obj, 110, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "L1 | 86F");
                                }
                            }
                        }
                        {
                            // drive_tire_r1
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_tire_r1 = obj;
                            lv_obj_set_pos(obj, 132, 64);
                            lv_obj_set_size(obj, 110, 90);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // drive_tire_r1_psi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_r1_psi = obj;
                                    lv_obj_set_pos(obj, 0, 16);
                                    lv_obj_set_size(obj, 110, 36);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "65");
                                }
                                {
                                    // drive_tire_r1_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_r1_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 60);
                                    lv_obj_set_size(obj, 110, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "R1 | 89F");
                                }
                            }
                        }
                        {
                            // drive_tire_l2
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_tire_l2 = obj;
                            lv_obj_set_pos(obj, 14, 162);
                            lv_obj_set_size(obj, 110, 90);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // drive_tire_l2_psi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_l2_psi = obj;
                                    lv_obj_set_pos(obj, 0, 16);
                                    lv_obj_set_size(obj, 110, 36);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "65");
                                }
                                {
                                    // drive_tire_l2_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_l2_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 60);
                                    lv_obj_set_size(obj, 110, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "L2 | 88F");
                                }
                            }
                        }
                        {
                            // drive_tire_r2
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_tire_r2 = obj;
                            lv_obj_set_pos(obj, 132, 162);
                            lv_obj_set_size(obj, 110, 90);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // drive_tire_r2_psi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_r2_psi = obj;
                                    lv_obj_set_pos(obj, 0, 16);
                                    lv_obj_set_size(obj, 110, 36);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "58");
                                }
                                {
                                    // drive_tire_r2_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_tire_r2_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 60);
                                    lv_obj_set_size(obj, 110, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "R2 | 96F");
                                }
                            }
                        }
                        {
                            // drive_bsm_warning
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_bsm_warning = obj;
                            lv_obj_set_pos(obj, 8, 8);
                            lv_obj_set_size(obj, 240, 26);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // drive_bsm_warn_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_bsm_warn_icon = obj;
                                    lv_obj_set_pos(obj, 8, 3);
                                    lv_obj_set_size(obj, 20, 20);
                                    add_style_label_fa16_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // drive_bsm_warn_text
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.drive_bsm_warn_text = obj;
                                    lv_obj_set_pos(obj, 34, 5);
                                    lv_obj_set_size(obj, 198, 16);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "VEHICLE IN BLIND SPOT");
                                }
                            }
                        }
                    }
                }
                {
                    // drive_card_solar
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_card_solar = obj;
                    lv_obj_set_pos(obj, 536, 8);
                    lv_obj_set_size(obj, 256, 280);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_solar_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_solar_title = obj;
                            lv_obj_set_pos(obj, 0, 12);
                            lv_obj_set_size(obj, 256, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SOLAR");
                        }
                        {
                            // drive_solar_arc
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.drive_solar_arc = obj;
                            lv_obj_set_pos(obj, 33, 36);
                            lv_obj_set_size(obj, 190, 190);
                            lv_arc_set_value(obj, 70);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_arc_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffc107), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 14, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_rounded(obj, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                        }
                        {
                            // drive_solar_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_solar_icon = obj;
                            lv_obj_set_pos(obj, 110, 71);
                            lv_obj_set_size(obj, 36, 36);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_solar_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_solar_value = obj;
                            lv_obj_set_pos(obj, 58, 115);
                            lv_obj_set_size(obj, 100, 50);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "410");
                        }
                        {
                            // drive_solar_unit_sym
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_solar_unit_sym = obj;
                            lv_obj_set_pos(obj, 164, 127);
                            lv_obj_set_size(obj, 30, 24);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "W");
                        }
                        {
                            // drive_solar_units_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_solar_units_label = obj;
                            lv_obj_set_pos(obj, 33, 167);
                            lv_obj_set_size(obj, 190, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "watts in");
                        }
                        {
                            // drive_solar_pct
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_solar_pct = obj;
                            lv_obj_set_pos(obj, 0, 248);
                            lv_obj_set_size(obj, 256, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "70% of capacity");
                        }
                    }
                }
                {
                    // drive_chip_run
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_run = obj;
                    lv_obj_set_pos(obj, 8, 296);
                    lv_obj_set_size(obj, 152, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 140, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_run_icon
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_chip_run_icon = obj;
                            lv_obj_set_pos(obj, 71, 12);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // drive_chip_run_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_run_lbl = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 152, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "RUNNING");
                        }
                    }
                }
                {
                    // drive_chip_left
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_left = obj;
                    lv_obj_set_pos(obj, 166, 296);
                    lv_obj_set_size(obj, 152, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 140, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_left_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_left_icon = obj;
                            lv_obj_set_pos(obj, 66, 6);
                            lv_obj_set_size(obj, 20, 20);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_chip_left_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_left_lbl = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 152, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "LEFT");
                        }
                    }
                }
                {
                    // drive_chip_brake
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_brake = obj;
                    lv_obj_set_pos(obj, 324, 296);
                    lv_obj_set_size(obj, 152, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 140, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_brake_icon
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_chip_brake_icon = obj;
                            lv_obj_set_pos(obj, 71, 12);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // drive_chip_brake_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_brake_lbl = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 152, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "BRAKE");
                        }
                    }
                }
                {
                    // drive_chip_right
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_right = obj;
                    lv_obj_set_pos(obj, 482, 296);
                    lv_obj_set_size(obj, 152, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 140, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_right_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_right_icon = obj;
                            lv_obj_set_pos(obj, 66, 6);
                            lv_obj_set_size(obj, 20, 20);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_chip_right_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_right_lbl = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 152, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "RIGHT");
                        }
                    }
                }
                {
                    // drive_chip_rev
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_rev = obj;
                    lv_obj_set_pos(obj, 640, 296);
                    lv_obj_set_size(obj, 152, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 140, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_rev_icon
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.drive_chip_rev_icon = obj;
                            lv_obj_set_pos(obj, 71, 12);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // drive_chip_rev_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_rev_lbl = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 152, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "REVERSE");
                        }
                    }
                }
            }
        }
        {
            // drive_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.drive_dock = obj;
            lv_obj_set_pos(obj, 0, 414);
            lv_obj_set_size(obj, 800, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_tab_bar(obj, 65);
        }
    }
    
    tick_screen_page_drive();
}

void tick_screen_page_drive() {
    tick_user_widget_top_status_bar(5);
    tick_user_widget_bottom_tab_bar(65);
}

void create_screen_page_lights() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_lights = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // lights_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.lights_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_top_status_bar(obj, 79);
        }
        {
            // lights_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.lights_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 800, 368);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // lights_header
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.lights_header = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 800, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // lights_prev_zone
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_prev_zone = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 48, 44);
                            lv_obj_add_event_cb(obj, action_prev_zone, LV_EVENT_CLICKED, (void *)0);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_prev_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_prev_icon = obj;
                                    lv_obj_set_pos(obj, 0, 11);
                                    lv_obj_set_size(obj, 48, 22);
                                    add_style_label_fa16_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // lights_zone_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.lights_zone_icon = obj;
                            lv_obj_set_pos(obj, 309, 19);
                            lv_obj_set_size(obj, 22, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // lights_zone_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.lights_zone_name = obj;
                            lv_obj_set_pos(obj, 250, 12);
                            lv_obj_set_size(obj, 200, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Galley");
                        }
                        {
                            // lights_zone_meta
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.lights_zone_meta = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 800, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Zone 1 of 6 | 1 on");
                        }
                        {
                            // lights_next_zone
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_next_zone = obj;
                            lv_obj_set_pos(obj, 740, 8);
                            lv_obj_set_size(obj, 48, 44);
                            lv_obj_add_event_cb(obj, action_next_zone, LV_EVENT_CLICKED, (void *)0);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_next_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_next_icon = obj;
                                    lv_obj_set_pos(obj, 0, 11);
                                    lv_obj_set_size(obj, 48, 22);
                                    add_style_label_fa16_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                    }
                }
                {
                    // lights_grid
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.lights_grid = obj;
                    lv_obj_set_pos(obj, 0, 60);
                    lv_obj_set_size(obj, 800, 248);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // lights_btn_1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_btn_1 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 383, 70);
                            lv_obj_add_event_cb(obj, action_toggle_light, LV_EVENT_CLICKED, (void *)1);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_btn_1_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_1_icon = obj;
                                    lv_obj_set_pos(obj, 14, 17);
                                    lv_obj_set_size(obj, 36, 36);
                                    add_style_label_fa32_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // lights_btn_1_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_1_name = obj;
                                    lv_obj_set_pos(obj, 64, 14);
                                    lv_obj_set_size(obj, 305, 22);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Light 1");
                                }
                                {
                                    // lights_btn_1_state
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_1_state = obj;
                                    lv_obj_set_pos(obj, 64, 42);
                                    lv_obj_set_size(obj, 305, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Off");
                                }
                            }
                        }
                        {
                            // lights_btn_2
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_btn_2 = obj;
                            lv_obj_set_pos(obj, 405, 8);
                            lv_obj_set_size(obj, 383, 70);
                            lv_obj_add_event_cb(obj, action_toggle_light, LV_EVENT_CLICKED, (void *)2);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_btn_2_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_2_icon = obj;
                                    lv_obj_set_pos(obj, 14, 17);
                                    lv_obj_set_size(obj, 36, 36);
                                    add_style_label_fa32_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // lights_btn_2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_2_name = obj;
                                    lv_obj_set_pos(obj, 64, 14);
                                    lv_obj_set_size(obj, 305, 22);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Light 2");
                                }
                                {
                                    // lights_btn_2_state
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_2_state = obj;
                                    lv_obj_set_pos(obj, 64, 42);
                                    lv_obj_set_size(obj, 305, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Off");
                                }
                            }
                        }
                        {
                            // lights_btn_3
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_btn_3 = obj;
                            lv_obj_set_pos(obj, 12, 88);
                            lv_obj_set_size(obj, 383, 70);
                            lv_obj_add_event_cb(obj, action_toggle_light, LV_EVENT_CLICKED, (void *)3);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_btn_3_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_3_icon = obj;
                                    lv_obj_set_pos(obj, 14, 17);
                                    lv_obj_set_size(obj, 36, 36);
                                    add_style_label_fa32_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // lights_btn_3_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_3_name = obj;
                                    lv_obj_set_pos(obj, 64, 14);
                                    lv_obj_set_size(obj, 305, 22);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Light 3");
                                }
                                {
                                    // lights_btn_3_state
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_3_state = obj;
                                    lv_obj_set_pos(obj, 64, 42);
                                    lv_obj_set_size(obj, 305, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Off");
                                }
                            }
                        }
                        {
                            // lights_btn_4
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_btn_4 = obj;
                            lv_obj_set_pos(obj, 405, 88);
                            lv_obj_set_size(obj, 383, 70);
                            lv_obj_add_event_cb(obj, action_toggle_light, LV_EVENT_CLICKED, (void *)4);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_btn_4_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_4_icon = obj;
                                    lv_obj_set_pos(obj, 14, 17);
                                    lv_obj_set_size(obj, 36, 36);
                                    add_style_label_fa32_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // lights_btn_4_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_4_name = obj;
                                    lv_obj_set_pos(obj, 64, 14);
                                    lv_obj_set_size(obj, 305, 22);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Light 4");
                                }
                                {
                                    // lights_btn_4_state
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_4_state = obj;
                                    lv_obj_set_pos(obj, 64, 42);
                                    lv_obj_set_size(obj, 305, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Off");
                                }
                            }
                        }
                        {
                            // lights_btn_5
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_btn_5 = obj;
                            lv_obj_set_pos(obj, 12, 168);
                            lv_obj_set_size(obj, 383, 70);
                            lv_obj_add_event_cb(obj, action_toggle_light, LV_EVENT_CLICKED, (void *)5);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_btn_5_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_5_icon = obj;
                                    lv_obj_set_pos(obj, 14, 17);
                                    lv_obj_set_size(obj, 36, 36);
                                    add_style_label_fa32_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // lights_btn_5_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_5_name = obj;
                                    lv_obj_set_pos(obj, 64, 14);
                                    lv_obj_set_size(obj, 305, 22);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Light 5");
                                }
                                {
                                    // lights_btn_5_state
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_5_state = obj;
                                    lv_obj_set_pos(obj, 64, 42);
                                    lv_obj_set_size(obj, 305, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Off");
                                }
                            }
                        }
                        {
                            // lights_btn_6
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_btn_6 = obj;
                            lv_obj_set_pos(obj, 405, 168);
                            lv_obj_set_size(obj, 383, 70);
                            lv_obj_add_event_cb(obj, action_toggle_light, LV_EVENT_CLICKED, (void *)6);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_btn_6_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_6_icon = obj;
                                    lv_obj_set_pos(obj, 14, 17);
                                    lv_obj_set_size(obj, 36, 36);
                                    add_style_label_fa32_icon(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // lights_btn_6_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_6_name = obj;
                                    lv_obj_set_pos(obj, 64, 14);
                                    lv_obj_set_size(obj, 305, 22);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Light 6");
                                }
                                {
                                    // lights_btn_6_state
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_btn_6_state = obj;
                                    lv_obj_set_pos(obj, 64, 42);
                                    lv_obj_set_size(obj, 305, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Off");
                                }
                            }
                        }
                    }
                }
                {
                    // lights_footer
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.lights_footer = obj;
                    lv_obj_set_pos(obj, 0, 308);
                    lv_obj_set_size(obj, 800, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // lights_all_on
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_all_on = obj;
                            lv_obj_set_pos(obj, 12, 10);
                            lv_obj_set_size(obj, 110, 40);
                            lv_obj_add_event_cb(obj, action_zone_all_on, LV_EVENT_CLICKED, (void *)0);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_all_on_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_all_on_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 11);
                                    lv_obj_set_size(obj, 110, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "All On");
                                }
                            }
                        }
                        {
                            // lights_all_off
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_all_off = obj;
                            lv_obj_set_pos(obj, 130, 10);
                            lv_obj_set_size(obj, 110, 40);
                            lv_obj_add_event_cb(obj, action_zone_all_off, LV_EVENT_CLICKED, (void *)0);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_all_off_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_all_off_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 11);
                                    lv_obj_set_size(obj, 110, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "All Off");
                                }
                            }
                        }
                        {
                            // lights_dot_0
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_dot_0 = obj;
                            lv_obj_set_pos(obj, 340, 25);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_dot_1
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_dot_1 = obj;
                            lv_obj_set_pos(obj, 362, 25);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_dot_2
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_dot_2 = obj;
                            lv_obj_set_pos(obj, 384, 25);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_dot_3
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_dot_3 = obj;
                            lv_obj_set_pos(obj, 406, 25);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_dot_4
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_dot_4 = obj;
                            lv_obj_set_pos(obj, 428, 25);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_dot_5
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_dot_5 = obj;
                            lv_obj_set_pos(obj, 450, 25);
                            lv_obj_set_size(obj, 10, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_off_all_devices
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.lights_off_all_devices = obj;
                            lv_obj_set_pos(obj, 658, 10);
                            lv_obj_set_size(obj, 130, 40);
                            lv_obj_add_event_cb(obj, action_all_lights_off, LV_EVENT_CLICKED, (void *)0);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lights_off_all_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lights_off_all_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 11);
                                    lv_obj_set_size(obj, 130, 18);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Off | All");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // lights_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.lights_dock = obj;
            lv_obj_set_pos(obj, 0, 414);
            lv_obj_set_size(obj, 800, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_tab_bar(obj, 137);
        }
    }
    
    tick_screen_page_lights();
}

void tick_screen_page_lights() {
    tick_user_widget_top_status_bar(79);
    tick_user_widget_bottom_tab_bar(137);
}

void create_screen_page_alarms() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_alarms = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // alarms_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.alarms_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_top_status_bar(obj, 151);
        }
        {
            // alarms_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.alarms_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 800, 368);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // alarms_header
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.alarms_header = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 800, 56);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // alarms_title
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_title = obj;
                            lv_obj_set_pos(obj, 14, 8);
                            lv_obj_set_size(obj, 400, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Alarm Triggers");
                        }
                        {
                            // alarms_subtitle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_subtitle = obj;
                            lv_obj_set_pos(obj, 14, 32);
                            lv_obj_set_size(obj, 400, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "What raises an alarm while driving");
                        }
                        {
                            // alarms_armed_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_armed_icon = obj;
                            lv_obj_set_pos(obj, 600, 18);
                            lv_obj_set_size(obj, 20, 20);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // alarms_armed_count
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_armed_count = obj;
                            lv_obj_set_pos(obj, 625, 19);
                            lv_obj_set_size(obj, 160, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 / 0 armed");
                        }
                    }
                }
                {
                    // alarms_list
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.alarms_list = obj;
                    lv_obj_set_pos(obj, 0, 56);
                    lv_obj_set_size(obj, 800, 312);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // alarms_grp_lbl_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_lbl_0 = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 300, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "DOORS & CABINETS");
                        }
                        {
                            // alarms_grp_desc_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_desc_0 = obj;
                            lv_obj_set_pos(obj, 506, 12);
                            lv_obj_set_size(obj, 280, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Alarm if opened");
                        }
                        {
                            // alarm_galley_cab_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_galley_cab_row = obj;
                            lv_obj_set_pos(obj, 14, 38);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_galley_cab_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_galley_cab_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Galley Cabinet");
                                }
                                {
                                    // alarm_galley_cab
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_galley_cab = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_pantry_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_pantry_row = obj;
                            lv_obj_set_pos(obj, 14, 94);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_pantry_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_pantry_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Pantry Door");
                                }
                                {
                                    // alarm_pantry
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_pantry = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)1);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_wardrobe_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_wardrobe_row = obj;
                            lv_obj_set_pos(obj, 14, 150);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_wardrobe_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_wardrobe_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Wardrobe");
                                }
                                {
                                    // alarm_wardrobe
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_wardrobe = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)2);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_bath_door_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_bath_door_row = obj;
                            lv_obj_set_pos(obj, 14, 206);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_bath_door_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_bath_door_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Bathroom Door");
                                }
                                {
                                    // alarm_bath_door
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_bath_door = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)3);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_entry_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_entry_row = obj;
                            lv_obj_set_pos(obj, 14, 262);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_entry_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_entry_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Main Entry Door");
                                }
                                {
                                    // alarm_entry
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_entry = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)4);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_pass_thru_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_pass_thru_row = obj;
                            lv_obj_set_pos(obj, 14, 318);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_pass_thru_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_pass_thru_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Pass-Thru Storage");
                                }
                                {
                                    // alarm_pass_thru
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_pass_thru = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)5);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarms_grp_lbl_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_lbl_6 = obj;
                            lv_obj_set_pos(obj, 14, 384);
                            lv_obj_set_size(obj, 300, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "LIGHTING");
                        }
                        {
                            // alarms_grp_desc_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_desc_6 = obj;
                            lv_obj_set_pos(obj, 506, 384);
                            lv_obj_set_size(obj, 280, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Alarm if left on");
                        }
                        {
                            // alarm_bath_light_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_bath_light_row = obj;
                            lv_obj_set_pos(obj, 14, 410);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_bath_light_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_bath_light_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Bathroom Light");
                                }
                                {
                                    // alarm_bath_light
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_bath_light = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_porch_light_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_porch_light_row = obj;
                            lv_obj_set_pos(obj, 14, 466);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_porch_light_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_porch_light_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Porch Light");
                                }
                                {
                                    // alarm_porch_light
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_porch_light = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)7);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_galley_light_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_galley_light_row = obj;
                            lv_obj_set_pos(obj, 14, 522);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_galley_light_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_galley_light_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Galley Light");
                                }
                                {
                                    // alarm_galley_light
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_galley_light = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarms_grp_lbl_9
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_lbl_9 = obj;
                            lv_obj_set_pos(obj, 14, 588);
                            lv_obj_set_size(obj, 300, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "APPLIANCES");
                        }
                        {
                            // alarms_grp_desc_9
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_desc_9 = obj;
                            lv_obj_set_pos(obj, 506, 588);
                            lv_obj_set_size(obj, 280, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Alarm if running");
                        }
                        {
                            // alarm_fridge_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_fridge_row = obj;
                            lv_obj_set_pos(obj, 14, 614);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_fridge_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_fridge_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Refrigerator");
                                }
                                {
                                    // alarm_fridge
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_fridge = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)9);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_pump_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_pump_row = obj;
                            lv_obj_set_pos(obj, 14, 670);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_pump_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_pump_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Water Pump");
                                }
                                {
                                    // alarm_pump
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_pump = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_heater_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_heater_row = obj;
                            lv_obj_set_pos(obj, 14, 726);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_heater_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_heater_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Water Heater");
                                }
                                {
                                    // alarm_heater
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_heater = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)11);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_inverter_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_inverter_row = obj;
                            lv_obj_set_pos(obj, 14, 782);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_inverter_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_inverter_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Inverter");
                                }
                                {
                                    // alarm_inverter
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_inverter = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)12);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarms_grp_lbl_13
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_lbl_13 = obj;
                            lv_obj_set_pos(obj, 14, 848);
                            lv_obj_set_size(obj, 300, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SAFETY");
                        }
                        {
                            // alarms_grp_desc_13
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarms_grp_desc_13 = obj;
                            lv_obj_set_pos(obj, 506, 848);
                            lv_obj_set_size(obj, 280, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Always recommended");
                        }
                        {
                            // alarm_co2_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_co2_row = obj;
                            lv_obj_set_pos(obj, 14, 874);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_co2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_co2_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "High CO2");
                                }
                                {
                                    // alarm_co2
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_co2 = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)13);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_smoke_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_smoke_row = obj;
                            lv_obj_set_pos(obj, 14, 930);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_smoke_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_smoke_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 400, 20);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Smoke / LP Gas");
                                }
                                {
                                    // alarm_smoke
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_smoke = obj;
                                    lv_obj_set_pos(obj, 724, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_alarm, LV_EVENT_VALUE_CHANGED, (void *)14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // alarms_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.alarms_dock = obj;
            lv_obj_set_pos(obj, 0, 414);
            lv_obj_set_size(obj, 800, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_tab_bar(obj, 222);
        }
    }
    
    tick_screen_page_alarms();
}

void tick_screen_page_alarms() {
    tick_user_widget_top_status_bar(151);
    tick_user_widget_bottom_tab_bar(222);
}

void create_screen_page_setup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_setup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // setup_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.setup_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_top_status_bar(obj, 236);
        }
        {
            // setup_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.setup_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 800, 368);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // setup_axle_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.setup_axle_title = obj;
                    lv_obj_set_pos(obj, 14, 10);
                    lv_obj_set_size(obj, 772, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "AXLE CONFIGURATION");
                }
                {
                    // setup_axle_single
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.setup_axle_single = obj;
                    lv_obj_set_pos(obj, 14, 34);
                    lv_obj_set_size(obj, 250, 78);
                    lv_obj_add_event_cb(obj, action_set_axle_count, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_axle_single_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_axle_single_lbl = obj;
                            lv_obj_set_pos(obj, 0, 18);
                            lv_obj_set_size(obj, 250, 26);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Single");
                        }
                        {
                            // setup_axle_single_sub
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_axle_single_sub = obj;
                            lv_obj_set_pos(obj, 0, 48);
                            lv_obj_set_size(obj, 250, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "2 tires");
                        }
                    }
                }
                {
                    // setup_axle_tandem
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.setup_axle_tandem = obj;
                    lv_obj_set_pos(obj, 274, 34);
                    lv_obj_set_size(obj, 250, 78);
                    lv_obj_add_event_cb(obj, action_set_axle_count, LV_EVENT_CLICKED, (void *)2);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_axle_tandem_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_axle_tandem_lbl = obj;
                            lv_obj_set_pos(obj, 0, 18);
                            lv_obj_set_size(obj, 250, 26);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Tandem");
                        }
                        {
                            // setup_axle_tandem_sub
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_axle_tandem_sub = obj;
                            lv_obj_set_pos(obj, 0, 48);
                            lv_obj_set_size(obj, 250, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "4 tires");
                        }
                    }
                }
                {
                    // setup_axle_triple
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.setup_axle_triple = obj;
                    lv_obj_set_pos(obj, 534, 34);
                    lv_obj_set_size(obj, 250, 78);
                    lv_obj_add_event_cb(obj, action_set_axle_count, LV_EVENT_CLICKED, (void *)3);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_axle_triple_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_axle_triple_lbl = obj;
                            lv_obj_set_pos(obj, 0, 18);
                            lv_obj_set_size(obj, 250, 26);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Triple");
                        }
                        {
                            // setup_axle_triple_sub
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_axle_triple_sub = obj;
                            lv_obj_set_pos(obj, 0, 48);
                            lv_obj_set_size(obj, 250, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "6 tires");
                        }
                    }
                }
                {
                    // setup_brake_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.setup_brake_title = obj;
                    lv_obj_set_pos(obj, 14, 128);
                    lv_obj_set_size(obj, 772, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "BRAKING & SAFETY");
                }
                {
                    // setup_brakes_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_brakes_row = obj;
                    lv_obj_set_pos(obj, 14, 152);
                    lv_obj_set_size(obj, 772, 54);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_brakes_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_brakes_icon = obj;
                            lv_obj_set_pos(obj, 14, 16);
                            lv_obj_set_size(obj, 24, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_brakes_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_brakes_name = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 500, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Electric Trailer Brakes");
                        }
                        {
                            // setup_brakes_desc
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_brakes_desc = obj;
                            lv_obj_set_pos(obj, 48, 32);
                            lv_obj_set_size(obj, 500, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Brake-controller output & gain");
                        }
                        {
                            // setup_brakes_sw
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.setup_brakes_sw = obj;
                            lv_obj_set_pos(obj, 722, 13);
                            lv_obj_set_size(obj, 50, 28);
                            lv_obj_add_event_cb(obj, action_toggle_brakes, LV_EVENT_VALUE_CHANGED, (void *)0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_switch_default(obj);
                        }
                    }
                }
                {
                    // setup_breakaway_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_breakaway_row = obj;
                    lv_obj_set_pos(obj, 14, 214);
                    lv_obj_set_size(obj, 772, 54);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_breakaway_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_breakaway_icon = obj;
                            lv_obj_set_pos(obj, 14, 16);
                            lv_obj_set_size(obj, 24, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_breakaway_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_breakaway_name = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 500, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Breakaway Switch");
                        }
                        {
                            // setup_breakaway_desc
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_breakaway_desc = obj;
                            lv_obj_set_pos(obj, 48, 32);
                            lv_obj_set_size(obj, 500, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Triggers brakes if trailer disconnects");
                        }
                        {
                            // setup_breakaway_sw
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.setup_breakaway_sw = obj;
                            lv_obj_set_pos(obj, 722, 13);
                            lv_obj_set_size(obj, 50, 28);
                            lv_obj_add_event_cb(obj, action_toggle_breakaway, LV_EVENT_VALUE_CHANGED, (void *)0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_switch_default(obj);
                        }
                    }
                }
                {
                    // setup_theme_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.setup_theme_title = obj;
                    lv_obj_set_pos(obj, 14, 284);
                    lv_obj_set_size(obj, 772, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "DISPLAY THEME");
                }
                {
                    // setup_theme_light
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.setup_theme_light = obj;
                    lv_obj_set_pos(obj, 14, 308);
                    lv_obj_set_size(obj, 381, 62);
                    lv_obj_add_event_cb(obj, action_change_theme, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_theme_light_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_theme_light_icon = obj;
                            lv_obj_set_pos(obj, 24, 20);
                            lv_obj_set_size(obj, 22, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_theme_light_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_theme_light_lbl = obj;
                            lv_obj_set_pos(obj, 60, 20);
                            lv_obj_set_size(obj, 307, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Light Theme");
                        }
                    }
                }
                {
                    // setup_theme_dark
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.setup_theme_dark = obj;
                    lv_obj_set_pos(obj, 405, 308);
                    lv_obj_set_size(obj, 381, 62);
                    lv_obj_add_event_cb(obj, action_change_theme, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_theme_dark_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_theme_dark_icon = obj;
                            lv_obj_set_pos(obj, 24, 20);
                            lv_obj_set_size(obj, 22, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_theme_dark_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_theme_dark_lbl = obj;
                            lv_obj_set_pos(obj, 60, 20);
                            lv_obj_set_size(obj, 307, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Dark Theme");
                        }
                    }
                }
                {
                    // setup_info_banner
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_info_banner = obj;
                    lv_obj_set_pos(obj, 14, 386);
                    lv_obj_set_size(obj, 772, 40);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_info_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_info_icon = obj;
                            lv_obj_set_pos(obj, 14, 10);
                            lv_obj_set_size(obj, 20, 20);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_info_text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_info_text = obj;
                            lv_obj_set_pos(obj, 42, 11);
                            lv_obj_set_size(obj, 716, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Light and alarm tabs are on the bar below.");
                        }
                    }
                }
            }
        }
        {
            // setup_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.setup_dock = obj;
            lv_obj_set_pos(obj, 0, 414);
            lv_obj_set_size(obj, 800, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_tab_bar(obj, 279);
        }
    }
    
    tick_screen_page_setup();
}

void tick_screen_page_setup() {
    tick_user_widget_top_status_bar(236);
    tick_user_widget_bottom_tab_bar(279);
}

void create_user_widget_top_status_bar(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // root
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 46);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // status_brand_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 12, 12);
                    lv_obj_set_size(obj, 22, 22);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // status_brand_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 40, 14);
                    lv_obj_set_size(obj, 90, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "SPOTTER");
                }
                {
                    // status_link_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 142, 18);
                    lv_obj_set_size(obj, 10, 10);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_min_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_max_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_min_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_max_height(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // status_link_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 158, 14);
                    lv_obj_set_size(obj, 220, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "TANDEM | Linked");
                }
                {
                    // status_signal_left
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                    lv_obj_set_pos(obj, 566, 12);
                    lv_obj_set_size(obj, 22, 22);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // status_signal_right
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                    lv_obj_set_pos(obj, 594, 12);
                    lv_obj_set_size(obj, 22, 22);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffc107), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // status_speed_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                    lv_obj_set_pos(obj, 630, 12);
                    lv_obj_set_size(obj, 50, 22);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0");
                }
                {
                    // status_speed_unit
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                    lv_obj_set_pos(obj, 682, 20);
                    lv_obj_set_size(obj, 38, 14);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "MPH");
                }
                {
                    // status_time
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                    lv_obj_set_pos(obj, 728, 14);
                    lv_obj_set_size(obj, 60, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--:--");
                }
            }
        }
    }
}

void tick_user_widget_top_status_bar(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void create_user_widget_bottom_tab_bar(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // root
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 66);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 66, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 66, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dock_btn_drive
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 200, 66);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_drive_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                            lv_obj_set_pos(obj, 82, 8);
                            lv_obj_set_size(obj, 36, 36);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_drive_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 0, 48);
                            lv_obj_set_size(obj, 200, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Drive");
                        }
                    }
                }
                {
                    // dock_btn_lights
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 200, 0);
                    lv_obj_set_size(obj, 200, 66);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_lights_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 82, 8);
                            lv_obj_set_size(obj, 36, 36);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_lights_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                            lv_obj_set_pos(obj, 0, 48);
                            lv_obj_set_size(obj, 200, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Lights");
                        }
                    }
                }
                {
                    // dock_btn_alarms
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                    lv_obj_set_pos(obj, 400, 0);
                    lv_obj_set_size(obj, 200, 66);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)2);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_alarms_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                            lv_obj_set_pos(obj, 82, 8);
                            lv_obj_set_size(obj, 36, 36);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_alarms_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 0, 48);
                            lv_obj_set_size(obj, 200, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Alarms");
                        }
                    }
                }
                {
                    // dock_btn_setup
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                    lv_obj_set_pos(obj, 600, 0);
                    lv_obj_set_size(obj, 200, 66);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)3);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_setup_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                            lv_obj_set_pos(obj, 82, 8);
                            lv_obj_set_size(obj, 36, 36);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_setup_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                            lv_obj_set_pos(obj, 0, 48);
                            lv_obj_set_size(obj, 200, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Setup");
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_bottom_tab_bar(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void change_color_theme(uint32_t theme_index) {
    active_theme_index = theme_index;
    
    lv_style_set_bg_color(get_style_arc_default_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_arc_color(get_style_arc_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_arc_color(get_style_arc_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_bar_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_bar_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_bar_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_button_circle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_text_color(get_style_button_circle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_button_list_menu_item_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_bg_color(get_style_button_list_menu_item_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_text_color(get_style_button_navbar_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_border_color(get_style_button_navbar_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_button_navbar_active_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_text_color(get_style_button_navbar_in_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_border_color(get_style_button_navbar_in_active_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_button_navbar_in_active_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_checkbox_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_checkbox_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_checkbox_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_checkbox_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_text_color(get_style_checkbox_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_bg_color(get_style_default_button_matrix_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_text_color(get_style_default_button_matrix_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_bg_color(get_style_default_button_matrix_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_default_button_matrix_ITEMS_CHECKED(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_bg_color(get_style_keyboard_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_bg_color(get_style_keyboard_default_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_led_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_led_default_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_text_color(get_style_label_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_label_default_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_text_color(get_style_label_fa16_icon_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_label_fa16_icon_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_text_color(get_style_label_fa32_icon_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_label_fa32_icon_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_text_color(get_style_label_fa_icon_active_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_label_nav_text_alternate_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_label_secondary_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_bg_color(get_style_message_box_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_bg_color(get_style_panel_screen_content_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_roller_default_SELECTED_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_bg_color(get_style_roller_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_text_color(get_style_roller_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_bg_color(get_style_spinner_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_arc_color(get_style_spinner_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_arc_color(get_style_spinner_default_INDICATOR_FOCUSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_spinner_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_spinner_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_arc_color(get_style_spinner_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_bg_color(get_style_style_button_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_style_button_default_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_border_color(get_style_style_button_default_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_content_panel_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_bg_color(get_style_style_default_slider_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_default_slider_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_bg_color(get_style_style_default_slider_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_text_color(get_style_style_device_status_ind_off_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_style_device_status_ind_on_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_panel_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_bg_color(get_style_style_panel_dialog_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_bg_color(get_style_style_panel_modal_blocker_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_style_screen_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_switch_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_obj_set_style_bg_color(objects.drive_body, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_card_bat, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_card_bat, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_title, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bat_arc, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bat_arc, lv_color_hex(theme_colors[theme_index][11]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_value, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_pct_sym, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_volts, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_remain, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_card_tires, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_card_tires, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_title, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_sub, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_l1, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_l1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_l1_psi, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_l1_lbl, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_r1, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_r1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_r1_psi, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_r1_lbl, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_l2, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_l2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_l2_psi, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_l2_lbl, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_r2, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_r2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_r2_lbl, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_bsm_warning, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_card_solar, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_card_solar, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_title, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_solar_arc, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_value, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_unit_sym, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_units_label, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_run, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_run, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_run_icon, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_run_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_left, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_left, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_left_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_left_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_brake, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_brake, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_brake_icon, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_brake_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_right, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_right, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_right_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_right_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_rev, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_rev, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_rev_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_rev_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_body, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_header, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_header, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_prev_zone, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_prev_zone, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_prev_icon, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_zone_icon, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_zone_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_zone_meta, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_next_zone, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_next_zone, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_next_icon, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_grid, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_1, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_btn_1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_1, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.lights_btn_1, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.lights_btn_1_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_1_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_1_state, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_2, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_btn_2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_2, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.lights_btn_2, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.lights_btn_2_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_2_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_2_state, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_3, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_btn_3, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_3, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.lights_btn_3, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.lights_btn_3_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_3_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_3_state, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_4, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_btn_4, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_4, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.lights_btn_4, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.lights_btn_4_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_4_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_4_state, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_5, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_btn_5, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_5, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.lights_btn_5, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.lights_btn_5_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_5_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_5_state, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_6, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_btn_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_btn_6, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.lights_btn_6, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.lights_btn_6_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_6_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_btn_6_state, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_footer, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_footer, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_all_on, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_all_on, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_all_on_lbl, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_all_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_all_off, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_all_off_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_dot_0, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_dot_1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_dot_2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_dot_3, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_dot_4, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_dot_5, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_off_all_devices, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_off_all_devices, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_off_all_lbl, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarms_body, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarms_header, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarms_header, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_title, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_subtitle, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_armed_icon, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_armed_count, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarms_list, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_lbl_0, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_desc_0, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_galley_cab_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_galley_cab_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_galley_cab_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_pantry_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_pantry_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_pantry_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_wardrobe_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_wardrobe_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_wardrobe_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_bath_door_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_bath_door_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_bath_door_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_entry_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_entry_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_entry_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_pass_thru_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_pass_thru_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_pass_thru_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_lbl_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_desc_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_bath_light_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_bath_light_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_bath_light_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_porch_light_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_porch_light_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_porch_light_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_galley_light_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_galley_light_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_galley_light_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_lbl_9, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_desc_9, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_fridge_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_fridge_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_fridge_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_pump_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_pump_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_pump_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_heater_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_heater_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_heater_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_inverter_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_inverter_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_inverter_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_lbl_13, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_grp_desc_13, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_co2_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_co2_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_co2_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_smoke_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarm_smoke_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_smoke_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_body, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_axle_title, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_axle_single, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_axle_single, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_axle_single, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.setup_axle_single, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.setup_axle_single_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_axle_single_sub, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_axle_tandem, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_axle_tandem, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_axle_tandem, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.setup_axle_tandem, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.setup_axle_tandem_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_axle_tandem_sub, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_axle_triple, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_axle_triple, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_axle_triple, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.setup_axle_triple, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.setup_axle_triple_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_axle_triple_sub, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_brake_title, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_brakes_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_brakes_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_brakes_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_brakes_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_brakes_desc, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_breakaway_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_breakaway_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_breakaway_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_breakaway_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_breakaway_desc, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_theme_title, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_theme_light, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_theme_light, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_theme_light, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.setup_theme_light, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.setup_theme_light_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_theme_dark, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_theme_dark, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_theme_dark, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_border_color(objects.setup_theme_dark, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.setup_theme_dark_icon, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_theme_dark_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_info_banner, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_info_banner, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_info_icon, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_info_text, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    {
        int startWidgetIndex = 5;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 65;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 79;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 137;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 151;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 222;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 236;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 279;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    lv_obj_invalidate(objects.page_drive);
    lv_obj_invalidate(objects.page_lights);
    lv_obj_invalidate(objects.page_alarms);
    lv_obj_invalidate(objects.page_setup);
}

uint32_t theme_colors[2][12] = {
    { 0xff52a441, 0xff000000, 0xffebebeb, 0xffd0e2c7, 0xffe3f3dc, 0xff5e635a, 0xff48e6fe, 0xffffffff, 0xffff5453, 0xff000000, 0xff83a79c, 0xff74fe00 },
    { 0xff00d004, 0xff000000, 0xff646667, 0xff859195, 0xff5b6768, 0xff9db8bb, 0xff48e6fe, 0xffffffff, 0xffff5453, 0xffffffff, 0xffe3f3ee, 0xff74fe00 },
};


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_page_drive,
    tick_screen_page_lights,
    tick_screen_page_alarms,
    tick_screen_page_setup,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_page_drive();
    create_screen_page_lights();
    create_screen_page_alarms();
    create_screen_page_setup();
}
