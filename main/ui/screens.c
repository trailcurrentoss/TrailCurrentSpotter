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
            create_user_widget_top_status_bar(obj, 11);
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
                    // drive_cab
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_cab = obj;
                    lv_obj_set_pos(obj, 373, 2);
                    lv_obj_set_size(obj, 54, 32);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][47]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][48]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_windshield
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_windshield = obj;
                    lv_obj_set_pos(obj, 382, 8);
                    lv_obj_set_size(obj, 36, 9);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][54]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][55]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_mirror_l
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_mirror_l = obj;
                    lv_obj_set_pos(obj, 369, 14);
                    lv_obj_set_size(obj, 4, 9);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_mirror_r
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_mirror_r = obj;
                    lv_obj_set_pos(obj, 427, 14);
                    lv_obj_set_size(obj, 4, 9);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_hitch_aframe
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_hitch_aframe = obj;
                    lv_obj_set_pos(obj, 388, 38);
                    lv_obj_set_size(obj, 24, 18);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][41]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][42]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_hitch_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_hitch_dot = obj;
                    lv_obj_set_pos(obj, 395, 42);
                    lv_obj_set_size(obj, 10, 10);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][42]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_breakaway
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_breakaway = obj;
                    lv_obj_set_pos(obj, 332, 61);
                    lv_obj_set_size(obj, 140, 11);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][40]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "BREAKAWAY ARMED");
                }
                {
                    // drive_trailer_body
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_trailer_body = obj;
                    lv_obj_set_pos(obj, 348, 79);
                    lv_obj_set_size(obj, 104, 200);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][47]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][48]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_ac
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_ac = obj;
                    lv_obj_set_pos(obj, 384, 89);
                    lv_obj_set_size(obj, 32, 17);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][47]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_axle1_bar
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_axle1_bar = obj;
                    lv_obj_set_pos(obj, 340, 229);
                    lv_obj_set_size(obj, 120, 3);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_l1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_tire_l1 = obj;
                    lv_obj_set_pos(obj, 337, 214);
                    lv_obj_set_size(obj, 14, 30);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_r1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_tire_r1 = obj;
                    lv_obj_set_pos(obj, 449, 214);
                    lv_obj_set_size(obj, 14, 30);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_l1_psi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_tire_l1_psi = obj;
                    lv_obj_set_pos(obj, 296, 220);
                    lv_obj_set_size(obj, 36, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // drive_tire_r1_psi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_tire_r1_psi = obj;
                    lv_obj_set_pos(obj, 468, 220);
                    lv_obj_set_size(obj, 36, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // drive_axle2_bar
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_axle2_bar = obj;
                    lv_obj_set_pos(obj, 340, 187);
                    lv_obj_set_size(obj, 120, 3);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_l2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_tire_l2 = obj;
                    lv_obj_set_pos(obj, 337, 172);
                    lv_obj_set_size(obj, 14, 30);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_r2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_tire_r2 = obj;
                    lv_obj_set_pos(obj, 449, 172);
                    lv_obj_set_size(obj, 14, 30);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_l2_psi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_tire_l2_psi = obj;
                    lv_obj_set_pos(obj, 296, 178);
                    lv_obj_set_size(obj, 36, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // drive_tire_r2_psi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_tire_r2_psi = obj;
                    lv_obj_set_pos(obj, 467, 178);
                    lv_obj_set_size(obj, 36, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // drive_axle3_bar
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_axle3_bar = obj;
                    lv_obj_set_pos(obj, 340, 145);
                    lv_obj_set_size(obj, 120, 3);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_l3
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_tire_l3 = obj;
                    lv_obj_set_pos(obj, 337, 130);
                    lv_obj_set_size(obj, 14, 30);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_r3
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_tire_r3 = obj;
                    lv_obj_set_pos(obj, 449, 130);
                    lv_obj_set_size(obj, 14, 30);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_tire_l3_psi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_tire_l3_psi = obj;
                    lv_obj_set_pos(obj, 297, 136);
                    lv_obj_set_size(obj, 36, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // drive_tire_r3_psi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_tire_r3_psi = obj;
                    lv_obj_set_pos(obj, 467, 136);
                    lv_obj_set_size(obj, 36, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // drive_chip_run
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_run = obj;
                    lv_obj_set_pos(obj, 12, 321);
                    lv_obj_set_size(obj, 150, 46);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][41]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][42]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_run_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_run_icon = obj;
                            lv_obj_set_pos(obj, 0, 8);
                            lv_obj_set_size(obj, 150, 22);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_chip_run_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_run_lbl = obj;
                            lv_obj_set_pos(obj, 0, 30);
                            lv_obj_set_size(obj, 150, 12);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][43]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "RUNNING");
                        }
                    }
                }
                {
                    // drive_chip_left
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_left = obj;
                    lv_obj_set_pos(obj, 168, 321);
                    lv_obj_set_size(obj, 150, 46);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][35]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_obj_set_pos(obj, 0, 8);
                            lv_obj_set_size(obj, 150, 22);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_chip_left_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_left_lbl = obj;
                            lv_obj_set_pos(obj, 0, 30);
                            lv_obj_set_size(obj, 150, 12);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "LEFT");
                        }
                    }
                }
                {
                    // drive_chip_brake
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_brake = obj;
                    lv_obj_set_pos(obj, 325, 321);
                    lv_obj_set_size(obj, 150, 46);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][44]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][45]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_brake_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_brake_icon = obj;
                            lv_obj_set_pos(obj, 0, 8);
                            lv_obj_set_size(obj, 150, 22);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_chip_brake_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_brake_lbl = obj;
                            lv_obj_set_pos(obj, 0, 30);
                            lv_obj_set_size(obj, 150, 12);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][46]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "BRAKE");
                        }
                    }
                }
                {
                    // drive_chip_right
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_right = obj;
                    lv_obj_set_pos(obj, 481, 321);
                    lv_obj_set_size(obj, 150, 46);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][35]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_obj_set_pos(obj, 0, 8);
                            lv_obj_set_size(obj, 150, 22);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_chip_right_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_right_lbl = obj;
                            lv_obj_set_pos(obj, 0, 30);
                            lv_obj_set_size(obj, 150, 12);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "RIGHT");
                        }
                    }
                }
                {
                    // drive_chip_rev
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_chip_rev = obj;
                    lv_obj_set_pos(obj, 638, 321);
                    lv_obj_set_size(obj, 150, 46);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][35]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_chip_rev_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_rev_icon = obj;
                            lv_obj_set_pos(obj, 0, 8);
                            lv_obj_set_size(obj, 150, 22);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // drive_chip_rev_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_chip_rev_lbl = obj;
                            lv_obj_set_pos(obj, 0, 30);
                            lv_obj_set_size(obj, 150, 12);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "REVERSE");
                        }
                    }
                }
                {
                    // drive_bat_arc
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_bat_arc = obj;
                    lv_obj_set_pos(obj, 16, 42);
                    lv_obj_set_size(obj, 230, 230);
                    lv_arc_set_value(obj, 0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_bat_dial
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_bat_dial = obj;
                    lv_obj_set_pos(obj, 31, 56);
                    lv_obj_set_size(obj, 200, 200);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][38]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][39]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 183, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_bat_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_bat_icon = obj;
                    lv_obj_set_pos(obj, -268, 72);
                    lv_obj_set_size(obj, 140, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // drive_bat_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_bat_value = obj;
                    lv_obj_set_pos(obj, 49, 122);
                    lv_obj_set_size(obj, 120, 50);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_64, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // drive_bat_volts
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_bat_volts = obj;
                    lv_obj_set_pos(obj, 47, 184);
                    lv_obj_set_size(obj, 170, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "----");
                }
                {
                    // drive_bat_remain
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_bat_remain = obj;
                    lv_obj_set_pos(obj, 45, 271);
                    lv_obj_set_size(obj, 170, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-- left");
                }
                {
                    // drive_solar_arc
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_solar_arc = obj;
                    lv_obj_set_pos(obj, 554, 42);
                    lv_obj_set_size(obj, 230, 230);
                    lv_arc_set_value(obj, 0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_solar_dial
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_solar_dial = obj;
                    lv_obj_set_pos(obj, 569, 56);
                    lv_obj_set_size(obj, 200, 200);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][38]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][39]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // drive_solar_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_solar_icon = obj;
                    lv_obj_set_pos(obj, 928, 72);
                    lv_obj_set_size(obj, 140, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // drive_solar_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_solar_value = obj;
                    lv_obj_set_pos(obj, 579, 122);
                    lv_obj_set_size(obj, 143, 50);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_64, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "---");
                }
                {
                    // drive_solar_unit
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_solar_unit = obj;
                    lv_obj_set_pos(obj, 583, 184);
                    lv_obj_set_size(obj, 170, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "watts in");
                }
                {
                    // drive_solar_pct
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_solar_pct = obj;
                    lv_obj_set_pos(obj, 519, 271);
                    lv_obj_set_size(obj, 300, 30);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "No data");
                }
                {
                    // drive_bsm_l_a1
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_bsm_l_a1 = obj;
                    lv_obj_set_pos(obj, 284, 151);
                    lv_obj_set_size(obj, 24, 24);
                    lv_arc_set_value(obj, 0);
                    lv_arc_set_bg_start_angle(obj, 130);
                    lv_arc_set_bg_end_angle(obj, 230);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_bsm_l_a2
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_bsm_l_a2 = obj;
                    lv_obj_set_pos(obj, 276, 143);
                    lv_obj_set_size(obj, 40, 40);
                    lv_arc_set_value(obj, 0);
                    lv_arc_set_bg_start_angle(obj, 130);
                    lv_arc_set_bg_end_angle(obj, 230);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_bsm_l_a3
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_bsm_l_a3 = obj;
                    lv_obj_set_pos(obj, 268, 135);
                    lv_obj_set_size(obj, 56, 56);
                    lv_arc_set_value(obj, 0);
                    lv_arc_set_bg_start_angle(obj, 130);
                    lv_arc_set_bg_end_angle(obj, 230);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_bsm_r_a1
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_bsm_r_a1 = obj;
                    lv_obj_set_pos(obj, 492, 151);
                    lv_obj_set_size(obj, 24, 24);
                    lv_arc_set_value(obj, 0);
                    lv_arc_set_bg_start_angle(obj, 310);
                    lv_arc_set_bg_end_angle(obj, 50);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_bsm_r_a2
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_bsm_r_a2 = obj;
                    lv_obj_set_pos(obj, 484, 143);
                    lv_obj_set_size(obj, 40, 40);
                    lv_arc_set_value(obj, 0);
                    lv_arc_set_bg_start_angle(obj, 310);
                    lv_arc_set_bg_end_angle(obj, 50);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_bsm_r_a3
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.drive_bsm_r_a3 = obj;
                    lv_obj_set_pos(obj, 476, 135);
                    lv_obj_set_size(obj, 56, 56);
                    lv_arc_set_value(obj, 0);
                    lv_arc_set_bg_start_angle(obj, 310);
                    lv_arc_set_bg_end_angle(obj, 50);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_arc_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // drive_bsm_l_car
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_bsm_l_car = obj;
                    lv_obj_set_pos(obj, 234, 118);
                    lv_obj_set_size(obj, 15, 15);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // drive_bsm_r_car
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_bsm_r_car = obj;
                    lv_obj_set_pos(obj, 551, 118);
                    lv_obj_set_size(obj, 15, 15);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // drive_bsm_warning
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.drive_bsm_warning = obj;
                    lv_obj_set_pos(obj, 323, 13);
                    lv_obj_set_size(obj, 154, 21);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 235, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drive_bsm_warn_text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.drive_bsm_warn_text = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 154, 21);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "VEHICLE IN BLIND SPOT");
                        }
                    }
                }
                {
                    // drive_solar_w
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_solar_w = obj;
                    lv_obj_set_pos(obj, 726, 133);
                    lv_obj_set_size(obj, 55, 43);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_nav_text_alternate(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "W");
                }
                {
                    // drive_sol_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.drive_sol_icon = obj;
                    lv_obj_set_pos(obj, 269, 72);
                    lv_obj_set_size(obj, 140, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uf185");
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
            create_user_widget_bottom_tab_bar(obj, 91);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 168, 167);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_secondary(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "%");
        }
    }
    
    tick_screen_page_drive();
}

