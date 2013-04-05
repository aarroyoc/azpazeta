#ifdef GL_ES
precision mediump float;
#endif
varying vec2 vTextureCoord;
uniform sampler2D uSampler;
void main()
{
 gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));
  //gl_FragColor = vec4(0.0,0.0,1.0,1.0);
}
