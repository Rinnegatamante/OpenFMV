# OpenFMV
OpenFMV is an opensource FMV (Full Motion Video) game engine made in C/C++. The engine is designed to be modular and compatible with Wales Interactive FMV games.

## Supported Platforms
| Platform         |
| :------------------- |
| PlayStation Vita     |

## Commercial Games Support
In order to play existing commercial games with this engine, you'll need to provide data files from your purchased copy of the game. Please refer to the setup section of the game you desire to play to know how to set it up.
This repository does not contain any copyrighted asset coming from the games and the game code has been completely rewritten from scratch by observing the game behaviour with the help of some Unity debugging tools.
| Game | Audio Code | Menus | Game Logic |
| :------------------- | :------------------- | :------------------- | :------------------- |
| [Bloodshore](https://store.steampowered.com/app/1490840/Bloodshore/)     | 0% | 0% |0% |
| [Five Dates](https://store.steampowered.com/app/1353270/Five_Dates/)     | 0% | 0% |0.13% |
| [I Saw Black Clouds](https://store.steampowered.com/app/1346830/I_Saw_Black_Clouds/)     | 0% | 0% |0% |
| [Late Shift](https://store.steampowered.com/app/584980/Late_Shift/)     | 1.57% | 92.00% |41.54% |
| [Mia and the Dragon Princess](https://store.steampowered.com/app/1837580/Mia_and_the_Dragon_Princess/)     | 0% | 0% |0% |
| [Night Book](https://store.steampowered.com/app/1477920/Night_Book/)     | 0% | 0% |0% |
| [Ten Dates](https://store.steampowered.com/app/1946070/Ten_Dates/)     | 0% | 0% |0% |
| [The Bunker](https://store.steampowered.com/app/481110/The_Bunker/)     | 0% | 0% |0% |
| [The Complex](https://store.steampowered.com/app/1107790/The_Complex/)     | 0% | 0% |0% |
| [The Shapeshifting Detective](https://store.steampowered.com/app/898650/The_Shapeshifting_Detective/)     | 0% | 0% |0% |
| [Who Pressed Mute on Uncle Marcus?](https://store.steampowered.com/app/1628130/Who_Pressed_Mute_on_Uncle_Marcus/)     | 0% | 0% |0% |

## Building the source
Assuming a standard vitasdk installation is properly set up on your machine. You can compile each game with the following commands:<br>
Late Shift: `make LATE_SHIFT=1`<br>
Five Dates: `make FIVE_DATES=1`

## Setting up the game
### Late Shift
- Install `lateshift.vpk`.
- Place the content of `data/Late Shift` (provided in the Release inside a .zip file) in `ux0:data/Late Shift`.
- Grab the `Subtitles` folder from your purchased copy of the game and place it in `ux0:data/Late Shift`.
- Place `scripts/video_process.bat` inside the folder of your purchased copy of the game and run it (you'll need to install ffmpeg if you don't have it already).
- Install [Total Commander](https://www.ghisler.com/download.htm) and its [PSARC plugin](http://totalcmd.net/plugring/PSARC.html).
- Launch Total Commander and navigate up to your purchased copy of the game main folder.
- Right click on `Converted` folder; it will turn red.
- Click on `File -> Pack`.
- Set `psarc` as Compressor and then click on `Configure` button right below.
- Set `PSARC Version` to `1.3`, `Compression` to `ZLIB` and `Ratio` to `0` and press `OK`.
- Press `OK` to launch the compression, it will create a file in `C:\Converted.psarc`. (If you get an error, manually change the location in the command line string `psarc: DESTINATIONFOLDER\Converted.psarc`).
- Place the resulting psarc file in `ux0:data/Late Shift` named as `Videos.psarc`.
- Download and install [AssetStudio](https://github.com/Perfare/AssetStudio/releases/tag/v0.16.47)
- Launch AssetStudioGUI and click on `File -> Load File`.
- Open the file `LateShift_Data/StreamingAssets/AssetBundles/audio` with it.
- Click on `Export -> All assets` and select an empty folder where to extract the assets.
- Place `scripts/audio_process.bat` in the same folder where you extracted the assets and run it.
- Copy the resulting `oggs` folder in `ux0:data/Late Shift`.

## Credits
- hatoving: Helping with setting up tools and giving an hand with initial Late Shift rewrite.
