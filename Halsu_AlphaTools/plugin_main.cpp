/*
 * Halsu AlphaTools for OBS Studio
 * Copyright (C) 2026 Halsu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>
 */

extern "C" {
#include <graphics/graphics.h>
#include <graphics/image-file.h>
#include <graphics/vec4.h>
#include <obs-module.h>
#include <util/dstr.h>
#include <util/platform.h>

}
#include <sys/stat.h>

OBS_DECLARE_MODULE()

/*
 * Generated OBS Plugin for Halsu_AlphaTools
 */

// --- Dynamic Uniform IDs ---
struct shader_data {
  obs_source_t *context;
  gs_effect_t *effect;

  int Tool_Mode;
  float Alpha_Expansion;
  float Alpha_Blur;
  float Median_Alpha;
  bool Unpremultiply;
  float Matte_offset_x;
  float Matte_offset_y;
  bool Preview_Alpha;
};

// --- Get Name ---
const char *get_name(void *unused) { return "Halsu AlphaTools"; }

// --- Update (Link UI to Variables) ---
void update(void *data, obs_data_t *settings) {
  shader_data *s = (shader_data *)data;

  s->Tool_Mode = (int)obs_data_get_int(settings, "Tool_Mode");
  s->Alpha_Expansion = (float)obs_data_get_double(settings, "Alpha_Expansion");
  s->Alpha_Blur = (float)obs_data_get_double(settings, "Alpha_Blur");
  s->Median_Alpha = (float)obs_data_get_double(settings, "Median_Alpha");
  s->Unpremultiply = obs_data_get_bool(settings, "Unpremultiply");
  s->Matte_offset_x = (float)obs_data_get_double(settings, "Matte_offset_x");
  s->Matte_offset_y = (float)obs_data_get_double(settings, "Matte_offset_y");
  s->Preview_Alpha = obs_data_get_bool(settings, "Preview_Alpha");
}

// --- Render (Draw Quad with Shader) ---
void video_render(void *data, gs_effect_t *effect) {
  shader_data *s = (shader_data *)data;

  if (!s->effect) {
    obs_source_skip_video_filter(s->context);
    return;
  }

  if (!obs_source_process_filter_begin(s->context, GS_RGBA,
                                       OBS_ALLOW_DIRECT_RENDERING))
    return;

  // Standard OBS Filter Bindings (obs-shaderfilter compatible)
  obs_source_t *target = obs_filter_get_target(s->context);
  uint32_t width = obs_source_get_base_width(target);
  uint32_t height = obs_source_get_base_height(target);

  struct vec4 v_uv_size;
  v_uv_size.x = (float)width;
  v_uv_size.y = (float)height;
  v_uv_size.z = width ? 1.0f / width : 0.0f;
  v_uv_size.w = height ? 1.0f / height : 0.0f;
  gs_effect_set_vec4(gs_effect_get_param_by_name(s->effect, "uv_size"),
                     &v_uv_size);

  // Bind Uniforms
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Tool_Mode"),
                    s->Tool_Mode);
  float Alpha_Expansion_norm =
      (s->Alpha_Expansion - 0.00000f) / (100.00000f - 0.00000f);
  float Alpha_Expansion_final =
      Alpha_Expansion_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Alpha_Expansion"),
                      Alpha_Expansion_final);
  float Alpha_Blur_norm = (s->Alpha_Blur - 0.00000f) / (100.00000f - 0.00000f);
  float Alpha_Blur_final =
      Alpha_Blur_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Alpha_Blur"),
                      Alpha_Blur_final);
  float Median_Alpha_norm =
      (s->Median_Alpha - 0.00000f) / (100.00000f - 0.00000f);
  float Median_Alpha_final =
      Median_Alpha_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Median_Alpha"),
                      Median_Alpha_final);
  gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Unpremultiply"),
                     s->Unpremultiply);
  float Matte_offset_x_norm =
      (s->Matte_offset_x - 0.00000f) / (100.00000f - 0.00000f);
  float Matte_offset_x_final =
      Matte_offset_x_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_offset_x"),
                      Matte_offset_x_final);
  float Matte_offset_y_norm =
      (s->Matte_offset_y - 0.00000f) / (100.00000f - 0.00000f);
  float Matte_offset_y_final =
      Matte_offset_y_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_offset_y"),
                      Matte_offset_y_final);
  gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Preview_Alpha"),
                     s->Preview_Alpha);

  obs_source_process_filter_end(s->context, s->effect, 0, 0);
}

