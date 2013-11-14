class Bud {

  // circle level
  float levelRotation = 18.0;
  float stemDegrees;
  float levelHeight;

  // cylinder
  byte cRadius = 6; 
  byte cHeight = 40; 
  float stemLength = 80.0;

  Bud(PVector gridPos, PVector gridDim) {
    stemDegrees = 360.0/gridDim.y;
    levelHeight = gridPos.x * 60;
    levelRotation = 18.0 * gridPos.x; //figure out how to integrate this
    stemLength = stemLength + (gridPos.x *7);
  }

  void draw(int r, int g, int b) {
    noStroke();
    
    translate(width/2, height/4, 0);
    rotateZ(radians(90));
    rotateX(radians(stemDegrees));
    rotateX(radians(levelRotation));
    translate(0,stemLength, 0);
    translate(levelHeight,0, 0);
    
    fill(100);
    translate(0, -stemLength, 0);
    box(4, stemLength*2, 4);
    box(60, 20, 20);
    
    
    fill(r, g, b);
    translate(0, stemLength, 0);
    cylinder(cRadius * 2, cHeight, 10);
    
    translate(-levelHeight,0, 0);
    translate(0,-stemLength,0);
    rotateX(radians(-levelRotation));
    rotateZ(radians(-90));
    translate(-width/2, -height/4);
  }

}

