# Kernel-Free Particle Fluids

## Abstract
本文書ではカーネルを用いない新しい粒子法を提案する．
質点粒子と流体粒子を区別し，積分する側と積分される側を区別する．
これにより，既存の粒子法と比べて，まったく新しく，安定した粒子法を開発することができた．

This paper describes a novel particle-based fluid simulation algorithm.
We separate mass particle and fluid particle, fluid particle contains mass particle.
Compared to exsting particle-based methods, our method is robust and fast.

## はじめに

## 関連研究
CGにおける流体シミュレーション法は主に二つに大別される．
格子法と粒子法である．

Fluid Simulation methods are categolized in two parts.
Grid-based methods and Particle-Based methods.

格子法はFedkiwらによって開発されたが，
計算量の多さとGridの空間制限により，
現在では粒子法が多く用いられている．

Grid-based methods are develoed by Fedkiws in graphics community.
However, it's computational cost is high, and limited to space.

粒子法はさらにSPH法とMPS法に大別される．
MPS法は越塚らによって開発された．
数値流体力学分野で使われているが，
CG分野では少数の研究が行われているにとどまっている．

Major particle-based methods are SPH and MPS.
MPS is developed by Koshizuka et al.
MPS is good at precision, but is time consuming algorithm.
Due to this nature, MPS is widelly used in CFD, is not reported in CG community.


SPH法はMullerらによってCG分野に導入された．
計算量の少なさと，事実上無限の空間領域を扱えること，実装が用意であることから，その後多数の研究がおこなわれている．
SPH法はPCISPH，WCISPH,PBF,IISPH,DFSPHなどによって改良がくわえられている．
また境界処理にはXらの手法が用いらレテイル．
これらの研究では大幅な進歩がみられたが，非圧縮性を実現するため，きわめて小さいタイムステップを刻む必要がある．

SPH was introduced by Muller et al.
SPH is less computational cost, and easy to implement, many researches are reported.
To improve boundary handling, 
After the research, PCISPH, WCISPHCISPH, PBF, IISPH, DFSPH are 
These reaserches solved incompressibility, however, time steps are still restricted.

これらの手法の主な問題点は主にカーネルの計算である．既存研究
One main bottleneck is cased by kernel calculation.

カーネルの影響範囲が大きくすると近傍粒子が指数関数的に増加し，また
As kernel
これら反復法では繰り返しカーネルを用いた積分行うため，カーネルの計算が非常にコスト高となる．
カーネル
我々は新しい

誤解を用いないように断っておくが，本手法はMPS法でもSPH法でもなく，新しい粒子法である．
To stress our notification, our method is NOT MPS nor SPH, is a new particle-based method.

## 理論



## アルゴリズム

粒子法におけるNavier-Stokes方程式は以下の式であらわされる．
In particle-based methods, Navie-stokes equation is described as follows.

ここで第１項は圧力勾配を表す，第２項は粘性を表す．第３項は重力を含む外力である．
First term describes pressure gradient,

グラディエントは積分計算を実行するために，MPS法でもSPH法でも近傍粒子の配置から積分を実行する．この積分が計算量の増加につながっている．

本手法では積分をすべて微小粒子の足し算に置き換える．
本手法ではマクロ粒子とミクロ粒子を導入する

すべての粒子を積分する側と積分される側と一緒にしては計算コストが莫大になる．

### 密度の計算
To calculate density estimation, the number of neighboring particles can be 

### 圧力項の計算

Pressure can be calculated differences 
ミクロ粒子の重心位置と，マクロ粒子の位置との間の差をとれば圧力項

カウントされる粒子数が増えるため，
マクロ粒子同士が近づけば近づくほど


### 粘性項の計算
本手法では，ミクロ粒子の平均速度と，マクロ粒子の速度との差で粘性力を実現する．

カウントされる粒子数が増えるため，
マクロ粒子同士が近づけば近づくほど

### BoundaryHandling
BoundaryHandlingは以下の通り

### 非圧縮性の実現

## 実装

すべての結果はCPUで実装している
疑似コードを表1.1にしめす．

## 実験結果

レンダリングはAnisotorophicKernelを用いてMarchingCubesをかけた．
VDB形式で出力してBlenderを用いてレンダリングした．

### DamBreakシナリオ


### 

### リアルタイム

## 比較

### 精度
本手法は新しいアルゴリズムであるが，一つの最先端アルゴリズムであるDFSPHと比較する．

### 計算速度
計算速度の内訳を表X.Xに示す．

近傍探索が最も計算コストがかかっている．
dtあたりの計算速度は最も速い．


## 終わりに
本文書ではカーネル不要の新しい粒子法を述べた．
本手法は全く新しい粒子法であり，BoundaryHandlingなど，さらなる改良の余地がある．