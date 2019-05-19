/// <reference path="../webgl.d.ts" />

let MTrack = class {
    constructor(gl, pos) {       
        this.rotation = [0, 0, 0];
        this.scale = [0.5, 1.0, 10000.0]
        this.pos = pos;

        this.positions = [
            -1.0, 0.0, -1.0,
            1.0, 0.0, -1.0,
            1.0, 0.0, 1.0,
            -1.0, 0.0, 1.0
        ];

        this.normals = [
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0
        ]

        this.indices = [
            0, 1, 2,    0, 2, 3
        ];

        this.texture = loadTexture(gl, 'resources/track.png', true);

        const textureCoordinates = [
            0.0,  0.0,
            1.0,  0.0,
            1.0,  5000.0,
            0.0,  5000.0
        ];         

        const positionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions), gl.STATIC_DRAW);

        const normalBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions), gl.STATIC_DRAW);

        const indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(this.indices), gl.STATIC_DRAW);

        const textureCoordBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates), gl.STATIC_DRAW);          

        this.buffers = {
            position: positionBuffer,
            index: indexBuffer,
            normal: normalBuffer,
            uv: textureCoordBuffer,
            texture: this.texture,
            vertexCount: this.indices.length
        }

        this.lighting = {
            Ka: 0.05,
            ambientColor: level_ambient_color,

            Kd: 0.8
        }

        this.buffers.uv.itemSize  = 3;
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        drawObject(gl, projectionMatrix, programInfo,
            this.pos, this.rotation, this.scale,
            this.buffers, this.lighting, true, level_grayscale);
    }
};