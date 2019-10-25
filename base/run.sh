$ JUCE_DIR / Projucer --set-global-search-path linux defaultJuceModulePath $ JUCE_DIR / modules
$ JUCE_DIR / Projucer --resave base.jucer

cd Builds / LinuxMakefile && make && cd ../ ..

Builds / LinuxMakefile / build / application