extern "C" {
#include <obs-module.h>
#include <graphics/graphics.h>
#include <graphics/vec4.h>
#include <util/platform.h>
#include <util/dstr.h>
}
#include <sys/stat.h>

OBS_DECLARE_MODULE()

#define SETTING_OPACITY "opacity"

/*
 * Generated OBS Plugin for Halsu_HybridKeyer_V025
 */

// --- Dynamic Uniform IDs ---
struct shader_data {
    obs_source_t *context;
    gs_effect_t *effect;
    
    struct vec4 Key_color;
    float Prekey_despill;
    float Prekey_saturate;
    float Matte_white;
    float Matte_black;
    float Matte_highlights;
    float Matte_shadows;
    struct vec4 Shadow_Color;
    float Shadow_Intensity;
    float Shadow_Crop_Left;
    float Shadow_Crop_Right;
    float Shadow_Crop_Top;
    float Shadow_Crop_Softness;
    float Spill_reduction;
    float Spill_balance;
    struct vec4 Spill_Tint;
    float Spill_Tint_Intensity;
    float Spill_unpremultiply;
    float Premultiply;
    float Matte_offset_x;
    float Matte_offset_y;
    float Soft_Unpremultiply;
    bool Use_reference_image;
    // Skipped texture Reference_image in proto
    bool Use_garbage_matte;
    // Skipped texture Garbage_matte in proto
    bool Use_inside_matte;
    bool Preserve_inside_color;
    // Skipped texture Inside_matte in proto
    bool Use_shadow_matte;
    // Skipped texture Shadow_matte in proto
    bool Show_Alpha;
    bool Show_PrekeyFG;
    bool Show_ProcessedFG;
    bool Use_alternate_key_method;
    bool Matte_antialising;

};

// --- Get Name ---
const char *get_name(void *unused)
{
    return "Halsu HybridKeyer V025";
}

// --- Update (Link UI to Variables) ---
void update(void *data, obs_data_t *settings)
{
    shader_data *s = (shader_data *)data;
    
    s->Prekey_despill = (float)obs_data_get_double(settings, "Prekey_despill");
    s->Prekey_saturate = (float)obs_data_get_double(settings, "Prekey_saturate");
    s->Matte_white = (float)obs_data_get_double(settings, "Matte_white");
    s->Matte_black = (float)obs_data_get_double(settings, "Matte_black");
    s->Matte_highlights = (float)obs_data_get_double(settings, "Matte_highlights");
    s->Matte_shadows = (float)obs_data_get_double(settings, "Matte_shadows");
    s->Shadow_Intensity = (float)obs_data_get_double(settings, "Shadow_Intensity");
    s->Shadow_Crop_Left = (float)obs_data_get_double(settings, "Shadow_Crop_Left");
    s->Shadow_Crop_Right = (float)obs_data_get_double(settings, "Shadow_Crop_Right");
    s->Shadow_Crop_Top = (float)obs_data_get_double(settings, "Shadow_Crop_Top");
    s->Shadow_Crop_Softness = (float)obs_data_get_double(settings, "Shadow_Crop_Softness");
    s->Spill_reduction = (float)obs_data_get_double(settings, "Spill_reduction");
    s->Spill_balance = (float)obs_data_get_double(settings, "Spill_balance");
    s->Spill_Tint_Intensity = (float)obs_data_get_double(settings, "Spill_Tint_Intensity");
    s->Spill_unpremultiply = (float)obs_data_get_double(settings, "Spill_unpremultiply");
    s->Premultiply = (float)obs_data_get_double(settings, "Premultiply");
    s->Matte_offset_x = (float)obs_data_get_double(settings, "Matte_offset_x");
    s->Matte_offset_y = (float)obs_data_get_double(settings, "Matte_offset_y");
    s->Soft_Unpremultiply = (float)obs_data_get_double(settings, "Soft_Unpremultiply");
    s->Use_reference_image = obs_data_get_bool(settings, "Use_reference_image");
    s->Use_garbage_matte = obs_data_get_bool(settings, "Use_garbage_matte");
    s->Use_inside_matte = obs_data_get_bool(settings, "Use_inside_matte");
    s->Preserve_inside_color = obs_data_get_bool(settings, "Preserve_inside_color");
    s->Use_shadow_matte = obs_data_get_bool(settings, "Use_shadow_matte");
    s->Show_Alpha = obs_data_get_bool(settings, "Show_Alpha");
    s->Show_PrekeyFG = obs_data_get_bool(settings, "Show_PrekeyFG");
    s->Show_ProcessedFG = obs_data_get_bool(settings, "Show_ProcessedFG");
    s->Use_alternate_key_method = obs_data_get_bool(settings, "Use_alternate_key_method");
    s->Matte_antialising = obs_data_get_bool(settings, "Matte_antialising");

}

