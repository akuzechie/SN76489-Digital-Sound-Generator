//--------------------------------------------------------
// Play Tones & Noise via SN76489 Digital Sound Generator
// using SN76489.h Library
// by: Anas Kuzechie (July, 2022)
//--------------------------------------------------------
#include <SN76489.h>
//-------------------------------------------------
           /*D0 D1 D2 D3 D4 D5 D6 D7 WE*/
SN76489 Play(2, 3, 4, 5, 6, 7, 8, 9, 13);
//===============================================================
void setup()
{
  Play.muteChannels();        /*mute audio at all channels*/
  delay(1000);
}
//===============================================================
void loop()
{
  for(unsigned int i=122; i<=1000; i+=50)
  {
    Play.Tone(1, i);          /*tone of freq i @ channel 1*/
    Play.Tone(2, 122);        /*tone of freq 122Hz @ channel 2*/
    Play.Tone(3, 500);        /*tone of freq 500Hz @ channel 3*/
    delay(200);
  }
  //-------------------------------------------------------------
  Play.Fade(1, 100);          /*fade audio of channel 1*/
  Play.Fade(2, 100);          /*fade audio of channel 2*/
  Play.Fade(3, 100);          /*fade audio of channel 3*/ 
  delay(1000);
}