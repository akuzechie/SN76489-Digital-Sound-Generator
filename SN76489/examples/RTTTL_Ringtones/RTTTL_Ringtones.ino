//----------------------------------------------------------
// Play RTTTL Ringtones via SN76489 Digital Sound Generator
// and TTP229 16 Touch-Key Module
// using SN76489.h Library
// by: Anas Kuzechie (July, 2022)
//----------------------------------------------------------
#include <SN76489.h>
#include "Ringtones.h"
//---------------------------------------
           /*D0 D1 D2 D3 D4 D5 D6 D7 WE*/
SN76489 Play(2, 3, 4, 5, 6, 7, 8, 9, 13);
//---------------------------------------
#define SDO 11 /*SDO of TTP229 connected to pin 11*/
#define SCL 12 /*SCL connected to pin 12*/
int buttonPressed = 0, previousButton = 0;
//======================================================================
void setup()
{
  pinMode(SDO, INPUT); pinMode(SCL, OUTPUT);
  Play.muteChannels();        /*mute audio at all channels*/
  delay(1000);
}
//=======================================================================
void loop()
{
 for(int j=1; j<=16; j++)     /*determine number of touched button*/
  {
    digitalWrite(SCL, LOW);
    if(!digitalRead(SDO)) buttonPressed = j;
    digitalWrite(SCL, HIGH);
  }
  //--------------------------------------------------
  if(buttonPressed && buttonPressed != previousButton)
  {
    switch(buttonPressed)
    {
      case 1:
      Play.RTTTL(AxelFoley); Play.muteChannels(); break;
      case 2:
      Play.RTTTL(Halloween); Play.muteChannels(); break;
      case 3:
      Play.RTTTL(StarWars); Play.muteChannels(); break;
      case 4:
      Play.RTTTL(Mission); Play.muteChannels(); break;
      case 5:
      Play.RTTTL(Muppets); Play.muteChannels(); break;
      case 6:
      Play.RTTTL(PinkPanther); Play.muteChannels(); break;
      case 7:
      Play.RTTTL(NewYear); Play.muteChannels(); break;
      case 8:
      Play.RTTTL(Macarena); Play.muteChannels(); break;
    }
  }
  previousButton = buttonPressed;
  buttonPressed = 0;
}