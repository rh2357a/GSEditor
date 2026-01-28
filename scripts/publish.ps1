# Build & Publish
dotnet publish ..\src -c Release -r win-x64 /p:PublishDir=..\build\publish

# Cleanup
Remove-Item ..\build\publish\*.dll -Force -ErrorAction SilentlyContinue
Remove-Item ..\build\publish\*.pdb -Force -ErrorAction SilentlyContinue
Remove-Item ..\build\publish\GSEditor*.json -Force -ErrorAction SilentlyContinue
Remove-Item ..\build\publish\Obfuscar -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item ..\build\publish\BuildFiles -Recurse -Force -ErrorAction SilentlyContinue
