//---------------------------------------------------------
// SN76489.h - Header File
// Library for Programming SN76489 Digital Sound Generator
// by: Anas Kuzechie (July, 2022)
//---------------------------------------------------------
//header guards
#ifndef SN76489_h
#define SN76489_h
//-----------------------------------------------------------------------
//class definition
class SN76489
{
    public:
    SN76489(byte D0,byte D1,byte D2,byte D3,byte D4,byte D5,byte D6,byte D7,byte WE);
    void muteChannels();
    void Tone(byte channel, uint16_t freq);
    void Noise(boolean noiseType, byte shiftRate);
    void Fade(byte channel, byte d);
    void RTTTL(char* song);
    //--------------------------------
    private:
    byte _D0, _D1, _D2, _D3, _D4, _D5, _D6, _D7, _WE;
    void sendByte(byte data);
};
//----------------------------------------------------------------------
#endif