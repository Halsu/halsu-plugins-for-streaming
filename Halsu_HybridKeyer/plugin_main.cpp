extern "C" {
#include <obs-module.h>
#include <graphics/graphics.h>
#include <graphics/vec4.h>
#include <util/platform.h>
#include <util/dstr.h>
#include <graphics/image-file.h>
}
#include <sys/stat.h>

OBS_DECLARE_MODULE()

/*
 * Generated OBS Plugin for Halsu_HybridKeyer
 */

// --- Dynamic Uniform IDs ---
struct shader_data {
    obs_source_t *context;
    gs_effect_t *effect;
    
    uint32_t Key_color;
    bool Use_alternate_key_method;
    bool Use_reference_image;
    gs_image_file_t Reference_image_image;
    char *Reference_image_path;
    float Prekey_despill;
    float Prekey_saturate;
    float Matte_white;
    float Matte_black;
    float Matte_highlights;
    float Matte_shadows;
    bool Matte_antialising;
    uint32_t Shadow_Color;
    float Shadow_Intensity;
    float Shadow_Crop_Left;
    float Shadow_Crop_Right;
    float Shadow_Crop_Top;
    float Shadow_Crop_Softness;
    bool Use_shadow_matte;
    gs_image_file_t Shadow_matte_image;
    char *Shadow_matte_path;
    float Spill_reduction;
    float Spill_balance;
    uint32_t Spill_Tint;
    float Spill_Tint_Intensity;
    float Spill_unpremultiply;
    float Premultiply;
    float Soft_Unpremultiply;
    bool Use_garbage_matte;
    gs_image_file_t Garbage_matte_image;
    char *Garbage_matte_path;
    bool Use_inside_matte;
    bool Preserve_inside_color;
    gs_image_file_t Inside_matte_image;
    char *Inside_matte_path;
    bool Show_Alpha;
    bool Show_PrekeyFG;
    bool Show_ProcessedFG;

};

// --- Get Name ---
const char *get_name(void *unused)
{
    return "Halsu HybridKeyer";
}