void tick_screen_page_drive() {
    tick_user_widget_top_status_bar(11);
    tick_user_widget_bottom_tab_bar(91);
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
            create_user_widget_top_status_bar(obj, 105);
        }
        {
            // lights_header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.lights_header = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 800, 62);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // lights_prev_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.lights_prev_btn = obj;
                    lv_obj_set_pos(obj, 12, 4);
                    lv_obj_set_size(obj, 54, 54);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // lights_next_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.lights_next_btn = obj;
                    lv_obj_set_pos(obj, 734, 4);
                    lv_obj_set_size(obj, 54, 54);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // lights_zone_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.lights_zone_title = obj;
                    lv_obj_set_pos(obj, 80, 8);
                    lv_obj_set_size(obj, 640, 26);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Galley");
                }
                {
                    // lights_zone_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.lights_zone_sub = obj;
                    lv_obj_set_pos(obj, 80, 36);
                    lv_obj_set_size(obj, 640, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Zone 1 of 6  -  0 on");
                }
            }
        }
        {
            // lights_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.lights_body = obj;
            lv_obj_set_pos(obj, 0, 108);
            lv_obj_set_size(obj, 800, 256);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // lights_body_placeholder
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.lights_body_placeholder = obj;
                    lv_obj_set_pos(obj, 0, 100);
                    lv_obj_set_size(obj, 776, 24);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Tap a tile to toggle (zones populate at runtime)");
                }
            }
        }
        {
            // lights_footer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.lights_footer = obj;
            lv_obj_set_pos(obj, 0, 364);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // lights_all_on_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.lights_all_on_btn = obj;
                    lv_obj_set_pos(obj, 12, 6);
                    lv_obj_set_size(obj, 144, 38);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_obj_set_pos(obj, 0, 14);
                            lv_obj_set_size(obj, 144, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "All On");
                        }
                    }
                }
                {
                    // lights_all_off_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.lights_all_off_btn = obj;
                    lv_obj_set_pos(obj, 166, 6);
                    lv_obj_set_size(obj, 144, 38);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_obj_set_pos(obj, 0, 14);
                            lv_obj_set_size(obj, 144, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "All Off");
                        }
                    }
                }
                {
                    // lights_zone_dots
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.lights_zone_dots = obj;
                    lv_obj_set_pos(obj, 320, 6);
                    lv_obj_set_size(obj, 160, 38);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // lights_zone_dot_0
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_zone_dot_0 = obj;
                            lv_obj_set_pos(obj, 356, 12);
                            lv_obj_set_size(obj, 8, 8);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_zone_dot_1
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_zone_dot_1 = obj;
                            lv_obj_set_pos(obj, 372, 12);
                            lv_obj_set_size(obj, 8, 8);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_zone_dot_2
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_zone_dot_2 = obj;
                            lv_obj_set_pos(obj, 388, 12);
                            lv_obj_set_size(obj, 8, 8);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_zone_dot_3
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_zone_dot_3 = obj;
                            lv_obj_set_pos(obj, 404, 12);
                            lv_obj_set_size(obj, 8, 8);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_zone_dot_4
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_zone_dot_4 = obj;
                            lv_obj_set_pos(obj, 420, 12);
                            lv_obj_set_size(obj, 8, 8);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // lights_zone_dot_5
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.lights_zone_dot_5 = obj;
                            lv_obj_set_pos(obj, 436, 12);
                            lv_obj_set_size(obj, 8, 8);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // lights_off_all_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.lights_off_all_btn = obj;
                    lv_obj_set_pos(obj, 644, 6);
                    lv_obj_set_size(obj, 144, 38);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            lv_obj_set_pos(obj, 0, 14);
                            lv_obj_set_size(obj, 144, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Off  -  All");
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
            create_user_widget_bottom_tab_bar(obj, 144);
        }
    }
    
    tick_screen_page_lights();
}

void tick_screen_page_lights() {
    tick_user_widget_top_status_bar(105);
    tick_user_widget_bottom_tab_bar(144);
}

