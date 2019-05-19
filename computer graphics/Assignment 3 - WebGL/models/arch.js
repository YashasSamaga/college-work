/// <reference path="../webgl.d.ts" />

let MArch = class {
    constructor(gl, pos) {       
        this.rotation = [Math.PI/2 * 3, 0, 0];
        this.scale = [1, 1, 1]
        this.pos = pos;

        this.buffers = {
            position: models.arch.vertexBuffer,
            uv: models.arch.textureBuffer,
            normal: models.arch.normalBuffer,
            index: models.arch.indexBuffer,
            texture: models.arch.texture,
            vertexCount: models.arch.indexBuffer.numItems
        }

        this.lighting = {
            Ka: 0.05,
            ambientColor: level_ambient_color,

            Kd: 0.8
        }
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        drawObject(gl, projectionMatrix, programInfo,
            this.pos, this.rotation, this.scale,
            this.buffers, this.lighting, true, level_grayscale);
    }
};