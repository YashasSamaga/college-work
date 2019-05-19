/// <reference path="../webgl.d.ts" />

let MFireplace = class {
    constructor(gl, pos) {       
        this.rotation = [Math.PI/6, Math.PI, 0];
        this.scale = [1, 1, 1]
        this.pos = pos;

        this.buffers = {
            position: models.fireplace.vertexBuffer,
            uv: models.fireplace.textureBuffer,
            normal: models.fireplace.normalBuffer,
            index: models.fireplace.indexBuffer,
            texture: models.fireplace.texture,
            vertexCount: models.fireplace.indexBuffer.numItems
        }

        this.lighting = {
            Ka: 0.0,
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