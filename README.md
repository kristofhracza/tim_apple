# :apple: Tim Apple
Simple CS2 external cheat

![Preview](screenshots/preview.png)

## Features
- Customizable ESP
	- Health bar (optional HP counter with numbers)
	- Player name
	- Weapon name
	- Skeleton
	- Snap lines
	- Distance
- Aimbot
- Recoil control system
- Bunny hop
- Anti flash

## Compiling from source
Open `tim_apple.sln` in Visual Studio 2022, set build configuration to `Release | x64`.      
Press Build solution and you should receive `tim_apple.exe` file.

## Offsets
### Script 
Run the `offset_download.ps1` in the same folder and you're executable is
### Manual
1. Download [client.dll.json](https://github.com/a2x/cs2-dumper/blob/main/generated/client.dll.json) and [offsets.json](https://github.com/a2x/cs2-dumper/blob/main/generated/offsets.json)    
2. Place these files in the same folder as the executable file `tim_apple.exe` is     

## To-Do
*These features will be implemented when I have the time...*
### Features
- Entity visibility check
- Change ESP colour depending on visibility
- Dropped item ESP
- Trigger Bot
- Proper UTF-8 names
### Code
- Proper implementation of the item and weapon classes

## Known bugs
- Bone ESP lines go through the screen sometimes
- RCS doesn't always work with aimbot

## Credits
- [ocornut/imgui](https://github.com/ocornut/imgui)
- [nlohmann/json](https://github.com/nlohmann/json)
- [a2x/cs2-dumper](https://github.com/a2x/cs2-dumper)
