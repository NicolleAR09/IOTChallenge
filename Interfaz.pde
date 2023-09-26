import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val= "";
String[]lines = new String[0];

void setup() 
{
  size(1080, 750);
  myPort = new Serial(this, "COM4", 9600);
  myPort.bufferUntil(',');
}

void draw()
{
 background(255); 
 fill(0);// fill white color to text
 rect(-85, 0, width, 5); // Top
 rect(width-90, 0, 5, 200); // Right(Linea derecha)
 rect(-85, 200, width, 5); // Bottom
 rect(-85, 50, width,5); // Bottom
  rect(-85, 105, width,5); // Bottom
 rect(0, 0, 5, 200); //Left
 rect(130, 50, 5, 150); // Left
  rect(400, 50, 5, 150); // Left
  rect(680, 50, 5, 150); // Left
  
 PFont f = createFont("Open Sans", 70);
 textFont(f);
 textSize(28);
 text("CROPSENSE", 370, 40);
 text("  #Nodo        Temperatura(°C)       Humedad Amb(%)       Humedad tierra(%)",10,100);
 fill(0);
 textSize(32);
 text(val, -10,140); 
}


void serialEvent(Serial myPort)// whenever serial event happens it runs
{
  val = myPort.readStringUntil(','); //gathering data from port in a variable val
  lines = append(lines, val);
}

void keyPressed(){
  if(key == 'h'){
    //save table to disk as .TSV instead of .CSV
    saveStrings("historicos.txt", lines);
  }
}

//save on exit
void exit(){
  saveStrings("historicos.txt", lines);
  super.exit();
}
