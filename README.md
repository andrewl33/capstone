# JUCE Synth

UI experiments live here. Base code is taken from https://github.com/theaudioprogrammer/juceSynthFramework, up to the last synth tutorial.
Main repo [rorschach synth](https://github.com/sjudkis/rorschach).

## Maximilian

Audio library

Steps to add:
1. Download [Maximilian](https://github.com/micknoise/Maximilian)
2. Delete folders: test, examples, openFrameworks.
3. In parent, delete everything but stb_vorbis.\*, maximilian.\*
4. In Projuicer, Exporters>Headers(all), add maximilian path
5. in Projuicer, File explorer, drag in Maximilian folder

## Folders

| Folder     | Description           | 
| ---|--:|
|base| Contains base working synth; all other projects are based on this.|
|static| Contains mock static UI |
