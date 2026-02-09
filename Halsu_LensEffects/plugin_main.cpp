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
 * Generated OBS Plugin for Halsu_LensEffects
 */

// --- Dynamic Uniform IDs ---
struct shader_data {
  obs_source_t *context;
  gs_effect_t *effect;

  int Effect;
  int Radius;
  int Quality;
  int Blend;
  int Vignette_strength;
  int Vignette_radius;
  int Vignette_falloff;
  int Vignette_blend_mode;
  uint32_t Vignette_color;
};

// --- Get Name ---
const char *get_name(void *unused) { return "Halsu LensEffects"; }

// --- Update (Link UI to Variables) ---
void update(void *data, obs_data_t *settings) {
  shader_data *s = (shader_data *)data;

  s->Effect = (int)obs_data_get_int(settings, "Effect");
  s->Radius = (int)obs_data_get_int(settings, "Radius");
  s->Quality = (int)obs_data_get_int(settings, "Quality");
  s->Blend = (int)obs_data_get_int(settings, "Blend");
  s->Vignette_strength = (int)obs_data_get_int(settings, "Vignette_strength");
  s->Vignette_radius = (int)obs_data_get_int(settings, "Vignette_radius");
  s->Vignette_falloff = (int)obs_data_get_int(settings, "Vignette_falloff");
  s->Vignette_blend_mode =
      (int)obs_data_get_int(settings, "Vignette_blend_mode");
  s->Vignette_color = (uint32_t)obs_data_get_int(settings, "Vignette_color");
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
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Effect"),
                    s->Effect);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Radius"),
                    s->Radius);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Quality"),
                    s->Quality);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Blend"), s->Blend);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Vignette_strength"),
                    s->Vignette_strength);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Vignette_radius"),
                    s->Vignette_radius);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Vignette_falloff"),
                    s->Vignette_falloff);
  gs_effect_set_int(
      gs_effect_get_param_by_name(s->effect, "Vignette_blend_mode"),
      s->Vignette_blend_mode);
  struct vec4 v_Vignette_color;
  vec4_from_rgba(&v_Vignette_color, s->Vignette_color);
  gs_effect_set_vec4(gs_effect_get_param_by_name(s->effect, "Vignette_color"),
                     &v_Vignette_color);

  obs_source_process_filter_end(s->context, s->effect, 0, 0);
}

// --- Properties (UI Definition) ---
obs_properties_t *get_properties(void *data) {
  obs_properties_t *props = obs_properties_create();

  obs_property_t *p_Effect = obs_properties_add_list(
      props, "Effect", "Effect", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
  obs_property_list_add_int(p_Effect, "Vignette Only", 0);
  obs_property_list_add_int(p_Effect, "Circle Blur", 1);
  obs_property_list_add_int(p_Effect, "Lens Blur (Natural)", 2);
  obs_property_list_add_int(p_Effect, "Lens Blur (Bokeh)", 3);
  obs_property_list_add_int(p_Effect, "Lens Blur (Bokeh Boost)", 4);
  obs_property_list_add_int(p_Effect, "Diffusion", 5);
  obs_property_list_add_int(p_Effect, "Diffusion (Boost)", 6);
  obs_property_list_add_int(p_Effect, "Glow", 7);
  obs_property_list_add_int(p_Effect, "Chromatic Aberration (RGB)", 8);
  obs_property_list_add_int(p_Effect, "Chromatic Aberration (BG)", 9);
  obs_property_list_add_int(p_Effect, "Chromatic Aberration (RB)", 10);
  obs_property_list_add_int(p_Effect, "Chromatic Aberration (RG)", 11);
  obs_properties_add_int_slider(props, "Radius", "Radius", 0, 100, 1);
  obs_properties_add_int_slider(props, "Quality", "Quality", 0, 100, 1);
  obs_properties_add_int_slider(props, "Blend", "Blend", 0, 100, 1);
  obs_properties_add_int_slider(props, "Vignette_strength", "Vignette strength",
                                0, 100, 1);
  obs_properties_add_int_slider(props, "Vignette_radius", "Vignette radius", 0,
                                100, 1);
  obs_properties_add_int_slider(props, "Vignette_falloff", "Vignette falloff",
                                0, 100, 1);
  obs_property_t *p_Vignette_blend_mode = obs_properties_add_list(
      props, "Vignette_blend_mode", "Vignette blend mode", OBS_COMBO_TYPE_LIST,
      OBS_COMBO_FORMAT_INT);
  obs_property_list_add_int(p_Vignette_blend_mode, "Off", 0);
  obs_property_list_add_int(p_Vignette_blend_mode, "Mix", 1);
  obs_property_list_add_int(p_Vignette_blend_mode, "Overlay", 2);
  obs_property_list_add_int(p_Vignette_blend_mode, "Multiply", 3);
  obs_property_list_add_int(p_Vignette_blend_mode, "Screen", 4);
  obs_property_list_add_int(p_Vignette_blend_mode, "Gamma", 5);
  obs_property_list_add_int(p_Vignette_blend_mode, "Modulate Blur (Edges)", 6);
  obs_property_list_add_int(p_Vignette_blend_mode, "Modulate Blur (Center)", 7);
  obs_properties_add_color(props, "Vignette_color", "Vignette color");

  return props;
}
// --- Defaults ---
void get_defaults(obs_data_t *settings) {
  obs_data_set_default_int(settings, "Effect", 3);
  obs_data_set_default_int(settings, "Radius", 30);
  obs_data_set_default_int(settings, "Quality", 50);
  obs_data_set_default_int(settings, "Blend", 100);
  obs_data_set_default_int(settings, "Vignette_strength", 50);
  obs_data_set_default_int(settings, "Vignette_radius", 50);
  obs_data_set_default_int(settings, "Vignette_falloff", 50);
  obs_data_set_default_int(settings, "Vignette_blend_mode", 0);
  obs_data_set_default_int(settings, "Vignette_color", 0xFF000000);
}

// --- Lifecycle ---
void *create(obs_data_t *settings, obs_source_t *context) {
  shader_data *s = (shader_data *)bzalloc(sizeof(shader_data));
  s->context = context;

  char *effect_path = obs_module_file("Halsu_LensEffects.effect");

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
  info.id = "Halsu_LensEffects";
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
