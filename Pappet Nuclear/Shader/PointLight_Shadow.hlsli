////スキニングメッシュでのポイントライトを使った影
////頂点シェーダの入力
//struct VS_INPUT
//{
//	float4 Position          : POSITION ;               //座標(ローカル座標)
//	int4 BlendIndices0       : BLENDINDICES0 ;          //スキニング処理用 Float型定数配列インデックス
//	float4 BlendWeight0      : BLENDWEIGHT0 ;           //スキニング処理用ウエイト値
//	float3 Normal            : NORMAL0 ;                //法線(ローカル座標)
//	float4 Diffuse           : COLOR0 ;                 //ディフューズカラー
//	float4 Specular          : COLOR1 ;                 //スペキュラカラー
//	float4 TexCoords0        : TEXCOORD0 ;              //テクスチャ座標
//};
//
////頂点シェーダの出力
//struct VS_OUTPUT
//{
//	float4 Position          : POSITION ;               //座標(射影空間)
//	float4 Diffuse           : COLOR0 ;                 //ディフューズカラー
//	float4 Specular          : COLOR1 ;                 //スペキュラカラー
//	float2 TexCoords0        : TEXCOORD0 ;              //テクスチャ座標
//	float4 DPPosition0       : TEXCOORD1 ;              //深度バッファ0レンダリング時の座標(射影空間)
//	float4 DPPosition1       : TEXCOORD2 ;              //深度バッファ1レンダリング時の座標(射影空間)
//	float4 DPPosition2       : TEXCOORD3 ;              //深度バッファ2レンダリング時の座標(射影空間)
//	float4 DPPosition3       : TEXCOORD4 ;              //深度バッファ3レンダリング時の座標(射影空間)
//	float4 DPPosition4       : TEXCOORD5 ;              //深度バッファ4レンダリング時の座標(射影空間)
//	float4 DPPosition5       : TEXCOORD6 ;              //深度バッファ5レンダリング時の座標(射影空間)
//};
//
////マテリアルパラメータ
//struct VS_CONST_MATERIAL
//{
//	float4 Diffuse ;                                    //マテリアルディフューズカラー
//	float4 Specular ;                                   //マテリアルスペキュラカラー
//	float4 Power ;                                      //マテリアルスペキュラハイライトの強さ
//};
//
////ライトパラメータ
//struct VS_CONST_LIGHT
//{
//	float4 Position ;                                   //座標(ビュー空間)
//	float3 Direction ;                                  //方向(ビュー空間)
//	float4 Diffuse ;                                    //ディフューズカラー
//	float4 Specular ;                                   //スペキュラカラー
//	float4 Ambient ;                                    //アンビエントカラーとマテリアルのアンビエントカラーを乗算したもの
//	float4 Range_FallOff_ATO_AT1 ;                      //x:有効距離 y:スポットライト用FallOff z:距離による減衰処理用パラメータ0 w:距離による減衰処理用パラメータ1
//	float4 AT2_SpotP0_SpotP1 ;                          //x:距離による減衰処理用パラメータ2 y:スポットライト用パラメータ0(cos(Phi / 2.0f)) z:スポットライト用パラメータ1(1.0f / (cos(Theta / 2.0f) - cos(Phi / 2.0f)))
//};
//
////C++側で設定する定数の定義
//float4             cfAmbient_Emissive       : register(c1) ;                //マテリアルエミッシブカラー + マテリアルアンビエントカラー * グローバルアンビエントカラー
//float4             cfProjectionMatrix[4]    : register(c2) ;                //ビュー   　→　　射影空間
//float4             cfViewMatrix[3]          : register(c6) ;                //ワールド 　→　　ビュー行列
//float4             cfLocalWorldMatrix[162]  : register(c94) ;               //ローカル　 →    ワールド行列
//VS_CONST_MATERIAL  cfMaterial               : register(c11) ;               //マテリアルパラメータ
//VS_CONST_LIGHT     cfLight                  : register(c14) ;               //有効ライト０番のパラメータ
//
//matrix             cfDepthViewMatrix0       : register(c43) ;               //深度バッファ0のレンダリング時のワールド    →　　ビュー行列
//matrix             cfDepthProjectionMatrix0 : register(c47) ;               //深度バッファ0のレンダリング時のビュー　　　→　　射影行列
//matrix             cfDepthViewMatrix1       : register(c51) ;               //深度バッファ1のレンダリング時のワールド　　→　　ビュー行列
//matrix             cfDepthProjectionMatrix1 : register(c55) ;               //深度バッファ1のレンダリング時のビュー　　　→　　射影行列
//matrix             cfDepthViewMatrix2       : register(c59) ;               //深度バッファ2のレンダリング時のワールド　　→　　ビュー行列
//matrix             cfDepthProjectionMatrix2 : register(c63) ;               //深度バッファ2のレンダリング時のビュー　　　→　　射影行列
//matrix             cfDepthViewMatrix3       : register(c67) ;               //深度バッファ3のレンダリング時のワールド　　→　　ビュー行列
//matrix             cfDepthProjectionMatrix3 : register(c71) ;               //深度バッファ3のレンダリング時のビュー　　　→　　射影行列
//matrix             cfDepthViewMatrix4       : register(c75) ;               //深度バッファ4のレンダリング時のワールド　　→　　ビュー行列
//matrix             cfDepthProjectionMatrix4 : register(c79) ;               //深度バッファ4のレンダリング時のビュー　　　→　　射影行列
//matrix             cfDepthViewMatrix5       : register(c83) ;               //深度バッファ5のレンダリング時のワールド　　→　　ビュー行列
//matrix             cfDepthProjectionMatrix5 : register(c87) ;               //深度バッファ5のレンダリング時のビュー　　　→　　射影行列
//
////main関数
//VS_OUTPUT main(VS_INPUT VSInput)
//{
//	VS_OUTPUT VSOutput;
//	float4 lWorldPosition;
//	float4 lViewPosition;
//	float4 lDViewPsosition;
//	float3 lWorld
//}