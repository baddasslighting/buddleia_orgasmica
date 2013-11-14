//MouseNav3D nav;

//Bud bud;

byte rows = 3;
byte cols = 3;
Bud[][] Buddleia = new Bud[cols][rows];

//byte gridPos = new PVector(0,0);
//PVector gridDim = new PVector(6,10);


void setup() {
  size(800,600,P3D);
  //nav=new MouseNav3D(this);
  //nav.trans.set(width/2,height/2,0);

  for (byte y=0; y < cols; y++) {
    for(byte x=0; x < rows; x++) {
      Buddleia[y][x] = new Bud(new PVector(y, x), new PVector(cols, rows));
    }
  }
}

void draw() {
  lights();
  background(255);
  rotateX(map(mouseY, 0, height, -PI/2, PI/2));
  //rotateY(map(mouseX, 0, width, -PI/2, PI/2));
  
  for (byte y=0; y < cols; y++) {
    for(byte x=0; x < rows; x++) {
      Buddleia[y][x].draw();
    }
  }
  //bud.draw();
}


/**
cylinder taken from http://wiki.processing.org/index.php/Cylinder
@author matt ditton
*/

void cylinder(float w, float h, int sides)
{
  float angle;
  float[] x = new float[sides+1];
  float[] z = new float[sides+1];
 
  //get the x and z position on a circle for all the sides
  for(int i=0; i < x.length; i++){
    angle = TWO_PI / (sides) * i;
    x[i] = sin(angle) * w;
    z[i] = cos(angle) * w;
  }
 
  //draw the top of the cylinder
  beginShape(TRIANGLE_FAN);
 
  vertex(0,   -h/2,    0);
 
  for(int i=0; i < x.length; i++){
    vertex(x[i], -h/2, z[i]);
  }
 
  endShape();
 
  //draw the center of the cylinder
  beginShape(QUAD_STRIP); 
 
  for(int i=0; i < x.length; i++){
    vertex(x[i], -h/2, z[i]);
    vertex(x[i], h/2, z[i]);
  }
 
  endShape();
 
  //draw the bottom of the cylinder
  beginShape(TRIANGLE_FAN); 
 
  vertex(0,   h/2,    0);
 
  for(int i=0; i < x.length; i++){
    vertex(x[i], h/2, z[i]);
  }
 
  endShape();
}
class Bud {
  float xPos;
  float yPos;
  float zPos;

  // circle level
  float stemDegrees;

  // cylinder
  byte cRadius = 3; 
  byte cHeight = 10; 
  byte stemLength = 20;

  Bud(PVector gridPos, PVector gridDim) {
    stemDegrees = 360.0/gridDim.x;
  }

  void draw() {
    noStroke();
    fill(175, 0, 178);
    translate(width/2, height/2);
    ellipse(0, 0, 3, 3);
    //rotateX(PI/2);
    //rotateZ(stemDegrees*180.0/PI);
    //println(stemDegrees*180.0/PI); //wtf
    //translate(0, stemLength+cHeight);
    cylinder(cRadius * 2, cHeight, 10);
    translate(0,0);
  }

}


