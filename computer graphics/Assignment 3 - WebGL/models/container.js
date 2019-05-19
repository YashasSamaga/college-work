/// <reference path="../webgl.d.ts" />

let MContainer = class {
    constructor(gl, pos) {       
        this.rotation = [Math.PI/6, Math.PI, 0];
        this.scale = [1, 1, 1]
        this.pos = pos;

        this.buffers = {
            position: models.container.vertexBuffer,
            uv: models.container.textureBuffer,
            normal: models.container.normalBuffer,
            index: models.container.indexBuffer,
            texture: models.container.texture,
            vertexCount: models.container.indexBuffer.numItems
        }

        this.lighting = {
            Ka: 0.1,
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