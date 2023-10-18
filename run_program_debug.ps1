# Set the environment variables
$env:GSETTINGS_SCHEMA_DIR = "build/src/"
$env:G_MESSAGES_DEBUG = "all"

Remove-Item "build" -Recurse
& meson setup build -Dwdebug=true
& ninja -C build

# generate gschema
$schemaPath = "C:\msys64\mingw64\share\glib-2.0\schemas"
Copy-Item "data/com.github.jkotra.unlockr.gschema.xml" $schemaPath
& glib-compile-schemas.exe $schemaPath
Write-Output "glib-compile-schemas executed!"

# execute
& python windows_portable.py
& "build/src/unlockr.exe"