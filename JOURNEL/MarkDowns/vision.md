ROS2 Assembly Studio
Purpose: Create robots visually and export .xacro files.

Architecture:

main ├─ Scene ├─ Camera ├─ Renderer └─ Shader

Current Milestone: Render 3D grid and XYZ axes.

Future: Orbit camera Robot parts Xacro exporter


_______________------future directories
JellyFish/
├── Future/
│   ├── roadmap.md
│   ├── architecture.md -- currently remodeding 
│   ├── journal.md
│   └── known_issues.md --none at the mommet, everything compiles and 0 bugs as of 11/18/26 - 1pm --- 1 issue as of 11/19 ~1am: minor is shader.cpp not defining cause compile issue but im impementing some fix to shader.cpp then will commit.


Quick paste: for newer people 
 recompile and debug-- cmake --build . --config Debug
 Running an exe-- dir -Recurse *.exe
 Executable--  .\Debug\JellyFish.exe or .\x64\Debug\JellyFish.exe
 Reconfiger-- cmake . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake