#include "playmidiout.h"
//#include <regex>
#include <math.h>


namespace RtMidiWrap {

PlayMidiOut::PlayMidiOut(){

    midiout = std::unique_ptr<MidiOut>(new MidiOut());
    midiinout = midiout.get();



}



std::vector<BYTE> PlayMidiOut::_convertNoteToArray(std::vector<std::string> notes){
    std::vector<BYTE> notesNumbers;
    for (auto &itm : notes)
    {
        notesNumbers.push_back(guessNoteNumber(itm));
    }
    return notesNumbers;
}

void PlayMidiOut::sendChannelMode(MIDI_CHANNEL_MODE_MESSAGES command, BYTE value, std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {0,0,0};
    const int i = MIDI_CHANNEL_MESSAGES::channelmode;
    sndVector[1] = command;
    sndVector[2] = value;
    for (auto &channel : channels){
        sndVector[0]= (i<<4) + (channel -1) ;
        sendMessage(&sndVector);
    }
}

void PlayMidiOut::_selectRegisteredParameter(std::vector<BYTE> parameterAry, std::vector<BYTE> channel){
    sendControlChange(0x65, parameterAry[0], channel);
    sendControlChange(0x64, parameterAry[1], channel);
}

void PlayMidiOut::_selectNonRegisteredParameter(std::vector<BYTE> parameterAry, std::vector<BYTE> channel){
    sendControlChange(0x63, parameterAry[0], channel);
    sendControlChange(0x62, parameterAry[1], channel);
}

void PlayMidiOut::_deselectRegisteredParameter( std::vector<BYTE> channels){
    sendControlChange(0x65, 0x7F, channels);
    sendControlChange(0x64, 0x7F, channels);
}

void PlayMidiOut::sendControlChange(BYTE controller, BYTE value, std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {0,0,0};
    const int i = MIDI_CHANNEL_MESSAGES::controlchange;
    sndVector[1] = controller;
    sndVector[2] = value;
    for (auto &channel : channels){
        sndVector[0]= (i<<4) + (channel -1) ;
        sendMessage(&sndVector);
    }
}

void PlayMidiOut::setNonRegisteredParameter( std::vector<BYTE> parameter, std::vector<BYTE> data, std::vector<BYTE> channels){
    parameter.insert( parameter.end(), data.begin(), data.end() );
    for (auto &channel : channels){
        _selectNonRegisteredParameter(parameter, {channel});
        _setCurrentRegisteredParameter(data, {channel});
        _deselectRegisteredParameter({channel});
    }
}

void PlayMidiOut::_setCurrentRegisteredParameter( std::vector<BYTE> data, std::vector<BYTE> channels){

    for (auto &channel : channels){
        sendControlChange(0x06, data[0], {channel});
    }

    //if(data[1] >= 0 && data[1] <= 127) { //this is always true because of data type
        for (auto &channel : channels){
            sendControlChange(0x26, data[1], {channel});
        }
    //}
}

void PlayMidiOut::setModulationRange(BYTE semitones,BYTE cents,std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {semitones,cents};
    for (auto &channel : channels){
        setRegisteredParameter(MIDI_REGISTERED_PARAMETER::modulationrange,sndVector,{channel});
    }
}

void PlayMidiOut::setPitchBendRange(BYTE semitones,BYTE cents,std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {semitones,cents};
    for (auto &channel : channels){
        setRegisteredParameter(MIDI_REGISTERED_PARAMETER::pitchbendrange,sndVector,{channel});
    }
}

void PlayMidiOut::sendClock(){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::clock;
    sendMessage(&sndVector);
}

void PlayMidiOut::sendContinue(){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::ccontinue;
    sendMessage(&sndVector);
}

void PlayMidiOut::sendSysex(std::vector<BYTE> data){
    std::vector<BYTE> sndVector = {0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::sysex;
    sndVector.insert( sndVector.end(), data.begin(), data.end() );
    sndVector.push_back(  MIDI_SYSTEM_MESSAGES::sysexend);
    sendMessage(&sndVector);
}

void PlayMidiOut::sendStop(){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::stop;
    sendMessage(&sndVector);
}

void PlayMidiOut::sendStart(){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::start;
    sendMessage(&sndVector);
}

void PlayMidiOut::sendMessage(const std::vector<BYTE> *message){    
    this->midiout->sendMessage(message);
}
void PlayMidiOut::sendMessage(const BYTE *message,size_t 	size){
    this->midiout->sendMessage(message,size);
}

void PlayMidiOut::sendSongSelect(BYTE value){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::songselect;
    sndVector[1] = value;
    sendMessage(&sndVector);
}

void PlayMidiOut::sendTimecodeQuarterFrame(BYTE value){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::timecode;
    sndVector[1] = value;
    sendMessage(&sndVector);
}


void PlayMidiOut::sendReset(){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::reset;
    sendMessage(&sndVector);
}

//desired decimal adjustment value in semitones (-65 < x < 64)
void PlayMidiOut::setMasterTuning(float value, std::vector<BYTE> channels ){
    if (value <= -65 || value >= 64) {
        throw std::runtime_error("The value must be a decimal number larger than -65 and smaller than 64.");
    }

    float coarse = floor(value) + 64;
    float fine = value - floor(value);

    // Calculate MSB and LSB for fine adjustment (14bit resolution)
    int finei = (int)ceill((fine + 1) / 2 * 16383);
    int msb = (finei >> 7) & 0x7F;
    int lsb = finei & 0x7F;

    std::vector<BYTE> sndVector = {0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::reset;
    sendMessage(&sndVector);

    for (auto &channel : channels){
        sndVector[0] = (BYTE)coarse;
        sndVector[1] = 0;
        setRegisteredParameter(MIDI_REGISTERED_PARAMETER::channelcoarsetuning, sndVector, {channel});
        sndVector[0] = msb;
        sndVector[1] = lsb;
        setRegisteredParameter(MIDI_REGISTERED_PARAMETER::channelfinetuning, sndVector, {channel});
    }


}

void PlayMidiOut::sendTuningRequest(){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::tuningrequest;
    sendMessage(&sndVector);
}

void PlayMidiOut::sendSongPosition(int value){
    std::vector<BYTE> sndVector = {0,0,0};
    int msb = (value >> 7) & 0x7F;
    int lsb = value & 0x7F;
    sndVector[0] = MIDI_SYSTEM_MESSAGES::songposition;
    sndVector[1] = msb;
    sndVector[2] = lsb;
    sendMessage(&sndVector);
}

void PlayMidiOut::sendActiveSensing(){
    std::vector<BYTE> sndVector = {0,0,0};
    sndVector[0] = MIDI_SYSTEM_MESSAGES::activesensing;
    sendMessage(&sndVector);
}
void PlayMidiOut::decrementRegisteredParameter(MIDI_REGISTERED_PARAMETER parameter, std::vector<BYTE> channels){
    std::vector<BYTE> parameterAry = midiRegisteredParameter[parameter];
    for (auto &channel : channels){

        _selectRegisteredParameter(parameterAry, {channel});
        sendControlChange(0x61, 0, {channel});
        _deselectRegisteredParameter({channel});

    }
}

void PlayMidiOut::incrementRegisteredParameter(MIDI_REGISTERED_PARAMETER parameter, std::vector<BYTE> channels){
    std::vector<BYTE> parameterAry = midiRegisteredParameter[parameter];
    for (auto &channel : channels){

        _selectRegisteredParameter(parameterAry, {channel});
        sendControlChange(0x60, 0, {channel});
        _deselectRegisteredParameter({channel});

    }
}

void PlayMidiOut::setRegisteredParameter(MIDI_REGISTERED_PARAMETER parameter,  std::vector<BYTE> data, std::vector<BYTE> channels){
    std::vector<BYTE> parameterAry = midiRegisteredParameter[parameter];
    for (auto &channel : channels){

        _selectRegisteredParameter(parameterAry, {channel});
        sendControlChange(data[0], data[1], {channel});
        _deselectRegisteredParameter({channel});

    }
}

void PlayMidiOut::stopNote( std::vector<std::string> notes, std::vector<BYTE>  channels, BYTE velocity){
    if (notes.size() == 1 && notes[0] == "all"){
        sendChannelMode(MIDI_CHANNEL_MODE_MESSAGES::allnotesoff, 0, channels);
        return;
    }
    std::vector<BYTE> sndVector = {0,0,0};
    const int i = MIDI_CHANNEL_MESSAGES::noteoff;
    for (auto &note: _convertNoteToArray(notes)){
        sndVector[1] = note;
        sndVector[2] = velocity;
        for (auto &channel : channels){
            sndVector[0]= (i<<4) + (channel -1) ;
            sendMessage(&sndVector);
        }
    }
}

void PlayMidiOut::playNote( std::vector<std::string> notes, std::vector<BYTE>  channels, BYTE velocity){


    std::vector<BYTE> sndVector = {0,0,0};
    for (auto &note: _convertNoteToArray(notes)){
        sndVector[1] = note;
        sndVector[2] = velocity;
        for (auto &channel : channels){
            int i = MIDI_CHANNEL_MESSAGES::noteon;
            sndVector[0]= (i<<4) + (channel -1) ;
            sendMessage(&sndVector);
        }
    }

}

void PlayMidiOut::sendKeyAftertouch(std::vector<std::string> notes, std::vector<BYTE> channels, BYTE pressure){
    std::vector<BYTE> sndVector = {0,0,0};
    for (auto &note: _convertNoteToArray(notes)){
        sndVector[1] = note;
        sndVector[2] = pressure;
        for (auto &channel : channels){
            int i = MIDI_CHANNEL_MESSAGES::keyaftertouch;
            sndVector[0]= (i<<4) + (channel -1) ;
            sendMessage(&sndVector);
        }
    }
}

void PlayMidiOut::sendChannelAftertouch(BYTE pressure, std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {0,0,0};

    sndVector[1] = pressure;
    for (auto &channel : channels){
        int i = MIDI_CHANNEL_MESSAGES::channelaftertouch;
        sndVector[0]= (i<<4) + (channel -1) ;
        sendMessage(&sndVector);
    }
}

void PlayMidiOut::sendPitchBendLsbMsb(BYTE lsb, BYTE msb,  std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {0,0,0};
    for (auto &channel : channels){
        int i = MIDI_CHANNEL_MESSAGES::pitchbend;
        sndVector[0]= (i<<4) + (channel -1) ;
        sndVector[1] = lsb;
        sndVector[2] = msb;
        sendMessage(&sndVector);
    }
}

void PlayMidiOut::sendProgramChange(BYTE program, std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {0,0};
    for (auto &channel : channels){
        int i = MIDI_CHANNEL_MESSAGES::programchange;
        sndVector[0]= (i<<4) + (channel -1) ;
        sndVector[1] = program;
        sendMessage(&sndVector);
    }
}

void PlayMidiOut::setTuningBank(BYTE value, std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {0,0};
    sndVector[0] = value;
    for (auto &channel : channels){
        setRegisteredParameter(MIDI_REGISTERED_PARAMETER::tuningbank,sndVector, {channel});
    }
}

void PlayMidiOut::setTuningProgram(BYTE value, std::vector<BYTE> channels){
    std::vector<BYTE> sndVector = {0,0};
    sndVector[0] = value;
    for (auto &channel : channels){
        setRegisteredParameter(MIDI_REGISTERED_PARAMETER::tuningprogram,sndVector, {channel});
    }
}

void PlayMidiOut::sendPitchBend(float bend,  std::vector<BYTE> channels){
    if (bend < -1 || bend > 1){throw std::runtime_error("Pitch bend value must be between -1 and 1.");}
    int nLevel = (int)ceill(( bend + 1) / 2 * 16383);
    int msb = (nLevel >> 7) & 0x7F;
    int lsb = nLevel & 0x7F;
    sendPitchBendLsbMsb(lsb,msb,channels);
}




}