// --- Properties (UI Definition) ---
obs_properties_t *get_properties(void *data) {
  obs_properties_t *props = obs_properties_create();

  obs_property_t *p_Tool_Mode =
      obs_properties_add_list(props, "Tool_Mode", "Tool Mode",
                              OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
  obs_property_list_add_int(p_Tool_Mode, "Alpha expansion", 0);
  obs_property_list_add_int(p_Tool_Mode, "Alpha expansion blur", 1);
  obs_property_list_add_int(p_Tool_Mode, "Alpha blur", 2);
  obs_property_list_add_int(p_Tool_Mode, "Alpha Median", 3);
  obs_properties_add_float_slider(props, "Alpha_Expansion", "Alpha Expansion",
                                  0.0, 100.0, 0.01);
  obs_properties_add_float_slider(props, "Alpha_Blur", "Alpha Blur", 0.0, 100.0,
                                  0.1);
  obs_properties_add_float_slider(props, "Median_Alpha", "Median Alpha", 0.0,
                                  100.0, 0.1);
  obs_properties_add_bool(props, "Unpremultiply", "Unpremultiply");
  obs_properties_add_float_slider(props, "Matte_offset_x", "Matte offset x",
                                  0.0, 100.0, 1.0);
  obs_properties_add_float_slider(props, "Matte_offset_y", "Matte offset y",
                                  0.0, 100.0, 1.0);
  obs_properties_add_bool(props, "Preview_Alpha", "Preview Alpha");

  return props;
}
// --- Defaults ---
void get_defaults(obs_data_t *settings) {
  obs_data_set_default_int(settings, "Tool_Mode", 1);
  obs_data_set_default_double(settings, "Alpha_Expansion", 50.00);
  obs_data_set_default_double(settings, "Alpha_Blur", 0.00);
  obs_data_set_default_double(settings, "Median_Alpha", 0.00);
  obs_data_set_default_bool(settings, "Unpremultiply", true);
  obs_data_set_default_double(settings, "Matte_offset_x", 50.00);
  obs_data_set_default_double(settings, "Matte_offset_y", 50.00);
  obs_data_set_default_bool(settings, "Preview_Alpha", false);
}

// --- Lifecycle ---
void *create(obs_data_t *settings, obs_source_t *context) {
  shader_data *s = (shader_data *)bzalloc(sizeof(shader_data));
  s->context = context;

  char *effect_path = obs_module_file("Halsu_AlphaTools.effect");

  obs_enter_graphics();
  s->effect = gs_effect_create_from_file(effect_path, NULL);
  obs_leave_graphics();

  bfree(effect_path);

  if (!s->effect) {
    bfree(s);
    return NULL;
  }

  update(s, settings);
  return s;
}

void destroy(void *data) {
  shader_data *s = (shader_data *)data;
  if (s->effect) {
    obs_enter_graphics();
    gs_effect_destroy(s->effect);
    obs_leave_graphics();
  }
  bfree(s);
}

// --- Info Definition ---
struct obs_source_info info = {};

bool obs_module_load(void) {
  info.id = "Halsu_AlphaTools";
  info.type = OBS_SOURCE_TYPE_FILTER;
  info.output_flags = OBS_SOURCE_VIDEO;
  info.get_name = get_name;
  info.create = create;
  info.destroy = destroy;
  info.update = update;
  info.get_properties = get_properties;
  info.get_defaults = get_defaults;
  info.video_render = video_render;

  obs_register_source(&info);
  return true;
}
