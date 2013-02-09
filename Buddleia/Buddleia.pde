//MouseNav3D nav;

//Bud bud;

byte rows = 10;
byte cols = 6;
Bud[][] Buddleia = new Bud[rows][cols];

//byte gridPos = new PVector(0,0);
//PVector gridDim = new PVector(6,10);


void setup() {
  size(900,800,P3D);
  //nav=new MouseNav3D(this);
  //nav.trans.set(width/2,height/2,0);

  for(byte x=0; x < rows; x++) {
    for (byte y=0; y < cols; y++) {
      Buddleia[x][y] = new Bud(new PVector(x, y), new PVector(rows, cols));
    }
  }
}

void draw() {
  lights();
  background(255);
  rotateX(map(mouseY, 0, height, -PI/2, PI/2));
  rotateY(map(mouseX, 0, width, -PI/2, PI/2));
  
  for(byte x=0; x < rows; x++) {
    for (byte y=0; y < cols; y++) {
      Buddleia[x][y].draw();
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
