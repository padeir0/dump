tetrominoes = { 
    // since there are only 7 shapes and 19 states, hardcoding beats transposing and inverting matrices
    // states of each tetromino can be more easily acessed, eg: tetrominoes.L[i]; i being one of the four states
    I : [[[1, 1, 1, 1]], [[1], [1], [1], [1]]],
    O : [[[1, 1], [1, 1]]],
    T : [[[0, 1, 0], [1, 1, 1]], [[1, 0], [1, 1], [1, 0]], [[1, 1, 1], [0, 1, 0]], [[0, 1], [1, 1], [0, 1]]],
    S : [[[0, 1, 1], [1, 1, 0]], [[1, 0], [1, 1], [0, 1]]],
    Z : [[[1, 1, 0], [0, 1, 1]], [[0, 1], [1, 1], [1, 0]]],
    J : [[[1, 0, 0], [1, 1, 1]], [[1, 1], [1, 0], [1, 0]], [[1, 1, 1], [0, 0, 1]], [[0, 1], [0, 1], [1, 1]]],
    L : [[[0, 0, 1], [1, 1, 1]], [[1, 0], [1, 0], [1, 1]], [[1, 1, 1], [1, 0, 0]], [[1, 1], [0, 1], [0, 1]]],
    TEST : [[[1, 1, 1, 1, 1, 1, 1, 1, 1, 1]], [[1, 1], [1, 1]]]
}

colors = {
    I : [45, 182, 250],
    O : [230, 222, 0],
    T : [150, 72, 145],
    S : [37, 179, 2],
    Z : [217, 46, 46],
    J : [2, 46, 207],
    L : [252, 105, 0],
    TEST : [0, 0, 0]
}

var blockSize = 20;

class Table{
    constructor(){
        this.tableWidth = 10;   // blocks wide
        this.tableHeight = 20;  // blocks high
        this.matrix = [];
        this.xPosition = 130;   // position of table relative to canvas in pixels

        this.canHold = true;
        this.holdTetro;
        this.currTetro;
        this.nextTetrominoes = [];

        this.level = 1;
        this.score = 1;
        this.deathN = 1;        // the game over line

        this.newMatrix();
    }

    nextTetro(){
        let all = ['I', 'O', 'T', 'L', 'S', 'J', 'Z', 'J', 'L', 'I', 'S', 'O', 'Z'];
        let len = all.length - 1;
        if (!this.nextTetrominoes[0]){
            while (this.nextTetrominoes.length < 3){
                let sh = all[round(Math.random() * len)];
                this.nextTetrominoes.push(new Tetromino(this, tetrominoes[sh], colors[sh]));
            }
        }
        this.currTetro = this.nextTetrominoes[0];
        this.nextTetrominoes.shift();

        let sh = all[round(Math.random() * len)];
        this.nextTetrominoes.push(new Tetromino(this, tetrominoes[sh], colors[sh]));

        this.canHold = true;
    }

    hold(){
        // holds a tetromino
        if (this.canHold){
            let backup = this.holdTetro;
            this.currTetro.resetPos();
            this.holdTetro = this.currTetro;
            this.currTetro = backup;
            this.canHold = false;
        }
    }
    
    increaseScore(value){
        this.score += value;
        if(this.score - (100 * (this.level + 1)**2) > 0){
            this.level++;
        }
    }

    checkSettle(){
        // checks if a tetromino is settled by counting fails-to-move-it-down
        if(this.currTetro.settleCount > 2 && !this.currTetro.checkMove("down")){
            this.currTetro.settleCount = 0;
            this.settleTetro();
            this.increaseScore(this.level * 3);
            this.nextTetro();
        }
    }

    settleTetro(){
        let tetro = this.currTetro.shape[this.currTetro.state];
        let pX = this.currTetro.posX;
        let pY = this.currTetro.posY;
        for (let i = 0; i < tetro.length; i++){
            for (let j = 0; j < tetro[i].length; j++){
                if (tetro[i][j] == 1){
                    let coloring = this.currTetro.coloring;
                    this.matrix[pY + i][pX + j] = new Block(pX + j, pY + i, coloring, this);
                }
            }
        }
    }

