#include <MenuBackend.h>    //MenuBackend library - copyright by Alexander Brevig
#include <LiquidCrystal.h>  //this library is included in the Arduino IDE
int led = 5 ;
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  

   // For V1.0 comment the other threshold and use the one below:
   /*
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
   */

    return btnNONE;                // when all others fail, return this.
}


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Menu variables
MenuBackend menu = MenuBackend(menuUsed,menuChanged);
//initialize menuitems
    MenuItem menu1Item1 = MenuItem("Item1");
      MenuItem menuItem1SubItem1 = MenuItem("Item1SubItem1");
      MenuItem menuItem1SubItem2 = MenuItem("Item1SubItem2");
    MenuItem menu1Item2 = MenuItem("Item2");
      MenuItem menuItem2SubItem1 = MenuItem("Item2SubItem1");
      MenuItem menuItem2SubItem2 = MenuItem("Item2SubItem2");
      MenuItem menuItem3SubItem3 = MenuItem("Item2SubItem3");
    MenuItem menu1Item3 = MenuItem("Item3");


void setup()
{
  lcd.begin(16, 2);

  //configure menu
  menu.getRoot().add(menu1Item1);
  menu1Item1.addRight(menu1Item2).addRight(menu1Item3);
  menu1Item1.add(menuItem1SubItem1).addRight(menuItem1SubItem2);
  menu1Item2.add(menuItem2SubItem1).addRight(menuItem2SubItem2).addRight(menuItem3SubItem3);
  menu.toRoot();
  lcd.setCursor(0,0);  
  lcd.print("www.Behavior.org");

}  // setup()...


void loop()
{

  navigateMenus();  //in some situations I want to use the button for other purpose (eg. to change some settings)
                  
} //loop()... 


void menuChanged(MenuChangeEvent changed){
  
  MenuItem newMenuItem=changed.to; //get the destination menu
  
  lcd.setCursor(0,1); //set the start position for lcd printing to the second row
  
  if(newMenuItem.getName()==menu.getRoot()){
      lcd.print("time mode      ");
  }else if(newMenuItem.getName()=="Item1"){
      lcd.print("Item1      ");
      
  }else if(newMenuItem.getName()=="Item1SubItem1"){
      lcd.print("Item1SubItem1");
                   // wait for a second
  }else if(newMenuItem.getName()=="Item1SubItem2"){
      lcd.print("Item1SubItem2   ");
  }else if(newMenuItem.getName()=="Item2"){
      lcd.print("Item2           ");
  }else if(newMenuItem.getName()=="Item2SubItem1"){
      lcd.print("Item2SubItem1   ");
  }else if(newMenuItem.getName()=="Item2SubItem2"){
      lcd.print("Item2SubItem2   ");
  }else if(newMenuItem.getName()=="Item2SubItem3"){
      lcd.print("Item2SubItem3   ");
  }else if(newMenuItem.getName()=="Item3"){
      lcd.print("Item3           ");
  }
}

void menuUsed(MenuUseEvent used){
  lcd.setCursor(0,0);  
  lcd.print("You used        ");
  lcd.setCursor(0,1); 
  lcd.print(used.item.getName());
  delay(3000);  //delay to allow message reading
  lcd.setCursor(0,0);  
  lcd.print("www.coagula.org");
  menu.toRoot();  //back to Main
}

void navigateMenus() {
  MenuItem currentMenu=menu.getCurrent();
  
  switch (adc_key_in){
   case btnDOWN:
      if(!(currentMenu.moveDown())){  //if the current menu has a child and has been pressed enter then menu navigate to item below
        menu.use();
      }else{  //otherwise, if menu has no child and has been pressed enter the current menu is used
        menu.moveDown();
       } 
      break;
    case btnUP:
      menu.toRoot();  //back to main
      break;
    case btnRIGHT:
      menu.moveRight();
      break;      
    case btnLEFT:
      menu.moveLeft();
      break;      
  }
  
}

