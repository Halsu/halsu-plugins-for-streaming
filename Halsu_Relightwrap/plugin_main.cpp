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
 * Generated OBS Plugin for Halsu_Relightwrap
 */

// --- Dynamic Uniform IDs ---
struct shader_data {
  obs_source_t *context;
  gs_effect_t *effect;

  int Wrap_Source;
  gs_image_file_t Background_Image_image;
  char *Background_Image_path;
  uint32_t Custom_Wrap_Color;
  float Defringe_Distance;
  float Defringe_Search_Radius;
  float Defringe_Strength;
  float Wrap_Strength;
  float Wrap_Width;
  float Wrap_Falloff;
  float Relight_Blend;
  float Bump_Strength;
  float Multiply_By_FG_Luma;
  float Light_Angle;
  float Light_Range;
  float Light_Quality;
  float Light_Directionality;
  bool Enable_Defringing;
  int Blend_Mode;
  int ApplyTo;
  int View;
};

// --- Get Name ---
const char *get_name(void *unused) { return "Halsu Relightwrap"; }

// --- Update (Link UI to Variables) ---
void update(void *data, obs_data_t *settings) {
  shader_data *s = (shader_data *)data;

  s->Wrap_Source = (int)obs_data_get_int(settings, "Wrap_Source");
  const char *path_Background_Image =
      obs_data_get_string(settings, "Background_Image");
  if (path_Background_Image && path_Background_Image[0] &&
      (!s->Background_Image_path ||
       strcmp(s->Background_Image_path, path_Background_Image) != 0)) {
    if (s->Background_Image_path)
      bfree(s->Background_Image_path);
    s->Background_Image_path = bstrdup(path_Background_Image);
    obs_enter_graphics();
    gs_image_file_free(&s->Background_Image_image);
    gs_image_file_init(&s->Background_Image_image, path_Background_Image);
    gs_image_file_init_texture(&s->Background_Image_image);
    obs_leave_graphics();
  }
  s->Custom_Wrap_Color =
      (uint32_t)obs_data_get_int(settings, "Custom_Wrap_Color");
  s->Defringe_Distance =
      (float)obs_data_get_double(settings, "Defringe_Distance");
  s->Defringe_Search_Radius =
      (float)obs_data_get_double(settings, "Defringe_Search_Radius");
  s->Defringe_Strength =
      (float)obs_data_get_double(settings, "Defringe_Strength");
  s->Wrap_Strength = (float)obs_data_get_double(settings, "Wrap_Strength");
  s->Wrap_Width = (float)obs_data_get_double(settings, "Wrap_Width");
  s->Wrap_Falloff = (float)obs_data_get_double(settings, "Wrap_Falloff");
  s->Relight_Blend = (float)obs_data_get_double(settings, "Relight_Blend");
  s->Bump_Strength = (float)obs_data_get_double(settings, "Bump_Strength");
  s->Multiply_By_FG_Luma =
      (float)obs_data_get_double(settings, "Multiply_By_FG_Luma");
  s->Light_Angle = (float)obs_data_get_double(settings, "Light_Angle");
  s->Light_Range = (float)obs_data_get_double(settings, "Light_Range");
  s->Light_Quality = (float)obs_data_get_double(settings, "Light_Quality");
  s->Light_Directionality =
      (float)obs_data_get_double(settings, "Light_Directionality");
  s->Enable_Defringing = obs_data_get_bool(settings, "Enable_Defringing");
  s->Blend_Mode = (int)obs_data_get_int(settings, "Blend_Mode");
  s->ApplyTo = (int)obs_data_get_int(settings, "ApplyTo");
  s->View = (int)obs_data_get_int(settings, "View");
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
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Wrap_Source"),
                    s->Wrap_Source);
  if (s->Background_Image_image.texture)
    gs_effect_set_texture(
        gs_effect_get_param_by_name(s->effect, "Background_Image"),
        s->Background_Image_image.texture);
  struct vec4 v_Custom_Wrap_Color;
  vec4_from_rgba(&v_Custom_Wrap_Color, s->Custom_Wrap_Color);
  gs_effect_set_vec4(
      gs_effect_get_param_by_name(s->effect, "Custom_Wrap_Color"),
      &v_Custom_Wrap_Color);
  float Defringe_Distance_norm =
      (s->Defringe_Distance - 0.00000f) / (100.00000f - 0.00000f);
  float Defringe_Distance_final =
      Defringe_Distance_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(
      gs_effect_get_param_by_name(s->effect, "Defringe_Distance"),
      Defringe_Distance_final);
  float Defringe_Search_Radius_norm =
      (s->Defringe_Search_Radius - 0.00000f) / (100.00000f - 0.00000f);
  float Defringe_Search_Radius_final =
      Defringe_Search_Radius_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(
      gs_effect_get_param_by_name(s->effect, "Defringe_Search_Radius"),
      Defringe_Search_Radius_final);
  float Defringe_Strength_norm =
      (s->Defringe_Strength - 0.00000f) / (100.00000f - 0.00000f);
  float Defringe_Strength_final =
      Defringe_Strength_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(
      gs_effect_get_param_by_name(s->effect, "Defringe_Strength"),
      Defringe_Strength_final);
  float Wrap_Strength_norm =
      (s->Wrap_Strength - 0.00000f) / (100.00000f - 0.00000f);
  float Wrap_Strength_final =
      Wrap_Strength_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Wrap_Strength"),
                      Wrap_Strength_final);
  float Wrap_Width_norm = (s->Wrap_Width - 0.00000f) / (100.00000f - 0.00000f);
  float Wrap_Width_final =
      Wrap_Width_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Wrap_Width"),
                      Wrap_Width_final);
  float Wrap_Falloff_norm =
      (s->Wrap_Falloff - 0.00000f) / (100.00000f - 0.00000f);
  float Wrap_Falloff_final =
      Wrap_Falloff_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Wrap_Falloff"),
                      Wrap_Falloff_final);
  float Relight_Blend_norm =
      (s->Relight_Blend - 0.00000f) / (100.00000f - 0.00000f);
  float Relight_Blend_final =
      Relight_Blend_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Relight_Blend"),
                      Relight_Blend_final);
  float Bump_Strength_norm =
      (s->Bump_Strength - 0.00000f) / (100.00000f - 0.00000f);
  float Bump_Strength_final =
      Bump_Strength_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Bump_Strength"),
                      Bump_Strength_final);
  float Multiply_By_FG_Luma_norm =
      (s->Multiply_By_FG_Luma - 0.00000f) / (100.00000f - 0.00000f);
  float Multiply_By_FG_Luma_final =
      Multiply_By_FG_Luma_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(
      gs_effect_get_param_by_name(s->effect, "Multiply_By_FG_Luma"),
      Multiply_By_FG_Luma_final);
  float Light_Angle_norm =
      (s->Light_Angle - -180.00000f) / (180.00000f - -180.00000f);
  float Light_Angle_final =
      Light_Angle_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Light_Angle"),
                      Light_Angle_final);
  float Light_Range_norm =
      (s->Light_Range - 1.00000f) / (180.00000f - 1.00000f);
  float Light_Range_final =
      Light_Range_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Light_Range"),
                      Light_Range_final);
  float Light_Quality_norm =
      (s->Light_Quality - 0.00000f) / (100.00000f - 0.00000f);
  float Light_Quality_final =
      Light_Quality_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Light_Quality"),
                      Light_Quality_final);
  float Light_Directionality_norm =
      (s->Light_Directionality - 0.00000f) / (100.00000f - 0.00000f);
  float Light_Directionality_final =
      Light_Directionality_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
  gs_effect_set_float(
      gs_effect_get_param_by_name(s->effect, "Light_Directionality"),
      Light_Directionality_final);
  gs_effect_set_bool(
      gs_effect_get_param_by_name(s->effect, "Enable_Defringing"),
      s->Enable_Defringing);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "Blend_Mode"),
                    s->Blend_Mode);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "ApplyTo"),
                    s->ApplyTo);
  gs_effect_set_int(gs_effect_get_param_by_name(s->effect, "View"), s->View);

  obs_source_process_filter_end(s->context, s->effect, 0, 0);
}

