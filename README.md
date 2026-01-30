# Halsu Plugins for Streaming

A collection of third-party tools and filters for OBS Studio.

---

## Halsu HybridKeyer

| Version 0.25 |

A hybrid RGB/YUV chroma- and luma-keyer with spill suppression, shadow extraction, reference-based correction, and advanced edge handling. The plugin exposes low-level controls for technical users, but is designed to give usable results with minimal adjustment.

---

## Quickstart (for most users)

1. Select the **Key Color** (the greenscreen / backdrop color).
2. Adjust **Matte White** until the foreground subject is fully opaque.
3. Adjust **Matte Black** until the background is fully transparent.
   
If the result looks good at this point, you are done.

If the foreground cannot be made fully opaque, slightly adjust **Prekey Despill**.  
If the background will not fully disappear, slightly adjust **Prekey Saturate**.

A little is a lot. After changing prekey settings, you will need to revisit Matte White and Matte Black. These controls are sufficient for decent results in most setups.

Everything below is optional fine-tuning.

---

## Settings (Top to Bottom)

### Key Color

The backdrop color to be keyed out. If the color is not pure green shade, the hue will be rotated so that it is. This affects the keying operations, but not the final output.

---

### Prekey Despill

Tints the image towards magenta before keying. Useful when reflected green spill light from the backdrop contaminates the subject (e.g. black clothes have become dark green). Affects only the matte creation (transparency).

---

### Prekey Saturate

Increases color saturation before keying. Usually used in combination with prekey despill, which tends to desaturate the greenscreen. Affects only the matte creation (transparency).

---

### Matte White

Controls foreground opacity. Adjust to find the sweet spot where the subject has just become solid but not more.

---

### Matte Black

Controls background transparency. Adjust to find the sweet spot where the background has just become transparent but not more.

---

### Highlights and Shadows (Luma Key)

Allows bright or dark areas to be keyed using luminance. Can be useful for e.g. fine strands of blonde hair, or deep shadows that have a lot of spill.

---

### Shadows Slider

Adds luma-keyed shadows of a user-defined color. Intended for separate control of the key just for shadows. Crop sliders or a reference image can be used to isolate the area where shadows will appear.

---

### Premultiply

Controls brightness of semi-transparent areas by multiplying (or dividing, depending on setting) luminance by alpha. Useful for controlling edge brightness. The default setting is "mathematically correct" but adjusting this may help getting visually better results.

---

### Soft Unpremultiply

Performs unpremultiplication/premultiplication based on alpha **before** matte level adjustments. Often produces smoother, more natural visual results, but may also affect opaque areas.

---

### Spill Unpremultiply

Attempts to remove backdrop color from semi-transparent areas.

---

### Spill Reduction

Controls the strength and algorithm of spill suppression. Green channel is compared (in order of strength) to the maximum, a mix, and the minimum of red and blue channels.

---

### Spill Balance

Adjusts which colors are affected by spill reduction - adjust to better retain yellows or turqoises. Applies mostly at medium spill reduction strength, when a mix of red and blue is used for spill comparision.

---

### Spill Tint

Tints areas thet have green spill or transparency towards user-selected color. Usage is similar to light wrap tools, helps the foreground blend better with the scene. 

---

### Reference Image (Empty Screen Grab)

A capture of the empty greenscreen used as a reference for the key. Particularly useful for pulling good key with uneven lighting or wrinkled backdrop. Requires a static camera for proper operation.

---

### Garbage Matte Image (B/W)

Masks out unwanted regions. Black areas will be set transparent, white areas will go through the keying process.

---

### Inside Matte Image (B/W)

Forces white regions to be opaque. Can be used to retain green plants, reflective objects etc., as long as they are stationary. Option to skip spill removal.

---

### Shadow Matte Image (B/W)

Limits where custom shadow extraction is applied.

---

### Alternate Key Method

Switches from RGB difference (Vlahos-style) keying to a pure chroma key in YUV color space. This may yield better result in some difficult cases. Requires new adjustments for at least matte white and matte black, often other settings too.

---

### Matte Anti-Aliasing

Attempts to smooth jagged edges caused by chroma subsampling, at the cost of less fine details, and a possible need to adjust matte offset. 

---

### Preview Options

Various debug and preview modes to help visualize different processing stages.

---

## Usage Notes

This plugin is not an automatic or AI-based keyer.  
Most controls exist to fix specific problems, not to improve an already good key.

If your image looks acceptable, stop adjusting settings.

---

## Installation

1. Extract the ZIP file
2. Copy `obs-plugins/64bit/Halsu_HybridKeyer.dll` to:
   `C:/Program Files/obs-studio/obs-plugins/64bit/`
3. Copy the `data` folder to:
   `C:/Program Files/obs-studio/`

## Usage
* Open OBS Studio
* Right-click a source -> **Filters**
* Click **+** -> **Halsu HybridKeyer**

---

## Support
If you encounter any issues or have feature suggestions, please [open an issue](https://github.com/Halsu/halsu-plugins-for-streaming/issues) on GitHub.

---

## AI Disclosure & Licensing

**License**  
GPL v2.0  
Source code: https://github.com/Halsu/halsu-plugin-factories

**AI Disclosure**  
Core shader logic and design were hand-coded by Halsu. AI tools were used for some shader features, C++ boilerplate, and build infrastructure.

**Affiliation**  
This is a third-party plugin and is not affiliated with the OBS Project.
