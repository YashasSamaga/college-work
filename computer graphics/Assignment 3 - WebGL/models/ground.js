/// <reference path="../webgl.d.ts" />

let MGround = class {
    constructor(gl, pos) {       
        this.rotation = [0, 0, 0];
        this.scale = [1.0, 1.0, 1.0];
        this.pos = pos;

        this.positions = [
             -4.0, -1.0, -1000.0,
             4.0, -1.0, -1000.0,
             4.0, -1.0, 1000.0,
             -4.0, -1.0, 1000.0
        ];

        this.colors = [
            0.6, 0.25, 0.2, 1.0,
            0.6, 0.25, 0.2, 1.0,
            0.6, 0.25, 0.2, 1.0,
            0.6, 0.25, 0.2, 1.0
        ];

        this.indices = [
            0, 1, 2,    0, 2, 3
        ];

        const textureCoordinates = [
            0.0,  500.0,
            8.0,  500.0,
            8.0,  0.0,
            0.0,  0.0                    
        ];

        this.texture = loadTexture(gl, 'resources/ground.png', true);

        const positionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions), gl.STATIC_DRAW);

        const colorBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.colors), gl.STATIC_DRAW);

        const indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(this.indices), gl.STATIC_DRAW);

        const textureCoordBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates), gl.STATIC_DRAW); 

        this.buffers = {
            position: positionBuffer,
            color: colorBuffer,
            index: indexBuffer,
            uv: textureCoordBuffer,
            texture: this.texture,
            vertexCount: this.indices.length
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