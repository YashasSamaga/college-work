/// <reference path="../webgl.d.ts" />

let MCoin = class {
    constructor(gl, pos) {       
        this.rotation = [Math.random() * Math.PI, Math.random() * Math.PI, Math.random() * Math.PI];
        this.scale = [0.1, 0.1, 0.1]
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
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
            1.0, 0.9, 0.1, 1.0,
            1.0, 0.9, 0, 1.0,
        ];

        this.indices = [
            0, 1, 2,    0, 2, 3,
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
            Ka: 0.0,
            ambientColor: level_ambient_color,
            
            Kd: 0.8
        }

        this.count = 0;
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        this.count += 0.25;
        this.lighting.Kd = Math.sin(this.count) * 0.2 + 0.8;
        drawObject(gl, projectionMatrix, programInfo,
            this.pos, this.rotation, this.scale,
            this.buffers, this.lighting, false, level_grayscale);
    }
};