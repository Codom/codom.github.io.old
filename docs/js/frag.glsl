uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 u_mouse;

void main() {
	float zoom = 1.0 / (u_time + 25.0);
	vec2 c = vec2(-1.4108866282582646, 0.0) + zoom
		* (2.*gl_FragCoord.xy-u_resolution.xy)/u_resolution.y;

	vec2 z = c;

	float ar = 0.; // average of reciprocals
	float i;
	for (i = 0.; i < 50.; i++) {
		ar += 1./length(z);
		z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
	}
	ar = ar / i;

	gl_FragColor = vec4(1.0, vec2(1.0 - (1. / ar)), ar / 2.0);
}
