function loadShader(gl, type, source) {
  const shader = gl.createShader(type);

  gl.shaderSource(shader, source);
  gl.compileShader(shader);

  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    alert('An error occurred compiling the shaders: ' + gl.getShaderInfoLog(shader));
    gl.deleteShader(shader);
    return null;
  }

  return shader;
}

function initShaderProgram(gl, vsSource, fsSource) {
  const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
  const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

  const shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertexShader);
  gl.attachShader(shaderProgram, fragmentShader);
  gl.linkProgram(shaderProgram);

  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    alert('Unable to initialize the shader program: ' + gl.getProgramInfoLog(shaderProgram));
    return null;
  }

  return shaderProgram;
}

function initShaders(gl) {
  const vertexShaderSource = `
    attribute vec3 aVertexPosition;
    attribute vec3 aVertexNormal;
    attribute vec2 aTextureCoord;
    attribute vec4 aVertexColor;

    uniform vec3 lightPos;

    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;

    varying highp vec4 vPosition;
    varying highp vec3 vNormal;
    varying highp vec2 vTextureCoord;
    varying lowp vec4 vColor;

    varying highp vec4 vLightPos;

    void main(void) {
      vPosition = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
      vNormal = aVertexNormal;
      vTextureCoord = aTextureCoord;
      vColor = aVertexColor;
      gl_Position = vPosition;
      vLightPos = uProjectionMatrix * uModelViewMatrix * vec4(lightPos, 1.0);
    }
  `;

  const fragmentShaderSource = `
    precision mediump float;
    
    varying highp vec4 vPosition;
    varying highp vec3 vNormal;
    varying highp vec2 vTextureCoord;
    varying lowp vec4 vColor;

    varying highp vec4 vLightPos;

    uniform float Ka;
    uniform vec3 ambientColor;
    uniform float Kd;

    uniform bool uHasTexture;
    uniform bool uRequireGrayscale;
    uniform sampler2D uSampler;

    void main(void) {
        vec4 object_color = vColor;
        if(uHasTexture)
        object_color = texture2D(uSampler, vTextureCoord);

        vec3 ambient_color = Ka * ambientColor;
        vec3 diffuse_color = Kd * vec3(object_color);

        vec4 final = vec4(ambient_color + diffuse_color, 1.0);

        if(uRequireGrayscale) {
            float amount = 0.299 * final.r + 0.587 * final.g + 0.114 * final.b;
            final = vec4(amount, amount, amount, 1.0);
        }

        gl_FragColor = final;
    }
  `;

  const shaderProgram = initShaderProgram(gl, vertexShaderSource, fragmentShaderSource);
  const programInfo = {
    program: shaderProgram,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
      //vertexNormal: gl.getAttribLocation(shaderProgram, 'aVertexNormal'),
      textureCoord: gl.getAttribLocation(shaderProgram, 'aTextureCoord'),
      vertexColor: gl.getAttribLocation(shaderProgram, 'aVertexColor'),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(shaderProgram, 'uProjectionMatrix'),
      modelViewMatrix: gl.getUniformLocation(shaderProgram, 'uModelViewMatrix'),
      hasTexture: gl.getUniformLocation(shaderProgram, 'uHasTexture'),
      requireGrayscale: gl.getUniformLocation(shaderProgram, 'uRequireGrayscale'),
      uSampler: gl.getUniformLocation(shaderProgram, 'uSampler'),
      Ka: gl.getUniformLocation(shaderProgram, 'Ka'),
      ambientColor: gl.getUniformLocation(shaderProgram, 'ambientColor'),
      Kd: gl.getUniformLocation(shaderProgram, 'Kd'),
      lightPos: gl.getUniformLocation(shaderProgram, 'lightPos'),
    },
  };
  return programInfo;
}

function drawObject(gl, projectionMatrix, programInfo,
  position, rotation, scale, buffers, lighting,
  hasTexture, requireGrayscale) {
    const modelViewMatrix = mat4.create();
    mat4.translate(modelViewMatrix, modelViewMatrix, position);

    mat4.rotate(modelViewMatrix, modelViewMatrix, rotation[0], [1, 0, 0]);
    mat4.rotate(modelViewMatrix, modelViewMatrix, rotation[1], [0, 1, 0]);
    mat4.rotate(modelViewMatrix, modelViewMatrix, rotation[2], [0, 0, 1]);

    mat4.scale(modelViewMatrix, modelViewMatrix, scale);

    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.position);
    gl.vertexAttribPointer(programInfo.attribLocations.vertexPosition, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(programInfo.attribLocations.vertexPosition);

    //gl.disableVertexAttribArray(programInfo.attribLocations.vertexNormal);    
    gl.disableVertexAttribArray(programInfo.attribLocations.textureCoord);
    gl.disableVertexAttribArray(programInfo.attribLocations.vertexColor);

    /*if("normal" in buffers) {
        gl.disableVertexAttribArray(programInfo.attribLocations.vertexNormal);    
        gl.bindBuffer(gl.ARRAY_BUFFER, buffers.normal);
        gl.vertexAttribPointer(programInfo.attribLocations.vertexNormal, 
        2, gl.FLOAT, false, 0, 0);
    }*/

    if(hasTexture) {
        gl.enableVertexAttribArray(programInfo.attribLocations.textureCoord);
        gl.bindBuffer(gl.ARRAY_BUFFER, buffers.uv);
        gl.vertexAttribPointer(programInfo.attribLocations.textureCoord, 
        2, gl.FLOAT, false, 0, 0);

        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, buffers.texture);
        gl.uniform1i(programInfo.uniformLocations.uSampler, 0);
    } else {
        gl.enableVertexAttribArray(programInfo.attribLocations.vertexColor);
        gl.bindBuffer(gl.ARRAY_BUFFER, buffers.color);
        gl.vertexAttribPointer(programInfo.attribLocations.vertexColor, 4, gl.FLOAT, false, 0, 0);
    }

    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffers.index);
    gl.useProgram(programInfo.program);
    gl.uniformMatrix4fv(programInfo.uniformLocations.projectionMatrix, false, projectionMatrix);
    gl.uniformMatrix4fv(programInfo.uniformLocations.modelViewMatrix, false, modelViewMatrix);
    gl.uniform1i(programInfo.uniformLocations.hasTexture, hasTexture);
    gl.uniform1i(programInfo.uniformLocations.requireGrayscale, requireGrayscale);

    gl.uniform1f(programInfo.uniformLocations.Ka, lighting.Ka);
    gl.uniform3fv(programInfo.uniformLocations.ambientColor, lighting.ambientColor);

    gl.uniform1f(programInfo.uniformLocations.Kd, lighting.Kd);
    gl.uniform3fv(programInfo.uniformLocations.lightPos, [0, 10, player.pos[2]]);

    gl.drawElements(gl.TRIANGLES, buffers.vertexCount, gl.UNSIGNED_SHORT, 0);
}