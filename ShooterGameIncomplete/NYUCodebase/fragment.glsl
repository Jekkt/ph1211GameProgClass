uniform sampler2D texture;
varying vec2 texCoordVar;


void main() {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);


	vec4 texColor = texture2D( texture, texCoordVar);
	vec4 finalColor = vec4((texture.r + texture.g + texture.b) / 3.0f);
	gl_FragColor =finalColor;

}