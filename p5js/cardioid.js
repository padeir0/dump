const width = 400;
const height = 400;
const middle = {x: width/2, y: height/2};
const diameter = width - 10;
const radius = diameter/2;


function setup() {
  createCanvas(width, height);
  frameRate(15);
  unit = PI/360;
  I = unit;
}

let divisions = 360;
let factor = 2;
let unit = 0;
let I = 0;

function draw() {
  background(220);
  fill(0,0,0,0);
  strokeWeight(1);
  circle(middle.x, middle.y, diameter);
  
  let lines = cremonas(divisions, factor);
  for (let i = 0; i < lines.length; i++) {
    let l = lines[i];
    line(l.begin.x, l.begin.y, l.end.x, l.end.y);
  }
  factor = round((cos(I)+1)*20, 2);
  I += unit;
  I = I%(PI*2)
}

function cremonas(divisions, factor) {
  let a = subdivide(divisions);
  let out = [];
  
  for (let i = 0; i < a.length; i++) {
    let begin = a[i];
    let end = wrapIndex(a, i * factor);
    
    out.push({begin: begin, end: end});
  }
  return out;
}

function wrapIndex(a, i) {
  let index = floor(i);
  return a[index % a.length];
}

function subdivide(divisions) {
  let angle = (2 * PI) / divisions;

  let out = [];
  for (let i = 0; i < divisions; i++) {
    let p = getPoint(angle*i);
    out.push(p);
  }
  return out;
}

function getPoint(angle) {
  let x = round(cos(angle)*radius + middle.x, 2);
  let y = round(sin(angle)*radius + middle.y, 2);
  return {x: x, y: y};
}