// --- Update (Link UI to Variables) ---
void update(void *data, obs_data_t *settings)
{
    shader_data *s = (shader_data *)data;
    
    s->Key_color = (uint32_t)obs_data_get_int(settings, "Key_color");
    s->Use_alternate_key_method = obs_data_get_bool(settings, "Use_alternate_key_method");
    s->Use_reference_image = obs_data_get_bool(settings, "Use_reference_image");
    const char *path_Reference_image = obs_data_get_string(settings, "Reference_image");
    if (path_Reference_image && path_Reference_image[0] && (!s->Reference_image_path || strcmp(s->Reference_image_path, path_Reference_image) != 0)) {
        if (s->Reference_image_path) bfree(s->Reference_image_path);
        s->Reference_image_path = bstrdup(path_Reference_image);
        obs_enter_graphics();
        gs_image_file_free(&s->Reference_image_image);
        gs_image_file_init(&s->Reference_image_image, path_Reference_image);
        gs_image_file_init_texture(&s->Reference_image_image);
        obs_leave_graphics();
    }
    s->Prekey_despill = (float)obs_data_get_double(settings, "Prekey_despill");
    s->Prekey_saturate = (float)obs_data_get_double(settings, "Prekey_saturate");
    s->Matte_white = (float)obs_data_get_double(settings, "Matte_white");
    s->Matte_black = (float)obs_data_get_double(settings, "Matte_black");
    s->Matte_highlights = (float)obs_data_get_double(settings, "Matte_highlights");
    s->Matte_shadows = (float)obs_data_get_double(settings, "Matte_shadows");
    s->Matte_antialising = obs_data_get_bool(settings, "Matte_antialising");
    s->Shadow_Color = (uint32_t)obs_data_get_int(settings, "Shadow_Color");
    s->Shadow_Intensity = (float)obs_data_get_double(settings, "Shadow_Intensity");
    s->Shadow_Crop_Left = (float)obs_data_get_double(settings, "Shadow_Crop_Left");
    s->Shadow_Crop_Right = (float)obs_data_get_double(settings, "Shadow_Crop_Right");
    s->Shadow_Crop_Top = (float)obs_data_get_double(settings, "Shadow_Crop_Top");
    s->Shadow_Crop_Softness = (float)obs_data_get_double(settings, "Shadow_Crop_Softness");
    s->Use_shadow_matte = obs_data_get_bool(settings, "Use_shadow_matte");
    const char *path_Shadow_matte = obs_data_get_string(settings, "Shadow_matte");
    if (path_Shadow_matte && path_Shadow_matte[0] && (!s->Shadow_matte_path || strcmp(s->Shadow_matte_path, path_Shadow_matte) != 0)) {
        if (s->Shadow_matte_path) bfree(s->Shadow_matte_path);
        s->Shadow_matte_path = bstrdup(path_Shadow_matte);
        obs_enter_graphics();
        gs_image_file_free(&s->Shadow_matte_image);
        gs_image_file_init(&s->Shadow_matte_image, path_Shadow_matte);
        gs_image_file_init_texture(&s->Shadow_matte_image);
        obs_leave_graphics();
    }
    s->Spill_reduction = (float)obs_data_get_double(settings, "Spill_reduction");
    s->Spill_balance = (float)obs_data_get_double(settings, "Spill_balance");
    s->Spill_Tint = (uint32_t)obs_data_get_int(settings, "Spill_Tint");
    s->Spill_Tint_Intensity = (float)obs_data_get_double(settings, "Spill_Tint_Intensity");
    s->Spill_unpremultiply = (float)obs_data_get_double(settings, "Spill_unpremultiply");
    s->Premultiply = (float)obs_data_get_double(settings, "Premultiply");
    s->Soft_Unpremultiply = (float)obs_data_get_double(settings, "Soft_Unpremultiply");
    s->Use_garbage_matte = obs_data_get_bool(settings, "Use_garbage_matte");
    const char *path_Garbage_matte = obs_data_get_string(settings, "Garbage_matte");
    if (path_Garbage_matte && path_Garbage_matte[0] && (!s->Garbage_matte_path || strcmp(s->Garbage_matte_path, path_Garbage_matte) != 0)) {
        if (s->Garbage_matte_path) bfree(s->Garbage_matte_path);
        s->Garbage_matte_path = bstrdup(path_Garbage_matte);
        obs_enter_graphics();
        gs_image_file_free(&s->Garbage_matte_image);
        gs_image_file_init(&s->Garbage_matte_image, path_Garbage_matte);
        gs_image_file_init_texture(&s->Garbage_matte_image);
        obs_leave_graphics();
    }
    s->Use_inside_matte = obs_data_get_bool(settings, "Use_inside_matte");
    s->Preserve_inside_color = obs_data_get_bool(settings, "Preserve_inside_color");
    const char *path_Inside_matte = obs_data_get_string(settings, "Inside_matte");
    if (path_Inside_matte && path_Inside_matte[0] && (!s->Inside_matte_path || strcmp(s->Inside_matte_path, path_Inside_matte) != 0)) {
        if (s->Inside_matte_path) bfree(s->Inside_matte_path);
        s->Inside_matte_path = bstrdup(path_Inside_matte);
        obs_enter_graphics();
        gs_image_file_free(&s->Inside_matte_image);
        gs_image_file_init(&s->Inside_matte_image, path_Inside_matte);
        gs_image_file_init_texture(&s->Inside_matte_image);
        obs_leave_graphics();
    }
    s->Show_Alpha = obs_data_get_bool(settings, "Show_Alpha");
    s->Show_PrekeyFG = obs_data_get_bool(settings, "Show_PrekeyFG");
    s->Show_ProcessedFG = obs_data_get_bool(settings, "Show_ProcessedFG");

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

    // Standard OBS Filter Bindings (obs-shaderfilter compatible)
    obs_source_t *target = obs_filter_get_target(s->context);
    uint32_t width = obs_source_get_base_width(target);
    uint32_t height = obs_source_get_base_height(target);
    
    struct vec4 v_uv_size;
    v_uv_size.x = (float)width;
    v_uv_size.y = (float)height;
    v_uv_size.z = width ? 1.0f / width : 0.0f;
    v_uv_size.w = height ? 1.0f / height : 0.0f;
    gs_effect_set_vec4(gs_effect_get_param_by_name(s->effect, "uv_size"), &v_uv_size);

    // Bind Uniforms
        struct vec4 v_Key_color;
    vec4_from_rgba(&v_Key_color, s->Key_color);
    gs_effect_set_vec4(gs_effect_get_param_by_name(s->effect, "Key_color"), &v_Key_color);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_alternate_key_method"), s->Use_alternate_key_method);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_reference_image"), s->Use_reference_image);
    if (s->Reference_image_image.texture)
        gs_effect_set_texture(gs_effect_get_param_by_name(s->effect, "Reference_image"), s->Reference_image_image.texture);
    float Prekey_despill_norm = (s->Prekey_despill - 0.00000f) / (100.00000f - 0.00000f);
    float Prekey_despill_final = Prekey_despill_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Prekey_despill"), Prekey_despill_final);
    float Prekey_saturate_norm = (s->Prekey_saturate - 0.00000f) / (100.00000f - 0.00000f);
    float Prekey_saturate_final = Prekey_saturate_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Prekey_saturate"), Prekey_saturate_final);
    float Matte_white_norm = (s->Matte_white - 0.00000f) / (100.00000f - 0.00000f);
    float Matte_white_final = Matte_white_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_white"), Matte_white_final);
    float Matte_black_norm = (s->Matte_black - 0.00000f) / (100.00000f - 0.00000f);
    float Matte_black_final = Matte_black_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_black"), Matte_black_final);
    float Matte_highlights_norm = (s->Matte_highlights - 0.00000f) / (100.00000f - 0.00000f);
    float Matte_highlights_final = Matte_highlights_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_highlights"), Matte_highlights_final);
    float Matte_shadows_norm = (s->Matte_shadows - 0.00000f) / (100.00000f - 0.00000f);
    float Matte_shadows_final = Matte_shadows_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Matte_shadows"), Matte_shadows_final);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Matte_antialising"), s->Matte_antialising);
    struct vec4 v_Shadow_Color;
    vec4_from_rgba(&v_Shadow_Color, s->Shadow_Color);
    gs_effect_set_vec4(gs_effect_get_param_by_name(s->effect, "Shadow_Color"), &v_Shadow_Color);
    float Shadow_Intensity_norm = (s->Shadow_Intensity - 0.00000f) / (100.00000f - 0.00000f);
    float Shadow_Intensity_final = Shadow_Intensity_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Intensity"), Shadow_Intensity_final);
    float Shadow_Crop_Left_norm = (s->Shadow_Crop_Left - 0.00000f) / (100.00000f - 0.00000f);
    float Shadow_Crop_Left_final = Shadow_Crop_Left_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Left"), Shadow_Crop_Left_final);
    float Shadow_Crop_Right_norm = (s->Shadow_Crop_Right - 0.00000f) / (100.00000f - 0.00000f);
    float Shadow_Crop_Right_final = Shadow_Crop_Right_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Right"), Shadow_Crop_Right_final);
    float Shadow_Crop_Top_norm = (s->Shadow_Crop_Top - 0.00000f) / (100.00000f - 0.00000f);
    float Shadow_Crop_Top_final = Shadow_Crop_Top_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Top"), Shadow_Crop_Top_final);
    float Shadow_Crop_Softness_norm = (s->Shadow_Crop_Softness - 0.00000f) / (100.00000f - 0.00000f);
    float Shadow_Crop_Softness_final = Shadow_Crop_Softness_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Shadow_Crop_Softness"), Shadow_Crop_Softness_final);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_shadow_matte"), s->Use_shadow_matte);
    if (s->Shadow_matte_image.texture)
        gs_effect_set_texture(gs_effect_get_param_by_name(s->effect, "Shadow_matte"), s->Shadow_matte_image.texture);
    float Spill_reduction_norm = (s->Spill_reduction - 0.00000f) / (100.00000f - 0.00000f);
    float Spill_reduction_final = Spill_reduction_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_reduction"), Spill_reduction_final);
    float Spill_balance_norm = (s->Spill_balance - 0.00000f) / (100.00000f - 0.00000f);
    float Spill_balance_final = Spill_balance_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_balance"), Spill_balance_final);
    struct vec4 v_Spill_Tint;
    vec4_from_rgba(&v_Spill_Tint, s->Spill_Tint);
    gs_effect_set_vec4(gs_effect_get_param_by_name(s->effect, "Spill_Tint"), &v_Spill_Tint);
    float Spill_Tint_Intensity_norm = (s->Spill_Tint_Intensity - 0.00000f) / (100.00000f - 0.00000f);
    float Spill_Tint_Intensity_final = Spill_Tint_Intensity_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_Tint_Intensity"), Spill_Tint_Intensity_final);
    float Spill_unpremultiply_norm = (s->Spill_unpremultiply - 0.00000f) / (100.00000f - 0.00000f);
    float Spill_unpremultiply_final = Spill_unpremultiply_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Spill_unpremultiply"), Spill_unpremultiply_final);
    float Premultiply_norm = (s->Premultiply - 0.00000f) / (100.00000f - 0.00000f);
    float Premultiply_final = Premultiply_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Premultiply"), Premultiply_final);
    float Soft_Unpremultiply_norm = (s->Soft_Unpremultiply - 0.00000f) / (100.00000f - 0.00000f);
    float Soft_Unpremultiply_final = Soft_Unpremultiply_norm * (1000.00000f - -1000.00000f) + -1000.00000f;
    gs_effect_set_float(gs_effect_get_param_by_name(s->effect, "Soft_Unpremultiply"), Soft_Unpremultiply_final);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_garbage_matte"), s->Use_garbage_matte);
    if (s->Garbage_matte_image.texture)
        gs_effect_set_texture(gs_effect_get_param_by_name(s->effect, "Garbage_matte"), s->Garbage_matte_image.texture);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Use_inside_matte"), s->Use_inside_matte);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Preserve_inside_color"), s->Preserve_inside_color);
    if (s->Inside_matte_image.texture)
        gs_effect_set_texture(gs_effect_get_param_by_name(s->effect, "Inside_matte"), s->Inside_matte_image.texture);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Show_Alpha"), s->Show_Alpha);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Show_PrekeyFG"), s->Show_PrekeyFG);
    gs_effect_set_bool(gs_effect_get_param_by_name(s->effect, "Show_ProcessedFG"), s->Show_ProcessedFG);


    obs_source_process_filter_end(s->context, s->effect, 0, 0);
}

