# Publishing Guide for Halsu Plugins for Streaming

This guide documents the process for publishing new plugins to the `halsu-plugins-for-streaming` repository, including documentation standards, GPL 2.0 compliance requirements, and release procedures.

---

## Repository Structure

```
halsu-plugins-for-streaming/
├── LICENSE                          # GPL v2.0 license file
├── README.md                        # Main documentation
├── docs/
│   └── images/                      # Screenshots and UI images
│       ├── HHK_*.png               # HybridKeyer screenshots
│       ├── AlphaTools*.png         # AlphaTools screenshots
│       └── Relightwrap_*.png       # Relightwrap screenshots
├── Halsu_HybridKeyer/              # Source code directory
│   ├── plugin_main.cpp
│   ├── Halsu_HybridKeyer.effect
│   └── CMakeLists.txt
├── Halsu_HybridKeyer_Installer.zip # Compiled installer
├── Halsu_AlphaTools/               # Source code directory
├── Halsu_AlphaTools_Installer.zip  # Compiled installer
├── Halsu_Relightwrap/              # Source code directory
└── Halsu_Relightwrap_Installer.zip # Compiled installer
```

---

## GPL 2.0 Compliance Requirements

All plugins in this repository are licensed under **GPL v2.0**. This means:

### ✅ Required

1. **Source Code Availability**
   - All source code must be included in the repository
   - Source must be in subdirectories (e.g., `Halsu_PluginName/`)
   - Include all files needed to build: `.cpp`, `.effect`, `CMakeLists.txt`

2. **License Notice**
   - The repository LICENSE file covers all plugins
   - Each source file should ideally include a GPL header comment
   - README must state "GPL v2.0" and link to source directories

3. **Attribution**
   - Maintain copyright notices
   - Document AI tool usage in the "AI Disclosure" section
   - Credit any third-party code or libraries

4. **Distribution**
   - Installers (.zip files) must be accompanied by source code
   - Users must be able to rebuild from source
   - No additional restrictions beyond GPL v2.0

### ❌ Prohibited

- Mixing GPL code with proprietary code
- Adding restrictive licenses or EULAs
- Distributing binaries without source code
- Removing or obscuring copyright notices

---

## Documentation Standards

### README Structure

Each plugin should have a dedicated section in `README.md` following this template:

```markdown
## Halsu PluginName

| Version X.Y.Z |

[One-paragraph description of what the plugin does and its key features]

<img src="docs/images/PluginName_Header.png" alt="Halsu PluginName" width="100%">

---

## Quickstart (PluginName)

1. [Most important control]
2. [Second most important control]
3. [Third most important control]
4. [Optional fourth control]

[One sentence about when these controls are sufficient]

---

## Settings (PluginName)

### Parameter Name

[Description of what this parameter does, including:]
- What it controls
- Typical use cases
- Range information if relevant
- Interaction with other parameters

![Setting Group](docs/images/PluginName_UI_01.png)

---

[Repeat for each parameter or parameter group]

---

## Usage Notes (PluginName)

[Important tips, warnings, or best practices]

---

## Installation (PluginName)

1. Close OBS Studio if it's running
2. Extract this ZIP file
3. Copy the contents to your OBS installation folder:
   - Windows: C:\\Program Files\\obs-studio\\
   - The folder structure should merge with existing folders

## Files Included

- obs-plugins/64bit/Halsu_PluginName.dll
- data/obs-plugins/Halsu_PluginName/Halsu_PluginName.effect

## Usage

* Open OBS Studio
* Right-click a source -> **Filters**
* Click **+** -> **Halsu PluginName**

![Filter Panel](docs/images/PluginName_UI_Final.png)

---
```

### Documentation Best Practices

1. **Be Concise**
   - One paragraph per parameter
   - Use bullet points for lists
   - Avoid redundancy

2. **Use Clear Language**
   - Write for users, not developers
   - Explain what, not how
   - Avoid jargon unless necessary

3. **No Marketing Adjectives**
   - ❌ **FORBIDDEN**: "professional", "high quality", "advanced", "powerful", "amazing", "best"
   - ✅ **ALLOWED**: Adjectives that describe actual function (e.g., "higher quality setting", "brighter result", "smoother edges")
   - Describe what the feature **does**, not how good it is
   - Let users judge quality for themselves

4. **Include Visuals**
   - Screenshot each UI section
   - Name images consistently: `PluginName_UI_01.png`, `PluginName_UI_02.png`, etc.
   - Use a header image showing the plugin in action
   - Keep images under 500KB when possible

4. **Organize Top-to-Bottom**
   - Document parameters in the order they appear in the UI
   - Group related parameters together
   - Use horizontal rules (`---`) to separate sections

5. **Provide Context**
   - Explain when to use each feature
   - Note interactions between parameters
   - Include usage notes for common scenarios

---

## Screenshot Guidelines

### Required Screenshots

1. **Header Image** (`PluginName_Header.png`)
   - Shows the plugin effect in action
   - Should be visually impressive
   - 1920x1080 or similar 16:9 aspect ratio

2. **UI Screenshots** (`PluginName_UI_01.png`, `_02.png`, etc.)
   - Capture the OBS filter properties panel
   - Group related controls together
   - Crop to show only relevant UI elements
   - Use consistent OBS theme (dark mode recommended)

3. **Filter Panel** (`PluginName_UI_Final.png`)
   - Shows where to add the filter in OBS
   - Helps users locate the plugin after installation

### Screenshot Tips

