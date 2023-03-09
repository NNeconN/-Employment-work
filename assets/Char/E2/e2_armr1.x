xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 13;
 0.12590;0.14350;-0.54414;,
 -0.41993;-0.96221;-0.95493;,
 -1.38253;-0.98429;-0.57733;,
 -0.38188;0.38823;-0.20218;,
 -1.23556;-1.27389;0.28173;,
 -0.17980;0.34016;0.36034;,
 -0.39299;-1.49328;0.45565;,
 0.28160;0.06131;0.42602;,
 0.04363;-1.62628;-0.26148;,
 0.49574;-0.05538;-0.10038;,
 -1.62660;-2.94120;-0.30115;,
 -1.12440;-3.03176;-0.20219;,
 -1.18883;-2.69751;-0.83092;;
 
 16;
 4;0,1,2,3;,
 4;2,4,5,3;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,1,0,9;,
 4;6,4,10,11;,
 3;8,12,1;,
 3;12,2,1;,
 3;4,2,10;,
 3;2,12,10;,
 3;8,11,12;,
 3;11,8,6;,
 3;11,10,12;,
 3;7,3,5;,
 3;3,9,0;,
 3;9,3,7;;
 
 MeshMaterialList {
  1;
  16;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
   TextureFilename {
    "assets\\model\\Char\\E2\\e2_othertex.bmp";
   }
  }
 }
 MeshNormals {
  23;
  -0.330126;0.466665;-0.820512;,
  -0.354470;0.286625;-0.890055;,
  -0.514162;0.199339;-0.834207;,
  -0.802179;0.504832;0.318831;,
  -0.901938;0.334673;0.272950;,
  -0.143328;0.067992;0.987337;,
  -0.198635;-0.103531;0.974590;,
  0.817464;-0.320088;0.478849;,
  0.812064;-0.539784;0.221780;,
  -0.247457;-0.271675;0.930031;,
  0.461548;-0.668915;-0.582689;,
  0.751462;-0.432468;0.498274;,
  0.683544;-0.229870;-0.692768;,
  0.743416;-0.132983;-0.655475;,
  -0.588169;0.052951;-0.807003;,
  -0.968331;0.087788;-0.233729;,
  0.768748;-0.636055;0.066791;,
  -0.068154;-0.883802;-0.462870;,
  0.490213;0.869143;-0.065441;,
  0.476857;0.878293;-0.034758;,
  0.525827;0.842519;-0.116911;,
  0.450503;0.892751;0.006464;,
  0.448492;0.893391;0.026593;;
  16;
  4;0,1,2,0;,
  4;4,4,3,3;,
  4;6,6,5,5;,
  4;11,8,7,7;,
  4;12,12,13,13;,
  4;6,6,9,9;,
  3;12,10,12;,
  3;14,2,1;,
  3;4,4,15;,
  3;2,14,15;,
  3;8,16,10;,
  3;16,8,11;,
  3;17,17,10;,
  3;18,19,20;,
  3;19,21,22;,
  3;21,19,18;;
 }
 MeshTextureCoords {
  13;
  -0.783450;0.112500;
  -0.929560;0.241830;
  -1.187230;0.244410;
  -0.919370;0.083870;
  -1.147890;0.278280;
  -0.865280;0.089490;
  -0.922350;0.303940;
  -0.741770;0.122110;
  -0.805470;0.319500;
  -0.684450;0.135760;
  -1.252570;0.473300;
  -1.118140;0.483890;
  -1.135380;0.444800;;
 }
}
