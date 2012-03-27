#include "stdafx.h"
#include "windows.h"

int DetectKeyInput()
{
  do {
    if(_kbhit())
    {
      return toupper(_getch());
      Sleep(100);
    }
  } while(1);
}