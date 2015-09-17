var xPos;
var yPos;
var mouseOverTriangle;

function setup(){
  createCanvas(2048,2048);
  xPos = 512;
  yPos = 512;
}

function draw(){
  background(255);
  fill(random(0,255),random(0,255),random(0,255),80);
  stroke(255,200);
  strokeWeight(30);
  frameRate(600);
  triangle(xPos-50, yPos-50, mouseX-50, mouseY-50, mouseX -xPos-50, mouseY -yPos-50);
  triangle(xPos-50, yPos-50, mouseY-50, mouseX-50, mouseX -xPos-50, mouseY -yPos-50);
  triangle(xPos-50, yPos-50, mouseY-50, mouseX-50, mouseX -50 , mouseY -50);
  triangle(mouseX-50, mouseY-50, mouseY-50, mouseX-50, mouseX -xPos-50, mouseY - yPos-50);
  println("X postition of mouse " + mouseX);
  println("Y postition of mouse " + mouseY);
  if (mouseX >= 512){
    mouseOverTriangle = true;
  }else if(mouseX <= 512){
    mouseOverTriangle = false;
  }
  
  if (mouseOverTriangle == true){
    xPos = xPos + random(0,3);
  }else {
    xPos = xPos - random(0,3);
  }
  println(xPos);

}

