#ifndef CALC_H
#define CALC_H
//#include <string>
//#include <map>
#include "common.h"
#include "libs/rtmidi/RtMidi.h"

// Platform-dependent sleep routines.
#if defined(WIN32)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif


namespace RtMidiWrap {




//MyClass.h
class RtMidiWrapClass {
public:
      //static defs
      typedef std::map<int, std::string> OpMap;
      static OpMap apiMap;
};


std::vector<std::string> getCompiledApi();


class IMidiInOut{

public:
    unsigned int getPortCount();
    std::string getPortName(unsigned int portNumber);
    int getPortNumber(const std::string &portName);
    void openPort( unsigned int portNumber = 0, const std::string &setPortName = std::string( "RtMidi" ) ) ;
    int openPort( const std::string &PortName, const std::string &setPortName = std::string( "RtMidi" ) ) ;
    bool isPortOpen	(void);
    void openVirtualPort	(const std::string & portName = std::string( "RtMidi Output" )	);
    void setErrorCallback	(RtMidiErrorCallback errorCallback = NULL, void * 	userData = 0 );
    int openedPortNumber = -1;
    std::string openedPortName = "";
protected:
    RtMidi  *p_midi=0;
private:
    unsigned int unqIdPortNumber(unsigned int portNumber);
};

class MidiIn:public IMidiInOut{
RtMidiIn  *p_midi_in=0;
public:
    //! User callback function type definition.
    typedef void (*RtMidiCallback)( double timeStamp, std::vector<unsigned char> *message, void *userData );

    MidiIn();
    ~MidiIn(void);
    std::string getCurrentApi();

    void setCallback( RtMidiCallback callback, void *userData = 0 );
    void cancelCallback();
    void ignoreTypes( bool midiSysex = true,bool midiTime = true, bool midiSense = true);
    double getMessage	(std::vector< unsigned char > * message	);

};

class MidiOut:public IMidiInOut{
    RtMidiOut  *p_midi_out=0;
public:
    MidiOut();
    ~MidiOut(void);
    std::string getCurrentApi();
    void sendMessage(const std::vector< BYTE > *message);
    void sendMessage(const BYTE * 	message,size_t 	size);

};

}






#endif // CALC_H
