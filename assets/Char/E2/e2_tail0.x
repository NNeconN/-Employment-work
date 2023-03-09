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
 0.39912;-0.75177;3.63302;,
 0.42210;-1.66996;3.85153;,
 0.46736;-0.31429;-0.45800;,
 0.45580;0.53911;-0.38905;,
 -0.45580;0.53911;-0.38905;,
 -0.46736;-0.31429;-0.45800;,
 -0.42210;-1.66996;3.85153;,
 -0.39912;-0.75177;3.63302;,
 0.61081;2.01630;6.15736;,
 0.51160;1.76036;7.07669;,
 -0.51160;1.76036;7.07669;,
 -0.61081;2.01630;6.15736;,
 0.00554;6.32325;6.37953;;
 
 12;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,4,7,0;,
 4;5,2,1,6;,
 4;0,8,9,1;,
 4;6,10,11,7;,
 4;11,8,0,7;,
 4;6,1,9,10;,
 3;10,12,11;,
 3;8,12,9;,
 3;12,10,9;,
 3;11,12,8;;
 
 MeshMaterialList {
  1;
  12;
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
  16;
  0.999603;0.020909;0.018908;,
  0.999666;-0.020486;0.015728;,
  -0.999603;0.020909;0.018908;,
  -0.999666;-0.020486;0.015728;,
  0.996360;0.034588;0.077906;,
  -0.996291;0.035817;0.078236;,
  -0.980767;0.132985;0.142867;,
  0.000000;0.952162;0.305595;,
  0.000000;-0.953914;-0.300079;,
  0.000000;0.385231;-0.922820;,
  0.000000;0.673828;-0.738888;,
  0.000000;-0.684983;0.728559;,
  0.000000;-0.296936;0.954897;,
  0.981186;0.130552;0.142235;,
  0.000000;0.151036;0.988528;,
  0.000000;0.051517;-0.998672;;
  12;
  4;1,1,0,0;,
  4;2,2,3,3;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;1,4,4,1;,
  4;3,5,5,3;,
  4;9,9,10,10;,
  4;11,11,12,12;,
  3;5,6,5;,
  3;4,13,4;,
  3;14,12,12;,
  3;9,15,9;;
 }
 MeshTextureCoords {
  13;
  -0.361590;0.582200;
  -0.359110;0.606370;
  -0.354220;0.570680;
  -0.355470;0.548210;
  -0.453920;0.548210;
  -0.455170;0.570680;
  -0.450280;0.606370;
  -0.447800;0.582200;
  -0.338730;0.509320;
  -0.349440;0.516060;
  -0.459940;0.516060;
  -0.470660;0.509320;
  -0.404100;0.395930;;
 }
}
