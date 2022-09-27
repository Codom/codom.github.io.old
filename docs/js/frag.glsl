uniform vec2 u_resolution;
uniform float u_time;

void main() {
	vec2 q = gl_FragCoord.xy;
	vec2 r = u_resolution.xy, 
	     p = q-.5*r;
	float l=length(p/=r.y),z=u_time;
	vec4 f;
	for( int i=0; i<4; )
		f[i++] = .01/length(fract( q/r + p/l* (1.0*sin(z+=.07 / 20.0)+1.) * abs(0.8*sin(l*9.-z-z / 20.0)) )-.5) / l;
	gl_FragColor = f;
}
