let canvas;
let ctx;

let canvas_width;
let canvas_height;

let rect_height = [];

window.onload = init;

let z;
let change = false;

function init() {
    canvas = document.getElementById("display");
    ctx = canvas.getContext("2d");

    canvas_width = canvas.getBoundingClientRect().width;
    canvas_height = canvas.getBoundingClientRect().height;

    generate_heights();

    render_graph();

    z = 0;

    window.requestAnimationFrame(mainLoop);

}

function mainLoop(timeStamp) {
    if (z != 600) {
        if (rect_height[z] > rect_height[z + 1]) {
            let c = rect_height[z];
            rect_height[z] = rect_height[z + 1];
            rect_height[z + 1] = c;

            change = true;
        }

        z++;
    } else {
        if (change) {
            z = 0;
        } else {
            z = 600;
        }
    }

    render_graph();

    window.requestAnimationFrame(mainLoop);
}

function generate_heights() {
    for (let i = 0; i < canvas_width; i++) {

        let new_num = Math.floor(Math.random() * canvas_height) + 1;

        while (rect_height.includes(new_num)) {
            new_num = Math.floor(Math.random() * canvas_height) + 1;
        }

        rect_height[i] = new_num;

    }

    console.log(rect_height);
}

function render_graph() {

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    for (let i = 0; i < rect_height.length; i++) {
        ctx.beginPath();
        ctx.rect(i, canvas_height - rect_height[i], 1, rect_height[i]);
        ctx.fillStyle = '#00000';
        ctx.fill();
        ctx.closePath();
    }
}

function sort() {
    do {
        var changed = false;
        for (let i = 0; i < rect_height.length; i++) {
            //render_graph();
            if (rect_height[i] > rect_height[i + 1]) {
                let c = rect_height[i];
                rect_height[i] = rect_height[i + 1];
                rect_height[i + 1] = c;

                changed = true;
            }
        }
    } while (changed);

    console.log(rect_height);
}