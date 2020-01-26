/////////////////////
// MenuSystem
// version: 1.0
// 22.12.2013
// CLASS
/////////////////////
#include <avr/pgmspace.h>
#include "MenuSystem.h"
#include "MenuDisplay.h"

MenuSystem::MenuSystem() {};

MenuSystem::MenuSystem(Adafruit_SSD1306 disp)
{
  //Serial.println("constrcutor menu system");
  qmd=MenuDisplay(disp);
  _selectedIndex=0;
  _itemCount=0;
  _firstVisible=1;
}

void MenuSystem::InitMenu(const char * const * page, int itemCount, int selectedIndex)
{
  CurrentMenu=page;
  _selectedIndex=selectedIndex;
  _itemCount=itemCount;
//  ProcessMenu(ACTION_NONE);
  ShowMenu();
}

int MenuSystem::ProcessMenu(int action)
{
  if (action==ACTION_DOWN)
    _selectedIndex++;
  if (action==ACTION_UP)
    _selectedIndex--;
    
  if (_selectedIndex>_itemCount)
    _selectedIndex=1;
  if (_selectedIndex<1)
    _selectedIndex=_itemCount;
  
  if (action==ACTION_SELECT)
    return _selectedIndex;
  
  ShowMenu();
  
  return 0;
}

void MenuSystem::ShowMenu()
{
  if (_selectedIndex>_firstVisible+2)
    _firstVisible=_selectedIndex-2;
  else if (_selectedIndex<_firstVisible)
    _firstVisible=_selectedIndex;
  
  qmd.Start();
  
  // display title
  strcpy_P(tempBuffer, (char*)pgm_read_word(&(CurrentMenu[0])));
  Serial.println(tempBuffer);
  qmd.Title(tempBuffer);
  
  // display items
  int p = 3;
  if (p > (_itemCount-_firstVisible+1))
    p=_itemCount-_firstVisible+1;
  for (int i=0;i<p;i++)
  {
    strcpy_P(tempBuffer, (char*)pgm_read_word(&(CurrentMenu[i+_firstVisible])));
    qmd.Item(i,tempBuffer);
  }
  
   strcpy_P(tempBuffer, (char*)pgm_read_word(&(CurrentMenu[_selectedIndex])));

   // display selection
   qmd.Highlight(_selectedIndex-_firstVisible,tempBuffer);
  
  qmd.Finish();
}
