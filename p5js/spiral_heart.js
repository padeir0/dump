const width = 400;
const height = 400;
const middleX = width/2;
const middleY = height/2;

const PI = 3.14159265358979323846264;
const Degree = PI/180;

const middle = {'x': middleX, 'y': middleY};
const middleRight = {'x': width, 'y': middleY};
const middleTop = {'x': middleX, 'y': 0};

let iVec = rot(unitVector(fromPoints(middle, middleRight)), PI/2);
let jVec = rot(unitVector(fromPoints(middle, middleTop)), -PI/2);

function setup() {
  createCanvas(width, height);
  frameRate(30);
}

function draw() {
  stroke(0);
  strokeWeight(2);
  background(220);
  
  multiple(18);
  fill(0,0,0,0);
  
  iVec = rot(iVec, Degree);
  //jVec = rot(jVec, Degree);
}

function multiple(quant) {
  for (let i = 1; i < quant; i++) {
    let clr = [255,0,0];
    spiral(Degree*(i*0.1), clr);
    spiral(Degree*-(i*0.1), clr);
  }
}

function spiral(unit, clr) {
  let mul = 1;
  let oldPoint = middle;
  stroke(clr[0], clr[1], clr[2]);
  for (let angle = 0; angle < 120; angle++) {
    let v = scalar(mul, lnCombination(cos(unit*angle), iVec, sin(unit*angle), jVec));
    let newP = translatePoint(middle, v);
    line(oldPoint.x, oldPoint.y, newP.x, newP.y);
    oldPoint = newP;
    mul++;
  }
}

function lnCombination(a, u, b, v) {
  return sum(scalar(a, u), scalar(b, v))
}
  
function scalar(a, v) {
  return {
    "x": a * v.x,
    "y": a * v.y
  };
}

function sum(u, v) {
  return {
    "x": u.x + v.x,
    "y": u.y + v.y
  }
}

function fromPoints(a, b) {
  return {
    "x": b.x - a.x,
    "y": b.y - a.y,
  }
}

function lengthOf(a) {
  return Math.sqrt(dotProduct(a, a));
}

function dotProduct(a, b) {
  return a.x * b.x + a.y * b.y;
}

function unitVector(v) {
  return scalar(1/lengthOf(v), v);
}

function translatePoint(p, v) {
  return {
    "x": p.x + v.x,
    "y": p.y + v.y,
  };
}

function rot(v, angle) {
  return {
    "x": v.x*Math.cos(angle) - v.y*Math.sin(angle),
    "y": v.x*Math.sin(angle) + v.y*Math.cos(angle),
  }
}