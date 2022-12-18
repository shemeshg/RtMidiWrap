# RtMidi c++ wrapper

<a href="https://sourceforge.net/projects/midi-router-client"><img alt="Midi router Reviews" src="https://sourceforge.net/cdn/syndication/badge_img/3211406/oss-rising-star-white?achievement=oss-rising-star&amp;r=https://sourceforge.net/p/midi-router-client/admin/files/badges"  style="width: 200px;"></a>



- Wrap RtMidi In [WebMidi.js](https://github.com/djipco/webmidi) format.

The library is here https://github.com/shemeshg/RtMidiWrap/tree/master/src/RtMidiRouterLib/RtMidiWrap 

To install, copy this folder to your project.

All function names and parameters are the same as in [WebMidi.js (version 2)](https://github.com/djipco/webmidi).

- The project of advanced Midi router is this repository.

1. Route midi over the network.
2. filter midi messages
3. Split keyboard

The frontend is Vue js can be clonedd here:
https://github.com/shemeshg/midi-router-client

[Compiled server and client for OSX,linux or windows:](https://sourceforge.net/projects/midi-router-client/)



## Getting Started

### Prerequisites

The router project is a Qt6, however the RtMidiWrap library is standard c++.


### Installing
Pull origin

```
git clone  https://github.com/shemeshg/RtMidiWrap.git
```

Open project in QtCreate and compile and qtdeploy.

## How to use the library

### input

```c++
class MidiInLogOut:public RtMidiWrap::PlayMidiIn{
    void listener(MidiEvent &m){
        std::cout<<m.data1<<" ";
        std::cout<<m.data2<<std::endl;
    }
};


MidiInLogOut p;
p.openPort(id);
p.ignoreTypes(false, false, false);
 ```

### output

```c++
RtMidiWrap::PlayMidiOut p;
p.openPort(od);
p.sendPitchBend(-1,{1});
```

## Midi Router command line options

`./MidiRouter` *run server on port 12345*

`./MidiRouter -h`  *Show help*

`./MidiRouter -p |port number|`  *run the webchannel server on selected port*

`./RtMidiWrap -v |port name|` *setup virtual port (input and output with the name provided*


## Routing configuration

### filters params mapping

`[a]` map a to a

`[[a],[b]]` map a to a, map b to b

`[a,b]` map a to b

`[4,8,10]` is equivalent to `[[4,10],[5,11],[6,12],[7,13],[8,14]]` 

`[1,3,10,16]` would map `[1,10],[2,13],[3,16]`

## Built With

- [Qt Create Open Source and QT6](https://www.qt.io/)

- [Qt web channel](https://doc.qt.io/qt-6/qtwebchannel-index.html) (This is part of the Complete open source Qt install) 

- [RtMidi](https://www.music.mcgill.ca/~gary/rtmidi/) - C++ access to MIDI (Already part of the project files, no need to install) 

- https://github.com/P1eaz/QWebchannelCppClient/blob/master/main.cpp (Already part of the project files, no need to install, for server to server WebChannel)

- Icon made by Pixel perfect from www.flaticon.com

## Authors

- **shemeshg**

## License

Copyright 2020 shemeshg

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
