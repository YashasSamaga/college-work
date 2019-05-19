var player;
var police;
var sky;

var level_grayscale = false;
var level_ambient_color =  [0.0, 0.0, 0.7]

var level_z = 0.0;

var objects = []
var death_objects = []
var damage_objects = []
var under_objects = []
var coins = []
var boost;
var spring;

var keystate = { "space" : false, "left" : false, "right" : true }

window.addEventListener("keyup", keyup);
window.addEventListener("keypress", keypress);
window.addEventListener("keydown", keydown);

function keyup(event){
    if(event.keyCode == 32)
        keystate["space"] = false;
    if(event.keyCode == 37)
        keystate["left"] = false;
    if(event.keyCode == 39)
        keystate["right"] = false;
    if(event.keyCode == 17)
        keystate["ctrl"] = false;
}

function keydown(event){
    if(event.keyCode == 32)
        keystate["space"] = true;
    if(event.keyCode == 37)
        keystate["left"] = true;
    if(event.keyCode == 39)
        keystate["right"] = true;
    if(event.keyCode == 17)
        keystate["ctrl"] = true;

    if(event.keyCode == 67)
        level_grayscale = false;

    if(event.keyCode == 77)
        level_grayscale = true;
}

function keypress(event) { }

function levelInit(gl) {
    player = new MPlayer(gl, [-0.6, -0.5, 0.0]);
    objects.push(player);

    police = new MPolice(gl, [0.0, -0.5, 1.0]);
    objects.push(police);

    objects.push(new MGround(gl, [0, -1.0, 0.0]));

    sky = new MSky(gl, [0.0, 2.0, 0.0]);
    objects.push(sky);
    
    objects.push(new MWall(gl, [-3.0, -2.0, -900.0]));
    objects.push(new MWall(gl, [3.0, -2.0, -900.0]));

    objects.push(new MTrack(gl, [-0.6, -1.0, 0.0]));
    objects.push(new MTrack(gl, [0.6, -1.0, 0.0]));

    for(let i = 0; i < 50; i++) {
        let type = i%4;
        let side = Math.random() * 2 > 1;

        if(type == 1) {
            let box = new MContainer(gl, [side ? 0.6 : -0.6, -0.8, -i*10 - 50]);
            box.scale = [0.005, 0.005, 0.01]
            objects.push(box);
            death_objects.push(box);
        } else if(type == 2) {
            let rock = new MRock(gl, [side ? 0.6 : -0.6, -0.8, -i*10 - 50]);
            rock.scale = [0.2, 0.25, 0.1]
            objects.push(rock);
            damage_objects.push(rock);
        } else if(type == 3) {
            let arch = new MArch(gl, [side ? 0.6 : -0.6, -1.0, -i*10 - 50]);
            arch.scale = [0.005, 0.005, 0.005]
            objects.push(arch);
            under_objects.push(arch);
        } else {
            let fireplace = new MFireplace(gl, [side ? 0.6 : -0.6, -1.0, -i*10 - 50]);
            fireplace.scale = [0.1, 0.1, 0.1]
            objects.push(fireplace);
            damage_objects.push(fireplace);
        }

        for(let j = 0; j < Math.random() * 7; j++) {
            let coin = new MCoin(gl, [!side ? 0.6 : -0.6, -Math.random()/2 + 0.5, -i*10 - j - 50])
            objects.push(coin);
            coins.push(coin);
        }
    }

    boost = new MWings(gl, [0.6, 0.25, -100]);
    objects.push(boost);

    spring = new MSpring(gl, [0.6, 0.25, -25]);
    objects.push(spring);
}

var variation = 0;
function levelDraw(gl, viewProjectionMatrix, programInfo, deltaTime) {
    variation += 0.01;
    level_ambient_color[2] = 0.0 + Math.sin(variation) * 0.4;

    if(player.dead)
        return;

    player.input(keystate);
    sky.pos[2] = level_z;
    level_z = player.pos[2];
    
    police.velocity[0] = (player.pos[0] < 0) ? -0.01 : 0.01;

    if(level_z < -600.0) {
        document.getElementById("status").innerHTML = "You won!";
        player.dead = true;
        return;
    }

    for(obj of coins) {
        if((obj.pos[0] - player.pos[0]) * (obj.pos[0] - player.pos[0]) +
           (obj.pos[1] - player.pos[1]) * (obj.pos[1] - player.pos[1]) +
           (obj.pos[2] - player.pos[2]) * (obj.pos[2] - player.pos[2]) < 0.1) {
            obj.pos = [100, 100, 100]
            player.score += 1;
        }
    }

    for(obj of death_objects) {
        if((obj.pos[0] - player.pos[0]) * (obj.pos[0] - player.pos[0]) +
           (obj.pos[2] - player.pos[2]) * (obj.pos[2] - player.pos[2]) < 0.5
        && player.pos[1] <= 0.0) {
            player.dead = true;
        }
    }

    for(obj of under_objects) {
        if((obj.pos[0] - player.pos[0]) * (obj.pos[0] - player.pos[0]) +
           (obj.pos[2] - player.pos[2]) * (obj.pos[2] - player.pos[2]) < 0.5
        && player.pos[1] >= -0.5 && player.pos[1] < 0.5) {
            player.dead = true;
        }
    }

    for(obj of damage_objects) {
        if((obj.pos[0] - player.pos[0]) * (obj.pos[0] - player.pos[0]) +
           (obj.pos[2] - player.pos[2]) * (obj.pos[2] - player.pos[2]) < 0.5
        && player.pos[1] <= 0.0) {
            obj.pos = [1900, 0100, 10]
            if(player.velocity[2] > -0.225)
                player.dead = true;
            else {
                player.velocity[2] = -0.2;
                police.pos[2] = player.pos[2] + 0.5
            }
        }
    }
    
    if((boost.pos[0] - player.pos[0]) * (boost.pos[0] - player.pos[0]) +
       (boost.pos[2] - player.pos[2]) * (boost.pos[2] - player.pos[2]) < 0.5
    && player.pos[1] >= 0.0) {
            boost.pos[2] -= 250
            player.fly = true;
    }

    if((spring.pos[0] - player.pos[0]) * (spring.pos[0] - player.pos[0]) +
       (spring.pos[2] - player.pos[2]) * (spring.pos[2] - player.pos[2]) < 0.5
    && player.pos[1] >= 0.0) {
            spring.pos[2] -= 250
            player.high_jump = true;
    }

    for(obj of objects) {
        if(typeof obj.tick === 'function')
            obj.tick();
    }

    for(obj of objects) {
        obj.draw(gl, viewProjectionMatrix, programInfo, deltaTime);
    }

    document.getElementById("score").innerHTML = "Score: " + player.score;

    if(player.dead) {
        document.getElementById("status").innerHTML = "Game Over!";
    }
}