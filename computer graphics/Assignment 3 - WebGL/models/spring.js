/// <reference path="../webgl.d.ts" />

let MSpring = class {
    constructor(gl, pos) {       
        this.rotation = [Math.PI/6, Math.PI, 0];
        this.scale = [0.003, 0.003, 0.003]
        this.pos = pos;

        this.buffers = {
            position: models.spring.vertexBuffer,
            uv: models.spring.textureBuffer,
            normal: models.spring.normalBuffer,
            index: models.spring.indexBuffer,
            texture: models.spring.texture,
            vertexCount: models.spring.indexBuffer.numItems
        }

        this.lighting = {
            Ka: 0.2,
            ambientColor: level_ambient_color,

            Kd: 0.8
        }
    }

    tick() {
        this.rotation[0] += 0.1;
        this.rotation[1] += 0.1; 
        this.rotation[2] += 0.1;
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        drawObject(gl, projectionMatrix, programInfo,
            this.pos, this.rotation, this.scale,
            this.buffers, this.lighting, true, level_grayscale);
    }
};