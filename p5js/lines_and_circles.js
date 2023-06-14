function linelineIntersection(line1, line2) { 
  let ln1 = line1.equation();
  let ln2 = line2.equation();

  let x = (ln2.b * ln1.c - ln2.c * ln1.b) / 
          (ln2.a * ln1.b - ln2.b * ln1.a);
  
  let y = (-ln1.c - ln1.a * x) / ln1.b;
  
  if (line1.inbounds(x, y) && line2.inbounds(x, y)) {
    return [{"x":x, "y":y}];
  }
  return [];
}

function squ(a) {
  return a * a;
}

function linecircleIntersection(line, circle) {
  let xoffset = -circle.ox;
  let yoffset = -circle.oy;
  let circ = circle.translation(xoffset, yoffset).equation();
  let ln = line.translation(xoffset, yoffset).equation();
  let a, b, c;
  if (ln.b == 0) {
    a = squ(ln.a);
    b = 0;
    c = squ(ln.c) - squ(circ.r) * squ(ln.a);
    
    let roots = bhaskara(a, b, c);
    if (roots) {
      let y1 = roots[0];
      let y2 = roots[1];
      let x1 = sqrt(squ(circ.r) - squ(y1));
      let x2 = sqrt(squ(circ.r) - squ(y2));
      
      x1 -= xoffset;
      x2 -= xoffset;
      y1 -= yoffset;
      y2 -= yoffset;
      
      let out = [];
      console.log({"x": x1, "y": y1}, {"x": x2, "y": y2});
      if (line.inbounds(x1, y1)) {
        out.push({"x": x1, "y": y1});
      }
      if (line.inbounds(x2, y2)) {
        out.push({"x": x2, "y": y2});
      }

      return out;
    }
  } else {
    a = squ(ln.b) + squ(ln.a);
    b = 2 * ln.a * ln.c
    c = squ(ln.c) - squ(ln.b) * squ(circ.r);

    let roots = bhaskara(a, b, c);
    if (roots) {
      let x1 = roots[0];
      let x2 = roots[1];
      let y1 = (-ln.c - ln.a * x1) / ln.b;
      let y2 = (-ln.c - ln.a * x2) / ln.b;
      
      x1 -= xoffset;
      x2 -= xoffset;
      y1 -= yoffset;
      y2 -= yoffset;

      let out = [];

      if (line.inbounds(x1, y1)) {
        out.push({"x": x1, "y": y1});
      }
      if (line.inbounds(x2, y2)) {
        out.push({"x": x2, "y": y2});
      }

      return out;
    }
  }
  
  return [];
}

// big thankts to: http://paulbourke.net/geometry/circlesphere/circle_intersection.py
function circlecircleIntersection(circle1, circle2) {
  let X1 = circle1.ox;
  let Y1 = circle1.oy;
  let X2 = circle2.ox;
  let Y2 = circle2.oy;
  let R1 = circle1.radius
  let R2 = circle2.radius
  
  let Dx = X2-X1;
  let Dy = Y2-Y1;
  
  let D = sqrt(squ(Dx) + squ(Dy));
  
  if ((D > R1 + R2)) {
    //console.log("Too far to intersect");
    return [];
  } 
  if (D < abs(R2 - R1)) {
    //console.log("One is contained within the other");
    return [];    
  } 
  if (D == 0 && R1 == R2) { 
    //console.log("The circles are equal and coincident");
    return [];
  }
  
  
  if (D == R1 + R2 || D == R1 - R2) {
    //console.log("intersect at a single point");
  } else {
    //console.log("intersect at two points");
  }
  
  let chorddistance = (squ(R1) - squ(R2) + squ(D))/(2 * D);
  let halfchordlength = sqrt(squ(R1) - squ(chorddistance));
  let chordmidpointx = X1 + (chorddistance*Dx)/D;
  let chordmidpointy = Y1 + (chorddistance*Dy)/D;
  
  let I1 = {
    "x": (chordmidpointx + (halfchordlength*Dy)/D),
    "y": (chordmidpointy - (halfchordlength*Dx)/D),
  };
  let I2 = {
    "x": (chordmidpointx - (halfchordlength*Dy)/D),
    "y": (chordmidpointy + (halfchordlength*Dx)/D)
  };
  
  return [I1, I2];
}

