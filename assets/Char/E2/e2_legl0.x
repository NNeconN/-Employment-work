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
 21;
 -0.22102;0.86010;-1.02631;,
 0.16683;0.24526;-1.22616;,
 -0.89763;-0.07640;-0.57016;,
 0.85321;1.02471;-0.04515;,
 0.97726;0.36440;-0.22277;,
 0.35687;0.15327;0.86410;,
 0.66228;-0.99145;-1.56723;,
 -0.03891;-1.37212;-1.07949;,
 1.30467;-0.85146;-0.80018;,
 0.98259;-1.25343;-0.13134;,
 0.98259;-1.25343;-0.13134;,
 0.35687;0.15327;0.86410;,
 -0.49080;-0.50904;0.71134;,
 0.28942;-1.72712;-0.34530;,
 -0.89763;-0.07640;-0.57016;,
 -0.03891;-1.37212;-1.07949;,
 1.13247;-2.43347;-1.81785;,
 1.50151;-2.34430;-1.40355;,
 1.02102;-2.75267;-1.24215;,
 1.02102;-2.75267;-1.24215;,
 -0.49080;-0.50904;0.71134;;
 
 19;
 3;0,1,2;,
 4;1,0,3,4;,
 3;4,3,5;,
 4;2,1,6,7;,
 4;6,1,4,8;,
 4;8,4,5,9;,
 4;10,11,12,13;,
 4;13,12,14,15;,
 3;16,7,6;,
 4;16,6,8,17;,
 3;8,9,17;,
 3;16,17,18;,
 3;10,13,19;,
 3;19,13,15;,
 3;18,7,16;,
 3;18,17,9;,
 3;20,5,3;,
 3;0,2,3;,
 3;3,2,20;;
 
 MeshMaterialList {
  1;
  19;
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
  27;
  -0.514022;-0.045829;-0.856552;,
  -0.530459;-0.026136;-0.847308;,
  0.618485;0.442841;-0.649129;,
  0.638175;0.444636;-0.628515;,
  0.722739;-0.179742;0.667339;,
  -0.647211;-0.197036;-0.736407;,
  -0.551768;-0.021900;-0.833710;,
  0.668239;0.394186;-0.630931;,
  0.614534;-0.358644;0.702654;,
  0.194950;-0.540585;0.818390;,
  0.174846;-0.563390;0.807478;,
  -0.685689;-0.293330;-0.666174;,
  0.676887;0.340976;-0.652349;,
  0.547992;-0.772036;-0.321971;,
  0.873002;0.028966;0.486856;,
  0.865759;0.028244;0.499664;,
  0.896494;-0.008165;0.442981;,
  -0.801190;-0.594885;0.064852;,
  -0.813286;-0.577269;0.072989;,
  0.792040;-0.264745;0.550075;,
  0.394107;-0.540595;0.743261;,
  -0.789150;-0.583164;-0.192776;,
  -0.593567;0.708452;0.381803;,
  -0.615892;0.709062;0.343377;,
  -0.584554;0.691554;0.424323;,
  -0.562735;0.653282;0.506510;,
  -0.567144;0.680752;0.463599;;
  19;
  3;0,1,1;,
  4;3,2,2,3;,
  3;14,15,4;,
  4;1,1,6,5;,
  4;7,3,3,7;,
  4;16,14,4,8;,
  4;8,4,9,10;,
  4;17,18,18,17;,
  3;11,5,6;,
  4;12,7,7,12;,
  3;16,8,19;,
  3;13,13,13;,
  3;8,10,20;,
  3;21,17,17;,
  3;21,5,11;,
  3;20,19,8;,
  3;22,23,24;,
  3;25,26,24;,
  3;24,26,22;;
 }
 MeshTextureCoords {
  21;
  -0.215350;0.045370;
  -0.365520;0.104870;
  0.046620;0.136000;
  -0.631270;0.029440;
  -0.679300;0.093340;
  -0.439100;0.113780;
  -0.557340;0.224550;
  -0.285860;0.261390;
  -0.806070;0.211010;
  -0.681360;0.249910;
  -0.141200;0.284010;
  -0.185410;0.121090;
  -0.482220;0.126280;
  -0.403010;0.292000;
  -0.879850;0.187140;
  -0.664940;0.318200;
  -0.739390;0.364100;
  -0.882280;0.355470;
  -0.696240;0.394990;
  -0.312900;0.435200;
  -0.110890;0.177870;;
 }
}