void create_screen_page_alarms() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_alarms = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
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
            create_user_widget_top_status_bar(obj, 158);
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
                            // alarm_spoor0_grp_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarm_spoor0_grp_lbl = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 480, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SWITCHBACK ADDR 0 (TEST)");
                        }
                        {
                            // alarm_spoor0_grp_desc
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarm_spoor0_grp_desc = obj;
                            lv_obj_set_pos(obj, 506, 12);
                            lv_obj_set_size(obj, 280, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_secondary(obj);
                            lv_label_set_text(obj, "Alarm if active");
                        }
                        {
                            // alarm_spoor0_s1_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s1_row = obj;
                            lv_obj_set_pos(obj, 14, 38);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s1_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s1_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 1");
                                }
                                {
                                    // alarm_spoor0_s1_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s1_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)0);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s1_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s1_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s1_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s1_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_s2_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s2_row = obj;
                            lv_obj_set_pos(obj, 14, 94);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s2_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 2");
                                }
                                {
                                    // alarm_spoor0_s2_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s2_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)1);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s2_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s2_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s2_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s2_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)1);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_s3_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s3_row = obj;
                            lv_obj_set_pos(obj, 14, 150);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s3_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s3_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 3");
                                }
                                {
                                    // alarm_spoor0_s3_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s3_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)2);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s3_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s3_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s3_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s3_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)2);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_s4_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s4_row = obj;
                            lv_obj_set_pos(obj, 14, 206);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s4_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s4_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 4");
                                }
                                {
                                    // alarm_spoor0_s4_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s4_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)3);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s4_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s4_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s4_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s4_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)3);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_s5_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s5_row = obj;
                            lv_obj_set_pos(obj, 14, 262);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s5_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s5_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 5");
                                }
                                {
                                    // alarm_spoor0_s5_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s5_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)4);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s5_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s5_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s5_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s5_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)4);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_s6_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s6_row = obj;
                            lv_obj_set_pos(obj, 14, 318);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s6_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s6_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 6");
                                }
                                {
                                    // alarm_spoor0_s6_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s6_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)5);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s6_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s6_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s6_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s6_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)5);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_s7_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s7_row = obj;
                            lv_obj_set_pos(obj, 14, 374);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s7_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s7_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 7");
                                }
                                {
                                    // alarm_spoor0_s7_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s7_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)6);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s7_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s7_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s7_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s7_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)6);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_s8_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_s8_row = obj;
                            lv_obj_set_pos(obj, 14, 430);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_s8_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_s8_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 8");
                                }
                                {
                                    // alarm_spoor0_s8_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_s8_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)7);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_s8_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_s8_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_s8_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_s8_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)7);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d1_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d1_row = obj;
                            lv_obj_set_pos(obj, 14, 486);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d1_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d1_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 1");
                                }
                                {
                                    // alarm_spoor0_d1_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d1_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)0);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d1_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d1_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d1_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d1_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d1_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d1_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d2_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d2_row = obj;
                            lv_obj_set_pos(obj, 14, 542);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d2_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 2");
                                }
                                {
                                    // alarm_spoor0_d2_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d2_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)1);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d2_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d2_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d2_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d2_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)1);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d2_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d2_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)1);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d3_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d3_row = obj;
                            lv_obj_set_pos(obj, 14, 598);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d3_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d3_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 3");
                                }
                                {
                                    // alarm_spoor0_d3_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d3_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)2);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d3_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d3_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d3_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d3_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)2);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d3_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d3_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)2);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d4_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d4_row = obj;
                            lv_obj_set_pos(obj, 14, 654);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d4_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d4_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 4");
                                }
                                {
                                    // alarm_spoor0_d4_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d4_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)3);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d4_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d4_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d4_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d4_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)3);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d4_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d4_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)3);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d5_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d5_row = obj;
                            lv_obj_set_pos(obj, 14, 710);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d5_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d5_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 5");
                                }
                                {
                                    // alarm_spoor0_d5_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d5_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)4);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d5_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d5_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d5_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d5_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)4);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d5_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d5_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)4);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d6_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d6_row = obj;
                            lv_obj_set_pos(obj, 14, 766);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d6_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d6_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 6");
                                }
                                {
                                    // alarm_spoor0_d6_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d6_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)5);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d6_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d6_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d6_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d6_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)5);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d6_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d6_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)5);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d7_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d7_row = obj;
                            lv_obj_set_pos(obj, 14, 822);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d7_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d7_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 7");
                                }
                                {
                                    // alarm_spoor0_d7_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d7_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)6);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d7_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d7_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d7_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d7_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)6);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d7_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d7_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)6);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor0_d8_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor0_d8_row = obj;
                            lv_obj_set_pos(obj, 14, 878);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor0_d8_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor0_d8_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 8");
                                }
                                {
                                    // alarm_spoor0_d8_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor0_d8_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)7);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor0_d8_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor0_d8_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor0_d8_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d8_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)7);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor0_d8_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor0_d8_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)7);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_grp_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarm_spoor1_grp_lbl = obj;
                            lv_obj_set_pos(obj, 14, 946);
                            lv_obj_set_size(obj, 480, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SWITCHBACK ADDR 1");
                        }
                        {
                            // alarm_spoor1_grp_desc
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarm_spoor1_grp_desc = obj;
                            lv_obj_set_pos(obj, 506, 946);
                            lv_obj_set_size(obj, 280, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_secondary(obj);
                            lv_label_set_text(obj, "Alarm if active");
                        }
                        {
                            // alarm_spoor1_s1_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s1_row = obj;
                            lv_obj_set_pos(obj, 14, 972);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s1_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s1_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 1");
                                }
                                {
                                    // alarm_spoor1_s1_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s1_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)8);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s1_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s1_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s1_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s1_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)8);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_s2_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s2_row = obj;
                            lv_obj_set_pos(obj, 14, 1028);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s2_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 2");
                                }
                                {
                                    // alarm_spoor1_s2_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s2_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)9);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s2_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s2_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s2_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s2_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)9);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_s3_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s3_row = obj;
                            lv_obj_set_pos(obj, 14, 1084);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s3_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s3_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 3");
                                }
                                {
                                    // alarm_spoor1_s3_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s3_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)10);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s3_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s3_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s3_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s3_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)10);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_s4_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s4_row = obj;
                            lv_obj_set_pos(obj, 14, 1140);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s4_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s4_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 4");
                                }
                                {
                                    // alarm_spoor1_s4_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s4_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)11);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s4_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s4_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s4_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s4_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)11);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_s5_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s5_row = obj;
                            lv_obj_set_pos(obj, 14, 1196);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s5_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s5_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 5");
                                }
                                {
                                    // alarm_spoor1_s5_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s5_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)12);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s5_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s5_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s5_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s5_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)12);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_s6_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s6_row = obj;
                            lv_obj_set_pos(obj, 14, 1252);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s6_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s6_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 6");
                                }
                                {
                                    // alarm_spoor1_s6_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s6_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)13);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s6_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s6_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s6_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s6_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)13);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_s7_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s7_row = obj;
                            lv_obj_set_pos(obj, 14, 1308);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s7_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s7_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 7");
                                }
                                {
                                    // alarm_spoor1_s7_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s7_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)14);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s7_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s7_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s7_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s7_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)14);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_s8_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_s8_row = obj;
                            lv_obj_set_pos(obj, 14, 1364);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_s8_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_s8_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 8");
                                }
                                {
                                    // alarm_spoor1_s8_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_s8_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)15);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_s8_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_s8_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_s8_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_s8_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)15);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d1_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d1_row = obj;
                            lv_obj_set_pos(obj, 14, 1420);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d1_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d1_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 1");
                                }
                                {
                                    // alarm_spoor1_d1_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d1_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)8);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d1_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d1_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d1_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d1_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)8);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d1_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d1_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)8);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d2_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d2_row = obj;
                            lv_obj_set_pos(obj, 14, 1476);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d2_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 2");
                                }
                                {
                                    // alarm_spoor1_d2_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d2_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)9);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d2_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d2_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d2_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d2_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)9);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d2_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d2_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)9);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d3_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d3_row = obj;
                            lv_obj_set_pos(obj, 14, 1532);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d3_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d3_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 3");
                                }
                                {
                                    // alarm_spoor1_d3_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d3_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)10);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d3_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d3_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d3_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d3_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)10);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d3_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d3_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)10);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d4_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d4_row = obj;
                            lv_obj_set_pos(obj, 14, 1588);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d4_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d4_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 4");
                                }
                                {
                                    // alarm_spoor1_d4_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d4_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)11);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d4_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d4_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d4_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d4_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)11);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d4_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d4_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)11);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d5_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d5_row = obj;
                            lv_obj_set_pos(obj, 14, 1644);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d5_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d5_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 5");
                                }
                                {
                                    // alarm_spoor1_d5_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d5_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)12);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d5_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d5_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d5_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d5_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)12);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d5_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d5_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)12);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d6_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d6_row = obj;
                            lv_obj_set_pos(obj, 14, 1700);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d6_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d6_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 6");
                                }
                                {
                                    // alarm_spoor1_d6_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d6_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)13);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d6_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d6_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d6_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d6_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)13);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d6_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d6_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)13);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d7_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d7_row = obj;
                            lv_obj_set_pos(obj, 14, 1756);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d7_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d7_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 7");
                                }
                                {
                                    // alarm_spoor1_d7_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d7_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)14);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d7_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d7_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d7_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d7_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)14);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d7_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d7_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)14);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor1_d8_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor1_d8_row = obj;
                            lv_obj_set_pos(obj, 14, 1812);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor1_d8_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor1_d8_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 8");
                                }
                                {
                                    // alarm_spoor1_d8_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor1_d8_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)15);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor1_d8_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor1_d8_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor1_d8_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d8_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)15);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor1_d8_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor1_d8_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)15);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_grp_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarm_spoor2_grp_lbl = obj;
                            lv_obj_set_pos(obj, 14, 1880);
                            lv_obj_set_size(obj, 480, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SWITCHBACK ADDR 2");
                        }
                        {
                            // alarm_spoor2_grp_desc
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.alarm_spoor2_grp_desc = obj;
                            lv_obj_set_pos(obj, 506, 1880);
                            lv_obj_set_size(obj, 280, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_secondary(obj);
                            lv_label_set_text(obj, "Alarm if active");
                        }
                        {
                            // alarm_spoor2_s1_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s1_row = obj;
                            lv_obj_set_pos(obj, 14, 1906);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s1_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s1_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 1");
                                }
                                {
                                    // alarm_spoor2_s1_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s1_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)16);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s1_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s1_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s1_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s1_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)16);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_s2_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s2_row = obj;
                            lv_obj_set_pos(obj, 14, 1962);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s2_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 2");
                                }
                                {
                                    // alarm_spoor2_s2_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s2_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)17);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s2_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s2_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s2_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s2_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)17);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_s3_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s3_row = obj;
                            lv_obj_set_pos(obj, 14, 2018);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s3_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s3_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 3");
                                }
                                {
                                    // alarm_spoor2_s3_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s3_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)18);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s3_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s3_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s3_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s3_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)18);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_s4_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s4_row = obj;
                            lv_obj_set_pos(obj, 14, 2074);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s4_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s4_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 4");
                                }
                                {
                                    // alarm_spoor2_s4_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s4_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)19);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s4_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s4_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s4_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s4_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)19);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_s5_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s5_row = obj;
                            lv_obj_set_pos(obj, 14, 2130);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s5_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s5_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 5");
                                }
                                {
                                    // alarm_spoor2_s5_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s5_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)20);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s5_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s5_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s5_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s5_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)20);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_s6_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s6_row = obj;
                            lv_obj_set_pos(obj, 14, 2186);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s6_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s6_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 6");
                                }
                                {
                                    // alarm_spoor2_s6_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s6_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)21);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s6_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s6_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s6_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s6_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)21);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_s7_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s7_row = obj;
                            lv_obj_set_pos(obj, 14, 2242);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s7_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s7_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 7");
                                }
                                {
                                    // alarm_spoor2_s7_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s7_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)22);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s7_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s7_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s7_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s7_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)22);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_s8_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_s8_row = obj;
                            lv_obj_set_pos(obj, 14, 2298);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_s8_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_s8_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 480, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Sensor 8");
                                }
                                {
                                    // alarm_spoor2_s8_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_s8_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 644, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_sensor, LV_EVENT_CLICKED, (void *)23);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_s8_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_s8_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_s8_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_s8_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_spoor_sensor, LV_EVENT_VALUE_CHANGED, (void *)23);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d1_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d1_row = obj;
                            lv_obj_set_pos(obj, 14, 2354);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d1_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d1_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 1");
                                }
                                {
                                    // alarm_spoor2_d1_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d1_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)16);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d1_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d1_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d1_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d1_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)16);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d1_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d1_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)16);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d2_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d2_row = obj;
                            lv_obj_set_pos(obj, 14, 2410);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d2_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d2_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 2");
                                }
                                {
                                    // alarm_spoor2_d2_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d2_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)17);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d2_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d2_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d2_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d2_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)17);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d2_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d2_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)17);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d3_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d3_row = obj;
                            lv_obj_set_pos(obj, 14, 2466);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d3_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d3_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 3");
                                }
                                {
                                    // alarm_spoor2_d3_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d3_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)18);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d3_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d3_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d3_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d3_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)18);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d3_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d3_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)18);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d4_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d4_row = obj;
                            lv_obj_set_pos(obj, 14, 2522);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d4_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d4_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 4");
                                }
                                {
                                    // alarm_spoor2_d4_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d4_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)19);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d4_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d4_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d4_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d4_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)19);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d4_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d4_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d5_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d5_row = obj;
                            lv_obj_set_pos(obj, 14, 2578);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d5_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d5_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 5");
                                }
                                {
                                    // alarm_spoor2_d5_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d5_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)20);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d5_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d5_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d5_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d5_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)20);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d5_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d5_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d6_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d6_row = obj;
                            lv_obj_set_pos(obj, 14, 2634);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d6_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d6_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 6");
                                }
                                {
                                    // alarm_spoor2_d6_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d6_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)21);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d6_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d6_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d6_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d6_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)21);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d6_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d6_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)21);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d7_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d7_row = obj;
                            lv_obj_set_pos(obj, 14, 2690);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d7_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d7_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 7");
                                }
                                {
                                    // alarm_spoor2_d7_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d7_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)22);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d7_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d7_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d7_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d7_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)22);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d7_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d7_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)22);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_switch_default(obj);
                                }
                            }
                        }
                        {
                            // alarm_spoor2_d8_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.alarm_spoor2_d8_row = obj;
                            lv_obj_set_pos(obj, 14, 2746);
                            lv_obj_set_size(obj, 772, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // alarm_spoor2_d8_name
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.alarm_spoor2_d8_name = obj;
                                    lv_obj_set_pos(obj, 14, 15);
                                    lv_obj_set_size(obj, 440, 20);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_label_set_text(obj, "Device 8");
                                }
                                {
                                    // alarm_spoor2_d8_pencil_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.alarm_spoor2_d8_pencil_btn = obj;
                                    lv_obj_set_pos(obj, 560, 11);
                                    lv_obj_set_size(obj, 32, 28);
                                    lv_obj_add_event_cb(obj, action_open_rename_device, LV_EVENT_CLICKED, (void *)23);
                                    add_style_style_button_default(obj);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // alarm_spoor2_d8_pencil_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.alarm_spoor2_d8_pencil_icon = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 32, 28);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_fa16_icon(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_width(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_min_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_max_height(obj, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "");
                                        }
                                    }
                                }
                                {
                                    // alarm_spoor2_d8_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d8_sw = obj;
                                    lv_obj_set_pos(obj, 700, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_alarm, LV_EVENT_VALUE_CHANGED, (void *)23);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // alarm_spoor2_d8_inv_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.alarm_spoor2_d8_inv_sw = obj;
                                    lv_obj_set_pos(obj, 620, 11);
                                    lv_obj_set_size(obj, 50, 28);
                                    lv_obj_add_event_cb(obj, action_toggle_device_invert, LV_EVENT_VALUE_CHANGED, (void *)23);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
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
            create_user_widget_bottom_tab_bar(obj, 451);
        }
    }
    
    tick_screen_page_alarms();
}

void tick_screen_page_alarms() {
    tick_user_widget_top_status_bar(158);
    tick_user_widget_bottom_tab_bar(451);
}