// --- Properties (UI Definition) ---
obs_properties_t *get_properties(void *data) {
  obs_properties_t *props = obs_properties_create();

  obs_property_t *p_View = obs_properties_add_list(
      props, "View", "View", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
  obs_property_list_add_int(p_View, "Final Result", 0);
  obs_property_list_add_int(p_View, "Original Foreground", 1);
  obs_property_list_add_int(p_View, "Wrap Fill", 2);
  obs_property_list_add_int(p_View, "Comp", 3);
  obs_property_list_add_int(p_View, "Mask", 4);
  obs_property_list_add_int(p_View, "Direction Debug", 5);
  obs_property_list_add_int(p_View, "LightWrap Preview", 6);
  obs_property_list_add_int(p_View, "Surface Detail", 7);
  obs_properties_add_text(props, "notes_view",
                          "0=Final 1=Orig 2=WrapFill 3=Comp 4=Mask 5=DirDebug "
                          "6=Preview 7=SurfDetail.",
                          OBS_TEXT_INFO);

  obs_property_t *p_ApplyTo = obs_properties_add_list(
      props, "ApplyTo", "ApplyTo", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
  obs_property_list_add_int(p_ApplyTo, "All", 0);
  obs_property_list_add_int(p_ApplyTo, "Highlights", 1);
  obs_property_list_add_int(p_ApplyTo, "Highlights/Mids", 2);
  obs_property_list_add_int(p_ApplyTo, "Shadows", 3);
  obs_properties_add_text(props, "notes_apply",
                          "0=All 1=Highlights 2=Highs/Mids 3=Shadows. Selects "
                          "the luma range to wrap onto.",
                          OBS_TEXT_INFO);

  obs_property_t *p_Wrap_Source =
      obs_properties_add_list(props, "Wrap_Source", "Wrap Source",
                              OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
  obs_property_list_add_int(p_Wrap_Source, "Background Image", 0);
  obs_property_list_add_int(p_Wrap_Source, "Custom Color", 1);

  obs_properties_add_path(
      props, "Background_Image", "Background Image", OBS_PATH_FILE,
      "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*.*)", NULL);
  obs_properties_add_color(props, "Custom_Wrap_Color", "Custom Wrap Color");
  obs_properties_add_float_slider(props, "Wrap_Strength", "Wrap Strength", 0.0,
                                  100.0, 1.0);
  obs_properties_add_float_slider(props, "Wrap_Width", "Wrap Width", 0.0, 100.0,
                                  1.0);
  obs_properties_add_float_slider(props, "Wrap_Falloff", "Wrap Falloff", 0.0,
                                  100.0, 1.0);

  obs_property_t *p_Blend_Mode =
      obs_properties_add_list(props, "Blend_Mode", "Blend Mode",
                              OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_INT);
  obs_property_list_add_int(p_Blend_Mode, "Add", 0);
  obs_property_list_add_int(p_Blend_Mode, "Screen", 1);
  obs_property_list_add_int(p_Blend_Mode, "Overlay", 2);
  obs_property_list_add_int(p_Blend_Mode, "Lighten", 3);
  obs_property_list_add_int(p_Blend_Mode, "Mix", 4);
  obs_property_list_add_int(p_Blend_Mode, "Darken", 5);
  obs_property_list_add_int(p_Blend_Mode, "Multiply", 6);
  obs_properties_add_text(props, "notes_blend",
                          "0=Add 1=Screen 2=Overlay 3=Lighten 4=Mix 5=Darken "
                          "6=Multiply. Controls the compositing method.",
                          OBS_TEXT_INFO);

  obs_properties_add_float_slider(props, "Relight_Blend", "Relight Blend", 0.0,
                                  100.0, 1.0);
  obs_properties_add_float_slider(props, "Bump_Strength", "Bump Strength", 0.0,
                                  100.0, 1.0);
  obs_properties_add_float_slider(props, "Multiply_By_FG_Luma",
                                  "Multiply By FG Luma", 0.0, 100.0, 1.0);
  obs_properties_add_float_slider(props, "Light_Angle", "Light Angle", -180.0,
                                  180.0, 1.0);
  obs_properties_add_float_slider(props, "Light_Range", "Light Range", 1.0,
                                  180.0, 1.0);
  obs_properties_add_float_slider(props, "Light_Quality", "Light Quality", 0.0,
                                  100.0, 1.0);
  obs_properties_add_float_slider(props, "Light_Directionality",
                                  "Light Directionality", 0.0, 100.0, 1.0);
  obs_properties_add_bool(props, "Enable_Defringing", "Enable Defringing");
  obs_properties_add_float_slider(props, "Defringe_Distance",
                                  "Defringe Distance", 0.0, 100.0, 1.0);
  obs_properties_add_float_slider(props, "Defringe_Search_Radius",
                                  "Defringe Search Radius", 0.0, 100.0, 1.0);
  obs_properties_add_float_slider(props, "Defringe_Strength",
                                  "Defringe Strength", 0.0, 100.0, 1.0);

  return props;
}
// --- Defaults ---
void get_defaults(obs_data_t *settings) {
  obs_data_set_default_int(settings, "Wrap_Source", 1);
  obs_data_set_default_string(settings, "Background_Image", "Background.png");
  obs_data_set_default_int(settings, "Custom_Wrap_Color", 0xFF000000);
  obs_data_set_default_double(settings, "Defringe_Distance", 33.35);
  obs_data_set_default_double(settings, "Defringe_Search_Radius", 20.00);
  obs_data_set_default_double(settings, "Defringe_Strength", 100.00);
  obs_data_set_default_double(settings, "Wrap_Strength", 50.00);
  obs_data_set_default_double(settings, "Wrap_Width", 50.50);
  obs_data_set_default_double(settings, "Wrap_Falloff", 52.50);
  obs_data_set_default_double(settings, "Relight_Blend", 50.00);
  obs_data_set_default_double(settings, "Bump_Strength", 0.00);
  obs_data_set_default_double(settings, "Multiply_By_FG_Luma", 0.00);
  obs_data_set_default_double(settings, "Light_Angle", -90.00);
  obs_data_set_default_double(settings, "Light_Range", 89.96);
  obs_data_set_default_double(settings, "Light_Quality", 0.00);
  obs_data_set_default_double(settings, "Light_Directionality", 0.00);
  obs_data_set_default_bool(settings, "Enable_Defringing", false);
  obs_data_set_default_double(settings, "Defringe_Distance", 33.35);
  obs_data_set_default_double(settings, "Defringe_Search_Radius", 20.00);
  obs_data_set_default_double(settings, "Defringe_Strength", 100.00);
  obs_data_set_default_int(settings, "Blend_Mode", 1);
  obs_data_set_default_int(settings, "ApplyTo", 0);
  obs_data_set_default_int(settings, "View", 0);
}

// --- Lifecycle ---
void *create(obs_data_t *settings, obs_source_t *context) {
  shader_data *s = (shader_data *)bzalloc(sizeof(shader_data));
  s->context = context;

  char *effect_path = obs_module_file("Halsu_Relightwrap.effect");

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
  info.id = "Halsu_Relightwrap";
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
