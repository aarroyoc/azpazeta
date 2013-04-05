attribute vec2 aTextureCoord;
attribute vec3 vPosition;
varying vec2 vTextureCoord;
uniform mat4 uMVMatrix;
mat4 igual=mat4(
1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0);
void main()
{
 gl_Position = uMVMatrix * vec4(vPosition, 1.0);
vTextureCoord = aTextureCoord;
}