function bhaskara(a, b, c) {
  let delta = squ(b) - (4 * a * c)
  if (delta < 0) {
    return null;
  }
  let sqrtdelta = sqrt(delta);
  let x1 = (-b + sqrtdelta) / (2 * a);
  let x2 = (-b - sqrtdelta) / (2 * a);
  return [x1, x2];
}

class eCircle {
  constructor(ox, oy, radius) {
    this.ox = ox;
    this.oy = oy;
    this.radius = radius;
  }
  draw() {
    noFill();
    circle(this.ox, this.oy, this.radius*2);
  }
  intersection(other) {
    if (other instanceof eLine) {
      return linecircleIntersection(other, this);
    } else if (other instanceof eCircle) {
      return circlecircleIntersection(this, other);
    }
    throw new Error("unreachable");
  }
  equation() {
    return {"h": this.ox, "k": this.oy, "r": this.radius};
  }
  translation(x, y) {
    return new eCircle(this.ox + x, this.oy + y, this.radius);
  }
}

class eLine {
  constructor(x0, y0, x1, y1) {
    this.x0 = x0;
    this.y0 = y0;
    this.x1 = x1;
    this.y1 = y1;
  }
  draw() {
    noFill();
    line(this.x0, this.y0, this.x1, this.y1);
  }
  intersection(other) {
    if (other instanceof eLine) {
      return linelineIntersection(this, other);
    } else if (other instanceof eCircle) {
      return linecircleIntersection(this, other);
    }
    throw new Error("unreachable");
  }
  inbounds(x, y) {
    let xlowerbound = min(this.x0, this.x1);
    let xupperbound = max(this.x0, this.x1);
    if (x < xlowerbound || x > xupperbound) {
      return false;
    }
    
    let ylowerbound = min(this.y0, this.y1);
    let yupperbound = max(this.y0, this.y1);
    if (y < ylowerbound || y > yupperbound) {
      return false;
    }
    
    return true;
  }
  equation() {
    let a = this.y1 - this.y0;
    let b = this.x0 - this.x1;
    let c = this.x1 * this.y0 - this.x0 * this.y1;
    return {"a":a, "b": b, "c": c};
  }
  translation(x, y) {
    return new eLine(this.x0 + x, this.y0 + y, this.x1 + x, this.y1 + y);
  }
}

let elements = [];

function setelements() {
  elements = [
    new eCircle(random(100, 400), random(100, 400), random(100)),
    new eLine(random(400), random(400), random(400), random(400)),
    
    new eCircle(random(100, 400), random(100, 400), random(100)),
    new eLine(random(400), random(400), random(400), random(400)),
    
    new eCircle(random(100, 400), random(100, 400), random(100)),
    new eLine(random(400), random(400), random(400), random(400)),
    
    new eCircle(random(100, 400), random(100, 400), random(100)),
    new eLine(random(400), random(400), random(400), random(400)),
    
    new eCircle(random(100, 400), random(100, 400), random(100)),
    new eLine(random(400), random(400), random(400), random(400)),
  ];
}

function setup() {
  createCanvas(800, 600);
  strokeWeight(2);
  frameRate(1);
  setelements();
}

function draw() {
  background(220);
  elements.forEach(a => {
    a.draw(); 
    elements.forEach(b => {
      if (a != b) {
        let points = a.intersection(b);
        strokeWeight(10);
        points.forEach(p => {      
          point(p.x, p.y);
        });
        strokeWeight(2);
      }
    });
  });
  setelements();
}