    drawHUD(){
        fill(2, 160, 184);
        textSize(16);

        let txtX1 = this.xPosition + (-4 * blockSize);
        let txtY1 = 5;
        let txtX2 = this.xPosition;
        let txtY2 = blockSize + 5;
        text(this.score, txtX1, txtY1, txtY2, txtX2);
    
        let tableH = blockSize * this.tableHeight;
        let tableW = blockSize * (this.tableWidth + 1);
        let deadLine = (1 + this.deathN) * blockSize;
        rect(this.xPosition, 0, blockSize, tableH);
        rect(this.xPosition + tableW, 0, blockSize, tableH);
        rect(this.xPosition, tableH, tableW + blockSize, blockSize);
        line(this.xPosition + blockSize, deadLine, this.xPosition + tableW, deadLine);

        if (this.holdTetro){
            this.holdTetro.drawOnHUD(-4, 1);
        }
        if (this.nextTetrominoes[0]){
            for (let i = 0; i < this.nextTetrominoes.length; i++){
                this.nextTetrominoes[i].drawOnHUD(this.tableWidth + 3, 3 * i);
            }
        }
    }

    checkRows(){
        // check if rows are completely filled with blocks and draws them as it goes by
        let blowedRows = [];        // stores the rows that were removed
        for (let i = 0; i < this.matrix.length - 1; i++){
            let isFull = true;
            for (let j = 1; j < this.matrix[i].length - 1; j++){
                if (typeof this.matrix[i][j] == "object"){
                    this.matrix[i][j].drawB();              // drawing is here
                    if (i < this.deathN){
                        this.gameOver();
                        break;
                    }
                }else if (this.matrix[i][j] == 0){
                    isFull = false;
                }
            }
            if (isFull){
                blowedRows.push(i)
                this.blowRowUp(i);
            }
        }
        for (let i = 0; i < blowedRows.length; i++){
            this.moveRowsDown(blowedRows[i]);
        }
        this.increaseScore(this.level * 15 * blowedRows.length ** 2);    // increments score
    }

    blowRowUp(i){
        // resets the row to zero
        for (let j = 1; j < this.matrix[i].length - 1; j++){
            this.matrix[i][j] = 0;
        }
    }

    moveRowsDown(row){
        for (let j = row; j > 2; j--){
            let backup = this.matrix[j];
            this.matrix[j] = this.matrix[j - 1];
            this.matrix[j-1] = backup;
            for (let item = 1; item < this.matrix[j].length - 1; item++){
                if (typeof this.matrix[j][item] == "object"){
                    this.matrix[j][item].pY += 1;
                }
            }
        }
    }

    gameOver(){
        console.log("Game Over");
        console.log(this.score);
        this.score = 1;
        this.level = 1;
        this.holdTetro = '';
        this.nextTetros = [];
        this.newMatrix();
    }

    newMatrix(){
        this.matrix = [];
        for (let i = 0; i <= this.tableHeight; i++){
            this.matrix.push([1]);
            for (let j = 0; j < this.tableWidth; j++){
                if(i == this.tableHeight) {
                    this.matrix[i].push(1);
                }else{
                    this.matrix[i].push(0);
                }
            }
            this.matrix[i].push(1);
        };
    }
}

class Block{
    constructor(pX, pY, coloring, table){
        this.rgbRed = coloring[0];
        this.rgbGreen = coloring[1];
        this.rgbBlue = coloring[2];
        this.table = table;

        this.pX = pX;
        this.pY = pY;
    }
    drawB(){
        let canvX = this.table.xPosition + (this.pX * blockSize);
        let canvY = this.pY * blockSize;
        fill(this.rgbRed, this.rgbGreen, this.rgbBlue);
        square(canvX, canvY, blockSize);
    }
}

