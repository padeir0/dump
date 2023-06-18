const width = 400;
const height = 400;
const middleX = width/2;
const middleY = height/2;

const PI = 3.14159265358979323846264338327950288;
const Degree = PI/180;

const origin = {"x":0,"y":0,"z":0};
const middleVec = {"x": middleX, "y": middleY, "z": 0};
const incXvec = {"x": 1, "y": 0, "z":0};
const incYvec = {"x":0,"y":1,"z":0};
const incZvec = {"x":0,"y":0,"z":1};
const baseDis = 500;

let paintings = {
  "nothing": paintNothing,
  "line": paintLine,
  "spiral": paintSpiral,
  
  "plane1": paintPlane1,
  "plane2": paintPlane2,
  "plane3": paintPlane3,
  
  "circle": paintCircle,
  "space": paintSpace,
  "sphere": paintSphere,
};
let chosen = "nothing";

let disOriginPlane = baseDis;
let myPlane;
let myPlane2;
let myPlane3;
let myCoord;
let objs;

function resetStroke() {
  stroke(0,0,0,128);
}

function resetDefaults() {
  strokeWeight(1);
  resetStroke();
  fill(0,0,0,64);
  background(220);
}

function setup() {
  createCanvas(width, height);
  frameRate(15);
  
  let dis = -1.4 * disOriginPlane;
  let p1 = Vec(100, 100, dis);
  let p2 = Vec(-100, 100, dis);
  let p3 = Vec(-100, -100, dis);
  let p4 = Vec(100, -100, dis);
  
  let c = medianOfPoints([p1, p2, p3, p4]); 
  myPlane = new Plane(p1, p2, p3, p4);
  myPlane2 = rotXObj(myPlane, c, PI/2, true);
  myPlane3 = rotYObj(myPlane, c, PI/2, true);
  myCoord = new CoordSys(
    c,
    translatePoint(c, scalar(100, incYvec)),
    translatePoint(c, scalar(100, incXvec)),
    translatePoint(c, scalar(100, incZvec)),
  );
  objs = [
    myCoord,
    myPlane,
    myPlane2,
    myPlane3
  ];
}


function draw() {
  resetDefaults();
  drawObjs();
}

function paintNothing(sys) {
  return;
}

function paintSpiral(sys) {
  let mul = 1;
  let oldPoint = origin;
  for (let angle = 0; angle < 360; angle++) {
    let v = scalar(mul,
      planarLnCombination(
        cos(Degree*angle), sys.e1, 
        sin(Degree*angle), sys.e2
      )
    );
    let newP = translatePoint(sys.origin, v);
    let l = new Line(oldPoint, newP);
    l.draw();
    oldPoint = newP;
    mul++;
  }
}

function paintPlane1(sys) {
  strokeWeight(1);
  for (let i = 0; i < 50; i++) {
    for (let j = 0; j < 50; j++) {
      let v = planarLnCombination(i*5, sys.e1, j*5, sys.e2);
      let p = translatePoint(sys.origin, v);
      let img = project(p);
      point(img.x, img.y);
    }
  }
}

function paintPlane2(sys) {
  strokeWeight(1);
  for (let i = 0; i < 50; i++) {
    for (let j = 0; j < 50; j++) {
      let v = planarLnCombination(i*5, sys.e2, j*5, sys.e3);
      let p = translatePoint(sys.origin, v);
      let img = project(p);
      point(img.x, img.y);
    }
  }
}

function paintPlane3(sys) {
  strokeWeight(1);
  for (let i = 0; i < 50; i++) {
    for (let j = 0; j < 50; j++) {
      let v = planarLnCombination(i*5, sys.e1, j*5, sys.e3);
      let p = translatePoint(sys.origin, v);
      let img = project(p);
      point(img.x, img.y);
    }
  }
}

function paintSpace(sys) {
  strokeWeight(1);
  for (let i = -10; i < 10; i++) {
    for (let j = -10; j < 10; j++) {
      for (let k = -10; k < 10; k++) {
        let v = spatialLnCombination(
          i*5, sys.e1,
          j*5, sys.e2,
          k*5, sys.e3);
        let p = translatePoint(sys.origin, v);
        let img = project(p);
        point(img.x, img.y);
      }
    }
  }
}

function paintCircle(sys) {
  strokeWeight(2);
  for (let i = -50; i < 50; i++) {
    for (let j = -50; j < 50; j++) {
      let v = planarLnCombination(i*1, sys.e2, j*1, sys.e3);
      let p = translatePoint(sys.origin, v);
      let vec = fromPoints(sys.origin, p);
      let distFromCenter = lengthOf(vec);
      let radius = 50;
      let tolerance = 1;
      if (distFromCenter > radius-tolerance &&
          distFromCenter < radius+tolerance) {
        let img = project(p);
        point(img.x, img.y);
      }
    }
  }
}

