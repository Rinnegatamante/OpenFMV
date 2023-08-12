mkdir oggs
for %%f in (AudioClip/*.wav) do ffmpeg -i "AudioClip/%%f" "oggs/%%f.ogg"