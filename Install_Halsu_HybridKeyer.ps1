
# Halsu Hybrid Keyer V025 - Installer
# This script copies the compiled plugin to your OBS directory.

$PluginName = "Halsu_HybridKeyer_V025"
$ObsPath = "C:\Program Files\obs-studio"

# 1. Source Paths (Relative to script location)
$CurrentDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$BaseSearchPath = Join-Path $CurrentDir "..\..\obs-shaderfilter\examples\generated_plugin\$PluginName\build"

$SrcDll = Join-Path $BaseSearchPath "Release\$PluginName.dll"
$SrcEffect = Join-Path $BaseSearchPath "$PluginName.effect"

# 2. Destination Paths
$DestDll = "$ObsPath\obs-plugins\64bit\$PluginName.dll"
$DestData = "$ObsPath\data\obs-plugins\$PluginName"
$DestEffect = "$DestData\$PluginName.effect"

Write-Host "--- Halsu OBS Plugin Installer ---" -ForegroundColor Cyan

# Check if OBS is running
if (Get-Process "obs64" -ErrorAction SilentlyContinue) {
    Write-Host "[!] Warning: OBS is currently running." -ForegroundColor Yellow
    Write-Host "Please close OBS Studio before proceeding." -ForegroundColor Red
    exit
}

# Check Source
if (!(Test-Path $SrcDll)) {
    Write-Host "[!] Error: Component not found at $SrcDll" -ForegroundColor Red
    Write-Host "Did you compile the plugin first?" -ForegroundColor Yellow
    exit
}

# Create Data Dir
if (!(Test-Path $DestData)) {
    Write-Host "[+] Creating data directory: $DestData"
    New-Item -ItemType Directory -Path $DestData -Force | Out-Null
}

try {
    Write-Host "[+] Copying DLL to: $DestDll"
    Copy-Item $SrcDll $DestDll -Force
    
    Write-Host "[+] Copying Effect to: $DestEffect"
    Copy-Item $SrcEffect $DestEffect -Force
    
    Write-Host "`n[***] INSTALLATION SUCCESSFUL [***]" -ForegroundColor Green
    Write-Host "You can now open OBS and find 'Halsu HybridKeyer V025' in your Filter list."
}
catch {
    Write-Host "`n[!] INSTALLATION FAILED" -ForegroundColor Red
    Write-Host $_.Exception.Message
    Write-Host "Note: You might need to run this script as Administrator." -ForegroundColor Yellow
}
