class Bud {

  // circle level
  float levelRotation = 18.0;
  float stemDegrees;
  float levelHeight;

  // cylinder
  byte cRadius = 6; 
  byte cHeight = 40; 
  byte stemLength = 120;

  Bud(PVector gridPos, PVector gridDim) {
    stemDegrees = 360.0/gridDim.y;
    levelHeight = gridPos.x * 60;
    levelRotation = 18.0 * gridPos.x;
  }

  void draw() {
    noStroke();
    fill(175, 0, 178);
    translate(width/2, height/2, 0);
    rotateZ(radians(90));
    rotateX(radians(stemDegrees + levelRotation));
    translate(0,stemLength, 0);
    translate(levelHeight,0, 0);
    cylinder(cRadius * 2, cHeight, 10);
    translate(-levelHeight,0, 0);
    translate(0,-stemLength,0);
    rotateZ(radians(-90));
    translate(-width/2, -height/2);
  }

}

