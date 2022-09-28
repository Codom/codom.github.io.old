/*
 * animation.js
 * Copyright (C) 2022 Christopher Odom <christopher.r.odom@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

/*
 * Starts up the 3js library
 */

var container;
var camera, scene, renderer, clock;
var uniforms;

var frag_shdr;
var vert_shdr;

fetch("js/frag.glsl").then((response) => {
	return response.text();
}).then((in_frag_shdr) => {
	frag_shdr = in_frag_shdr;
	console.log(frag_shdr);
}).then(() => {
	return fetch("js/vert.glsl")
}).then((response) => {
	return response.text()
}).then((in_vert_shdr) => {
	vert_shdr = in_vert_shdr;
	console.log(vert_shdr);
	init();
	animate();
}).catch((e) => {
	console.log(e)
})


function init() {
	container = document.getElementById( 'animContainer' );

	camera = new THREE.Camera();
	camera.position.z = 1;

	scene = new THREE.Scene();
	clock = new THREE.Clock();

	var geometry = new THREE.PlaneGeometry( 2, 2 );

	uniforms = {
		u_time: { type: "f", value: 1.0 },
		u_resolution: { type: "v2", value: new THREE.Vector2() },
		u_mouse: { type: "v2", value: new THREE.Vector2() }
	};

	var material = new THREE.ShaderMaterial( {
		uniforms: uniforms,
		vertexShader:   document.getElementById('vertexShader').text, 
		fragmentShader: frag_shdr
	} );

	var mesh = new THREE.Mesh( geometry, material );
	scene.add( mesh );

	renderer = new THREE.WebGLRenderer();
	renderer.setPixelRatio( window.devicePixelRatio );
	renderer.setClearColor(0xffffff, 1);

	container.appendChild( renderer.domElement );

	onWindowResize();
	window.addEventListener( 'resize', onWindowResize, false );

	document.onmousemove = function(e){
		uniforms.u_mouse.value.x = e.pageX
		uniforms.u_mouse.value.y = e.pageY
	}
}

function onWindowResize( event ) {
	renderer.setSize( window.innerWidth, window.innerHeight );
	uniforms.u_resolution.value.x = renderer.domElement.width;
	uniforms.u_resolution.value.y = renderer.domElement.height;
	uniforms.u_resolution.value.z = 1;
}

function animate() {
	requestAnimationFrame( animate );
	render();
}

function render() {
	uniforms.u_time.value += clock.getDelta();
	renderer.render( scene, camera );
}
