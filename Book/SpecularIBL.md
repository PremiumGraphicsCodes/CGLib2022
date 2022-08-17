前の章で既にPBR
この賞ではスペキュラについて解説します．

$$
L_o(p,\omega_o) = \int\limits_{\Omega} 
    	(k_d\frac{c}{\pi} + k_s\frac{DFG}{4(\omega_o \cdot n)(\omega_i \cdot n)})
    	L_i(p,\omega_i) n \cdot \omega_i  d\omega_i
$$


Specular IBL
In the previous chapter we've set up PBR in combination with image based lighting by pre-computing an irradiance map as the lighting's indirect diffuse portion. In this chapter we'll focus on the specular part of the reflectance equation:

既に皆さんはクックトレランスのスペキュラ（Ksをかけられる）は積分するときに定数でない，入ってくる光るの向きに依存し，ことに気づいていることでしょう．

You'll notice that the Cook-Torrance specular portion (multiplied by kS) isn't constant over the integral and is dependent on the incoming light direction, but also the incoming view direction. Trying to solve the integral for all incoming light directions including all possible view directions is a combinatorial overload and way too expensive to calculate on a real-time basis. Epic Games proposed a solution where they were able to pre-convolute the specular part for real time purposes, given a few compromises, known as the split sum approximation.


$$
L_o(p,\omega_o) = 
		\int\limits_{\Omega} (k_s\frac{DFG}{4(\omega_o \cdot n)(\omega_i \cdot n)}
			L_i(p,\omega_i) n \cdot \omega_i  d\omega_i
			=
		\int\limits_{\Omega} f_r(p, \omega_i, \omega_o) L_i(p,\omega_i) n \cdot \omega_i  d\omega_i
$$

Epic Gamesは解決策を提案しました．多少の妥協をすることで，

$$
f_r(p, w_i, w_o) = \frac{DFG}{4(\omega_o \cdot n)(\omega_i \cdot n)}
$$

この積分もw0に依存し，サンプルすることができません．
ここで述べる位置pは前章と無関係です．
事前計算

イラディアンス畳み込みのいくつかの同じ理由（速度）で，スペキュラ部分の積分はリアルタイムに解くことができません．そこでスペキュラIBLマップを事前計算し，

![犬](https://learnopengl.com/img/pbr/ibl_prefilter_map.png)

# HDR環境マップの事前フィルタリング

環境マップの事前フィルタリングはイラディアンスマップのコンボリューションとよく似ています．
違いはラフネスを考慮することと，ラフな連続した反射をミップマップレベルで保存することです．

まず，キューブマップを生成します．
First, we need to generate a new cubemap to hold the pre-filtered environment map data. To make sure we allocate enough memory for its mip levels we call glGenerateMipmap as an easy way to allocate the required amount of memory:

```
unsigned int prefilterMap;
glGenTextures(1, &prefilterMap);
glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
for (unsigned int i = 0; i < 6; ++i)
{
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
}
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
```

## モンテカルロ積分とインポータンスサンプリング