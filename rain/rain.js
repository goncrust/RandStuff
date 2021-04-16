let canvas;
let ctx;

let rain;

let colors = ["#c4dbff", "#a6c9ff", "#79a7ed", "#577199", "#a8bfe3"];

window.onload = init;

function init() {
    canvas = document.getElementById("display");
    ctx = canvas.getContext("2d");

    rain = new Array(500);
    createRain();

    console.log(rain);

    window.requestAnimationFrame(mainloop);
}

function createRain() {

    for (let i = 0; i < 1500; i++) {
        let x = Math.floor(Math.random() * (1920 - 0 + 1)) + 0;
        let y = Math.floor(Math.random() * (1080 - 0 + 1)) + 0;
        let w = Math.floor(Math.random() * (6 - 1 + 1)) + 1;
        let l = Math.floor(Math.random() * (10 - 1 + 1)) + 1;

        let c = Math.floor(Math.random() * (5 - 0 + 1)) + 0;
        //let c = "#" + (Math.floor(Math.random() * (Math.pow(2, 24) - 0 + 1)) + 0).toString(16);

        rain[i] = { x, y, w, l, c }
    }

}

function mainloop() {

    //ctx.clearRect(0, 0, 1920, 1080);
    ctx.beginPath();
    ctx.fillStyle = "#535f73";
    ctx.rect(0, 0, 1920, 1080);
    ctx.fill();
    ctx.closePath();

    for (let i = 0; i < 1500; i++) {
        ctx.beginPath();
        ctx.fillStyle = colors[rain[i]['c']];
        //ctx.fillStyle = rain[i]['c'];
        ctx.rect(rain[i]['x'], rain[i]['y'], rain[i]['w'], rain[i]['l']);
        ctx.fill();
        ctx.closePath();
    }

    for (let i = 0; i < 1500; i++) {
        let vy = Math.floor(Math.random() * (6 - 5 + 1)) + 5;
        // let vx = Math.floor(Math.random() * (2 - (-0.01) + 1)) - 0.01;
        // rain[i]['x'] += vx;
        rain[i]['y'] += vy;

        if (rain[i]['y'] > 1080) {
            // let y = Math.floor(Math.random() * (1080 - 0 + 1)) + 0;
            // rain[i]['y'] = y;

            let x = Math.floor(Math.random() * (1920 - 0 + 1)) + 0;
            rain[i]['x'] = x;
            rain[i]['y'] = 0;
        }
    }



    window.requestAnimationFrame(mainloop);
}