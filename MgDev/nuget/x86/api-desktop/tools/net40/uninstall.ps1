param($installPath, $toolsPath, $package, $project)

. (Join-Path $toolsPath "GetMgDesktopPostBuildCmd.ps1")

# Get the current Post Build Event cmd
$currentPostBuildCmd = $project.Properties.Item("PostBuildEvent").Value

# Remove our post build command from it (if it's there)
$project.Properties.Item("PostBuildEvent").Value = $currentPostBuildCmd.Replace($MgDesktopPostBuildCmd, "")
Write-Host "Removed mg-desktop post-build event"