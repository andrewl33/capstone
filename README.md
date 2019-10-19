# JUCE Synth

UI experiments live here. Base code is taken from https://github.com/theaudioprogrammer/juceSynthFramework, up to the last synth tutorial.
Main repo [rorschach synth](https://github.com/sjudkis/rorschach).

The end product should look like, with many UI components living in this repo:
![Rorsharch Synth](https://raw.githubusercontent.com/andrewl33/capstone/master/imgs/goal.png)

## Maximilian

Audio library

Steps to add:
1. Download [Maximilian](https://github.com/micknoise/Maximilian)
2. Delete folders: test, examples, openFrameworks.
3. In parent, delete everything but stb_vorbis.\*, maximilian.\*
4. In Projuicer, Exporters>Headers(all), add maximilian path
5. in Projuicer, File explorer, drag in Maximilian folder

## Folders

| Folder     | Description           | Image |
| ---|:--:|---:|
|base| Contains base working synth; all other projects are based on this.|
|static| Contains mock static UI |![Week 4 update](https://raw.githubusercontent.com/andrewl33/capstone/master/imgs/week4lookandfeel.png)|
