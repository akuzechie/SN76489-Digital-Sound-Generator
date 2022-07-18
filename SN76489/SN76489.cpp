//---------------------------------------------------------
// SN76489.cpp - Source File
// Library for Programming SN76489 Digital Sound Generator
// by: Anas Kuzechie (July, 2022)
//---------------------------------------------------------
#include <Arduino.h>
#include <SN76489.h>
//========================================================================
// Constructor
//========================================================================
SN76489::SN76489(byte D0,byte D1,byte D2,byte D3,byte D4,byte D5,byte D6,byte D7,byte WE)
{
  pinMode(D0, OUTPUT); _D0 = D0;
  pinMode(D1, OUTPUT); _D1 = D1;
  pinMode(D2, OUTPUT); _D2 = D2;
  pinMode(D3, OUTPUT); _D3 = D3;
  pinMode(D4, OUTPUT); _D4 = D4;
  pinMode(D5, OUTPUT); _D5 = D5;
  pinMode(D6, OUTPUT); _D6 = D6;
  pinMode(D7, OUTPUT); _D7 = D7;
  pinMode(WE, OUTPUT); _WE = WE;
}
//========================================================================
#define QUARTZFREQ 4000000UL
//---------------------------
uint32_t freq[] = {112640,126434,66976,75178,84385,89403,100351,119338,
                   0,70959,79649,0,94719,106318};
//========================================================================
// Public Methods
//========================================================================
void SN76489::muteChannels()
{
  sendByte(0x9F);               /*mute channel 1*/
  sendByte(0xBF);               /*mute channel 2*/
  sendByte(0xDF);               /*mute channel 3*/
  sendByte(0xFF);               /*mute noise channel*/
}
//========================================================================
void SN76489::Tone(byte channel, uint16_t freq)
{
  uint16_t f76489;
  f76489 = 4000000UL/(32*freq); /*compute 10-bit tone freq*/
  //----------------------------------------------------------------------
  switch(channel)               /*send 1st byte to channel 1, 2, or 3*/
  {
    case 1: sendByte(0x80 | (f76489 & 0x0F)); break;
    case 2: sendByte(0xA0 | (f76489 & 0x0F)); break;
    case 3: sendByte(0xC0 | (f76489 & 0x0F));
  }
  sendByte(f76489>>4);          /*send 2nd byte*/
  //----------------------------------------------------------------------
  switch(channel)               /*max audio @ channel 1, 2, or 3*/
  {
    case 1: sendByte(0x90); break;
    case 2: sendByte(0xB0); break;
    case 3: sendByte(0xD0);
  }
}
//========================================================================
void SN76489::Noise(boolean noiseType, byte shiftRate)
{
  if(noiseType==0)
  {
    sendByte(0xE0|shiftRate);     /*perioic noise*/
    sendByte(0xF0);
  }
  else
  {
    sendByte(0xE4|shiftRate);     /*white noise*/
    sendByte(0xF0);
  }
}
//========================================================================
void SN76489::Fade(byte channel, byte d)
{
  byte i, j, k;
  switch(channel)
  {
    case 1: i=0x91; j=0x9F; break;
    case 2: i=0xB1; j=0xBF; break;
    case 3: i=0xD1; j=0xDF; break;
    case 4: i=0xF1; j=0xFF;
  }
  for(k=i; k<=j; k++)
  {
    sendByte(k); delay(d);
  }
}
//========================================================================
// Function by Le Fauve (https://github.com/LeFauve)
// which does the following:
// 1. extracts the default values from RTTTL string
// 2. extracts each musical note from string and computes tone freq in Hz
// 3. computes from tone freq the 10-bit freq & sends it to SN76489
//-------------------------------------------------------------------------
void SN76489::RTTTL(char* song)
{
  uint16_t d, o, b, i=0;
  uint16_t beatDuration, durationStep, fIndex, nd, no, duration;
  uint16_t frequency, f76489;
  uint16_t* pV;
  byte v;
  while(song[i]!=':') ++i;              /*Skip title*/
  ++i;
  //----------------------------------------------------------------------
  while(song[i]!=':')                   /*default values*/
  {
    switch(song[i])
    {
      case 'o': pV = &o; break;
      case 'd': pV = &d; break;
      case 'b': pV = &b; break;
      default: return; break;           /*error (unexpected character)*/
    }
    //---------------------------------------------------------------------
    while(song[++i] == '=');            /*skip '=' if present*/
    //---------------------------------------------------------------------
    *pV = 0;
    while(song[i]!=',' && song[i]!=':')
    {
      *pV = *pV*10 + (song[i]-'0');
      ++i;
    }
    if(song[i]==',') ++i;
  }
  ++i;
  //----------------------------------------------------------------------
  beatDuration = 240000UL/b;            /*measure duration (4 beats)*/
  durationStep = beatDuration>>(4+2);   /*16 steps for volume sweep/beat*/
  //----------------------------------------------------------------------
  while(song[i])                        /*song*/
  {
    if(isDigit(song[i]))                /*override duration*/
    { 
      nd = song[i++]-'0';
      if(isDigit(song[i]))
      {
        nd = nd*10 + (song[i++]-'0');
      }
    }
    else nd = d;

    duration = beatDuration / nd;
    
    if(song[i]=='p')                    /*pause*/
    { 
      frequency = 0;   
      ++i;
    }
    else                                /*note*/
    { 
      fIndex = song[i++]-'a';
      if(song[i] == '#')
      {
        fIndex += 7;
        ++i;
      }
      if(isDigit(song[i]))              /*override octave*/
      {
        no = 0;
        while(isdigit(song[i])) no = no * 10 + (song[i++]-'0');
      }
      else no = o;
      frequency = freq[fIndex] >> (7-no);
    }
    if(song[i] == '.')
    {
      duration *= 1.5;
      ++i;
    }
    //--------------------------------------------------------------------
    if(frequency)                       /*play note*/
    { 
      f76489 = QUARTZFREQ / frequency;  /*compute 10-bit freq*/
      sendByte(0x80 | (f76489 & 0x0F)); /*send 1st byte*/
      sendByte(f76489>>4);              /*send 2nd byte*/
      sendByte(0x90);
      //------------------------------------------------------------------
      if(duration>(durationStep<<4))
      {
        delay(duration-(durationStep<<4));
        duration = durationStep<<4;
      }
      for(v=0x91; v<0x90+(duration/durationStep); ++v)
      {
        delay(durationStep);
        sendByte(v);
      }
      delay(durationStep);
    }
    else delay(duration);               /*wait for pause*/
    if(song[i] == ',') ++i;
  }
  sendByte(0x9F);
}
//========================================================================
void SN76489::sendByte(byte data)
{
  digitalWrite(_WE, HIGH);
  //-------------------------------------
  digitalWrite(_D0, (data & 1)  ?HIGH:LOW);
  digitalWrite(_D1, (data & 2)  ?HIGH:LOW);
  digitalWrite(_D2, (data & 4)  ?HIGH:LOW);
  digitalWrite(_D3, (data & 8)  ?HIGH:LOW);
  digitalWrite(_D4, (data & 16) ?HIGH:LOW);
  digitalWrite(_D5, (data & 32) ?HIGH:LOW);
  digitalWrite(_D6, (data & 64) ?HIGH:LOW);
  digitalWrite(_D7, (data & 128)?HIGH:LOW);
  //-------------------------------------
  digitalWrite(_WE, LOW); delay(1);
  digitalWrite(_WE, HIGH);
}