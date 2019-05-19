/// <reference path="../webgl.d.ts" />

let MRock = class {
    constructor(gl, pos) {       
        this.rotation = [Math.PI/6, Math.PI, 0];
        this.scale = [1, 1, 1]
        this.pos = pos;

        this.buffers = {
            position: models.rock.vertexBuffer,
            uv: models.rock.textureBuffer,
            normal: models.rock.normalBuffer,
            index: models.rock.indexBuffer,
            texture: models.rock.texture,
            vertexCount: models.rock.indexBuffer.numItems
        }

        this.lighting = {
            Ka: 0.2,
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