class Tetromino{
    constructor(table, shape, clr){
        this.shape = shape;
        this.state = 0;
        this.posY = 0;  // position of the first item in the matrix
        this.posX = 4;
        this.canvasY = this.posY * blockSize;
        this.canvasX = this.posX * blockSize;
        this.table = table;

        this.coloring = clr;
        this.rgbRed = clr[0];
        this.rgbGreen = clr[1];
        this.rgbBlue = clr[2];

        this.settleCount = 0;
    }

    move(dir){
        if (this.checkMove(dir)){
            if(dir == "down"){
                this.posY++;
                this.settleCount = 0;
            }
            else if (dir == "left"){this.posX--;}
            else if (dir == "right"){this.posX++;}
            else if (dir == "up"){this.posY--;}
            this.drawS();
        }else if (dir == "down"){
            this.settleCount++;
        }
    }

    resetPos(){
        this.posY = 0;
        this.posX = 4;
        this.state = 0;
    }

    rotateT(){
        let i = 1;
        while (i < this.shape.length){
            if (this.checkRotation(this.state + i)){
                this.state += i;
                if (this.state >= this.shape.length){
                    this.state -= this.shape.length;
                }
                break;
            }
            i++;
        }
    }

    checkMove(dir){
        let x = 0;
        let y = 0;
        let form = this.shape[this.state];
        if(dir == "down"){y = 1;}
        else if (dir == "left"){x = -1;}
        else if (dir == "right"){x = 1;}
        else if (dir == "up"){y = -1;}
        for (let i = 0; i < form.length; i++){
            for (let j = 0; j < form[i].length; j++){
                if (this.table.matrix[i + this.posY + y][j + this.posX + x] != 0 && form[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    checkRotation(state){
        if (state >= this.shape.length){
            state -= this.shape.length;
        }
        for (let i = 0; i < this.shape[state].length; i++){
            for (let j = 0; j < this.shape[state][i].length; j++){
                if (this.table.matrix[i + this.posY][j + this.posX] != 0){
                    return false;
                }
            }
        }
        return true;
    }

    drawS(){
        let tetro = this.shape[this.state];
        for (let i = 0; i < tetro.length; i++){
            for (let j = 0; j < tetro[i].length; j++){
                if(tetro[i][j] != 0){
                    let x = (this.posX + j) * blockSize;
                    let y =  (this.posY + i) * blockSize;
                    let tableH = (this.table.tableHeight) * blockSize;
                    fill(this.rgbRed, this.rgbGreen, this.rgbBlue);
                    square(this.table.xPosition + x, y, blockSize);
                    square(this.table.xPosition + x, tableH, blockSize);
                }
            }
        }
    }

    drawOnHUD(pX, pY){
        let tetro = this.shape[this.state];
        for (let i = 0; i < tetro.length; i++){
            for (let j = 0; j < tetro[i].length; j++){
                if(tetro[i][j] != 0){
                    let x = (pX + j) * blockSize;
                    let y =  (pY + i) * blockSize;
                    fill(this.rgbRed, this.rgbGreen, this.rgbBlue);
                    square(this.table.xPosition + x, y, blockSize);}
            }
        }
    }

}

function keyPressed(){
    if (keyCode === UP_ARROW){
        table.currTetro.rotateT();
    }else if(keyCode === SHIFT){
        table.hold();
    }
}

// function mousePressed(){
//     console.log(table.matrix);
// }

function setup() {
    createCanvas(500, 420);
    table = new Table();
    // noLoop();
}

loops = 0;

spd = 5;

function draw() {
    background(80);
    if (!table.currTetro){
        table.nextTetro();
    }
    if(loops > 50 / table.level){
        table.currTetro.move('down');
        loops = 0;
    }

    if (keyIsDown(LEFT_ARROW) && loops % spd == 0){
        table.currTetro.move('left');
    }else if (keyIsDown(RIGHT_ARROW) && loops % spd == 0){
        table.currTetro.move('right');
    }else if (keyIsDown(DOWN_ARROW)){
        table.currTetro.move('down');
    }

    table.checkSettle();
    table.checkRows();
    table.drawHUD();
    table.currTetro.drawS();
    loops++;
}