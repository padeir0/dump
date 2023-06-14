const width = 600;
const height = 400;
const graphBottom = height-30;

function setup() {
  createCanvas(width, height);
}

const groupSize = 100;
const numPrimes = 10000;

let once = false;
function draw() {
  if (once) {
    return;
  }
  background(220);
  let primes = findPrimes(numPrimes);
  let bars = distribution(primes, groupSize);
  let graph = new barGraph(bars, groupSize);
  graph.draw();
  once = true;
}

class barGraph {
  constructor(bars, groupSize) {
    this.bars = bars;
    this.groupSize = groupSize;
  }
  draw() {
    let offset = width / this.bars.length;
    fill(127, 127, 127);
    for (let i = 0; i < this.bars.length; i++) {
      let size = this.bars[i];
      let x = i * offset;
      rect(x, graphBottom-size, offset, size);
      
      let textX = x + (offset/4);
      let init = i * this.groupSize;
      let end = (i+1) * this.groupSize;
      let range = init + ":" + end;
      text(range, textX, height-10);
    }
  }
}

function isPrime(n) {
  for (let i = 2; i < n; i++){
    if (n%i == 0 && n != i) {
      return false;
    }
  }
  return true;
}

function findPrimes(upTo) {
  let out = [];
  for (let i = 0; i<upTo; i++) {
    if (isPrime(i)) {
      out.push(i);
    }
  }
  return out;
}

function distribution(primes, groupSize) {
  let bars = [];
  for (let i = 0; i < primes.length; i++) {
    let prime = primes[i];
    let index = floor(prime/groupSize);
    while (index>=bars.length) {bars.push(0);}
    bars[index]++;
  }
  return bars;
}