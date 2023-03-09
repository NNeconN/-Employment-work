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
 -1.98792;2.16114;0.97763;,
 -1.98915;1.95246;1.50243;,
 0.50468;-0.17810;0.27124;,
 0.33506;0.42207;-0.39834;,
 -2.48353;1.85328;1.16290;,
 -0.04390;-0.44791;-0.30483;,
 -1.98792;2.16114;0.97763;,
 -2.41281;3.94132;0.97286;,
 -2.34281;3.91419;2.00047;,
 -1.98915;1.95246;1.50243;,
 -2.48353;1.85328;1.16290;,
 -3.14250;4.12005;1.45830;,
 -1.99903;5.12743;1.54328;;
 
 9;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,5,4,0;,
 4;6,7,8,9;,
 4;6,10,11,7;,
 4;10,9,8,11;,
 3;11,12,7;,
 3;7,12,8;,
 3;11,8,12;;
 
 MeshMaterialList {
  1;
  9;
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
  12;
  0.694653;0.642511;0.323475;,
  0.880799;0.441256;0.171717;,
  -0.436350;-0.518150;0.735608;,
  -0.298437;-0.716544;0.630476;,
  0.998005;-0.051896;-0.035945;,
  -0.433104;0.229797;-0.871558;,
  -0.388454;0.505906;-0.770171;,
  -0.433928;0.115858;-0.893467;,
  -0.438506;0.024707;-0.898389;,
  -0.522302;0.074329;0.849515;,
  0.952053;-0.297168;-0.072702;,
  -0.431542;0.422605;0.796980;;
  9;
  4;1,1,0,0;,
  4;2,2,3,3;,
  4;7,7,8,8;,
  4;1,4,4,1;,
  4;8,8,5,5;,
  4;2,2,9,9;,
  3;5,6,5;,
  3;4,10,4;,
  3;9,9,11;;
 }
 MeshTextureCoords {
  13;
  -0.265480;0.161760;
  -0.292980;0.172210;
  -0.279450;0.441610;
  -0.223690;0.399830;
  -0.349230;0.147480;
  -0.358110;0.422980;
  -0.478580;0.228580;
  -0.321190;0.107000;
  -0.325510;0.111480;
  -0.506090;0.239030;
  -0.562340;0.214300;
  -0.375720;0.051840;
  -0.153370;0.068210;;
 }
}
