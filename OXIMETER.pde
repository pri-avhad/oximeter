import processing.serial.*;

Serial s;
int n = 10;
void setup(){
  size(1000,800);
  s = new Serial(this, "COM3", 9600);
}

void draw(){
  while(s.available()>0){
    String str = s.readStringUntil(n);
    if(str != null){
      background(0);
      textSize(70);
      text(str.substring(0,18), 200, 320);
      text(str.substring(20), 200, 390);
    }
  }
}