// --- Properties (UI Definition) ---
obs_properties_t *get_properties(void *data)
{
    obs_properties_t *props = obs_properties_create();
    
    obs_properties_add_color(props, "Key_color", "Key color");
    obs_properties_add_bool(props, "Use_alternate_key_method", "Use alternate key method");
    obs_properties_add_bool(props, "Use_reference_image", "Use reference image");
    obs_properties_add_path(props, "Reference_image", "Reference image", OBS_PATH_FILE, "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*.*)", NULL);
    obs_properties_add_float_slider(props, "Prekey_despill", "Prekey despill", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Prekey_saturate", "Prekey saturate", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_white", "Matte white", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_black", "Matte black", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_highlights", "Matte highlights", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Matte_shadows", "Matte shadows", 0.0, 100.0, 0.01);
    obs_properties_add_bool(props, "Matte_antialising", "Matte antialising");
    obs_properties_add_color(props, "Shadow_Color", "Shadow Color");
    obs_properties_add_float_slider(props, "Shadow_Intensity", "Shadow Intensity", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Left", "Shadow Crop Left", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Right", "Shadow Crop Right", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Top", "Shadow Crop Top", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Shadow_Crop_Softness", "Shadow Crop Softness", 0.0, 100.0, 0.01);
    obs_properties_add_bool(props, "Use_shadow_matte", "Use shadow matte");
    obs_properties_add_path(props, "Shadow_matte", "Shadow matte", OBS_PATH_FILE, "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*.*)", NULL);
    obs_properties_add_float_slider(props, "Spill_reduction", "Spill reduction", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Spill_balance", "Spill balance", 0.0, 100.0, 0.01);
    obs_properties_add_color(props, "Spill_Tint", "Spill Tint");
    obs_properties_add_float_slider(props, "Spill_Tint_Intensity", "Spill Tint Intensity", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Spill_unpremultiply", "Spill unpremultiply", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Premultiply", "Premultiply", 0.0, 100.0, 0.01);
    obs_properties_add_float_slider(props, "Soft_Unpremultiply", "Soft Unpremultiply", 0.0, 100.0, 0.01);
    obs_properties_add_bool(props, "Use_garbage_matte", "Use garbage matte");
    obs_properties_add_path(props, "Garbage_matte", "Garbage matte", OBS_PATH_FILE, "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*.*)", NULL);
    obs_properties_add_bool(props, "Use_inside_matte", "Use inside matte");
    obs_properties_add_bool(props, "Preserve_inside_color", "Preserve inside color");
    obs_properties_add_path(props, "Inside_matte", "Inside matte", OBS_PATH_FILE, "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*.*)", NULL);
    obs_properties_add_bool(props, "Show_Alpha", "Show Alpha");
    obs_properties_add_bool(props, "Show_PrekeyFG", "Show PrekeyFG");
    obs_properties_add_bool(props, "Show_ProcessedFG", "Show ProcessedFG");
    obs_properties_add_text(props, "notes", "Halsu Hybrid Keyer v0.27.1 | Prekey despill attempts to remove spill before keying, Prekey saturate increases saturation before keying. Matte white controls the opacity of the foreground, matte black cleans up the background. A screen grab of the empty greenscreen can be used as a reference image for the key, which greatly improves keying result especially with unevenly lit backdrops. A black and white garbage matte image can be used to mask out unwanted regions, and an inside matte image can be used to mask in opaque regions, with the option to also skip foreground processing. Highlights and shadows can be keyed using luma keyer if the chroma keyer does not do good enough a job. Shadows slider adds luma-keyed shadows, and can be further controlled with black and white image mask. The premultiply slider controls the greenscreen / semi transparent area brightness by multiplying the luminosity by alpha.", OBS_TEXT_INFO);

    
    return props;
}
// --- Defaults ---
void get_defaults(obs_data_t *settings)
{
    obs_data_set_default_int(settings, "Key_color", 0x00000000);
    obs_data_set_default_bool(settings, "Use_alternate_key_method", false);
    obs_data_set_default_bool(settings, "Use_reference_image", false);
    obs_data_set_default_string(settings, "Reference_image", "Reference.png");
    obs_data_set_default_double(settings, "Prekey_despill", 0.00);
    obs_data_set_default_double(settings, "Prekey_saturate", 0.00);
    obs_data_set_default_double(settings, "Matte_white", 50.00);
    obs_data_set_default_double(settings, "Matte_black", 50.00);
    obs_data_set_default_double(settings, "Matte_highlights", 0.00);
    obs_data_set_default_double(settings, "Matte_shadows", 0.00);
    obs_data_set_default_bool(settings, "Matte_antialising", true);
    obs_data_set_default_int(settings, "Shadow_Color", 0xFF000000);
    obs_data_set_default_double(settings, "Shadow_Intensity", 0.00);
    obs_data_set_default_double(settings, "Shadow_Crop_Left", 0.00);
    obs_data_set_default_double(settings, "Shadow_Crop_Right", 100.00);
    obs_data_set_default_double(settings, "Shadow_Crop_Top", 50.00);
    obs_data_set_default_double(settings, "Shadow_Crop_Softness", 0.00);
    obs_data_set_default_bool(settings, "Use_shadow_matte", false);
    obs_data_set_default_string(settings, "Shadow_matte", "Shadow.png");
    obs_data_set_default_double(settings, "Spill_reduction", 50.00);
    obs_data_set_default_double(settings, "Spill_balance", 50.00);
    obs_data_set_default_int(settings, "Spill_Tint", 0xFF000000);
    obs_data_set_default_double(settings, "Spill_Tint_Intensity", 50.00);
    obs_data_set_default_double(settings, "Spill_unpremultiply", 0.00);
    obs_data_set_default_double(settings, "Premultiply", 50.00);
    obs_data_set_default_double(settings, "Soft_Unpremultiply", 50.00);
    obs_data_set_default_bool(settings, "Use_garbage_matte", false);
    obs_data_set_default_string(settings, "Garbage_matte", "Garbage.png");
    obs_data_set_default_bool(settings, "Use_inside_matte", false);
    obs_data_set_default_bool(settings, "Preserve_inside_color", false);
    obs_data_set_default_string(settings, "Inside_matte", "Inside.png");
    obs_data_set_default_bool(settings, "Show_Alpha", false);
    obs_data_set_default_bool(settings, "Show_PrekeyFG", false);
    obs_data_set_default_bool(settings, "Show_ProcessedFG", false);

}

// --- Lifecycle ---
void *create(obs_data_t *settings, obs_source_t *context)
{
    shader_data *s = (shader_data*)bzalloc(sizeof(shader_data));
    s->context = context;
    
    char *effect_path = obs_module_file("Halsu_HybridKeyer.effect");
    
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

void destroy(void *data)
{
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

bool obs_module_load(void)
{
    info.id = "Halsu_HybridKeyer";
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