void create_screen_page_setup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_setup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
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
            create_user_widget_top_status_bar(obj, 465);
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
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    lv_obj_set_pos(obj, 14, 734);
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
                {
                    // setup_reset_conn_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.setup_reset_conn_title = obj;
                    lv_obj_set_pos(obj, 14, 1010);
                    lv_obj_set_size(obj, 772, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "NETWORK");
                }
                {
                    // setup_reset_conn_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.setup_reset_conn_btn = obj;
                    lv_obj_set_pos(obj, 14, 1038);
                    lv_obj_set_size(obj, 772, 56);
                    lv_obj_add_event_cb(obj, action_clear_connection, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_reset_conn_btn_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_reset_conn_btn_lbl = obj;
                            lv_obj_set_pos(obj, 0, 18);
                            lv_obj_set_size(obj, 772, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Reset Connection (clears WiFi + MQTT)");
                        }
                    }
                }
                {
                    // setup_alarm_timing_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.setup_alarm_timing_title = obj;
                    lv_obj_set_pos(obj, 14, 794);
                    lv_obj_set_size(obj, 772, 18);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "ALARM TIMING");
                }
                {
                    // setup_alarm_snooze_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_alarm_snooze_row = obj;
                    lv_obj_set_pos(obj, 14, 822);
                    lv_obj_set_size(obj, 772, 60);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_alarm_snooze_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_alarm_snooze_name = obj;
                            lv_obj_set_pos(obj, 14, 4);
                            lv_obj_set_size(obj, 400, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_label_set_text(obj, "Alarm Snooze Duration");
                        }
                        {
                            // setup_alarm_snooze_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_alarm_snooze_value = obj;
                            lv_obj_set_pos(obj, 692, 4);
                            lv_obj_set_size(obj, 70, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_secondary(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "30 sec");
                        }
                        {
                            // setup_alarm_snooze_slider
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.setup_alarm_snooze_slider = obj;
                            lv_obj_set_pos(obj, 14, 34);
                            lv_obj_set_size(obj, 720, 18);
                            lv_slider_set_range(obj, 10, 180);
                            lv_slider_set_value(obj, 30, LV_ANIM_OFF);
                            lv_obj_add_event_cb(obj, action_alarm_snooze_duration_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            add_style_style_default_slider(obj);
                        }
                    }
                }
                {
                    // setup_audio_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.setup_audio_title = obj;
                    lv_obj_set_pos(obj, 14, 902);
                    lv_obj_set_size(obj, 772, 18);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "AUDIO");
                }
                {
                    // setup_volume_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_volume_row = obj;
                    lv_obj_set_pos(obj, 14, 930);
                    lv_obj_set_size(obj, 772, 60);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_volume_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_volume_name = obj;
                            lv_obj_set_pos(obj, 14, 4);
                            lv_obj_set_size(obj, 400, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_label_set_text(obj, "Chime Volume");
                        }
                        {
                            // setup_volume_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_volume_value = obj;
                            lv_obj_set_pos(obj, 692, 4);
                            lv_obj_set_size(obj, 70, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_secondary(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "80%");
                        }
                        {
                            // setup_volume_slider
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.setup_volume_slider = obj;
                            lv_obj_set_pos(obj, 14, 34);
                            lv_obj_set_size(obj, 720, 18);
                            lv_slider_set_value(obj, 80, LV_ANIM_OFF);
                            lv_obj_add_event_cb(obj, action_volume_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            add_style_style_default_slider(obj);
                        }
                    }
                }
                {
                    // setup_brightness_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_brightness_row = obj;
                    lv_obj_set_pos(obj, 14, 384);
                    lv_obj_set_size(obj, 772, 60);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // setup_brightness_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_brightness_name = obj;
                            lv_obj_set_pos(obj, 14, 4);
                            lv_obj_set_size(obj, 400, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_label_set_text(obj, "Backlight Brightness");
                        }
                        {
                            // setup_brightness_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_brightness_value = obj;
                            lv_obj_set_pos(obj, 692, 4);
                            lv_obj_set_size(obj, 70, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_secondary(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "80%");
                        }
                        {
                            // setup_brightness_slider
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.setup_brightness_slider = obj;
                            lv_obj_set_pos(obj, 14, 34);
                            lv_obj_set_size(obj, 720, 18);
                            lv_slider_set_range(obj, 10, 100);
                            lv_slider_set_value(obj, 80, LV_ANIM_OFF);
                            lv_obj_add_event_cb(obj, action_brightness_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            add_style_style_default_slider(obj);
                        }
                    }
                }
                {
                    // setup_timezone_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.setup_timezone_title = obj;
                    lv_obj_set_pos(obj, 14, 454);
                    lv_obj_set_size(obj, 772, 18);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Timezone");
                }
                {
                    // setup_timezone_dropdown
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.setup_timezone_dropdown = obj;
                    lv_obj_set_pos(obj, 14, 482);
                    lv_obj_set_size(obj, 772, 50);
                    lv_dropdown_set_options(obj, "Alaska\nChicago, Illinois\nDenver, Colorado\nHawaii\nLos Angeles\nNew York\nPhoenix");
                    lv_dropdown_set_dir(obj, LV_DIR_TOP);
                    lv_dropdown_set_symbol(obj, LV_SYMBOL_UP);
                    lv_dropdown_set_selected(obj, 5);
                    lv_obj_add_event_cb(obj, action_timezone_change, LV_EVENT_VALUE_CHANGED, (void *)0);
                }
                {
                    // setup_date_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_date_row = obj;
                    lv_obj_set_pos(obj, 14, 540);
                    lv_obj_set_size(obj, 772, 54);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
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
                            // setup_date_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_date_icon = obj;
                            lv_obj_set_pos(obj, 14, 16);
                            lv_obj_set_size(obj, 24, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_date_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_date_name = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 200, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Date");
                        }
                        {
                            // setup_date_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_date_value = obj;
                            lv_obj_set_pos(obj, 48, 32);
                            lv_obj_set_size(obj, 600, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "--");
                        }
                    }
                }
                {
                    // setup_time_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_time_row = obj;
                    lv_obj_set_pos(obj, 14, 602);
                    lv_obj_set_size(obj, 772, 54);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
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
                            // setup_time_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_time_icon = obj;
                            lv_obj_set_pos(obj, 14, 16);
                            lv_obj_set_size(obj, 24, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_time_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_time_name = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 200, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Time");
                        }
                        {
                            // setup_time_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_time_value = obj;
                            lv_obj_set_pos(obj, 48, 32);
                            lv_obj_set_size(obj, 600, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "--");
                        }
                    }
                }
                {
                    // setup_clock_format_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.setup_clock_format_row = obj;
                    lv_obj_set_pos(obj, 14, 664);
                    lv_obj_set_size(obj, 772, 54);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
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
                            // setup_clock_format_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_clock_format_icon = obj;
                            lv_obj_set_pos(obj, 14, 16);
                            lv_obj_set_size(obj, 24, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // setup_clock_format_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_clock_format_name = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 500, 22);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "24-hour clock");
                        }
                        {
                            // setup_clock_format_desc
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.setup_clock_format_desc = obj;
                            lv_obj_set_pos(obj, 48, 32);
                            lv_obj_set_size(obj, 600, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Off shows 12-hour with AM/PM; on shows 24-hour.");
                        }
                        {
                            // setup_clock_format_sw
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.setup_clock_format_sw = obj;
                            lv_obj_set_pos(obj, 722, 13);
                            lv_obj_set_size(obj, 50, 28);
                            lv_obj_add_event_cb(obj, action_toggle_clock_format, LV_EVENT_VALUE_CHANGED, (void *)0);
                            add_style_switch_default(obj);
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
            create_user_widget_bottom_tab_bar(obj, 545);
        }
    }
    
    tick_screen_page_setup();
}

void tick_screen_page_setup() {
    tick_user_widget_top_status_bar(465);
    tick_user_widget_bottom_tab_bar(545);
}

