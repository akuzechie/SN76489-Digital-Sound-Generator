//----------------------------------------------------------
// Play RTTTL Ring Tones via SN76489 Digital Sound Generator
// using SN76489.h Library
// by: Anas Kuzechie (July, 2022)
//-----------------------------------------------------------
#include <SN76489.h>
//---------------------------------------
           /*D0 D1 D2 D3 D4 D5 D6 D7 WE*/
SN76489 Play(2, 3, 4, 5, 6, 7, 8, 9, 13);
//----------------------------------------------------------------------
const char*  AxelFoley =      /*string of RTTTL ringtone*/
"Axel F:d=4,o=4,b=125:f#,8a.,8f#,16f#,8b,8f#,8e,f#,8c#5.,8f#,16f#,8d5,"
"8c#5,8a,8f#,8c#5,8f#5,16f#,8e,16e,8c#,8g#,f#";
//======================================================================
void setup()
{
  Play.muteChannels();        /*mute audio at all channels*/
  delay(1000);
}
//=======================================================================
void loop()
{
  Play.RTTTL(AxelFoley);      /*play RTTTL ringtone*/
  Play.muteChannels();
  delay(1000);
}