# Halsu Plugins for Streaming
A collection of professional 3rd-party tools and filters for OBS Studio.

---

## Available Plugins

### 1. Halsu HybridKeyer V025
A hybrid chromakey/lumakey solution with spill suppression, shadow extraction, and advanced edge cleanup.

#### Description
**Key color** will be keyed out. **Prekey despill** attempts to remove spill before keying, **Prekey saturate** increases saturation before keying. **Matte white** controls the opacity of the foreground, **matte black** cleans up the background. **Highlights and shadows** can be keyed using luma keyer if the chroma keyer does not do good enough a job. **Shadows slider** adds luma-keyed shadows of user-defined color, and can be further controlled with black and white image mask and soft garbage matte. The **premultiply slider** controls the greenscreen / semi transparent area brightness by multiplying the luminosity by alpha. **Soft unpremultiply** does this based on alpha before level adjustments, often creating better, more visually pleasing results. **Spill unpremultiply** attempts to remove the backdrop color from semi-transparent areas. **Spill reduction** controls the strength (and algorithm) of spill reduction and **spill balance** controls can be used to tweak which colors are affected by spill reduction - this setting only applies at medium strength spill reduction. The default is a mix of the two. **Spill tint** can be used to smoothly integrate the foreground to the background color scheme. A **screen grab** of the empty greenscreen can be used as a **reference image** for the key, which greatly improves keying result especially with unevenly lit backdrops. A black and white **garbage matte** image can be used to mask out unwanted regions, and an **inside matte** image can be used to mask in opaque regions, with the option to also skip foreground processing. **Shadow matte** image can be used to more accurately tweak the area where shadow extraction is applied, in the cases where garbage matte is not enough.

#### General settings
The **alternate key method** checkbox switches from Vlahos-style RGB color difference key to a pure chromakey in YUV color space. **Matte anti-alising** checkbox attempts to filter out jagged edges caused by chroma subsampling. There are also some more or less helpful preview checkboxes. A good rule of thumb is to work on the settings top-down: from key color to matte white to matte black etc.

---

## Installation

## Automated Install
1. Open PowerShell as Administrator.
2. Run `Install_Halsu_HybridKeyer.ps1`.

## Manual Install
If you prefer to install manually:
1. Copy `obs-plugins/64bit/Halsu_HybridKeyer_V025.dll` to your OBS Studio directory:
   `C:/Program Files/obs-studio/obs-plugins/64bit/`
2. Copy the `data` folder to your OBS Studio directory:
   `C:/Program Files/obs-studio/`

## Usage
* Open OBS Studio.
* Right-click a source -> **Filters**.
* Click **+** -> **Halsu HybridKeyer V025**.

## AI Disclosure & Licensing
*   **Licensing**: This plugin is licensed under GPL v2.0. Source code is available [on GitHub](https://github.com/Halsu/halsu-plugin-factories).
*   **AI Disclaimer**: This resource was developed as a hybrid of human expertise and AI assistance. While the core project and original shader logic were hand-coded by Halsu, AI tools (including Antigravity) were utilized to implement specific shader features, generate C++ boilerplate, and develop the build infrastructure.
*   **Affiliation**: This is a third-party plugin. It is not affiliated with, or an official part of, the OBS Project.