// --- Render (Draw Quad with Shader) ---
void video_render(void *data, gs_effect_t *effect)
{
    shader_data *s = (shader_data *)data;
    
    if (!s->effect) {
        obs_source_skip_video_filter(s->context);
        return;
    }

    if (!obs_source_process_filter_begin(s->context, GS_RGBA, OBS_ALLOW_DIRECT_RENDERING))
        return;

    // Bind Uniforms
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Prekey_despill"), s->Prekey_despill);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Prekey_saturate"), s->Prekey_saturate);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_white"), s->Matte_white);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_black"), s->Matte_black);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_highlights"), s->Matte_highlights);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_shadows"), s->Matte_shadows);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Intensity"), s->Shadow_Intensity);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Left"), s->Shadow_Crop_Left);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Right"), s->Shadow_Crop_Right);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Top"), s->Shadow_Crop_Top);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Softness"), s->Shadow_Crop_Softness);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_reduction"), s->Spill_reduction);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_balance"), s->Spill_balance);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_Tint_Intensity"), s->Spill_Tint_Intensity);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_unpremultiply"), s->Spill_unpremultiply);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Premultiply"), s->Premultiply);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_offset_x"), s->Matte_offset_x);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_offset_y"), s->Matte_offset_y);
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Soft_Unpremultiply"), s->Soft_Unpremultiply);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_reference_image"), s->Use_reference_image);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_garbage_matte"), s->Use_garbage_matte);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_inside_matte"), s->Use_inside_matte);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Preserve_inside_color"), s->Preserve_inside_color);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_shadow_matte"), s->Use_shadow_matte);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Show_Alpha"), s->Show_Alpha);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Show_PrekeyFG"), s->Show_PrekeyFG);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Show_ProcessedFG"), s->Show_ProcessedFG);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_alternate_key_method"), s->Use_alternate_key_method);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Matte_antialising"), s->Matte_antialising);


    obs_source_process_filter_end(s->context, s->effect, 0, 0);
}

// --- Properties (UI Definition) ---
obs_properties_t *get_properties(void *data)
{
    obs_properties_t *props = obs_properties_create();
    
    obs_properties_add_float_slider(props, "Prekey_despill", "Prekey despill", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Prekey_saturate", "Prekey saturate", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_white", "Matte white", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_black", "Matte black", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_highlights", "Matte highlights", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_shadows", "Matte shadows", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Intensity", "Shadow Intensity", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Left", "Shadow Crop Left", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Right", "Shadow Crop Right", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Top", "Shadow Crop Top", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Softness", "Shadow Crop Softness", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Spill_reduction", "Spill reduction", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Spill_balance", "Spill balance", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Spill_Tint_Intensity", "Spill Tint Intensity", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Spill_unpremultiply", "Spill unpremultiply", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Premultiply", "Premultiply", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_offset_x", "Matte offset x", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_offset_y", "Matte offset y", -1000.0, 1000.0, 0.01);
    obs_properties_add_float_slider(props, "Soft_Unpremultiply", "Soft Unpremultiply", -1000.0, 1000.0, 0.01);
    obs_properties_add_bool(props, "Use_reference_image", "Use reference image");
    obs_properties_add_bool(props, "Use_garbage_matte", "Use garbage matte");
    obs_properties_add_bool(props, "Use_inside_matte", "Use inside matte");
    obs_properties_add_bool(props, "Preserve_inside_color", "Preserve inside color");
    obs_properties_add_bool(props, "Use_shadow_matte", "Use shadow matte");
    obs_properties_add_bool(props, "Show_Alpha", "Show Alpha");
    obs_properties_add_bool(props, "Show_PrekeyFG", "Show PrekeyFG");
    obs_properties_add_bool(props, "Show_ProcessedFG", "Show ProcessedFG");
    obs_properties_add_bool(props, "Use_alternate_key_method", "Use alternate key method");
    obs_properties_add_bool(props, "Matte_antialising", "Matte antialising");

    
    return props;
}

// --- Lifecycle ---
void *create(obs_data_t *settings, obs_source_t *context)
{
    shader_data *s = (shader_data*)bzalloc(sizeof(shader_data));
    s->context = context;
    
    char *effect_path = obs_module_file("Halsu_HybridKeyer_V025.effect");
    s->effect = gs_effect_create_from_file(effect_path, NULL);
    bfree(effect_path);
    
    update(s, settings);
    return s;
}

void destroy(void *data)
{
    shader_data *s = (shader_data *)data;
    if (s->effect) gs_effect_destroy(s->effect);
    bfree(s);
}

// --- Info Definition ---
struct obs_source_info info = {};

bool obs_module_load(void)
{
    info.id = "Halsu_HybridKeyer_V025";
    info.type = OBS_SOURCE_TYPE_FILTER;
    info.output_flags = OBS_SOURCE_VIDEO;
    info.get_name = get_name;
    info.create = create;
    info.destroy = destroy;
    info.update = update;
    info.get_properties = get_properties;
    info.video_render = video_render;
    
    obs_register_source(&info);
    return true;
}
