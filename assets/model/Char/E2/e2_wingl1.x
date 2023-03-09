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
 10;
 -0.15547;-0.01503;-0.23614;,
 0.03140;0.26288;-0.03233;,
 3.14485;-3.17462;2.54460;,
 2.71442;-3.30234;2.26265;,
 2.71442;-3.30234;2.26265;,
 3.14485;-3.17462;2.54460;,
 3.49455;-8.12978;2.78811;,
 -0.24869;0.04915;0.13143;,
 2.67727;-3.17098;2.64817;,
 2.67727;-3.17098;2.64817;;
 
 6;
 4;0,1,2,3;,
 3;4,5,6;,
 4;2,1,7,8;,
 3;6,5,9;,
 3;4,6,9;,
 4;8,7,0,3;;
 
 MeshMaterialList {
  1;
  6;
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
  9;
  0.633956;-0.020566;-0.773096;,
  0.592063;-0.011493;-0.805810;,
  0.548448;-0.002386;-0.836181;,
  0.079246;0.650620;0.755257;,
  0.156022;0.376809;0.913057;,
  0.216297;0.063143;0.974284;,
  -0.906355;-0.422506;-0.002902;,
  -0.985750;-0.163573;-0.039244;,
  -0.759282;-0.649890;0.033657;;
  6;
  4;0,0,1,1;,
  3;1,1,2;,
  4;4,3,3,4;,
  3;5,4,4;,
  3;6,7,6;,
  4;6,8,8,6;;
 }
 MeshTextureCoords {
  10;
  -0.002590;0.248130;
  -0.052190;0.227480;
  -1.059490;0.394910;
  -0.959310;0.408840;
  -0.310640;0.245680;
  -0.410810;0.231750;
  -0.705220;0.536700;
  -0.057930;0.241780;
  -1.022060;0.397680;
  -0.373380;0.234520;;
 }
}