function paintLine(sys) {
  strokeWeight(1);
  let basevec = sum(sys.e1, sys.e2);
  for (let i = 0; i < 100; i++) {
    let v = scalar(i*2, basevec);
    let p = translatePoint(sys.origin, v);
    let img = project(p);
    point(img.x, img.y);
  }
}

function paintSphere(sys) {
  strokeWeight(1);
  for (let i = -30; i < 30; i++) {
    for (let j = -30; j < 30; j++) {
      for (let k = -30; k < 30; k++) {
        let v = spatialLnCombination(
          i*2, sys.e1,
          j*2, sys.e2,
          k*2, sys.e3);
        let p = translatePoint(sys.origin, v);
        let vec = fromPoints(sys.origin, p);
        let distFromCenter = lengthOf(vec);
        let radius = 50;
        let tolerance = 0.5;
        if (distFromCenter > radius-tolerance &&
            distFromCenter < radius+tolerance) {
          let img = project(p);
          point(img.x, img.y);
        }
      }
    }
  }
}

function drawObjs() { 
  let xRot = 7.5 *Degree * document.getElementById("xRotSlider").value;
  let yRot = 7.5 * Degree * document.getElementById("yRotSlider").value;
  let zRot = 7.5 * Degree * document.getElementById("zRotSlider").value;
  setZoom();
  for (let i = 0; i < objs.length; i++) {
    let obj = objs[i].make(a => a);
    if (xRot != 0) {
      rotXObj(obj, centerObj(obj), round(xRot, 2));
    }
    if (yRot != 0) {
      rotYObj(obj, centerObj(obj), round(yRot, 2));
    }
    if (zRot != 0) {
      rotZObj(obj, centerObj(obj), round(zRot, 2));
    }
    obj.draw();
    if (obj instanceof CoordSys) {
      let sys = obj.sys();
      paintings[chosen](sys);
    }
  }
}

class CoordSys {
  constructor(origin, e1, e2, e3) {
    this.origin = origin;
    this.e1 = e1;
    this.e2 = e2;
    this.e3 = e3;
  }
  
  draw() {
    let points = projectPoints(
      [this.origin,this.e1,this.e2,this.e3]
    );
    strokeWeight(5);  
    point(points[0].x, points[0].y);
    stroke(255, 0, 0, 128);
    line(
      points[0].x, points[0].y,
      points[1].x, points[1].y
    );
    stroke(0, 255, 0, 128);
    line(
      points[0].x, points[0].y,
      points[2].x, points[2].y
    );
    stroke(0, 0, 255, 128);
    line(
      points[0].x, points[0].y,
      points[3].x, points[3].y
    );
    resetStroke();
  }
  
  apply(f) {
    this.origin = f(this.origin);
    this.e1 = f(this.e1);
    this.e2 = f(this.e2);
    this.e3 = f(this.e3);
  }
  make(f) {
    return new CoordSys(
      f(this.origin),
      f(this.e1),
      f(this.e2),
      f(this.e3)
    );
  }
  points() {
    return [this.origin];
  }
  sys() {
    return {
      "origin": this.origin,
      "e1": unitVector(fromPoints(this.origin, this.e1)),
      "e2": unitVector(fromPoints(this.origin, this.e2)),
      "e3": unitVector(fromPoints(this.origin, this.e3)),
    }
  }
}

class Line {
  constructor(a, b) {
    this.a = a;
    this.b = b;
  }
  
  draw() {
    let points = projectPoints([this.a, this.b])
    strokeWeight(2);
    line(
      points[0].x, points[0].y,
      points[1].x, points[1].y
    );
  }
  apply(f) {
    this.a = f(this.a);
    this.b = f(this.b);
  }
  make(f) {
    return new Line(
      f(this.a),
      f(this.b)
    );
  }
  points() {
    return [this.a, this.b];
  }
}

class Triangle {
  constructor(a,b,c) {
    this.a = a;
    this.b = b;
    this.c = c;
  }
  
  draw() {
    let points = projectPoints([this.a, this.b, this.c]);
    
    triangle(
      points[0].x, points[0].y,
      points[1].x, points[1].y,
      points[2].x, points[2].y,
    );
  }
  apply(f) {
    this.a = f(this.a);
    this.b = f(this.b);
    this.c = f(this.c);
  }
  make(f) {
    return new Triangle(
      f(this.a),
      f(this.b),
      f(this.c)
    );
  }

  points() {
    return [this.a, this.b, this.c];
  }  
}

class Plane {
  constructor(a,b,c,d) {
    this.a = a;
    this.b = b;
    this.c = c;
    this.d = d;
  }
  
