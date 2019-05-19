var cubeRotation = 0.0;

var models = {}

window.onload = function() {
  OBJ.downloadMeshes({
    'player': 'resources/player/player.obj',
    'police': 'resources/police/EAGLE_2.OBJ',
    'container' : 'resources/crate/12280_Container_v1_L1.obj',
    'rock' : 'resources/rock/rock.obj',
    'arch' : 'resources/arch/arch.obj',
    'fireplace' : 'resources/fireplace/fireplace.obj',
    'spring' : 'resources/spring/spring.obj',
    'wall' : 'resources/wall/wall.obj'
  }, main);
}

function main(meshes) {
  const canvas = document.querySelector('#glcanvas');
  const gl = canvas.getContext('webgl') || canvas.getContext('experimental-webgl');
  gl.viewportWidth = canvas.width;
  gl.viewportHeight = canvas.height;

  models = meshes;
  OBJ.initMeshBuffers(gl, models.player);
  models.player.texture = loadTexture(gl, 'resources/player/player.png');

  OBJ.initMeshBuffers(gl, models.police);  
  models.police.texture = loadTexture(gl, 'resources/police/EAGLE2.png');

  OBJ.initMeshBuffers(gl, models.container);
  models.container.texture = loadTexture(gl, 'resources/crate/Container_diffuse.png');

  OBJ.initMeshBuffers(gl, models.rock);
  models.rock.texture = loadTexture(gl, 'resources/rock/rock.png');

  OBJ.initMeshBuffers(gl, models.arch);
  models.arch.texture = loadTexture(gl, 'resources/rock/rock.png');

  OBJ.initMeshBuffers(gl, models.fireplace);
  models.fireplace.texture = loadTexture(gl, 'resources/fireplace/fireplace.png');

  OBJ.initMeshBuffers(gl, models.spring);
  models.spring.texture = loadTexture(gl, 'resources/spring/spring.png');

  OBJ.initMeshBuffers(gl, models.wall);
  models.wall.texture = loadTexture(gl, 'resources/wall/wall.png');

  levelInit(gl);

  if (!gl) {
    alert('Unable to initialize WebGL. Your browser or machine may not support it.');
    return;
  }

  const programInfo = initShaders(gl);

  var then = 0;
  function render(now) {
    now *= 0.001;
    const deltaTime = now - then;
    then = now;

    drawScene(gl, programInfo, deltaTime);

    requestAnimationFrame(render);
  }

  requestAnimationFrame(render);
}

function drawScene(gl, programInfo, deltaTime) {
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.clearDepth(1.0);
  gl.enable(gl.DEPTH_TEST);
  gl.depthFunc(gl.LEQUAL);

  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  const projectionMatrix = mat4.create();
  mat4.perspective(projectionMatrix,
                   45 * Math.PI / 180, /* field of view */
                   gl.viewportWidth / gl.viewportHeight, /* aspect ratio */
                   0.1, /* near */
                   10000.0 /* far */
                  ); 


    var cameraMatrix = mat4.create();
    mat4.translate(cameraMatrix, cameraMatrix, [0, 0, player.pos[2] + 3]);
    var cameraPosition = [
      cameraMatrix[12],
      cameraMatrix[13],
      cameraMatrix[14],
    ];

    var up = [0, 1, 0];

    mat4.lookAt(cameraMatrix, cameraPosition, [0.0, 0.0, player.pos[2] - 100.0], up);

    var viewMatrix = cameraMatrix;//mat4.create();

    var viewProjectionMatrix = mat4.create();

    mat4.multiply(viewProjectionMatrix, projectionMatrix, viewMatrix);

    levelDraw(gl, viewProjectionMatrix, programInfo, deltaTime);
}

