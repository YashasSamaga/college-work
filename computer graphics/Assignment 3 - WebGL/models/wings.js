/// <reference path="../webgl.d.ts" />

let MWings = class {
    constructor(gl, pos) {       
        this.rotation = [0, 0, 0];
        this.scale = [0.2, 0.2, 0.2]
        this.pos = pos;

        this.positions = [
             // Front face
             -1.0, -1.0, 1.0,
             1.0, -1.0, 1.0,
             1.0, 1.0, 1.0,
             -1.0, 1.0, 1.0,
             //Back Face
             -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, 1.0, -1.0,
             -1.0, 1.0, -1.0,
             //Top Face
             -1.0, 1.0, -1.0,
             1.0, 1.0, -1.0,
             1.0, 1.0, 1.0,
             -1.0, 1.0, 1.0,
             //Bottom Face
             -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0, 1.0,
             -1.0, -1.0, 1.0,
             //Left Face
             -1.0, -1.0, -1.0,
             -1.0, 1.0, -1.0,
             -1.0, 1.0, 1.0,
             -1.0, -1.0, 1.0,
             //Right Face
             1.0, -1.0, -1.0,
             1.0, 1.0, -1.0,
             1.0, 1.0, 1.0,
             1.0, -1.0, 1.0,
        ];

        this.colors = [
            0.3, 0.3, 0.3, 1.0,
            0.23, 0.3, 0.43, 1.0,
            0.83, 0.23, 0.43, 1.0,
            0.93, 0.3, 0.53, 1.0,
            0.23, 0.3, 0.23, 1.0,
            0.23, 0.13, 0.83, 1.0,
            0.63, 0.3, 0.33, 1.0,
            0.63, 0.23, 0.93, 1.0,
            0.53, 0.3, 0.53, 1.0,
            0.63, 0.13, 0.13, 1.0,
            0.33, 0.23, 0.3, 1.0,
            0.43, 0.13, 0.63, 1.0,
            0.83, 0.13, 0.33, 1.0,
            0.3, 0.23, 0.83, 1.0,
            0.03, 0.13, 0.3, 1.0,
            0.13, 0.23, 0.453, 1.0,
            0.43, 0.23, 0.73, 1.0,
            0.73, 0.13, 0.23, 1.0,
            0.73, 0.3, 0.43, 1.0,
            0.33, 0.3, 0.563, 1.0,
            0.63, 0.63, 0.83, 1.0,
            0.43, 0.43, 0.33, 1.0,
            0.93, 0.43, 0.53, 1.0,
            0.83, 0.33, 0.83, 1.0,
        ];

        this.indices = [
            0, 1, 2,    0, 2, 3, // front
            4, 5, 6,    4, 6, 7,
            8, 9, 10,   8, 10, 11,
            12, 13, 14, 12, 14, 15,
            16, 17, 18, 16, 18, 19,
            20, 21, 22, 20, 22, 23, 
        ];

        const positionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions), gl.STATIC_DRAW);

        const colorBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.colors), gl.STATIC_DRAW);

        const indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(this.indices), gl.STATIC_DRAW);

        this.buffers = {
            position: positionBuffer,
            color: colorBuffer,
            index: indexBuffer,
            vertexCount: this.indices.length
        }

        this.lighting = {
            Ka: 0.2,
            ambientColor: level_ambient_color,

            Kd: 0.8
        }
    }

    tick() {
        this.rotation[0] += 0.1;
        this.rotation[1] += 0.2;
        this.rotation[2] += 0.3;
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        drawObject(gl, projectionMatrix, programInfo,
            this.pos, this.rotation, this.scale,
            this.buffers, this.lighting, false, level_grayscale);
    }
};