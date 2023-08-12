mkdir Converted
for %%f in (Videos/*.mp4) do ffmpeg -i Videos/%%f -ac 2 -vf "fps=30,scale=1280:720:force_original_aspect_ratio=decrease,pad=1280:720:-1:-1:color=black" Converted/%%f