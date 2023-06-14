const height = 400;
const width = 400;

const middleX = width/2;
const middleY = height/2;
const middle = {"x": middleX, "y": middleY};

function setup() {
  createCanvas(width, height);
  unit = PI/180;
  angle = PI;
}

let angle = 0;
let unit = 0;
let lineX = 40;
let x = middleX+140; 
let y = middleY;
let d = lineX-middleX;
let radius = 50;
let colors = [[255, 0, 0], [0, 255, 0], [0, 0, 255]];

function draw() {
  background(220);
  stroke(0);
  fill(0);
  
  circle(middleX, middleY, 5);
  line(lineX, 0, lineX, height);
  
  let points = rotTriangle(x, y, angle, radius);
  
  for (let i = 0; i < points.length; i++) {
    let p = points[i];
    let projected = projectPoint(middle, d, p);
    let clr = colors[i];
    stroke(clr[0], clr[1], clr[2]);
    line(projected.x, projected.y, p.x, p.y);
    circle(projected.x, projected.y, 5);
    circle(p.x, p.y, 5);
  }
  lineX = round(abs(cos(angle) * 150), 2)
  d = abs(lineX - middleX);
  angle = round(angle+unit, 4);
}

function rotTriangle(x, y, angle, radius) {
  let thirdOfCircle = round(2*PI/3, 3);
  
  let x0 = x + cos(angle) * radius;
  let x1 = x + cos(angle+thirdOfCircle) * radius;
  let x2 = x + cos(angle+2*thirdOfCircle) * radius;
  
  let y0 = y + sin(angle) * radius;
  let y1 = y + sin(angle+thirdOfCircle) * radius;
  let y2 = y + sin(angle+2*thirdOfCircle) * radius;
  
  line(x0, y0, x1, y1);
  line(x0, y0, x2, y2);
  line(x1, y1, x2, y2);
  return [
    {"x": x0, "y": y0},
    {"x": x1, "y": y1},
    {"x": x2, "y": y2},
  ];
}

// translates point p to new center c
function translatePoint(p, c) {
  return {
    "x": p.x - c.x,
    "y": p.y - c.y,
  };
}

function projectPoint(pinhole, d, p0) {
  let newP0 = translatePoint(p0, pinhole);
  let yi = pinhole.y - ((d*newP0.y)/newP0.x);
  return {"x": pinhole.x-d, "y": yi};
}
