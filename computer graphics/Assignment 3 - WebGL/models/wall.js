/// <reference path="../webgl.d.ts" />

let MWall = class {
    constructor(gl, pos) {       
        this.rotation = [0, 0, 0];
        this.scale = [1.0, 2.5, 1.0]
        this.pos = pos;

        this.positions = [
             0.0, 1.0, -1000.0,
             0.0, 1.0, 1000.0,
             0.0, 0.0, 1000.0,
             0.0, 0.0, -1000.0
        ];

        this.colors = [
            0.9, 0.35, 0.1, 1.0,
            0.9, 0.35, 0.1, 1.0,
            0.9, 0.35, 0.1, 1.0,
            0.9, 0.35, 0.1, 1.0
        ];

        this.indices = [
            0, 1, 2,    0, 2, 3
        ];

        const textureCoordinates = [
            0.0,  0.0,
            0.0,  1000.0,
            1.0,  1000.0,
            1.0,  0.0           
        ];

        this.texture = loadTexture(gl, 'resources/wall/wall.png', true);

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
            Ka: 0.2,
            ambientColor: level_ambient_color,

            Kd: 0.8
        }

        this.count = 0;
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        this.count += 0.05;
        this.lighting.Kd = Math.sin(this.count) * 0.2 + 0.8;
        drawObject(gl, projectionMatrix, programInfo,
            this.pos, this.rotation, this.scale,
            this.buffers, this.lighting, true, level_grayscale);
    }
};