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
const char*  AxelFoley =
"Axel F:d=4,o=4,b=125:f#,8a.,8f#,16f#,8b,8f#,8e,f#,8c#5.,8f#,16f#,8d5,"
"8c#5,8a,8f#,8c#5,8f#5,16f#,8e,16e,8c#,8g#,f#";
//----------------------------------------------------------------------
const char*  Halloween =
"Halloween:d=4,o=5,b=180:8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,"
"8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,"
"8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,f#";
//----------------------------------------------------------------------
const char*  Muppets =
"Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,"
"f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,"
"g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//======================================================================
void setup()
{
  Play.muteChannels();        /*mute audio at all channels*/
  delay(1000);
}
//=======================================================================
void loop()
{
  Play.RTTTL(AxelFoley);
  Play.muteChannels();
  delay(1000);

  Play.RTTTL(Halloween);
  Play.muteChannels();
  delay(1000);

  Play.RTTTL(Muppets);
  Play.muteChannels();
  delay(1000);
}