/// <reference path="../webgl.d.ts" />

let MPolice = class {
    constructor(gl, pos, texture) {       
        this.rotation = [Math.PI/6, Math.PI, 0];
        this.scale = [1, 1, 1]
        this.pos = pos;
        this.velocity = [0, 0, -0.2]

        this.buffers = {
            position: models.police.vertexBuffer,
            uv: models.police.textureBuffer,
            normal: models.police.normalBuffer,
            index: models.police.indexBuffer,
            texture: models.police.texture,
            vertexCount: models.police.indexBuffer.numItems
        }

        this.lighting = {
            Ka: 0.2,
            ambientColor: level_ambient_color,

            Kd: 0.8
        }

        this.count = 0.0;
    }

    tick() {
        this.pos[0] += this.velocity[0];
        this.pos[2] += this.velocity[2];

        this.count += 0.1;
        this.pos[1] = Math.sin(this.count)/4.0 - 0.5;

        this.pos[0] = clamp(this.pos[0], -0.6, 0.6);
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
       drawObject(gl, projectionMatrix, programInfo,
        this.pos, this.rotation, this.scale,
        this.buffers, this.lighting, true, level_grayscale);
    }
};