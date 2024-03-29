#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    float4 colortex0 = tex0.Sample(smp, input.uv);
    float4 colortex1 = tex1.Sample(smp, input.uv);
    float4 color = colortex0;

    if (fmod(input.uv.y, 0.1f) < 0.05f)
    {
        color = colortex1;
    }

    return float4(color.rgb, 1);
}


//// UV指定したピクセルの色をサンプリング
//float4 texcolor = tex.Sample(smp, input.uv);
//return float4(texcolor.rgb, 1);

// 明度変更(RGBの数値を2倍にして出力)
// float4 texcolor = tex.Sample(smp, input.uv);
// return float4(texcolor.rgb * 2.0f, 1);

// 色反転(最大値から現在値を減算して出力)
// float4 texcolor = tex.Sample(smp, input.uv);
// return float4(1.0f - texcolor.rgb, 1);

// UVずらし(0.0f～1.0fの間)
// float4 texcolor = tex.Sample(smp, input.uv + float2(0.5f,0.0f));
// アルファに1を入れて出力
// return float4(texcolor.rgb, 1);

//// 平均ぼかし
//// テクスチャのサイズを指定
//int uWidth = 512;  // テクスチャの幅
//int vHeight = 512; // テクスチャの高さ
//// サンプリング範囲の設定
//float2 texelSize = float2(1.0 / uWidth, 1.0 / vHeight);
//// カーネルサイズ
//int kernelSize = 3;
//// ピクセルの初期値を設定
//float3 color = float3(0, 0, 0);
//// サンプリング範囲内のピクセルを合計
//for (int x = -kernelSize; x <= kernelSize; x++)
//{
//    for (int y = -kernelSize; y <= kernelSize; y++)
//    {
//        float2 offset = float2(x, y) * texelSize;
//        color += tex.Sample(smp, input.uv + offset).rgb;
//    }
//}
//// ピクセル数で割って平均化
//color /= (kernelSize * 2 + 1) * (kernelSize * 2 + 1);
//return float4(color, 1);