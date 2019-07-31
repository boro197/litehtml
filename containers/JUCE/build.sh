#!/bin/sh
#cd containers/JUCE
Projucer --resave LiteHtmlForJUCE.jucer
cd JuceFiles 
make -j 12 CXX=g++-8
cd ..
mv JuceFiles/build/LiteHtmlForJUCE-DEBUG ./