- Use OBS Studio's default dark theme
- Ensure text is readable (no blur, compression artifacts)
- Highlight important UI elements if needed
- Save as PNG for UI screenshots
- Compress images before committing (use tools like TinyPNG)

---

## Release Process

### 1. Build the Plugin

From the factory repository (`halsu-plugin-factories`):

```powershell
# Generate plugin
cd OBS_Factory
python generate_obs_plugin.py "PluginName.shader"

# Apply any manual edits (see RELIGHTWRAP_V03_MANUAL_STEPS.md for example)

# Build
cmake --build Generated_Plugins\Halsu_PluginName\build --config Release

# Package installer
Remove-Item -Recurse -Force Halsu_PluginName_Installer -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Path Halsu_PluginName_Installer\obs-plugins\64bit -Force | Out-Null
New-Item -ItemType Directory -Path Halsu_PluginName_Installer\data\obs-plugins\Halsu_PluginName -Force | Out-Null
Copy-Item Generated_Plugins\Halsu_PluginName\build\Release\Halsu_PluginName.dll Halsu_PluginName_Installer\obs-plugins\64bit\
Copy-Item Generated_Plugins\Halsu_PluginName\Halsu_PluginName.effect Halsu_PluginName_Installer\data\obs-plugins\Halsu_PluginName\
Copy-Item RELEASE_README.md Halsu_PluginName_Installer\README.md
Compress-Archive -Path Halsu_PluginName_Installer\* -DestinationPath Halsu_PluginName_Installer.zip -Force
```

### 2. Prepare Source Code

Copy source files to the public repository:

```powershell
cd ..\..
cd Halsu_Plugins_For_Streaming

# Create source directory
New-Item -ItemType Directory -Path Halsu_PluginName -Force

# Copy source files
Copy-Item ..\Halsu_Plugin_Factories\OBS_Factory\Generated_Plugins\Halsu_PluginName\plugin_main.cpp Halsu_PluginName\
Copy-Item ..\Halsu_Plugin_Factories\OBS_Factory\Generated_Plugins\Halsu_PluginName\Halsu_PluginName.effect Halsu_PluginName\
Copy-Item ..\Halsu_Plugin_Factories\OBS_Factory\Generated_Plugins\Halsu_PluginName\CMakeLists.txt Halsu_PluginName\
```

### 3. Copy Installer

```powershell
Copy-Item ..\Halsu_Plugin_Factories\OBS_Factory\Halsu_PluginName_Installer.zip .
```

### 4. Add Screenshots

**Typical workflow:** The user will provide screenshots beforehand and specify their location.

If screenshots need to be created:
1. Load the plugin in OBS Studio
2. Capture screenshots following the guidelines above
3. Save to `docs/images/` with consistent naming
4. Compress images before committing

If screenshots are already provided:
```powershell
# Copy from user-specified location to docs/images/
Copy-Item [user-provided-path]\*.png docs\images\
```

### 5. Update README.md

1. Add plugin to the navigation table at the top
2. Add complete plugin documentation section
3. Update version numbers
4. Test all image links

### 6. Commit and Tag

```powershell
git add .
git commit -m "Add Halsu PluginName vX.Y.Z - [brief description]"
git tag -a vX.Y.Z-pluginname -m "Halsu PluginName vX.Y.Z - [description]"
git push
git push --tags
```

### 7. Create GitHub Release

1. Go to https://github.com/Halsu/halsu-plugins-for-streaming/releases
2. Click "Draft a new release"
3. Select the tag you just created
4. Title: "Halsu PluginName vX.Y.Z"
5. Description:
   ```markdown
   ## What's New
   - [Feature 1]
   - [Feature 2]
   - [Bug fix 1]

   ## Installation
   Download `Halsu_PluginName_Installer.zip` and extract to your OBS installation folder.

   ## Documentation
   See the [README](https://github.com/Halsu/halsu-plugins-for-streaming#halsu-pluginname) for full documentation.
   ```
6. Attach `Halsu_PluginName_Installer.zip` as a binary
7. Publish release

---

## Version Numbering

Use semantic versioning: `MAJOR.MINOR.PATCH`

- **MAJOR**: Breaking changes, major feature additions
- **MINOR**: New features, significant improvements
- **PATCH**: Bug fixes, minor tweaks

Examples:
- `0.1.0` - Initial release
- `0.2.0` - Added new feature
- `0.2.1` - Fixed bug in feature
- `1.0.0` - Stable release, API finalized

---

## Checklist for New Plugin Release

- [ ] Plugin built and tested in OBS
- [ ] Source code copied to `Halsu_PluginName/` directory
- [ ] Installer created and tested
- [ ] All screenshots captured and compressed
- [ ] README.md updated with full documentation
- [ ] Navigation table updated
- [ ] GPL v2.0 compliance verified (source code included)
- [ ] AI disclosure updated if applicable
- [ ] Changes committed with descriptive message
- [ ] Version tag created and pushed
- [ ] GitHub release created with installer attachment

---

## Common Issues

### Git Won't Add Installer ZIP

If `.gitignore` blocks ZIP files:
```powershell
git add -f Halsu_PluginName_Installer.zip
```

### Images Not Displaying

- Verify paths use forward slashes: `docs/images/file.png`
- Check image files are committed to the repository
- Ensure filenames match exactly (case-sensitive)

### Plugin Not Appearing in OBS

- Verify DLL is in `obs-plugins/64bit/`
- Verify .effect file is in `data/obs-plugins/Halsu_PluginName/`
- Check OBS logs for loading errors
- Ensure OBS was restarted after installation

---

## Contact

For questions about the publishing process, open an issue in the repository or contact the maintainer.
