# :apple: Tim Apple
Simple CS2 external cheat

![Preview](screenshots/preview.png)

## Features
*Most features have visibility check*
### ESP
- Health bar
- Player name
- Weapon icons / names
- Skeleton
- Joints
- Snap lines
- Distance
### Aim
- Aimbot
- Recoil control system
- Trigger bot
### Misc
- Bunny hop
- Anti flash

## Compiling from source
Open `tim_apple.sln` in Visual Studio 2022, set build configuration to `Release | x64`.      
Press Build solution and you should receive `tim_apple.exe` file.      

## Controls
Press the `INSERT` key to toggle the menu.     
Press the `END` key to end the cheat.

## Offsets
### Script download
Run the `offset_download.ps1` in the same folder as you're executable is
### Manual download
1. Download [client.dll.json](https://github.com/a2x/cs2-dumper/blob/main/generated/client.dll.json) and [offsets.json](https://github.com/a2x/cs2-dumper/blob/main/generated/offsets.json)    
2. Place these files in the same folder as the executable file `tim_apple.exe` is    

## FAQ
### How to use the weapon icon font file
**(If you download the release just leave it as is)** otherwise:
1. Make a folder called `fonts` in the same folder as the executable is.
2. Add the file `weaponIcons.ttf` in the folder.
*(If the program cannot see the file, weapon names will be displayed instead)*

## To-Do
- Add item ESP
- Add mouse_event to; aimbot,rcs
- Config file system

## Credits
- [ocornut/imgui](https://github.com/ocornut/imgui)
- [nlohmann/json](https://github.com/nlohmann/json)
- [a2x/cs2-dumper](https://github.com/a2x/cs2-dumper)
