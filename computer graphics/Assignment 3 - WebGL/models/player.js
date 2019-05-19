/// <reference path="../webgl.d.ts" />

let MPlayer = class {
    constructor(gl, pos) {
        this.hasTexture = false
        
        this.rotation = [0, Math.PI, 0];
        this.scale = [5, 5, 5]
        this.pos = pos;
        this.velocity = [0, 0, 0.2]

        this.dead = false;
        this.duck = false;
        this.count = 0;
        this.fly = false
        this.score = 0;
        this.high_jump = false

        this.buffers = {
            position: models.player.vertexBuffer,
            uv: models.player.textureBuffer,
            normal: models.player.normalBuffer,
            index: models.player.indexBuffer,
            texture: models.player.texture,
            vertexCount: models.player.indexBuffer.numItems
        }

        this.lighting = {
            Ka: 0.2,
            ambientColor: level_ambient_color,

            Kd: 0.8
        }
    }

    input(keys) {
        if(this.pos[1] > -0.5 && !this.fly)
            return;

        if(keys["space"]) {
            if(this.velocity[1] <= 0.0)
                this.velocity[1] = this.high_jump ? 0.3 : 0.2;
        }

        if(keys["left"])
            this.velocity[0] = -0.1;

        if(keys["right"])
            this.velocity[0] = 0.1;

        this.duck = keys["ctrl"];
    }

    tick() {
        if(this.fly) {
            this.count += 1
            if(this.count == 200) {
                this.count = 0;
                this.fly = false
            }
        }

        if(this.high_jump) {
            this.count += 1
            if(this.count == 200) {
                this.count = 0;
                this.high_jump = false
            }
        }

        if(this.dead)
            return;

        this.pos[0] += this.velocity[0];
        this.pos[1] += this.velocity[1];
        this.pos[2] += this.velocity[2];

        if(this.duck) {
            this.pos[1] = -0.9;
        } else {
            this.pos[1] = clamp(this.pos[1], -0.5, this.high_jump ? 1.5 : 0.5);

            if(this.velocity[1] > -0.01)
                this.velocity[1] -= 0.025;
        }

        this.velocity[2] -= 0.0001;
        this.velocity[2] = clamp(this.velocity[2], -0.25, -0.2);

        this.pos[0] = clamp(this.pos[0], -0.6, 0.6);
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        drawObject(gl, projectionMatrix, programInfo,
            this.pos, this.rotation, this.scale,
            this.buffers, this.lighting, true, level_grayscale);
    }
};