void create_screen_page_wifi_setup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_wifi_setup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wifi_header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
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
                    // wifi_brand
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_brand = obj;
                    lv_obj_set_pos(obj, 12, 14);
                    lv_obj_set_size(obj, 22, 22);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // wifi_brand_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_brand_sub = obj;
                    lv_obj_set_pos(obj, 40, 13);
                    lv_obj_set_size(obj, 90, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "SPOTTER");
                }
                {
                    // wifi_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_title = obj;
                    lv_obj_set_pos(obj, 0, 5);
                    lv_obj_set_size(obj, 800, 22);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "WiFi Setup");
                }
                {
                    // wifi_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_sub = obj;
                    lv_obj_set_pos(obj, 0, 30);
                    lv_obj_set_size(obj, 800, 16);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Pick a network, then enter the password.");
                }
                {
                    // wifi_scan_spinner
                    lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
                    objects.wifi_scan_spinner = obj;
                    lv_obj_set_pos(obj, 760, 14);
                    lv_obj_set_size(obj, 22, 22);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                    add_style_spinner_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // wifi_scan_status
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_scan_status = obj;
                    lv_obj_set_pos(obj, 570, 16);
                    lv_obj_set_size(obj, 180, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Scanning...");
                }
            }
        }
        {
            // wifi_scan_list
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_scan_list = obj;
            lv_obj_set_pos(obj, 0, 50);
            lv_obj_set_size(obj, 800, 380);
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
                    // wifi_net_0
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_0 = obj;
                    lv_obj_set_pos(obj, 12, 6);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_0 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_0 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_0
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_0 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_0
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_0 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_0
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_0 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_0
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_0 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_0 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_0
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_0 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)0);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // wifi_net_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_1 = obj;
                    lv_obj_set_pos(obj, 12, 52);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_1 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_1 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_1
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_1 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_1 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_1 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_1 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_1 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)1);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // wifi_net_2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_2 = obj;
                    lv_obj_set_pos(obj, 12, 98);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_2 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_2 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_2
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_2 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_2 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_2 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_2 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_2 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_2
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_2 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)2);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // wifi_net_3
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_3 = obj;
                    lv_obj_set_pos(obj, 12, 144);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_3 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_3 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_3
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_3 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_3
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_3 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_3
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_3 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_3
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_3 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_3 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_3
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_3 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)3);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // wifi_net_4
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_4 = obj;
                    lv_obj_set_pos(obj, 12, 190);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_4 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_4 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_4
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_4 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_4
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_4 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_4
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_4 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_4
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_4 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_4 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_4
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_4 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)4);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // wifi_net_5
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_5 = obj;
                    lv_obj_set_pos(obj, 12, 236);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_5 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_5 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_5
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_5 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_5
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_5 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_5
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_5 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_5
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_5 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_5 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_5
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_5 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)5);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // wifi_net_6
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_6 = obj;
                    lv_obj_set_pos(obj, 12, 282);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_6 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_6 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_6
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_6 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_6
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_6 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_6
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_6 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_6
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_6 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_6 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_6
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_6 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)6);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // wifi_net_7
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_net_7 = obj;
                    lv_obj_set_pos(obj, 12, 328);
                    lv_obj_set_size(obj, 776, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_7 = obj;
                            lv_obj_set_pos(obj, 12, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_ssid_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_7 = obj;
                            lv_obj_set_pos(obj, 44, 11);
                            lv_obj_set_size(obj, 600, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_7
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_7 = obj;
                            lv_obj_set_pos(obj, 700, 12);
                            lv_obj_set_size(obj, 36, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_7
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_7 = obj;
                                    lv_obj_set_pos(obj, 0, 10);
                                    lv_obj_set_size(obj, 8, 6);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar2_7
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_7 = obj;
                                    lv_obj_set_pos(obj, 12, 6);
                                    lv_obj_set_size(obj, 8, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                                {
                                    // wifi_net_bar3_7
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_7 = obj;
                                    lv_obj_set_pos(obj, 24, 2);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_7 = obj;
                            lv_obj_set_pos(obj, 744, 8);
                            lv_obj_set_size(obj, 24, 24);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_act_7
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.wifi_net_act_7 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 776, 40);
                            lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)7);
                            add_style_style_button_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // wifi_footer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_footer = obj;
            lv_obj_set_pos(obj, 0, 430);
            lv_obj_set_size(obj, 800, 50);
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
                    // wifi_btn_refresh
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_btn_refresh = obj;
                    lv_obj_set_pos(obj, 12, 6);
                    lv_obj_set_size(obj, 120, 38);
                    lv_obj_add_event_cb(obj, action_wifi_scan, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            // wifi_btn_refresh_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_btn_refresh_icon = obj;
                            lv_obj_set_pos(obj, 12, 9);
                            lv_obj_set_size(obj, 20, 20);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_btn_refresh_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_btn_refresh_lbl = obj;
                            lv_obj_set_pos(obj, 36, 10);
                            lv_obj_set_size(obj, 80, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Rescan");
                        }
                    }
                }
                {
                    // wifi_btn_skip
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_btn_skip = obj;
                    lv_obj_set_pos(obj, 668, 6);
                    lv_obj_set_size(obj, 120, 38);
                    lv_obj_add_event_cb(obj, action_wifi_skip_to_serial, LV_EVENT_CLICKED, (void *)0);
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
                            // wifi_btn_skip_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_btn_skip_lbl = obj;
                            lv_obj_set_pos(obj, 0, 10);
                            lv_obj_set_size(obj, 120, 18);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Skip");
                        }
                    }
                }
            }
        }
        {
            // wifi_password_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_password_panel = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 480, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 480, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // wifi_pwd_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_pwd_caption = obj;
                    lv_obj_set_pos(obj, 0, 4);
                    lv_obj_set_size(obj, 800, 16);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Enter password for");
                }
                {
                    // wifi_pwd_ssid
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_pwd_ssid = obj;
                    lv_obj_set_pos(obj, 0, 4);
                    lv_obj_set_size(obj, 800, 42);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // wifi_pwd_input
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.wifi_pwd_input = obj;
                    lv_obj_set_pos(obj, 60, 50);
                    lv_obj_set_size(obj, 620, 52);
                    lv_textarea_set_max_length(obj, 64);
                    lv_textarea_set_placeholder_text(obj, "WiFi password");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, true);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_min_width(obj, 620, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_max_width(obj, 620, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_min_height(obj, 52, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_max_height(obj, 52, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // wifi_pwd_reveal
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_pwd_reveal = obj;
                    lv_obj_set_pos(obj, 690, 50);
                    lv_obj_set_size(obj, 50, 52);
                    lv_obj_add_event_cb(obj, action_wifi_toggle_password_reveal, LV_EVENT_CLICKED, (void *)0);
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
                            // wifi_pwd_reveal_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_pwd_reveal_icon = obj;
                            lv_obj_set_pos(obj, 0, 18);
                            lv_obj_set_size(obj, 50, 22);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // wifi_pwd_keyboard
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    objects.wifi_pwd_keyboard = obj;
                    lv_obj_set_pos(obj, 8, 110);
                    lv_obj_set_size(obj, 784, 280);
                    lv_obj_add_event_cb(obj, action_wifi_password_submit, LV_EVENT_READY, (void *)0);
                    lv_obj_add_event_cb(obj, action_wifi_back, LV_EVENT_CANCEL, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_keyboard_default(obj);
                    lv_obj_set_style_min_width(obj, 784, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_max_width(obj, 784, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_min_height(obj, 280, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_max_height(obj, 280, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // wifi_pwd_cancel
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_pwd_cancel = obj;
                    lv_obj_set_pos(obj, 12, 400);
                    lv_obj_set_size(obj, 180, 64);
                    lv_obj_add_event_cb(obj, action_wifi_back, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_pwd_cancel_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_pwd_cancel_lbl = obj;
                            lv_obj_set_pos(obj, 0, 22);
                            lv_obj_set_size(obj, 180, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Cancel");
                        }
                    }
                }
                {
                    // wifi_pwd_connect
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_pwd_connect = obj;
                    lv_obj_set_pos(obj, 608, 400);
                    lv_obj_set_size(obj, 180, 64);
                    lv_obj_add_event_cb(obj, action_wifi_password_submit, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_pwd_connect_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_pwd_connect_lbl = obj;
                            lv_obj_set_pos(obj, 0, 22);
                            lv_obj_set_size(obj, 180, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_wifi_setup();
}

void tick_screen_page_wifi_setup() {
}

void create_screen_page_wifi_connecting() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_wifi_connecting = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wifi_connecting_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_connecting_panel = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
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
                    // wifi_conn_brand
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_conn_brand = obj;
                    lv_obj_set_pos(obj, 389, 40);
                    lv_obj_set_size(obj, 22, 22);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // wifi_conn_brand_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_conn_brand_sub = obj;
                    lv_obj_set_pos(obj, 0, 64);
                    lv_obj_set_size(obj, 800, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "SPOTTER");
                }
                {
                    // wifi_connecting_spinner
                    lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
                    objects.wifi_connecting_spinner = obj;
                    lv_obj_set_pos(obj, 350, 160);
                    lv_obj_set_size(obj, 100, 100);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                    add_style_spinner_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // wifi_connecting_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_connecting_caption = obj;
                    lv_obj_set_pos(obj, 0, 290);
                    lv_obj_set_size(obj, 800, 20);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Connecting to");
                }
                {
                    // wifi_connecting_ssid
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_connecting_ssid = obj;
                    lv_obj_set_pos(obj, 0, 312);
                    lv_obj_set_size(obj, 800, 28);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "...");
                }
                {
                    // wifi_connecting_hint
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_connecting_hint = obj;
                    lv_obj_set_pos(obj, 0, 430);
                    lv_obj_set_size(obj, 800, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "If this takes more than 30 seconds, check the password and try again.");
                }
            }
        }
    }
    
    tick_screen_page_wifi_connecting();
}

void tick_screen_page_wifi_connecting() {
}

void create_screen_page_mqtt_setup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_mqtt_setup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // mqtt_brand
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mqtt_brand = obj;
            lv_obj_set_pos(obj, 12, 14);
            lv_obj_set_size(obj, 22, 22);
            add_style_label_fa16_icon(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // mqtt_brand_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mqtt_brand_text = obj;
            lv_obj_set_pos(obj, 40, 14);
            lv_obj_set_size(obj, 90, 18);
            add_style_label_default(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "SPOTTER");
        }
        {
            // mqtt_caption
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mqtt_caption = obj;
            lv_obj_set_pos(obj, 0, 4);
            lv_obj_set_size(obj, 800, 22);
            add_style_label_default(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "TrailCurrent server");
        }
        {
            // mqtt_step
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mqtt_step = obj;
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 800, 16);
            add_style_label_default(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Step 1 of 3");
        }
        {
            // mqtt_input
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.mqtt_input = obj;
            lv_obj_set_pos(obj, 60, 52);
            lv_obj_set_size(obj, 680, 44);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_placeholder_text(obj, "hostname or IP");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 680, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 680, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 44, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 44, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // mqtt_keyboard
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.mqtt_keyboard = obj;
            lv_obj_set_pos(obj, 8, 100);
            lv_obj_set_size(obj, 784, 290);
            lv_obj_add_event_cb(obj, action_mqtt_next, LV_EVENT_READY, (void *)0);
            lv_obj_add_event_cb(obj, action_mqtt_back, LV_EVENT_CANCEL, (void *)0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_keyboard_default(obj);
            lv_obj_set_style_min_width(obj, 784, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 784, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 290, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 290, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // mqtt_footer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.mqtt_footer = obj;
            lv_obj_set_pos(obj, 0, 400);
            lv_obj_set_size(obj, 800, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // mqtt_back
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mqtt_back = obj;
                    lv_obj_set_pos(obj, 12, 18);
                    lv_obj_set_size(obj, 180, 44);
                    lv_obj_add_event_cb(obj, action_mqtt_back, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 120, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // mqtt_back_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.mqtt_back_lbl = obj;
                            lv_obj_set_pos(obj, 0, 12);
                            lv_obj_set_size(obj, 180, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Back");
                        }
                    }
                }
                {
                    // mqtt_next
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mqtt_next = obj;
                    lv_obj_set_pos(obj, 608, 18);
                    lv_obj_set_size(obj, 180, 44);
                    lv_obj_add_event_cb(obj, action_mqtt_next, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // mqtt_next_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.mqtt_next_lbl = obj;
                            lv_obj_set_pos(obj, 0, 12);
                            lv_obj_set_size(obj, 180, 20);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Next");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_mqtt_setup();
}

void tick_screen_page_mqtt_setup() {
}

void create_screen_page_mqtt_connecting() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_mqtt_connecting = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // mqtt_connecting_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.mqtt_connecting_panel = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
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
                    // mqtt_conn_brand
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.mqtt_conn_brand = obj;
                    lv_obj_set_pos(obj, 389, 40);
                    lv_obj_set_size(obj, 22, 22);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // mqtt_conn_brand_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.mqtt_conn_brand_sub = obj;
                    lv_obj_set_pos(obj, 0, 64);
                    lv_obj_set_size(obj, 800, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "SPOTTER");
                }
                {
                    // mqtt_connecting_spinner
                    lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
                    objects.mqtt_connecting_spinner = obj;
                    lv_obj_set_pos(obj, 350, 160);
                    lv_obj_set_size(obj, 100, 100);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                    add_style_spinner_default(obj);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // mqtt_connecting_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.mqtt_connecting_caption = obj;
                    lv_obj_set_pos(obj, 0, 290);
                    lv_obj_set_size(obj, 800, 20);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Connecting to MQTT broker");
                }
                {
                    // mqtt_connecting_host
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.mqtt_connecting_host = obj;
                    lv_obj_set_pos(obj, 0, 312);
                    lv_obj_set_size(obj, 800, 28);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "...");
                }
                {
                    // mqtt_connecting_hint
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.mqtt_connecting_hint = obj;
                    lv_obj_set_pos(obj, 0, 430);
                    lv_obj_set_size(obj, 800, 18);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "TLS cert verification is skipped - any cert is accepted.");
                }
            }
        }
    }
    
    tick_screen_page_mqtt_connecting();
}

void tick_screen_page_mqtt_connecting() {
}

void create_screen_page_rename_sensor() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_rename_sensor = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // rename_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.rename_title = obj;
            lv_obj_set_pos(obj, 0, 12);
            lv_obj_set_size(obj, 800, 28);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Rename Sensor");
        }
        {
            // rename_subtitle
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.rename_subtitle = obj;
            lv_obj_set_pos(obj, 0, 44);
            lv_obj_set_size(obj, 800, 20);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_secondary(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // sensor_rename_input
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.sensor_rename_input = obj;
            lv_obj_set_pos(obj, 40, 76);
            lv_obj_set_size(obj, 720, 56);
            lv_textarea_set_max_length(obj, 24);
            lv_textarea_set_placeholder_text(obj, "Sensor name");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 720, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 720, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sensor_rename_kb
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.sensor_rename_kb = obj;
            lv_obj_set_pos(obj, 8, 140);
            lv_obj_set_size(obj, 784, 270);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_keyboard_default(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 784, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 784, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 270, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 270, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // rename_footer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.rename_footer = obj;
            lv_obj_set_pos(obj, 0, 420);
            lv_obj_set_size(obj, 800, 60);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_style_panel_default(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    // rename_cancel_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.rename_cancel_btn = obj;
                    lv_obj_set_pos(obj, 12, 8);
                    lv_obj_set_size(obj, 180, 44);
                    lv_obj_add_event_cb(obj, action_cancel_sensor_rename, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // rename_cancel_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.rename_cancel_lbl = obj;
                            lv_obj_set_pos(obj, 0, 11);
                            lv_obj_set_size(obj, 180, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Cancel");
                        }
                    }
                }
                {
                    // rename_save_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.rename_save_btn = obj;
                    lv_obj_set_pos(obj, 608, 8);
                    lv_obj_set_size(obj, 180, 44);
                    lv_obj_add_event_cb(obj, action_save_sensor_rename, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // rename_save_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.rename_save_lbl = obj;
                            lv_obj_set_pos(obj, 0, 11);
                            lv_obj_set_size(obj, 180, 22);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Save");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_rename_sensor();
}

void tick_screen_page_rename_sensor() {
}

void create_screen_page_clock_mode() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_clock_mode = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_style_screen_default(obj);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // header_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 54);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_clock_header_bar(obj);
        }
        {
            // clock_brand_icon
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_brand_icon = obj;
            lv_obj_set_pos(obj, 16, 16);
            lv_obj_set_size(obj, 22, 22);
            lv_img_set_src(obj, &img_spotter_logo_22);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // clock_brand_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_brand_text = obj;
            lv_obj_set_pos(obj, 44, 18);
            lv_obj_set_size(obj, 90, 18);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "SPOTTER");
        }
        {
            // clock_brand_divider
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_brand_divider = obj;
            lv_obj_set_pos(obj, 134, 19);
            lv_obj_set_size(obj, 1, 16);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_clock_divider(obj);
        }
        {
            // clock_brand_subtitle
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_brand_subtitle = obj;
            lv_obj_set_pos(obj, 145, 19);
            lv_obj_set_size(obj, 130, 17);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Standalone Clock");
        }
        {
            // clock_warning_pill
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_warning_pill = obj;
            lv_obj_set_pos(obj, 532, 11);
            lv_obj_set_size(obj, 202, 33);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_clock_status_pill(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clock_warning_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.clock_warning_dot = obj;
                    lv_obj_set_pos(obj, 12, 12);
                    lv_obj_set_size(obj, 9, 9);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_clock_pill_dot_style(obj);
                }
                {
                    // clock_warning_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_warning_text = obj;
                    lv_obj_set_pos(obj, 27, 7);
                    lv_obj_set_size(obj, 165, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][29]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "No trailer link - searching");
                }
            }
        }
        {
            // clock_theme_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.clock_theme_btn = obj;
            lv_obj_set_pos(obj, 744, 7);
            lv_obj_set_size(obj, 40, 40);
            lv_obj_add_event_cb(obj, action_toggle_theme, LV_EVENT_CLICKED, (void *)0);
            add_style_clock_theme_toggle_btn(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clock_theme_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_theme_icon = obj;
                    lv_obj_set_pos(obj, 0, 10);
                    lv_obj_set_size(obj, 40, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_fa16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // clock_dow
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_dow = obj;
            lv_obj_set_pos(obj, 360, 57);
            lv_obj_set_size(obj, 80, 18);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "MONDAY");
        }
        {
            // digit_hh
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.digit_hh = obj;
            lv_obj_set_pos(obj, 227, 91);
            lv_obj_set_size(obj, 90, 138);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_clock_hero(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, -3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "--");
        }
        {
            // clock_colon
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_colon = obj;
            lv_obj_set_pos(obj, 309, 91);
            lv_obj_set_size(obj, 44, 138);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_clock_hero(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, ":");
        }
        {
            // digit_mm
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.digit_mm = obj;
            lv_obj_set_pos(obj, 353, 91);
            lv_obj_set_size(obj, 165, 138);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_clock_hero(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, -3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "--");
        }
        {
            // clock_ampm
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_ampm = obj;
            lv_obj_set_pos(obj, 530, 109);
            lv_obj_set_size(obj, 50, 30);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "--");
        }
        {
            // clock_seconds
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_seconds = obj;
            lv_obj_set_pos(obj, 530, 153);
            lv_obj_set_size(obj, 50, 36);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "--");
        }
        {
            // clock_date_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_date_label = obj;
            lv_obj_set_pos(obj, 290, 239);
            lv_obj_set_size(obj, 220, 28);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "June 22, 2026");
        }
        {
            // clock_last_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_last_header = obj;
            lv_obj_set_pos(obj, 18, 265);
            lv_obj_set_size(obj, 290, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "LAST READINGS BEFORE LINK DROPPED");
        }
        {
            // clock_ago_icon
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_ago_icon = obj;
            lv_obj_set_pos(obj, 700, 266);
            lv_obj_set_size(obj, 16, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][29]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_fa16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // clock_ago_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_ago_label = obj;
            lv_obj_set_pos(obj, 720, 265);
            lv_obj_set_size(obj, 70, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_label_default(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][29]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "12 min ago");
        }
        {
            // clock_bat_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_bat_card = obj;
            lv_obj_set_pos(obj, 16, 289);
            lv_obj_set_size(obj, 249, 106);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_clock_card_panel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clock_bat_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_bat_icon = obj;
                    lv_obj_set_pos(obj, 14, 12);
                    lv_obj_set_size(obj, 18, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_fa16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // clock_bat_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_bat_title = obj;
                    lv_obj_set_pos(obj, 38, 12);
                    lv_obj_set_size(obj, 150, 17);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][21]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Battery");
                }
                {
                    // clock_bat_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.clock_bat_dot = obj;
                    lv_obj_set_pos(obj, 227, 17);
                    lv_obj_set_size(obj, 7, 7);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_clock_stale_dot_style(obj);
                }
                {
                    // clock_bat_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_bat_value = obj;
                    lv_obj_set_pos(obj, 14, 36);
                    lv_obj_set_size(obj, 175, 40);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][24]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "87");
                }
                {
                    // clock_bat_unit
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_bat_unit = obj;
                    lv_obj_set_pos(obj, 110, 53);
                    lv_obj_set_size(obj, 60, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][25]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "%");
                }
                {
                    // clock_bat_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_bat_sub = obj;
                    lv_obj_set_pos(obj, 14, 80);
                    lv_obj_set_size(obj, 230, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][26]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "12.9 V - house bank");
                }
            }
        }
        {
            // clock_sol_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_sol_card = obj;
            lv_obj_set_pos(obj, 275, 289);
            lv_obj_set_size(obj, 249, 106);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_clock_card_panel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clock_sol_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_sol_icon = obj;
                    lv_obj_set_pos(obj, 14, 12);
                    lv_obj_set_size(obj, 18, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_fa16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // clock_sol_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_sol_title = obj;
                    lv_obj_set_pos(obj, 38, 12);
                    lv_obj_set_size(obj, 150, 17);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][21]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Solar");
                }
                {
                    // clock_sol_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.clock_sol_dot = obj;
                    lv_obj_set_pos(obj, 227, 17);
                    lv_obj_set_size(obj, 7, 7);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_clock_stale_dot_style(obj);
                }
                {
                    // clock_sol_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_sol_value = obj;
                    lv_obj_set_pos(obj, 14, 36);
                    lv_obj_set_size(obj, 175, 40);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][24]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "410");
                }
                {
                    // clock_sol_unit
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_sol_unit = obj;
                    lv_obj_set_pos(obj, 110, 53);
                    lv_obj_set_size(obj, 60, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][25]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "W");
                }
                {
                    // clock_sol_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_sol_sub = obj;
                    lv_obj_set_pos(obj, 14, 80);
                    lv_obj_set_size(obj, 230, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][26]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Charging - bulk");
                }
            }
        }
        {
            // clock_fresh_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_fresh_card = obj;
            lv_obj_set_pos(obj, 535, 289);
            lv_obj_set_size(obj, 249, 106);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_clock_card_panel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clock_fresh_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_fresh_icon = obj;
                    lv_obj_set_pos(obj, 14, 12);
                    lv_obj_set_size(obj, 18, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_fa16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // clock_fresh_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_fresh_title = obj;
                    lv_obj_set_pos(obj, 38, 12);
                    lv_obj_set_size(obj, 150, 17);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][21]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Fresh");
                }
                {
                    // clock_fresh_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.clock_fresh_dot = obj;
                    lv_obj_set_pos(obj, 227, 17);
                    lv_obj_set_size(obj, 7, 7);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_clock_stale_dot_style(obj);
                }
                {
                    // clock_fresh_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_fresh_value = obj;
                    lv_obj_set_pos(obj, 14, 36);
                    lv_obj_set_size(obj, 175, 40);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][24]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_mono_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "62");
                }
                {
                    // clock_fresh_unit
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_fresh_unit = obj;
                    lv_obj_set_pos(obj, 110, 53);
                    lv_obj_set_size(obj, 60, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][25]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "%");
                }
                {
                    // clock_fresh_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_fresh_sub = obj;
                    lv_obj_set_pos(obj, 14, 80);
                    lv_obj_set_size(obj, 230, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][26]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Grey 38% - Black 21%");
                }
            }
        }
        {
            // footer_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.footer_bar = obj;
            lv_obj_set_pos(obj, 0, 407);
            lv_obj_set_size(obj, 800, 73);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_clock_footer_bar(obj);
        }
        {
            // clock_retry_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.clock_retry_btn = obj;
            lv_obj_set_pos(obj, 16, 420);
            lv_obj_set_size(obj, 618, 48);
            lv_obj_add_event_cb(obj, action_retry_connection, LV_EVENT_CLICKED, (void *)0);
            add_style_clock_retry_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clock_retry_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_retry_icon = obj;
                    lv_obj_set_pos(obj, 247, 14);
                    lv_obj_set_size(obj, 19, 19);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][32]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_fa16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // clock_retry_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_retry_label = obj;
                    lv_obj_set_pos(obj, 275, 12);
                    lv_obj_set_size(obj, 200, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][32]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Retry connection");
                }
            }
        }
        {
            // clock_settings_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.clock_settings_btn = obj;
            lv_obj_set_pos(obj, 644, 420);
            lv_obj_set_size(obj, 140, 48);
            lv_obj_add_event_cb(obj, action_go_setup_from_clock, LV_EVENT_CLICKED, (void *)0);
            add_style_clock_settings_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clock_settings_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_settings_icon = obj;
                    lv_obj_set_pos(obj, 24, 14);
                    lv_obj_set_size(obj, 19, 19);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_fa16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // clock_settings_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.clock_settings_label = obj;
                    lv_obj_set_pos(obj, 52, 12);
                    lv_obj_set_size(obj, 80, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Settings");
                }
            }
        }
    }
    
    tick_screen_page_clock_mode();
}