  draw() {
    let points = projectPoints([this.a, this.b, this.c, this.d]);
    strokeWeight(1);
    quad(
      points[0].x, points[0].y,
      points[1].x, points[1].y,
      points[2].x, points[2].y,
      points[3].x, points[3].y,
    );
  }
  apply(f) {
    this.a = f(this.a);
    this.b = f(this.b);
    this.c = f(this.c);
    this.d = f(this.d);
  }
  make(f) {
    return new Plane(
      f(this.a),
      f(this.b),
      f(this.c),
      f(this.d)
    );
  }

  points() {
    return [this.a, this.b, this.c, this.d];
  }
}

function createOrApply(obj, f, create) {
  if (create) {
    return obj.make(f);
  }
  obj.apply(f);
  return null;
}

function translateObj(obj, v, create=false) {
  let f = (a) => translatePoint(a, v);
  return createOrApply(obj, f, create);
}
function rotXObj(obj, p, angle, create=false) {
  let f = (v) => rotX(p, v, angle);
  return createOrApply(obj, f, create);
}
function rotYObj(obj, p, angle, create=false) {
  let f = (v) => rotY(p, v, angle);
  return createOrApply(obj, f, create);
}
function rotZObj(obj, p, angle, create=false) {
  let f = (v) => rotZ(p, v, angle);
  return createOrApply(obj, f, create);
}

function centerObj(obj) {
  return medianOfPoints(obj.points());
}

function medianOfPoints(plist) {
  let p = {"x":0, "y":0, "z":0};
  for (let i = 0; i < plist.length; i++) {
    p.x += plist[i].x;
    p.y += plist[i].y;
    p.z += plist[i].z;
  }
  p.x /= plist.length;
  p.y /= plist.length;
  p.z /= plist.length;
  return p;
}

function projectPoints(pts) {
  let out = [];
  for (let i = 0; i <pts.length; i++) {
    out.push(project(pts[i]));
  }
  return out;
}

function project(p) {
  let d = disOriginPlane;
  let img = {
    "x": (d / p.z) * p.x,
    "y": (d / p.z) * p.y,
    "z": d,
  }
  return translatePoint(img, middleVec);
}

function spatialLnCombination(a, u, b, v, c, w) {
  return sum(sum(scalar(a, u), scalar(b, v)), scalar(c, w))
}

function planarLnCombination(a, u, b, v) {
  return sum(scalar(a, u), scalar(b, v))
}

function scalar(a, v) {
  return {
    "x": a * v.x,
    "y": a * v.y,
    "z": a * v.z,
  };
}

function sum(u, v) {
  return {
    "x": u.x + v.x,
    "y": u.y + v.y,
    "z": u.z + v.z,
  }
}

function fromPoints(a, b) {
  return {
    "x": b.x - a.x,
    "y": b.y - a.y,
    "z": b.z - a.z,
  }
}

function lengthOf(a) {
  return round(Math.sqrt(dotProduct(a, a)), 2);
}

function dotProduct(a, b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

function unitVector(v) {
  return scalar(1/lengthOf(v), v);
}

function translatePoint(p, v) {
  return {
    "x": p.x + v.x,
    "y": p.y + v.y,
    "z": p.z + v.z,
  };
}

// rotates X axis around center P
function rotX(p, v1, angle) {
  let v = translatePoint(v1, scalar(-1, p));
  v = {
    "x": v.x,
    "y": v.y * Math.cos(angle) - v.z * Math.sin(angle),
    "z": v.y * Math.sin(angle) + v.z * Math.cos(angle),
  }
  return translatePoint(v, p);
}

// rotates Y axis around center P
function rotY(p, v1, angle) {
  let v = translatePoint(v1, scalar(-1, p));
  v = {
    "x": v.x*Math.cos(angle) + v.z*Math.sin(angle),
    "y": v.y,
    "z": v.z * Math.cos(angle) - v.x * Math.sin(angle),
  }
  return translatePoint(v, p);
}

// rotates Z axis around center P
function rotZ(p, v1, angle) {
  let v = translatePoint(v1, scalar(-1, p));
  v = {
    "x": v.x * Math.cos(angle) - v.y * Math.sin(angle),
    "y": v.x * Math.sin(angle) + v.y * Math.cos(angle),
    "z": v.z,
  }
  return translatePoint(v, p);
}

function Vec(a, b, c) {
  return {
    "x": a,
    "y": b,
    "z": c,
  }
}

function resetSliders() {
  document.getElementById("xRotSlider").value = 0;
  document.getElementById("yRotSlider").value = 0;
  document.getElementById("zRotSlider").value = 0;
}

function setZoom() {
  let zoom = Number(document.getElementById("zoomSlider").value);
  if (zoom) {
    disOriginPlane = baseDis + zoom;
  }
}

function setPainting(i) {
  chosen = i;
}

let showPlanes = true;

function togglePlanes() {
  if (showPlanes) {
    objs = [myCoord]
    showPlanes = false;
    return;
  }
  objs = [
    myCoord,
    myPlane,
    myPlane2,
    myPlane3,
  ];
  showPlanes = true;
}