void tick_screen_page_clock_mode() {
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
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 46, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // status_brand_icon
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 12, 12);
                    lv_obj_set_size(obj, 18, 18);
                    lv_img_set_src(obj, &img_spotter_logo_18);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_img_recolor(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // status_brand_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 46, 14);
                    lv_obj_set_size(obj, 78, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "SPOTTER");
                }
                {
                    // status_div_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 128, 15);
                    lv_obj_set_size(obj, 1, 16);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // status_link_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 141, 20);
                    lv_obj_set_size(obj, 7, 7);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // status_link_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                    lv_obj_set_pos(obj, 155, 16);
                    lv_obj_set_size(obj, 220, 16);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "TANDEM AXLE - Linked");
                }
                {
                    // status_wifi_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                    lv_obj_set_pos(obj, 540, 14);
                    lv_obj_set_size(obj, 18, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // status_signal_left
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                    lv_obj_set_pos(obj, 564, 14);
                    lv_obj_set_size(obj, 20, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // status_signal_right
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                    lv_obj_set_pos(obj, 597, 14);
                    lv_obj_set_size(obj, 20, 18);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_fa16_icon(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // status_div_2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                    lv_obj_set_pos(obj, 608, 14);
                    lv_obj_set_size(obj, 1, 16);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    add_style_style_panel_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // status_speed_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                    lv_obj_set_pos(obj, 618, 10);
                    lv_obj_set_size(obj, 34, 28);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--");
                }
                {
                    // status_speed_unit
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                    lv_obj_set_pos(obj, 655, 20);
                    lv_obj_set_size(obj, 26, 14);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "MPH");
                }
                {
                    // status_time
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                    lv_obj_set_pos(obj, 690, 14);
                    lv_obj_set_size(obj, 45, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "--:--");
                }
                {
                    // status_theme_toggle
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 13] = obj;
                    lv_obj_set_pos(obj, 750, 6);
                    lv_obj_set_size(obj, 34, 34);
                    lv_obj_add_event_cb(obj, action_toggle_theme, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 17, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // status_theme_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 14] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 16, 16);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa16_icon(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
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
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 800, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 66, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 66, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dock_btn_drive
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 200, 66);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 31, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_drive_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                            lv_obj_set_pos(obj, 0, 9);
                            lv_obj_set_size(obj, 200, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_fa32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_drive_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 0, 41);
                            lv_obj_set_size(obj, 200, 16);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 31, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_lights_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 0, 9);
                            lv_obj_set_size(obj, 200, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_fa32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_lights_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                            lv_obj_set_pos(obj, 0, 41);
                            lv_obj_set_size(obj, 200, 16);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 31, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_alarms_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                            lv_obj_set_pos(obj, 0, 9);
                            lv_obj_set_size(obj, 200, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_fa32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_alarms_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 0, 41);
                            lv_obj_set_size(obj, 200, 16);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 31, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_btn_setup_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                            lv_obj_set_pos(obj, 0, 9);
                            lv_obj_set_size(obj, 200, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_fa32_icon(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_fa32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // dock_btn_setup_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                            lv_obj_set_pos(obj, 0, 41);
                            lv_obj_set_size(obj, 200, 16);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
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
    
    lv_style_set_text_color(get_style_label_nav_text_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_text_color(get_style_label_nav_text_alternate_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_label_secondary_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_bg_color(get_style_message_box_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_text_color(get_style_nav_bar_icon_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_bg_color(get_style_panel_nav_bar_top_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_text_color(get_style_panel_nav_bar_top_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_bg_color(get_style_panel_screen_content_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_roller_default_SELECTED_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_text_color(get_style_roller_default_SELECTED_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
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
    
    lv_style_set_text_color(get_style_style_device_status_ind_on_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_panel_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_bg_color(get_style_style_panel_dialog_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_bg_color(get_style_style_panel_modal_blocker_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_style_panel_nav_bar_bottom_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_style_screen_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_style_screen_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_style_top_nav_text_normal_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_bg_color(get_style_style_top_nav_text_normal_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_switch_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_label_data_value18_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_label_data_value32_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_label_data_value36_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_bg_color(get_style_panel_warning_ribbon_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    
    lv_style_set_text_color(get_style_label_warning_text_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_text_color(get_style_label_clock_hero_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_bg_color(get_style_button_clock_settings_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_clock_screen_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_text_color(get_style_clock_screen_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_clock_header_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_clock_header_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_bg_color(get_style_clock_footer_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_clock_footer_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_bg_color(get_style_clock_divider_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_clock_status_pill_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][27]));
    
    lv_style_set_border_color(get_style_clock_status_pill_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][28]));
    
    lv_style_set_bg_color(get_style_clock_pill_dot_style_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][30]));
    
    lv_style_set_bg_color(get_style_clock_stale_dot_style_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][31]));
    
    lv_style_set_bg_color(get_style_clock_theme_toggle_btn_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_clock_theme_toggle_btn_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_clock_theme_toggle_btn_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    
    lv_style_set_bg_color(get_style_clock_theme_toggle_btn_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_bg_color(get_style_clock_card_panel_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][22]));
    
    lv_style_set_border_color(get_style_clock_card_panel_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][23]));
    
    lv_style_set_bg_color(get_style_clock_retry_button_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    
    lv_style_set_shadow_color(get_style_clock_retry_button_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    
    lv_style_set_text_color(get_style_clock_retry_button_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][32]));
    
    lv_style_set_bg_color(get_style_clock_retry_button_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][21]));
    
    lv_style_set_bg_color(get_style_clock_settings_button_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_clock_settings_button_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_clock_settings_button_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    
    lv_style_set_bg_color(get_style_clock_settings_button_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_obj_set_style_bg_color(objects.drive_body, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_cab, lv_color_hex(theme_colors[theme_index][47]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_cab, lv_color_hex(theme_colors[theme_index][48]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_cab, lv_color_hex(theme_colors[theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_windshield, lv_color_hex(theme_colors[theme_index][54]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_windshield, lv_color_hex(theme_colors[theme_index][55]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_mirror_l, lv_color_hex(theme_colors[theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_mirror_r, lv_color_hex(theme_colors[theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_hitch_aframe, lv_color_hex(theme_colors[theme_index][41]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_hitch_aframe, lv_color_hex(theme_colors[theme_index][42]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_hitch_dot, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_hitch_dot, lv_color_hex(theme_colors[theme_index][42]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_breakaway, lv_color_hex(theme_colors[theme_index][40]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_trailer_body, lv_color_hex(theme_colors[theme_index][47]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_trailer_body, lv_color_hex(theme_colors[theme_index][48]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_trailer_body, lv_color_hex(theme_colors[theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_ac, lv_color_hex(theme_colors[theme_index][47]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_ac, lv_color_hex(theme_colors[theme_index][49]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_axle1_bar, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_l1, lv_color_hex(theme_colors[theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_tire_l1, lv_color_hex(theme_colors[theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_l1, lv_color_hex(theme_colors[theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_r1, lv_color_hex(theme_colors[theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_tire_r1, lv_color_hex(theme_colors[theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_r1, lv_color_hex(theme_colors[theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_l1_psi, lv_color_hex(theme_colors[theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_r1_psi, lv_color_hex(theme_colors[theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_axle2_bar, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_l2, lv_color_hex(theme_colors[theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_tire_l2, lv_color_hex(theme_colors[theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_l2, lv_color_hex(theme_colors[theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_r2, lv_color_hex(theme_colors[theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_tire_r2, lv_color_hex(theme_colors[theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_r2, lv_color_hex(theme_colors[theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_l2_psi, lv_color_hex(theme_colors[theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_r2_psi, lv_color_hex(theme_colors[theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_axle3_bar, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_l3, lv_color_hex(theme_colors[theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_tire_l3, lv_color_hex(theme_colors[theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_l3, lv_color_hex(theme_colors[theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_tire_r3, lv_color_hex(theme_colors[theme_index][51]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_tire_r3, lv_color_hex(theme_colors[theme_index][50]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_tire_r3, lv_color_hex(theme_colors[theme_index][52]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_l3_psi, lv_color_hex(theme_colors[theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_tire_r3_psi, lv_color_hex(theme_colors[theme_index][53]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_run, lv_color_hex(theme_colors[theme_index][41]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_run, lv_color_hex(theme_colors[theme_index][42]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_run_icon, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_run_lbl, lv_color_hex(theme_colors[theme_index][43]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_left, lv_color_hex(theme_colors[theme_index][35]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_left, lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_left_icon, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_left_lbl, lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_brake, lv_color_hex(theme_colors[theme_index][44]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_brake, lv_color_hex(theme_colors[theme_index][45]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_brake_icon, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_brake_lbl, lv_color_hex(theme_colors[theme_index][46]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_right, lv_color_hex(theme_colors[theme_index][35]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_right, lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_right_icon, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_right_lbl, lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_chip_rev, lv_color_hex(theme_colors[theme_index][35]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_chip_rev, lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_rev_icon, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_chip_rev_lbl, lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bat_arc, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bat_arc, lv_color_hex(theme_colors[theme_index][0]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_bat_dial, lv_color_hex(theme_colors[theme_index][38]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_bat_dial, lv_color_hex(theme_colors[theme_index][39]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_bat_dial, lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_icon, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_value, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_volts, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bat_remain, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_solar_arc, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_solar_arc, lv_color_hex(theme_colors[theme_index][0]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_solar_dial, lv_color_hex(theme_colors[theme_index][38]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_grad_color(objects.drive_solar_dial, lv_color_hex(theme_colors[theme_index][39]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_solar_dial, lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_icon, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_value, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_unit, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_pct, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_l_a1, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_l_a1, lv_color_hex(theme_colors[theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_l_a2, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_l_a2, lv_color_hex(theme_colors[theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_l_a3, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_l_a3, lv_color_hex(theme_colors[theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_r_a1, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_r_a1, lv_color_hex(theme_colors[theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_r_a2, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_r_a2, lv_color_hex(theme_colors[theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_r_a3, lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.drive_bsm_r_a3, lv_color_hex(theme_colors[theme_index][37]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bsm_l_car, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bsm_r_car, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.drive_bsm_warning, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.drive_bsm_warning, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_bsm_warn_text, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_solar_w, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.drive_sol_icon, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_header, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_header, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_prev_btn, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_prev_btn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_prev_icon, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_next_btn, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_next_btn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_next_icon, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_zone_title, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_zone_sub, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_body, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_body_placeholder, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_footer, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_footer, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_all_on_btn, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_all_on_lbl, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_all_off_btn, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_all_off_btn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_all_off_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_zone_dots, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_zone_dot_0, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_zone_dot_1, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_zone_dot_2, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_zone_dot_3, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_zone_dot_4, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_zone_dot_5, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.lights_off_all_btn, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.lights_off_all_btn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.lights_off_all_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarms_body, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarms_header, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.alarms_header, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_title, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_subtitle, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_armed_icon, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarms_armed_count, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarms_list, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_spoor0_grp_lbl, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s1_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s2_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s3_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s4_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s5_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s6_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s7_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_s8_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d1_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d2_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d3_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d4_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d5_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d6_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d7_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor0_d8_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_spoor1_grp_lbl, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s1_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s2_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s3_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s4_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s5_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s6_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s7_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_s8_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d1_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d2_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d3_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d4_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d5_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d6_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d7_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor1_d8_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.alarm_spoor2_grp_lbl, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s1_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s2_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s3_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s4_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s5_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s6_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s7_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_s8_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d1_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d2_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d3_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d4_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d5_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d6_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d7_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.alarm_spoor2_d8_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
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
    
    lv_obj_set_style_text_color(objects.setup_theme_light_icon, lv_color_hex(theme_colors[theme_index][12]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
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
    
    lv_obj_set_style_text_color(objects.setup_reset_conn_title, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_reset_conn_btn, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_reset_conn_btn, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_reset_conn_btn_lbl, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_alarm_timing_title, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_audio_title, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_timezone_title, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_date_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_date_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_date_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_date_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_date_value, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_time_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_time_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_time_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_time_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_time_value, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.setup_clock_format_row, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.setup_clock_format_row, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_clock_format_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_clock_format_name, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.setup_clock_format_desc, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_header, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_header, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_brand, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_brand_sub, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_title, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_sub, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.wifi_scan_spinner, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_scan_status, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_scan_list, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_0, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_0, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_0, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_0, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_0, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_0, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_0, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_0, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_0, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_0, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_0, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_1, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_1, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_1, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_1, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_1, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_1, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_1, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_2, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_2, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_2, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_2, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_2, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_2, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_2, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_3, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_3, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_3, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_3, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_3, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_3, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_3, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_3, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_3, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_3, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_3, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_4, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_4, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_4, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_4, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_4, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_4, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_4, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_4, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_4, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_4, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_4, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_5, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_5, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_5, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_5, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_5, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_5, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_5, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_5, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_5, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_5, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_5, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_6, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_6, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_6, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_6, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_6, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_6, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_6, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_7, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_net_7, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_7, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_ssid_7, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_7, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_7, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_7, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_7, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_7, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_7, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_CHECKED);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_7, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_footer, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_footer, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_btn_refresh, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_btn_refresh, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_btn_refresh_icon, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_btn_refresh_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_btn_skip, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_btn_skip, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_btn_skip_lbl, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_password_panel, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_pwd_caption, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_pwd_ssid, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_pwd_input, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_pwd_input, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_pwd_input, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_pwd_reveal, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_pwd_reveal, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_pwd_reveal_icon, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_pwd_cancel, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_pwd_cancel, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_pwd_cancel_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_pwd_connect, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.wifi_pwd_connect, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_pwd_connect_lbl, lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_connecting_panel, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_conn_brand, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_conn_brand_sub, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.wifi_connecting_spinner, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_connecting_caption, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_connecting_ssid, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_connecting_hint, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_brand, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_brand_text, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_caption, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_step, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.mqtt_input, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.mqtt_input, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_input, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.mqtt_footer, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.mqtt_footer, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.mqtt_back, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.mqtt_back, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_back_lbl, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.mqtt_next, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.mqtt_next, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.mqtt_connecting_panel, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_conn_brand, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_conn_brand_sub, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_arc_color(objects.mqtt_connecting_spinner, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_connecting_caption, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_connecting_host, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mqtt_connecting_hint, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.rename_title, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.rename_subtitle, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.sensor_rename_input, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.sensor_rename_input, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.sensor_rename_input, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.rename_footer, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.rename_save_btn, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.rename_save_lbl, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.page_clock_mode, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.page_clock_mode, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_brand_text, lv_color_hex(theme_colors[theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_brand_subtitle, lv_color_hex(theme_colors[theme_index][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_warning_text, lv_color_hex(theme_colors[theme_index][29]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_theme_icon, lv_color_hex(theme_colors[theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_dow, lv_color_hex(theme_colors[theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.digit_hh, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_colon, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.digit_mm, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_ampm, lv_color_hex(theme_colors[theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_seconds, lv_color_hex(theme_colors[theme_index][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_date_label, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_last_header, lv_color_hex(theme_colors[theme_index][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_ago_icon, lv_color_hex(theme_colors[theme_index][29]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_ago_label, lv_color_hex(theme_colors[theme_index][29]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_bat_icon, lv_color_hex(theme_colors[theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_bat_title, lv_color_hex(theme_colors[theme_index][21]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_bat_value, lv_color_hex(theme_colors[theme_index][24]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_bat_unit, lv_color_hex(theme_colors[theme_index][25]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_bat_sub, lv_color_hex(theme_colors[theme_index][26]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_sol_icon, lv_color_hex(theme_colors[theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_sol_title, lv_color_hex(theme_colors[theme_index][21]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_sol_value, lv_color_hex(theme_colors[theme_index][24]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_sol_unit, lv_color_hex(theme_colors[theme_index][25]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_sol_sub, lv_color_hex(theme_colors[theme_index][26]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_fresh_icon, lv_color_hex(theme_colors[theme_index][20]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_fresh_title, lv_color_hex(theme_colors[theme_index][21]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_fresh_value, lv_color_hex(theme_colors[theme_index][24]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_fresh_unit, lv_color_hex(theme_colors[theme_index][25]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_fresh_sub, lv_color_hex(theme_colors[theme_index][26]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_retry_icon, lv_color_hex(theme_colors[theme_index][32]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_retry_label, lv_color_hex(theme_colors[theme_index][32]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_settings_icon, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.clock_settings_label, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    {
        int startWidgetIndex = 11;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 91;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 105;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 144;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 158;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 451;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 465;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][37]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][34]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 545;
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 0], lv_color_hex(theme_colors[theme_index][33]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 5], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 6], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 8], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 9], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 11], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 12], lv_color_hex(theme_colors[theme_index][36]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    lv_obj_invalidate(objects.page_drive);
    lv_obj_invalidate(objects.page_lights);
    lv_obj_invalidate(objects.page_alarms);
    lv_obj_invalidate(objects.page_setup);
    lv_obj_invalidate(objects.page_wifi_setup);
    lv_obj_invalidate(objects.page_wifi_connecting);
    lv_obj_invalidate(objects.page_mqtt_setup);
    lv_obj_invalidate(objects.page_mqtt_connecting);
    lv_obj_invalidate(objects.page_rename_sensor);
    lv_obj_invalidate(objects.page_clock_mode);
}

uint32_t theme_colors[2][60] = {
    { 0xff52a441, 0xff000000, 0xfff5f5f5, 0xffd0e2c7, 0xffffffff, 0xff5e635a, 0xff48e6fe, 0xffffffff, 0xffff5453, 0xff1a1a1a, 0xff4a4a4a, 0xff3d7b31, 0xffffc107, 0xfff5f5f5, 0xffffffff, 0xffdddddd, 0xffe2e2e2, 0xff1a1a1a, 0xff4a4a4a, 0xff888888, 0xff52a441, 0xff3d7b31, 0xffedf3ea, 0xffdcedd9, 0xff6a6a6a, 0xff9a9a9a, 0xffa0a0a0, 0xfffff8e6, 0xfff2d98a, 0xff9a6d00, 0xffe0a800, 0xffc9a24b, 0xffffffff, 0xffdddddd, 0xffe2e2e2, 0xffeef0ee, 0xff8a8a8a, 0xffe4e4e4, 0xffffffff, 0xffeef0ee, 0xff3d7b31, 0xffedf3ea, 0xffcfe3c8, 0xff4f7a46, 0xfffbeaea, 0xfff0caca, 0xffb06a6a, 0xfff4f4f4, 0xffe4e4e4, 0xffc8c8c8, 0xffdcdcdc, 0xffbcbcbc, 0xffbdbdbd, 0xff5a5a5a, 0xffd6e4f1, 0xffaac4dd, 0xff9a6d00, 0xff3a0808, 0xff1c0303, 0xffc23b3a },
    { 0xff7bc96a, 0xff000000, 0xff000000, 0xff859195, 0xff121212, 0xff9db8bb, 0xff48e6fe, 0xffffffff, 0xffff5453, 0xffffffff, 0xffa2a2a2, 0xff74fe00, 0xffffc107, 0xff000000, 0xff0d0d0d, 0xff2a2a2a, 0xff2a2a2a, 0xffffffff, 0xffaaaaaa, 0xff777777, 0xff7bc96a, 0xff8fd080, 0xff141a13, 0xff26331f, 0xff9a9a9a, 0xff777777, 0xff6f6f6f, 0xff1a1605, 0xff5a4a18, 0xffffc107, 0xffffc107, 0xffd4a93f, 0xff08140a, 0xff1f1f1f, 0xff232323, 0xff0e0e0e, 0xff6f6f6f, 0xff242424, 0xff141414, 0xff070707, 0xff5a8a50, 0xff0e120e, 0xff233223, 0xff9fae9f, 0xff120e0e, 0xff322323, 0xffae9f9f, 0xff1d1d1d, 0xff0d0d0d, 0xff313131, 0xff272727, 0xff040404, 0xff343434, 0xffe6e6e6, 0xff0d1620, 0xff25333f, 0xffffc107, 0xff3a0808, 0xff1c0303, 0xffc23b3a },
};


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_page_drive,
    tick_screen_page_lights,
    tick_screen_page_alarms,
    tick_screen_page_setup,
    tick_screen_page_wifi_setup,
    tick_screen_page_wifi_connecting,
    tick_screen_page_mqtt_setup,
    tick_screen_page_mqtt_connecting,
    tick_screen_page_rename_sensor,
    tick_screen_page_clock_mode,
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
    create_screen_page_wifi_setup();
    create_screen_page_wifi_connecting();
    create_screen_page_mqtt_setup();
    create_screen_page_mqtt_connecting();
    create_screen_page_rename_sensor();
    create_screen_page_clock_mode();
}
